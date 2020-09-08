//
//  main.cpp
//  EcommerceProject1
//
//  Created by Ayaan Faraz on 2/5/19.
//  Copyright © 2019 Ayaan Faraz. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAX_ITEMS = 145; // constant int variable to define the max amount of rows in array
const int MAX_COL = 4; // constant int variable to define maximum columns in array

bool readData(string, double[][MAX_COL]); // Method prototype for read data to read data in from csv file
int linearSearch(int& , double[][MAX_COL], int, double); // Method prototype for linear search
bool checkQuantity(double, double[][MAX_COL], int, double[][MAX_COL] ); // Method prototype to validate quant.
void getUserInfo(string&,string&,string&); //Method prototype for user info method to get user info
void generateReport(string, string, string,double[][MAX_COL] ); // Method prototype for report outputs results

int main()
{
    double databaseArray[MAX_ITEMS][MAX_COL]; // 2d array initialized to store the csv file data
    double shoppingCart [MAX_ITEMS][MAX_COL]; // user item shoppping cart array to store items
    int itemsInCart = 0; // int variable to keep track of how many items added to array
    int position = 0; // int variable to store index of an object if found
    string name, address, cityStateZipcode; // string variables to get user info

    if(readData("ProductData.csv", databaseArray)) // If array is successfully populated from file
    {

        while(itemsInCart<=145) // While user does not have 145 items checked out prompt for more
        {
            double productNum; // create new product variable to store product id from array

            cout << endl << "Please enter the item number of a product you would like to buy: ";
            cin >> productNum;

            if(productNum == 0)
            {
                getUserInfo(name, address, cityStateZipcode);
                generateReport(name, address, cityStateZipcode, shoppingCart);
            }

            if(linearSearch(position, databaseArray, MAX_ITEMS, productNum)!=-1)
            {
                if(position<=8)
                    cout << "Product Name: 00" << databaseArray[position][1] << " Cost: " <<
                         fixed << setprecision(2) << databaseArray[position][2] << endl;

                if(position>8&&position<99)
                    cout << "Product Name: 0" << databaseArray[position][1] << " Cost: " <<
                         fixed << setprecision(2) << databaseArray[position][2] << endl;;

                if(position>99)
                    cout << "Product Name: " << databaseArray[position][1] << " Cost: " <<
                         fixed << setprecision(2) << databaseArray[position][2] << endl;;

                double desiredQuantity;
                cout << "Enter the desired quantity for Product Number " << setprecision(0) << productNum <<": ";
                cin >> desiredQuantity;

                if(checkQuantity(desiredQuantity, databaseArray, position, shoppingCart))
                {

                }


            }

        }


    }

    return 0;
}

bool readData (string filename, double array[MAX_ITEMS][MAX_COL] )
{
    double productID;
    double productCost;
    double productQuantity;

    ifstream file; // declare input stream object
    file.open(filename); // open file for processing

    if(file)
    {
        file.seekg(25L,ios::beg); // skip headings in file

        for(int i=0; i<MAX_ITEMS; i++) //loop through the 145 lines in file
        {
            file.seekg(2L,ios::cur); // move pointer 2 places to productID and read in following double
            file >> productID;
            //cout << productID << " ";
            array[i][0] = productID;

            array[i][1] = i+1; // Product Name Redundant so directly add current iteration value as product Name

            file.seekg(13L,ios::cur); // move pointer 3 places to productID and read in following double of productCose
            file >> productCost;
            //  cout << productCost << " ";
            array[i][2] = productCost;

            file.seekg(1L,ios::cur); // move pointer 3 places to productQuantity and read in following double of productQuantity
            file >> productQuantity;
            //  cout << productQuantity << endl;
            array[i][3] = productQuantity;

        } // end of file processing

        file.close();
        return true;

    }

    cout << "File couldnt be opened" << endl;
    return false;

}

int linearSearch(int& position, double array[MAX_ITEMS][MAX_COL], int size, double value )
{

    for (int i = 0; i< size; i++)
    {
        if(array[i][0] == value)
        {
            position = i;
            return position;
        }
    }
    return -1;
}

bool checkQuantity(double desired, double array[MAX_ITEMS][MAX_COL], int position, double shoppingCart[MAX_ITEMS][MAX_COL] )
{
    int available = array[position][3];


    if(desired > available && available!= 0 )
    {
        cout << "The quantity " << desired << " is not available" << endl << "There is only " <<
             available << " of this product available" << endl << "Please re-enter a valid quantity: " << endl;

        double newQuantity;
        cin >> newQuantity;

        checkQuantity(newQuantity, array, position, shoppingCart);

    } // end of if

    if(desired <= available)
    {
        shoppingCart[position][0] = array[position][0];
        shoppingCart[position][1] = array[position][1];
        shoppingCart[position][2] = array[position][2];
        shoppingCart[position][3] = array[position][3];

        cout << "The item has been added to cart" << endl;
        return true;
    } // end of if

    if(available == 0)
    {
        cout << "This item is out of stock " << endl;
        return false;
    } // end of if

    return false;
}

void getUserInfo(string& name, string& address, string& citStaZip)
{
    cin.ignore();
    cout << "Please enter your Name: ";
    getline(cin,name);
    cout << endl;

    cout << "Please enter your Street Address: ";
    getline(cin,address);
    cout << endl;

    cout << "Please enter your City State and Zipcode: ";
    getline(cin,citStaZip);
    cout << endl;
}

void generateReport(string name, string address, string csZ, double shoppingCart[MAX_ITEMS][MAX_COL])
{
    ofstream outputFile;
    outputFile.open("results.txt");

    double grandTotal = 0;
    double total = 0;

    cout << left << "Customer Name: " << name << endl;
    outputFile << left << "Customer Name: " << name << endl;
    cout << left << "Customer Address: " << address << endl;
    outputFile<< left << "Customer Address: " << address << endl;
    cout << "                  "<<right  << csZ << endl << endl;
    outputFile <<"                  "<< right << setw(18) << csZ << endl << endl;

    cout << "Item Number" << setw(20) << "Item Name" << setw(15) << "Qty" << setw(20) << "Unit Cost" << setw(20) << "Total" << endl;
    cout <<"--------------------------------------------------------------------------------------------" << "\n"<< endl;

    outputFile << "Item Number" << setw(20) << "Item Name" << setw(15) << "Qty" << setw(20) << "Unit Cost" << setw(20) << "Total" << endl;
    outputFile<<"\n"<<"--------------------------------------------------------------------------------------------" << endl;

    for(int i = 0; i<MAX_ITEMS ; i++)
    {
        if(shoppingCart[i][0]>1000)
        {
            cout <<setprecision(0)<<shoppingCart[i][0] << setw(20);
            outputFile <<setprecision(0)<<shoppingCart[i][0] << setw(20);

            if(i<=8)
            {
                cout << "00" << setprecision(0)<<shoppingCart[i][1];
                outputFile << "00" <<setprecision(0)<< shoppingCart[i][1];

            }


            if(i>8&&i<99)
            {
                cout << "0" <<setprecision(0)<< shoppingCart[i][1];
                outputFile<< "0" <<setprecision(0)<< shoppingCart[i][1];
            }


            if(i>99)
            {
                cout <<setprecision(0)<< shoppingCart[i][1];
                outputFile <<setprecision(0)<< shoppingCart[i][1];
            }


            cout << setw(20) << setprecision(0)<< shoppingCart[i][3] << setprecision(2)<< setw(20)<< shoppingCart[i][2] << setw(20);

            outputFile << setw(20) << setprecision(0)<< shoppingCart[i][3] << setprecision(2)<< setw(20)<< shoppingCart[i][2] << setw(20);

            total+= (shoppingCart[i][2]*shoppingCart[i][3]);

            cout << total << endl << endl;

            outputFile << total << endl << endl;

            grandTotal+=total;
        }
    }
    cout <<"--------------------------------------------------------------------------------------------" << endl;
    outputFile<<"--------------------------------------------------------------------------------------------" << endl;
    cout<< right <<setw(80)<< "Total: $" << fixed << setprecision(2) << grandTotal << endl;
    outputFile << right <<setw(80)<< "Total: $" << fixed << setprecision(2) << grandTotal << endl;

    exit(EXIT_SUCCESS);

}
