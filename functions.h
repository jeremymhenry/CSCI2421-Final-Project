/*
 
 Jeremy Henry
 CSCI 2421
 Last Modified: 4/26/17
 
 Desc:  Develop a simple database system. The database is to handle 
        multiple records, each composed of several fields. The database
        will store its information to a file, addition and deletion of 
        records, field modifications, and it will allow users to 
        sort records based on the selected keys, and produce reports
        according to predefined criteria.
 
 Status: Compiles on Xcode and the csegrid.
 
 
 */

#ifndef functions_h
#define functions_h

#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include "Contacts.h"
#include "BSTree.h"
#include "Menu.h"

using namespace std;

//Prototypes
void readFromFile(BSTree*&, string);                                        //read data from file
void displayRecords(BSTree*&);                                              //display database
Node* search(BSTree *tree);                                                 //return searched record(s)
BSTree* exactSearch(Node* node, int option, string data, BSTree* tree);    //perform exact search
BSTree* containsSearch(Node*, string, BSTree*&);                            //perform contains search
BSTree* modifyRecord(BSTree*&);                                             //edit record(s)
BSTree* sortRecords(BSTree*&, int);                                         //sort records
BSTree* deleteRecord(BSTree*&);                                             //delete record(s)
void save(Node* node, BSTree* &tree, string);                               //save to existing file or new file
void saveAs(ostream& out, Node* node);                                      //writes records to file
vector<Contacts> BSTreeVector(Node*, vector<Contacts>&);                    //transfer bstree to vector
BSTree* sortedTree(int, vector<Contacts>&);                                 //transfer vector to bstree


//****************************************************************************************************
//                                      READ FROM FILE
//
//                          DESC:       Starts program by reading in file typed
//                                      in by the user.
//                          RETURNS:    Current database with new records
//****************************************************************************************************
void readFromFile(BSTree* &tree, string file)
{
    //holds fields of the contact database
    string contactData;
    char choice;
    
    //open file
    ifstream inFile;
    inFile.open(file);
    
    //close program if file not of correct type
    if (inFile.fail())
    {
        cout << "Error. Could not open the file" << endl;
        exit(1);
    }
    else
    {
        cout << "Reading in file..." << endl << endl;
        //go to until end of the file
        while (getline(inFile, contactData))
        {
            //instantiate Contacts object contact;
            Contacts contact;

            //Read in records fields until the end of the file
            contact.setUserID(contactData);
            
            inFile >> contactData;
            contact.setFirstName(contactData);
            
            inFile >> contactData;
            contact.setMiddle(contactData);
            
            inFile >> contactData;
            contact.setLastName(contactData);
            
            inFile.ignore();
            getline(inFile, contactData);
            contact.setCompany(contactData);
            
            getline(inFile, contactData);
            contact.setHomePhone(contactData);
            
            getline(inFile, contactData);
            contact.setOfficePhone(contactData);
            
            inFile >> contactData;
            contact.setEmail(contactData);
            
            inFile.ignore();
            getline(inFile, contactData);
            contact.setMobilePhone(contactData);
            
            getline(inFile, contactData);
            contact.setAddress(contactData);
            
            getline(inFile, contactData);
            contact.setCity(contactData);
            
            getline(inFile, contactData);
            contact.setState(contactData);
            
            getline(inFile, contactData);
            contact.setZip(contactData);
            
            getline(inFile, contactData);
            contact.setCountry(contactData);
            
            //read in affiliate records
            string affData;
            Affiliates affiliate;
            while (affData != "|")
            {
                //break out of loop if no more affiliate data
                if (!getline(inFile, affData))
                    break;
                else if (affData != "|")
                {
                    //stream affData
                    stringstream ss(affData);

                    //read in affiliate data and skip commas
                    getline(ss, affData, ','); 
                    affiliate.setName(affData);
                    
                    getline(ss, affData, ',');
                    affiliate.setPhone(affData);
                    
                    //read in affiliate email and skip semicolon
                    getline(ss, affData, ';');
                    affiliate.setEmail(affData);
                    
                    //push affiliate object to Affiliate vector
                    contact.addAffiliate(affiliate);
                }
                
            }
            //add database to BSTree
            tree->addNode(contact.getUserID(), contact);
        }
        
    }
    //display status message to user
    cout << "File read successfully!" << endl << endl;
    
    //close the file
    inFile.close();
    
    //ask user if they would like the tree to be displayed to console
    cout << "Display updated tree? (Y/N): ";
    cin >> choice;
    
    //char input validator
    while (!isalpha(choice))
    {
        cout << "Invalid selection! Please try again" << endl;
        cin >> choice;
        cin.clear();
        cin.ignore(256, '\n');
    }
    
    if (choice == 'y' || choice == 'Y')
    {
        //display sorted records
        displayRecords(tree);
    }
    
    
}




//****************************************************************************************************
//                                          DISPLAY RECORDS
//
//                          DESC:       Displays records, whether read in or added
//                          RETURNS:    Current database
//****************************************************************************************************
void displayRecords(BSTree* &tree)
{
    //check if database is empty
    if (tree->Root() == nullptr)
        cout << "No records to display!" << endl << endl;
    else
        //display records in order by Unique ID
        tree->printInorder(tree->Root());
  
}




//****************************************************************************************************
//                                          INSERT RECORD
//
//                          DESC:       Allows user to add records to database
//                                      User determines all fields of the new record
//                          RETURNS:    Updated tree with new record inserted
//****************************************************************************************************

void addRecord(BSTree* tree)
{
    Contacts _contact;  //object _contact of type Contacts
    Affiliates aff;
    string uniqueID, fName, mName, lName;   //holds contact database fields
    string hPhone, oPhone, email, company;
    string mPhone, address, city, state, zip, country;
    string aName, aEmail, aPhone;           //holds affiliate database fields
    
    string affName, affPhone, affEmail;
    
    char choice = '\0';
    
    cout << "We will proceed to insert a new record into the database!" << endl << endl;
    
    do
    {
        //prompts user to enter all new fields to be
        //added to database
        cout << "Enter a unique, 9-digit ID: " << endl;
        cin >> uniqueID;
        //input validator
        while (uniqueID.size() > 9 || uniqueID.size() < 9)
        {
                cout << "Please input a valid ID" << endl;
                cin >> uniqueID;
        }
        _contact.setUserID(uniqueID);
        
        //first name
        cin.ignore();
        cout << "Enter a first name: ";
        getline(cin, fName);
        while (fName.size() > 20)
        {
            cout << "Please input a valid first name" << endl;
            cin >> fName;
        }
        //set first name to fName
        _contact.setFirstName(fName);
        
        //middle name
        cout << "Enter a middle name or initial: ";
        cin >> mName;
        while (mName.size() > 20)
        {
            cout << "Please input a valid middle name" << endl;
            cin >> mName;
        }
        //set middle name to mName
        _contact.setMiddle(mName);
        
        //last name
        cout << "Enter a last name: ";
        cin >> lName;
        while (lName.size() > 20)
        {
            cout << "Please input a valid last  name" << endl;
            cin >> lName;
        }
        //set last name to lName
        _contact.setLastName(lName);
        
        //company name
        cin.ignore();
        cout << "Enter the company name: ";
        getline(cin, company);
        while (company.size() > 50)
        {
            cout << "Please input a valid company name" << endl;
            cin >> company;
        }
        //set company name to company
        _contact.setCompany(company);
        
        //home phone
        cout << "Enter a home phone number --> (xxx)xxx-xxxx: " << endl;
        getline(cin, hPhone);
        while (hPhone.size() > 15)
        {
            cout << "Please input a valid home phone number" << endl;
            cin >> hPhone;
        }
        //set home phone to hPhone
        _contact.setHomePhone(hPhone);
        
        //office phone
        cout << "Enter an office phone number -->(xxx)xxx-xxxx: "  << endl;
        getline(cin, oPhone);
        while (oPhone.size() > 20)
        {
            cout << "Please input a valid office phone number" << endl;
            cin >> oPhone;
        }
        //set office phone to oPhone
        _contact.setOfficePhone(oPhone);
        
        //email
        cout << "Enter an email address --> somename@someaddress.com: " << endl;
        cin >> email;
        while (email.size() > 30)
        {
            cout << "Please input a valid email" << endl;
            cin >> email;
        }
        _contact.setEmail(email);
        
        //mobile phone
        cin.ignore();
        cout << "Enter a mobile phone number -->(xxx)xxx-xxxx: " << endl;
        getline(cin, mPhone);
        while (mPhone.size() > 15)
        {
            cout << "Please input a valid mobile phone number" << endl;
            cin >> mPhone;
        }
        //set mobile phone to mPhone
        _contact.setMobilePhone(mPhone);
        
        //street address
        cout << "Enter a street address: ";
        getline(cin, address);
        while (address.size() > 50)
        {
            cout << "Please input a valid street address" << endl;
            cin >> address;
        }
        //set new address to address
        _contact.setAddress(address);
        
        //city
        cout << "Enter a city: ";
        getline(cin, city);
        while (city.size() > 50)
        {
            cout << "Please input a valid city" << endl;
            cin >> city;
        }
        //set new city to city
        _contact.setCity(city);
        
        //state
        cout << "Enter a state --> ex. Colorado = CO: ";
        cin >> state;
        while (state.size() > 3)
        {
            cout << "Please input a valid state" << endl;
            cin >> state;
        }
        //set new state to state
        _contact.setState(state);
        
        //zip code
        cout << "Enter a zip code: ";
        cin >> zip;
        while (zip.size() > 11)
        {
            cout << "Please input a valid zip code" << endl;
            cin >> zip;
        }
        //set new zip code to zip
        _contact.setZip(zip);
        
        //country
        cin.ignore();
        cout << "Enter a country: ";
        getline(cin, country);
        while (country.size() > 30)
        {
            cout << "Please input a valid country" << endl;
            cin >> country;
        }
        //set new country to country
        _contact.setCountry(country);
        cout << endl << endl;
        
        //ask user if they would like to add any affiliates
        cout << "Would you like to add any associated affiliates? (Y/N)" << endl;
        cin >> choice;
        
        //int input validator
        while (!isalpha(choice))
        {
            cout << "Invalid selection! Please try again" << endl;
            cin >> choice;
            cin.clear();
            cin.ignore(256, '\n');
        }
        
        //Add affiliates
        if (choice == 'y' || choice == 'Y')
        {
            do
            {
                //input affiliate name
                cout << "Enter affiliate name: ";
                cin.ignore();
                getline(cin, affName);
                while (affName.size() > 20)
                {
                    cout << "Please input a valid affiliate name" << endl;
                    cin >> affName;
                }
                aff.setName(affName);
                
                //input affiliate phone number
                cout << "Enter affiliate phone number: ";
                getline(cin, affPhone);
                while (affPhone.size() > 15)
                {
                    cout << "Please input a valid affiliate phone number" << endl;
                    cin >> affPhone;
                }
                aff.setPhone(affPhone);
                
                //input affiliate email address
                cout << "Enter affiliate email: ";
                getline(cin, affEmail);
                while (affEmail.size() > 30)
                {
                    cout << "Please input a valid affiliate email" << endl;
                    cin >> affEmail;
                }
                aff.setEmail(affEmail);
                
                //add affiliates to contact records
                _contact.addAffiliate(aff);
                
                //display message asking user if they would like to add another affiliate
                cout << "Add another affiliate? (Y/N): ";
                cin >> choice;
                //int input validaot
                while (!isalpha(choice))
                {
                    cout << "Invalid selection! Please try again" << endl;
                    cin >> choice;
                    cin.clear();
                    cin.ignore(256, '\n');
                }
                
                
            } while (choice != 'n' && choice != 'N');   //continue adding affiliates unless user chooses selection 2
            
            //add record to database
            tree->addNode(_contact.getUserID(), _contact);
            _contact.clearAffiliate(aff);
        }
        //user does not want to add affiliates; just add contact to database
        else if (choice == 'n' || choice == 'N')
        {
            //add contact record to database
            tree->addNode(_contact.getUserID(), _contact);
        }
        
        cout << "Display updated tree? (Y/N): ";
        cin >> choice;
        
        //char input validator
        while (!isalpha(choice))
        {
            cout << "Invalid selection! Please try again" << endl;
            cin >> choice;
            cin.clear();
            cin.ignore(256, '\n');
        }
        
        if (choice == 'y' || choice == 'Y')
        {
            //display sorted records
            displayRecords(tree);
        }
        
        //display message asking user if they would like to add another contact record
        cout << "Add another record to the database? (Y/N): ";
        cin >> choice;
        
        //char input validator
        while (!isalpha(choice))
        {
            cout << "Invalid selection! Please try again" << endl;
            cin >> choice;
            cin.clear();
            cin.ignore(256, '\n');
        }
        
        
    } while (choice != 'n' && choice != 'N');
    
}




//****************************************************************************************************
//                                          SEARCH RECORDS
//
//                          DESC:       Allows user to search records by multiple modes,
//                                      (exact & contains) and by multiple fields
//                          RETURNS:    Current tree
//****************************************************************************************************
Node* search(BSTree *tree)
{
    //holds user selections
    int option;
    char choice;
    
    //create new Node object node
    Node *node = new Node;
    
    //check if tree is empty
    //if empty, display appropriate message to user
    if (tree->Root() == nullptr)
        cout << "Invalid operation! Database is empty" << endl << endl;
    else
    {
        do
        {
            //Search type menu
            cout << "Select a search option" << endl;
            cout << "1. Exact Search" << endl;
            cout << "2. Contains Search" << endl;
            cout << "3. Exit" << endl << endl;
            cout << "Selection: ";
            cin >> option;
            
            //int input validator
            while (option < 1 || option > 3 || isdigit(option))
            {
                cout << "Invalid selection! Please try again" << endl;
                cin >> option;
                cin.clear();
                cin.ignore(256, '\n');
            }
            
            //Exact Search
            if (option == 1)
            {
                do
                {
                    //create new temporary BSTree object tempTree
                    BSTree *tempTree = new BSTree;
                    
                    //Field search menu
                    cout << "\tPlease select a field to search for:" << endl;
                    cout << "1. ID" << endl;
                    cout << "2. First name" << endl;
                    cout << "3. Middle" << endl;
                    cout << "4. Last name" << endl;
                    cout << "5. Company name" << endl;
                    cout << "6. Home phone" << endl;
                    cout << "7. Office phone" << endl;
                    cout << "8. Email" << endl;
                    cout << "9. Mobile phone" << endl;
                    cout << "10. Street address" << endl;
                    cout << "11. City" << endl;
                    cout << "12. State" << endl;
                    cout << "13. Zip code" << endl;
                    cout << "14. Country" << endl;
                    cout << "15. Affiliate name" << endl;
                    cout << "16. Affiliate phone" << endl;
                    cout << "17. Affiliate email" << endl << endl;
                    cout << "Selection: ";
                    cin >> option;
                    //int input validator
                    while (option < 1 || option > 17 || isdigit(option))
                    {
                        cout << "Invalid selection! Please try again" << endl;
                        cin >> option;
                        cin.clear();
                        cin.ignore(256, '\n');
                    }
                    
                    //search for user id
                    if (option == 1)
                    {
                        string userID;  //holds user input for id
                        //user inputs user id to search for
                        cout << "Search user ID: ";
                        cin >> userID;
                        cout << endl;
                        //search for user id using findNode() function
                        //node will hold the record or nullptr
                        tempTree = exactSearch(tree->Root(), option, userID, tempTree);
                        
                        //display record and appropriate message if found
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        //record not found
                        else
                            cout << "Record not found" << endl << endl;
                    }
                    
                    //search for first name
                    else if (option == 2)
                    {
                        string fName;   //holds user input first name
                        cout << "Search first name: ";
                        cin >> fName;
                        cout << endl;
        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, fName, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        //record not found
                        else
                            cout << "Record(s) not found" << endl << endl;
                    }
                    
                    //search for middle name
                    else if (option == 3)
                    {
                        string mName;
                        cout << "Search middle name or initial: ";
                        cin >> mName;
                        cout << endl;
                        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, mName, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        //record not found
                        else
                            cout << "Record(s) not found" << endl << endl;
                    }
                    
                    //Last name
                    else if (option == 4)
                    {
                        cin.ignore();
                        string lName;
                        cout << "Search last name: ";
                        getline(cin, lName);
                        cout << endl;
                        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, lName, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        //record not found
                        else
                            cout << "Record(s) not found" << endl << endl;
                    }
                    
                    //Company
                    else if (option == 5)
                    {
                        cin.ignore();
                        string company;
                        cout << "Search company name: ";
                        getline(cin, company);
                        cout << endl;
                        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, company, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        //record not found
                        else
                            cout << "Record(s) not found" << endl << endl;
                    }
                    
                    //Home Phone
                    else if (option == 6)
                    {
                        cin.ignore();
                        string hPhone;
                        cout << "Search home phone #: ";
                        getline(cin, hPhone);
                        cout << endl;
                        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, hPhone, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        //record not found
                        else
                            cout << "Record(s) not found" << endl << endl;
                    }
                    
                    //Office Phone
                    else if (option == 7)
                    {
                        cin.ignore();
                        string oPhone;
                        cout << "Search office phone #: ";
                        getline(cin, oPhone);
                        cout << endl;
                        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, oPhone, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        //record not found
                        else
                            cout << "Record(s) not found" << endl << endl;
                    }
                    
                    //Email
                    else if (option == 8)
                    {
                        string email;
                        cout << "Search email address: ";
                        cin >> email;
                        cout << endl;
                        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, email, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        //record not found
                        else
                            cout << "Record(s) not found" << endl << endl;
                    }
                    
                    //Mobile
                    else if (option == 9)
                    {
                        string mPhone;
                        cout << "Search mobile phone #: ";
                        cin >> mPhone;
                        cout << endl;
                        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, mPhone, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        //record not found
                        else
                            cout << "Record(s) not found" << endl << endl;
                    }
                    
                    //Address
                    else if (option == 10)
                    {
                        cin.ignore();
                        string address;
                        cout << "Search street address: ";
                        getline(cin, address);
                        cout << endl;
                        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, address, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        else
                            cout << "Record(s) not found" << endl << endl;
                    }
                    
                    //City
                    else if (option == 11)
                    {
                        cin.ignore();
                        string city;
                        cout << "Search city: ";
                        getline(cin, city);
                        cout << endl;
                        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, city, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        else
                            cout << "Record(s) not found" << endl << endl;
                    }
                    
                    //State
                    else if (option == 12)
                    {
                        string state;
                        cout << "Search state: ";
                        cin >> state;
                        cout << endl;
                        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, state, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                            
                        }
                        else
                            cout << "Record(s) not found" << endl << endl;
                    }
                    
                    //Zip code
                    else if (option == 13)
                    {
                        string zip;
                        cout << "Search a zip code: ";
                        cin >> zip;
                        cout << endl;
                        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, zip, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        else
                            cout << "Record(s) not found" << endl << endl;
                    }
                    
                    //Country
                    else if (option == 14)
                    {
                        cin.ignore();
                        string country;
                        cout << "Search country: ";
                        getline(cin, country);
                        cout << endl;
                        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, country, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        else
                            cout << "Record(s) not found" << endl << endl;
                        
                    }
                    
                    //Affiliate name
                    else if (option == 15)
                    {
                        cin.ignore();
                        //holds affiliate name
                        string affName;
                        //ask user to search for affiliate name
                        cout << "Search affiliate name: ";
                        getline(cin, affName);
                        cout << endl;
                        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, affName, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        else
                            cout << "Record(s) not found" << endl << endl;
                    }
                    
                    //Affiliate phone number
                    else if (option == 16)
                    {
                        cin.ignore();
                        //holds affiliate phone number
                        string affPhone;
                        //ask user to search for affiliate name
                        cout << "Search affiliate phone #: ";
                        getline(cin, affPhone);
                        cout << endl;
                        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, affPhone, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        else
                            cout << "Record(s) not found" << endl << endl;
                    }
                    
                    //Affiliate email
                    else if (option == 17)
                    {
                        cin.ignore();
                        //holds affiliate email
                        string affEmail;
                        //ask user to search for affiliate name
                        cout << "Search affiliate email: ";
                        getline(cin, affEmail);
                        cout << endl;
                        
                        //call exactSearch() function
                        //assign temporary tree tempTree to exactSearch()
                        //tempTree will hold results
                        tempTree = exactSearch(tree->Root(), option, affEmail, tempTree);
                        
                        //if tree is not empty, display results
                        if (tempTree->Root() != nullptr)
                        {
                            cout << "Record(s) found!" << endl;
                            tempTree->printInorder(tempTree->Root());
                            cout << endl;
                        }
                        else
                            cout << "Record(s) not found" << endl << endl;
                    }
                    
                    
                    //Allow user to perform another search using a different field
                    cout << "Search using a different field? (Y/N)" << endl;
                    cin >> choice;
                    //char input validator
                    while (!isalpha(choice))
                    {
                        cout << "Invalid selection! Please try again" << endl;
                        cin >> choice;
                        cin.clear();
                        cin.ignore(256, '\n');
                    }
                    
                    if (choice == 'n' || choice == 'N')
                    {
                        node = tempTree->Root();
                    }
                    
                } while (choice != 'n' && choice != 'N');
            }
            //Contains Search
            else if (option == 2)
            {
                do
                {
                    //create new BSTree object temp
                    BSTree *temp = new BSTree;
                    //holds user contains search data
                    string containsData;
        
                    cin.ignore();
                    //asks user to type in what they're searching for
                    cout << "Search: ";
                    getline(cin, containsData);
                    cout << endl;
                    
                    //assing temp to the temporary binary search tree
                    //returned from containsSearch
                    temp = containsSearch(tree->Root(), containsData, temp);
                    
                    //if the tree is not empty, display the search results
                    //else, display appropriate message to user
                    if (temp->Root() != nullptr)
                    {
                        
                        cout << "Record(s) found!" << endl;
                        temp->printInorder(temp->Root());
                        cout << endl;
                    }
                    else
                        cout << "Record(s) not found" << endl << endl;
                    
                    //ask user if they would like to perform another
                    //contains search
                    cout << "Perform another 'contains' search? (Y/N)" << endl;
                    cin >> choice;
                    //char input validator
                    while (!isalpha(choice))
                    {
                        cout << "Invalid selection! Please try again" << endl;
                        cin >> choice;
                        cin.clear();
                        cin.ignore(256, '\n');
                    }
                    if (choice == 'n' || choice == 'N')
                    {
                        node = temp->Root();
                    }
                    
                } while (choice != 'n' && choice != 'N');
            }
            
        } while (option != 3);
     
        //returns record(s) user searched for or nullptr if not record found
        return node;
    }
    //returns record(s) user searched for or nullptr if not record found
    return node;
}





//****************************************************************************************************
//                                      EXACT SEARCH
//
//****************************************************************************************************
BSTree* exactSearch(Node* node, int option, string data, BSTree* tree)
{
    //CHANGE NODE->KEY() TO DATA?
    if (node != nullptr)
    {
        //user id
        if (option == 1)
        {
            //if user input search is equal to id in database,
            //add the node to the temporary tree
            if (node->getContacts().getUserID() == data)
                tree->addNode(node->Key(), node->getContacts());
        }
        //first name
        if (option == 2)
        {
            //if user input search is equal to first name in database,
            //add the node to the temporary tree
            if (node->getContacts().getFirstName() == data)
                tree->addNode(node->Key(), node->getContacts());
        }
        //middle name
        else if (option == 3)
        {
            //if user input search is equal to middle name in database,
            //add the node to the temporary tree
            if (node->getContacts().getMiddle() == data)
                tree->addNode(node->Key(), node->getContacts());
        }
        //last name
        else if (option == 4)
        {
            //if user input search is equal to last name in database,
            //add the node to the temporary tree
            if (node->getContacts().getLastName() == data)
                tree->addNode(node->Key(), node->getContacts());
        }
        //company
        else if (option == 5)
        {
            //if user input search is equal to company in database,
            //add the node to the temporary tree
            if (node->getContacts().getCompanyName() == data)
                tree->addNode(node->Key(), node->getContacts());
        }
        //home phone
        else if (option == 6)
        {
            //if user input search is equal to home phone in database,
            //add the node to the temporary tree
            if (node->getContacts().getHomePhone() == data)
                tree->addNode(node->Key(), node->getContacts());
        }
        //office phone
        else if (option == 7)
        {
            //if user input search is equal to office phone in database,
            //add the node to the temporary tree
            if (node->getContacts().getOfficePhone() == data)
                tree->addNode(node->Key(), node->getContacts());
        }
        //email
        else if (option == 8)
        {
            //if user input search is equal to email in database,
            //add the node to the temporary tree
            if (node->getContacts().getEmail() == data)
                tree->addNode(node->Key(), node->getContacts());
        }
        //mobile phone
        else if (option == 9)
        {
            //if user input search is equal to mobile phone in database,
            //add the node to the temporary tree
            if (node->getContacts().getMobilePhone() == data)
                tree->addNode(node->Key(), node->getContacts());
        }
        //street address
        else if (option == 10)
        {
            //if user input search is equal to address in database,
            //add the node to the temporary tree
            if (node->getContacts().getAddress() == data)
                tree->addNode(node->Key(), node->getContacts());
        }
        //city
        else if (option == 11)
        {
            //if user input search is equal to city in database,
            //add the node to the temporary tree
            if (node->getContacts().getCity() == data)
                tree->addNode(node->Key(), node->getContacts());
        }
        //state
        else if (option == 12)
        {
            //if user input search is equal to state in database,
            //add the node to the temporary tree
            if (node->getContacts().getState() == data)
                tree->addNode(node->Key(), node->getContacts());
        }
        //zip code
        else if (option == 13)
        {
            //if user input search is equal to zip code in database,
            //add the node to the temporary tree
            if (node->getContacts().getZipCode() == data)
                tree->addNode(node->Key(), node->getContacts());
        }
        //country
        else if (option == 14)
        {
            //if user input search is equal to country in database,
            //add the node to the temporary tree
            if (node->getContacts().getCountry() == data)
                tree->addNode(node->Key(), node->getContacts());
        }
        //affiliate name
        else if (option == 15)
        {
            //check if affiliate vector is empty
            if (!node->getContacts().getAffiliates().empty())
            {
                //if not empty, compare corresponding affiliates to data
                //if found, add to tree
                for (int i = 0; i < node->getContacts().getAffiliates().size(); i++)
                {
                    //getAffiliates()[i] == affVector[i]
                    if (node->getContacts().getAffiliates()[i].getName() == data)
                    {
                        tree->addNode(node->Key(), node->getContacts());
                    }
                }
            }
        }
        
        //affiliate phone number
        else if (option == 16)
        {
            //check if affiliate vector is empty
            if (!node->getContacts().getAffiliates().empty())
            {
                //if not empty, compare corresponding affiliates to data
                //if found, add to tree
                for (int i = 0; i < node->getContacts().getAffiliates().size(); i++)
                {
                    if (node->getContacts().getAffiliates()[i].getPhone() == data)
                    {
                        tree->addNode(node->Key(), node->getContacts());
                    }
                }
            }
        }
        
        //affiliate email
        else if (option == 17)
        {
            //check if affiliate vector is empty
            if (!node->getContacts().getAffiliates().empty())
            {
                //if not empty, compare corresponding affiliates to data
                //if found, add to tree
                for (int i = 0; i < node->getContacts().getAffiliates().size(); i++)
                {
                    if (node->getContacts().getAffiliates()[i].getEmail() == data)
                    {
                        tree->addNode(node->Key(), node->getContacts());
                    }
                }
            }
        }
        //Traverse entire tree
        exactSearch(node->Left(), option, data, tree);
        exactSearch(node->Right(), option, data, tree);
    }
    
    return tree;
}



//****************************************************************************************************
//                                      CONTAINS SEARCH
//
//****************************************************************************************************
BSTree* containsSearch(Node* node, string data, BSTree* &tree)
{
    string search;
    size_t found = 0;
    
    if (node != nullptr)
    {
        //User id
    
        //assign search to first record in database
        search = node->getContacts().getUserID();
        //assign found to results of search.find() function
        found = search.find(data);
        //if found doesn't reach end of the string, add to tree
        if (found != string::npos)
            tree->addNode(node->Key(), node->getContacts());
    
        //First name
        //assign search to first record in database
        search = node->getContacts().getFirstName();
        found = search.find(data);
        if (found != string::npos)
            tree->addNode(node->Key(), node->getContacts());
    
        //Middle
        //assign search to first record in database
        search = node->getContacts().getMiddle();
        found = search.find(data);
        if (found != string::npos)
            tree->addNode(node->Key(), node->getContacts());
    
        //Last name
        //assign search to first record in database
        search = node->getContacts().getLastName();
        found = search.find(data);
        if (found != string::npos)
            tree->addNode(node->Key(), node->getContacts());
    
        //Company name
        //assign search to first record in database
        search = node->getContacts().getCompanyName();
        found = search.find(data);
        if (found != string::npos)
            tree->addNode(node->Key(), node->getContacts());
    
        //Home phone
        //assign search to first record in database
        search = node->getContacts().getHomePhone();
        found = search.find(data);
        if (found != string::npos)
            tree->addNode(node->Key(), node->getContacts());
    
        //Office phone
        //assign search to first record in database
        search = node->getContacts().getOfficePhone();
        found = search.find(data);
        if (found != string::npos)
            tree->addNode(node->Key(), node->getContacts());
        
        //Email
        //assign search to first record in database
        search = node->getContacts().getEmail();
        found = search.find(data);
        if (found != string::npos)
            tree->addNode(node->Key(), node->getContacts());
    
        //Mobile phone
        //assign search to first record in database
        search = node->getContacts().getMobilePhone();
        found = search.find(data);
        if (found != string::npos)
            tree->addNode(node->Key(), node->getContacts());
    
        //Street address
        //assign search to first record in database
        search = node->getContacts().getAddress();
        found = search.find(data);
        if (found != string::npos)
            tree->addNode(node->Key(), node->getContacts());
    
        //City
        //assign search to first record in database
        search = node->getContacts().getCity();
        found = search.find(data);
        if (found != string::npos)
            tree->addNode(node->Key(), node->getContacts());
    
        //State
        //assign search to first record in database
        search = node->getContacts().getState();
        found = search.find(data);
        if (found != string::npos)
            tree->addNode(node->Key(), node->getContacts());
    
        //Zip code
        //assign search to first record in database
        search = node->getContacts().getZipCode();
        found = search.find(data);
        if (found != string::npos)
            tree->addNode(node->Key(), node->getContacts());
        
        //Country
        //assign search to first record in database
        search = node->getContacts().getCountry();
        found = search.find(data);
        if (found != string::npos)
            tree->addNode(node->Key(), node->getContacts());
        
        //Affiliate name
        if (!node->getContacts().getAffiliates().empty())
        {
            for (int i = 0; i < node->getContacts().getAffiliates().size(); i++)
            {
                //assign search to first affiliate in database
                search = node->getContacts().getAffiliates()[i].getName();
                found = search.find(data);
                if (found != string::npos)
                {
                    tree->addNode(node->Key(), node->getContacts());
                }
            }
        }
        
        //Affiliate phone
        if (!node->getContacts().getAffiliates().empty())
        {
            for (int i = 0; i < node->getContacts().getAffiliates().size(); i++)
            {
                search = node->getContacts().getAffiliates()[i].getPhone();
                found = search.find(data);
                if (found != string::npos)
                {
                    tree->addNode(node->Key(), node->getContacts());
                }
            }
        }
        
        //Affiliate email
        if (!node->getContacts().getAffiliates().empty())
        {
            for (int i = 0; i < node->getContacts().getAffiliates().size(); i++)
            {
                search = node->getContacts().getAffiliates()[i].getEmail();
                found = search.find(data);
                if (found != string::npos)
                {
                    tree->addNode(node->Key(), node->getContacts());
                }
            }
        }
        
        //recursively traverse entire tree
        containsSearch(node->Left(), data, tree);
        containsSearch(node->Right(), data, tree);
        
    }
    
    return tree;
}





//****************************************************************************************************
//                                      MODIFY RECORDS
//
//                            DESC:       User searches (exact or contain) for record
//                                        they would like to edit. If user saves changes,
//                                        updated record is added to database.
//                            RETURNS:    Updated tree with modified records.
//****************************************************************************************************
BSTree* modifyRecord(BSTree* &tree)
{
    //ask user to search for record to edit
    //call search records function
    string searchData;
    char selection;
    int option;
    Node *tempNode = new Node();
    Contacts contact;
    
    //check if database is empty
    if (tree->Root() == nullptr)
        cout << "Invalid operation! Database is empty" << endl;
    else
    {
        do
        {
            //holds user inputs
            string newData;
            cout << "Search for a record to modify? (Y/N)" << endl;
            cin >> selection;
            
            //char input validator
            while (!isalpha(selection))
            {
                cout << "Invalid selection! Please try again" << endl;
                cin >> selection;
                cin.clear();
                cin.ignore(256, '\n');
            }
            
            if (selection == 'y' || selection == 'Y')
            {
                //assign tempNode to record returned from search() function
                tempNode = search(tree);
            }
            
            //display search result and ask if user would like to delete record
            
            tree->printInorder(tempNode);
            
            cout << "Would you like to modify this record? (Y/N)" << endl;
            cin >> selection;
            searchData = tempNode->Key();       //assign searchData to tempNode key
            
            //char input validator
            while (!isalpha(selection))
            {
                cout << "Invalid selection! Please try again" << endl;
                cin >> selection;
                cin.clear();
                cin.ignore(256, '\n');
            }
            
            //user chooses to modify record
            if (selection == 'y' || selection == 'Y')
            {
                do
                {
                    cout << "\tSelect field to edit: " << endl << endl;
                    cout << "1. ID" << endl;
                    cout << "2. First name" << endl;
                    cout << "3. Middle" << endl;
                    cout << "4. Last name" << endl;
                    cout << "5. Company name" << endl;
                    cout << "6. Home phone" << endl;
                    cout << "7. Office phone" << endl;
                    cout << "8. Email" << endl;
                    cout << "9. Mobile phone" << endl;
                    cout << "10. Street address" << endl;
                    cout << "11. City" << endl;
                    cout << "12. State" << endl;
                    cout << "13. Zip code" << endl;
                    cout << "14. Country" << endl;
                    cout << "15. Affiliate name" << endl;
                    cout << "16. Affiliate phone" << endl;
                    cout << "17. Affiliate email" << endl << endl;
                    cout << "Selection: ";
                    cin >> option;   //user selection
                    //int input validator
                    while (option < 1 || option > 17 || isdigit(option))
                    {
                        cout << "Invalid selection! Please try again" << endl;
                        cin >> option;
                        cin.clear();
                        cin.ignore(256, '\n');
                    }
                    
                    //edit id
                    if (option == 1)
                    {
                        cout << "Enter the new user ID: ";
                        cin >> newData;
                        tempNode->getContacts().setUserID(newData);
                        tempNode->setKey(newData);
                    }
                    //edit first name
                    else if (option == 2)
                    {
                        cout << "Enter the new user first name: ";
                        cin >> newData;
                        tempNode->getContacts().setFirstName(newData);
                    }
                    //edit middle name
                    else if (option == 3)
                    {
                        cout << "Enter the new user middle name: ";
                        cin >> newData;
                        tempNode->getContacts().setMiddle(newData);
                    }
                    //edit last name

                    else if (option == 4)
                    {
                        cout << "Enter the new user last name: ";
                        cin >> newData;
                        tempNode->getContacts().setLastName(newData);
                    }
                    //company name
                    else if (option == 5)
                    {
                        cin.ignore();
                        cout << "Enter the new company name: ";
                        getline(cin, newData);
                        tempNode->getContacts().setCompany(newData);
                    }
                    //home phone
                    else if (option == 6)
                    {
                        cout << "Enter the new home phone #: ";
                        cin >> newData;
                        tempNode->getContacts().setHomePhone(newData);
                    }
                    //office phone
                    else if (option == 7)
                    {
                        cout << "Enter the new office phone #: ";
                        cin >> newData;
                        //set new office phone number to newData
                        tempNode->getContacts().setOfficePhone(newData);
                    }
                    //email
                    else if (option == 8)
                    {
                        cout << "Enter the new email address: ";
                        cin >> newData;
                        //set new email to newData
                        tempNode->getContacts().setEmail(newData);
                    }
                    //mobile phone
                    else if (option == 9)
                    {
                        cout << "Enter the new mobile phone #: ";
                        cin >> newData;
                        //set new mobile phone to newData
                        tempNode->getContacts().setMobilePhone(newData);
                    }
                    //street address
                    else if (option == 10)
                    {
                        cin.ignore();
                        cout << "Enter the new street address: ";
                        getline(cin, newData);
                        //set new street address to newData
                        tempNode->getContacts().setAddress(newData);
                    }
                    // city
                    else if (option == 11)
                    {
                        cin.ignore();
                        cout << "Enter the new city: ";
                        getline(cin, newData);
                        //set new city to newData
                        tempNode->getContacts().setCity(newData);
                    }
                    //state
                    else if (option == 12)
                    {
                        cout << "Enter the new state: ";
                        cin >> newData;
                        //sett new state to newData
                        tempNode->getContacts().setState(newData);
                    }
                    //zip code
                    else if (option == 13)
                    {
                        cout << "Enter the new zip code: ";
                        cin >> newData;
                        //set new zip code to newData;
                        tempNode->getContacts().setZip(newData);
                    }
                    //country
                    else if (option == 14)
                    {
                        cin.ignore();
                        cout << "Enter the new country: ";;
                        getline(cin, newData);
                        //set new country to newData
                        tempNode->getContacts().setCountry(newData);
                    }
                    
                    cout << endl;
                    // display edited contact info
                    tree->printInorder(tempNode);
                    cout << "Would you like to save your changes? (Y/N)" << endl;
                    cin >> selection;
                    //char input validator
                    while (!isalpha(selection))
                    {
                        cout << "Invalid selection! Please try again" << endl;
                        cin >> selection;
                        cin.clear();
                        cin.ignore(256, '\n');
                    }
                    
                    //user selects to save changes made
                    if (selection == 'y' || selection == 'Y')
                    {
                        //delete record from database
                        tree->deleteNode(searchData);
                        //add updated record to database
                        tree->addNode(tempNode->Key(), tempNode->getContacts());
                    }
                    
                    //ask user if they would like to modify a different field
                    cout << "Would you like to modify another field? (Y/N)" << endl;
                    cin >> selection;
                    //char input validator
                    while (!isalpha(selection))
                    {
                        cout << "Invalid selection! Please try again" << endl;
                        cin >> selection;
                        cin.clear();
                        cin.ignore(256, '\n');
                    }
                    
                } while (selection != 'n' && selection != 'N');
                    
            }
            
            cout << "Display updated tree? (Y/N)" << endl;
            cin >> selection;
            
            //char input validator
            while (!isalpha(selection))
            {
                cout << "Invalid selection! Please try again" << endl;
                cin >> selection;
                cin.clear();
                cin.ignore(256, '\n');
            }
            
            if (selection == 'y' || selection == 'Y')
            {
                //display sorted records
                displayRecords(tree);
            }
            
            //ask user if they would liek to modify a different record
            cout << "Modify another record? (Y/N)" << endl;
            cin >> selection;
            
            //char input validator
            while (!isalpha(selection))
            {
                cout << "Invalid selection! Please try again" << endl;
                cin >> selection;
                cin.clear();
                cin.ignore(256, '\n');
            }
            
        } while (selection != 'n' && selection != 'N');
            
    }
    
    return tree;
}









//****************************************************************************************************
//                                           SORT RECORDS
//                        DESC:     Sorts the database by user choice of field
//                        RETURNS:  Updated database
//****************************************************************************************************
BSTree* sortRecords(BSTree* &tree)
{
    vector<Contacts> contact;           //holds vector of Contacts contact
    BSTree *tempTree = new BSTree();    //create new BSTree object tempTree
    char choice;                        //holds user menu choice
    int option;
    
    //check if tree is empty
    if (tree->Root() == nullptr)
        cout << "Invalid operation! Database is empty" << endl << endl;
    else
    {
        do
        {
            //Sort menu
            cout << "\tHow would you like to sort the records?" << endl;
            cout << "1. User ID" << endl;
            cout << "2. First name" << endl;
            cout << "3. Middle" << endl;
            cout << "4. Last name" << endl;
            cout << "5. Company name" << endl;
            cout << "6. Home phone" << endl;
            cout << "7. Office phone" << endl;
            cout << "8. Email" << endl;
            cout << "9. Mobile phone" << endl;
            cout << "10. Street address" << endl;
            cout << "11. City" << endl;
            cout << "12. State" << endl;
            cout << "13. Country" << endl;
            cout << "14. Zip code" << endl << endl;
            cout << "Selection: ";
            cin >> option;   //user selection
            
            //int input validator
            while (option < 1 || option > 14 || isdigit(option))
            {
                cout << "Invalid selection! Please try again" << endl;
                cin >> option;
                cin.clear();
                cin.ignore(256, '\n');
            }
            
            //User ID
            if (option == 1)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contact = BSTreeVector(tree->Root(), contact);
                //call function sortedTree to transfer database in vector to tempTree
                tempTree = sortedTree(option, contact);
                cout << "Database now sorted by user ID!" << endl << endl;
            }
            
            //First name
            else if (option == 2)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contact = BSTreeVector(tree->Root(), contact);
                //call function sortedTree to transfer database in vector to tempTree
                tempTree = sortedTree(option, contact);
                cout << "Database now sorted by first name!" << endl << endl;
            }
            
            //Middle name
            else if (option == 3)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contact = BSTreeVector(tree->Root(), contact);
                //call function sortedTree to transfer database in vector to tempTree
                tempTree = sortedTree(option, contact);
                cout << "Database now sorted by middle name!" << endl << endl;
            }
            
            //Last name
            else if (option == 4)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contact = BSTreeVector(tree->Root(), contact);
                //call function sortedTree to transfer database in vector to tempTree
                tempTree = sortedTree(option, contact);
                cout << "Database now sorted by last name!" << endl << endl;
            }
            
            //Company name
            else if (option == 5)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contact = BSTreeVector(tree->Root(), contact);
                //call function sortedTree to transfer database in vector to tempTree
                tempTree = sortedTree(option, contact);
                cout << "Database now sorted by company name!" << endl << endl;
            }
            
            //Home phone #
            else if (option == 6)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contact = BSTreeVector(tree->Root(), contact);
                //call function sortedTree to transfer database in vector to tempTree
                tempTree = sortedTree(option, contact);
                cout << "Database now sorted by home phone #!" << endl << endl;
            }
            
            //Office phone #
            else if (option == 7)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contact = BSTreeVector(tree->Root(), contact);
                //call function sortedTree to transfer database in vector to tempTree
                tempTree = sortedTree(option, contact);
                cout << "Database now sorted by office phone #!" << endl << endl;
            }
            
            //Email
            else if (option == 8)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contact = BSTreeVector(tree->Root(), contact);
                //call function sortedTree to transfer database in vector to tempTree
                tempTree = sortedTree(option, contact);
                cout << "Database now sorted by email!" << endl << endl;
            }
            
            //Mobile phone #
            else if (option == 9)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contact = BSTreeVector(tree->Root(), contact);
                //call function sortedTree to transfer database in vector to tempTree
                tempTree = sortedTree(option, contact);
                cout << "Database now sorted by mobile phone #!" << endl << endl;
            }
            
            //Street address
            else if (option == 10)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contact = BSTreeVector(tree->Root(), contact);
                //call function sortedTree to transfer database in vector to tempTree
                tempTree = sortedTree(option, contact);
                cout << "Database now sorted by street address!" << endl << endl;
            }
            
            //City
            else if (option == 11)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contact = BSTreeVector(tree->Root(), contact);
                //call function sortedTree to transfer database in vector to tempTree
                tempTree = sortedTree(option, contact);
                cout << "Database now sorted by city!" << endl << endl;
            }
            
            //State
            else if (option == 12)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contact = BSTreeVector(tree->Root(), contact);
                //call function sortedTree to transfer database in vector to tempTree
                tempTree = sortedTree(option, contact);
                cout << "Database now sorted by state!" << endl << endl;
            }
            
            //Country
            else if (option == 13)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contact = BSTreeVector(tree->Root(), contact);
                //call function sortedTree to transfer database in vector to tempTree
                tempTree = sortedTree(option, contact);
                cout << "Database now sorted by country!" << endl << endl;
            }
            
            //Zip code
            else if (option == 14)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contact = BSTreeVector(tree->Root(), contact);
                //call function sortedTree to transfer database in vector to tempTree
                tempTree = sortedTree(option, contact);
                cout << "Database now sorted by zip code!" << endl << endl;
            }
            
            
            cout << "Display sorted records? (Y/N)" << endl;
            cin >> choice;
            
            //char input validator
            while (!isalpha(choice))
            {
                cout << "Invalid selection! Please try again" << endl;
                cin >> choice;
                cin.clear();
                cin.ignore(256, '\n');
            }
            
            if (choice == 'y' || choice == 'Y')
            {
                //display sorted records
                displayRecords(tempTree);
            }
            
            //ask user if they would like to sort by different fiel
            cout << "Sort by a different field? (Y/N)" << endl;
            cin >> choice;
            
            //char input validator
            while (!isalpha(choice))
            {
                cout << "Invalid selection! Please try again" << endl;
                cin >> choice;
                cin.clear();
                cin.ignore(256, '\n');
            }
            
        } while (choice != 'n' && choice != 'N');
        
    }
    //return updated tree
    return tempTree;
}




//****************************************************************************************************
//                                          DELETE RECORDS
//                        DESC:     Deletes records based on user search result
//                        RETURNS:  Udated tree
//****************************************************************************************************

BSTree* deleteRecord(BSTree* &tree)
{
    Node *tempNode = new Node;      //create new temporary node
    char choice;                    //holds user menu choices
    
    //check if database is empty
    if (tree->Root() == nullptr)
        cout << "Invalid operation! Database is empty" << endl << endl;
    else
    {
        do
        {
            //tempNode holds the record that the user searched for
            tempNode = search(tree);
            
            //display record and ask if user would like to permanently continue to
            //delete the record
            cout << tempNode->getContacts() << endl;
            cout << "Delete this record? (Y/N)" << endl;
            cin >> choice;
            //char input validator
            while (!isalpha(choice))
            {
                cout << "Invalid selection! Please try again" << endl;
                cin >> choice;
                cin.clear();
                cin.ignore(256, '\n');
            }
            
            //delete record from database by calling deleteNode()
            if (choice == 'y' || choice == 'Y')
            {
                //use key from tempNode to delete record
                cout << "Deleting contact records..." << endl << endl;
                tree->deleteNode(tempNode->Key());
            }

            //Ask user if they would like to delete another record
            cout << "Search for a different record to delete? (Y/N)" << endl;
            cin >> choice;
            //char input validator
            while (!isalpha(choice))
            {
                cout << "Invalid selection! Please try again" << endl;
                cin >> choice;
                cin.clear();
                cin.ignore(256, '\n');
            }
            
        } while (choice != 'n' && choice != 'N');
        
    }
    
    cout << "Display updated tree? (Y/N)" << endl;
    cin >> choice;
    //char input validator
    while (!isalpha(choice))
    {
        cout << "Invalid selection! Please try again" << endl;
        cin >> choice;
        cin.clear();
        cin.ignore(256, '\n');
    }
    
    if (choice == 'y' || choice == 'Y')
    {
        displayRecords(tree);
    }
    //return updated tree with record removed from database
    return tree;
    
}




//****************************************************************************************************
//                                          Save to file
//                              DESC:
//                              RETURNS:
//****************************************************************************************************
void save(Node* node, BSTree* &tree, string fileName)
{
    int option;                     //holds user option
    vector<Contacts> contactVec;    //temporary vector of Contacts contactVec
    char choice;                    //hodsl user menu choice
    
    //user selects preferred save option
    cout << "\tPLEASE SELECT A SAVE OPTION" << endl;
    cout << "1. Save" << endl;
    cout << "2. Save As" << endl;
    cout << "3. Exit" << endl;
    cin >> option;
    
    //int input validator
    while (option < 1 || option > 3 || isdigit(option))
    {
        cout << "Invalid selection! Please try again" << endl;
        cin >> option;
        cin.clear();
        cin.ignore(256, '\n');
    }
    
    //Save
    if (option == 1)
    {
        ofstream outfile;
        outfile.open(fileName);
        
        do
        {
            //create new BSTree object temp
            BSTree *temp = new BSTree;
            
            cout << "\tHOW WOULD YOU LIKE TO SORT THE RECORDS?" << endl << endl;
            cout << "1. User ID" << endl;
            cout << "2. First name" << endl;
            cout << "3. Middle" << endl;
            cout << "4. Last name" << endl;
            cout << "5. Company name" << endl;
            cout << "6. Home phone" << endl;
            cout << "7. Office phone" << endl;
            cout << "8. Email" << endl;
            cout << "9. Mobile phone" << endl;
            cout << "10. Street address" << endl;
            cout << "11. City" << endl;
            cout << "12. State" << endl;
            cout << "13. Country" << endl;
            cout << "14. Zip code" << endl << endl;
            cout << "Selection: ";
            cin >> option;   //user selection
            //int input validator
            while (option < 1 || option > 14 || isdigit(option))
            {
                cout << "Invalid selection! Please try again" << endl;
                cin >> option;
                cin.clear();
                cin.ignore(256, '\n');
            }
            
            //User ID
            if (option == 1)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contactVec = BSTreeVector(tree->Root(), contactVec);
                //call function sortedTree to transfer database in vector to tempTree
                temp = sortedTree(option, contactVec);
                //call saveAs function to save to file
                saveAs(outfile, temp->Root());
            }
            //first name
            else if (option == 2)
            {
                contactVec = BSTreeVector(tree->Root(), contactVec);
                temp = sortedTree(option, contactVec);
                saveAs(outfile, temp->Root());
            }
            //middle name
            else if (option == 3)
            {
                contactVec = BSTreeVector(tree->Root(), contactVec);
                temp = sortedTree(option, contactVec);
                saveAs(outfile, temp->Root());
            }
            //last name
            else if (option == 4)
            {
                contactVec = BSTreeVector(tree->Root(), contactVec);
                temp = sortedTree(option, contactVec);
                saveAs(outfile, temp->Root());
            }
            //company name
            else if (option == 5)
            {
                contactVec = BSTreeVector(tree->Root(), contactVec);
                temp = sortedTree(option, contactVec);
                saveAs(outfile, temp->Root());
            }
            //home phone
            else if (option == 6)
            {
                contactVec = BSTreeVector(tree->Root(), contactVec);
                temp = sortedTree(option, contactVec);
                saveAs(outfile, temp->Root());
            }
            //office phone
            else if (option == 7)
            {
                contactVec = BSTreeVector(tree->Root(), contactVec);
                temp = sortedTree(option, contactVec);
                saveAs(outfile, temp->Root());
            }
            //email
            else if (option == 8)
            {
                contactVec = BSTreeVector(tree->Root(), contactVec);
                temp = sortedTree(option, contactVec);
                saveAs(outfile, temp->Root());
            }
            //mobile phone
            else if (option == 9)
            {
                contactVec = BSTreeVector(tree->Root(), contactVec);
                temp = sortedTree(option, contactVec);
                saveAs(outfile, temp->Root());
            }
            //street address
            else if (option == 10)
            {
                contactVec = BSTreeVector(tree->Root(), contactVec);
                temp = sortedTree(option, contactVec);
                saveAs(outfile, temp->Root());
            }
            //city
            else if (option == 11)
            {
                contactVec = BSTreeVector(tree->Root(), contactVec);
                temp = sortedTree(option, contactVec);
                saveAs(outfile, temp->Root());
            }
            //state
            else if (option == 12)
            {
                contactVec = BSTreeVector(tree->Root(), contactVec);
                temp = sortedTree(option, contactVec);
                saveAs(outfile, temp->Root());
            }
            //country
            else if (option == 13)
            {
                contactVec = BSTreeVector(tree->Root(), contactVec);
                temp = sortedTree(option, contactVec);
                saveAs(outfile, temp->Root());
            }
            //zip code
            else if (option == 14)
            {
                contactVec = BSTreeVector(tree->Root(), contactVec);
                temp = sortedTree(option, contactVec);
                saveAs(outfile, temp->Root());
            }
            
            //ask user if they would like to sort by a different field
            cout << "Sort file by another field? (Y/N)" << endl << endl;
            cin >> choice;
            
            //char input validator
            while (!isalpha(choice))
            {
                cout << "Invalid selection! Please try again" << endl;
                cin >> choice;
                cin.clear();
                cin.ignore(256, '\n');
            }
            
        } while (choice != 'n' && choice != 'N');
        
        //close the file
        outfile.close();
    }
    //Save As
    else if (option == 2)
    {
        string file;
    
        cout << "Enter the name of the file you're saving to:" << endl;
        cin >> file;
        
        ofstream outFile;
        outFile.open(file);
        
        do
        {
            
            //create new BSTree object tempTree
            BSTree *tempTree = new BSTree;
            
            cout << "\tHOW WOULD YOU LIKE TO SORT THE RECORDS?" << endl << endl;
            cout << "1. User ID" << endl;
            cout << "2. First name" << endl;
            cout << "3. Middle" << endl;
            cout << "4. Last name" << endl;
            cout << "5. Company name" << endl;
            cout << "6. Home phone" << endl;
            cout << "7. Office phone" << endl;
            cout << "8. Email" << endl;
            cout << "9. Mobile phone" << endl;
            cout << "10. Street address" << endl;
            cout << "11. City" << endl;
            cout << "12. State" << endl;
            cout << "13. Country" << endl;
            cout << "14. Zip code" << endl << endl;
            cout << "Selection: ";
            cin >> option;   //user selection
            
            //int input validator
            while (option < 1 || option > 14 || isdigit(option))
            {
                cout << "Invalid selection! Please try again" << endl;
                cin >> option;
                cin.clear();
                cin.ignore(256, '\n');
            }
            
            //sort by user ID
            if (option == 1)
            {
                //call function BSTReeVector to insert database into contact Vector
                //assign contact to BSTreeVector
                contactVec = BSTreeVector(tree->Root(), contactVec);
                
                //call function sortedTree to transfer database in vector to tempTree
                tempTree = sortedTree(option, contactVec);
                
                //call saveAs function to write to file
                saveAs(outFile, tempTree->Root());
            }
            //sort by first name
            else if (option == 2)
            {
                
                contactVec = BSTreeVector(tree->Root(), contactVec);
                tempTree = sortedTree(option, contactVec);
                saveAs(outFile, tempTree->Root());
            }
            //sort by middle name
            else if (option == 3)
            {
                
                contactVec = BSTreeVector(tree->Root(), contactVec);
                tempTree = sortedTree(option, contactVec);
                saveAs(outFile, tempTree->Root());
            }
            //sort by last name
            else if (option == 4)
            {
                
                contactVec = BSTreeVector(tree->Root(), contactVec);
                tempTree = sortedTree(option, contactVec);
                saveAs(outFile, tempTree->Root());
            }
            //sort by company name
            else if (option == 5)
            {
                
                contactVec = BSTreeVector(tree->Root(), contactVec);
                tempTree = sortedTree(option, contactVec);
                saveAs(outFile, tempTree->Root());
            }
            //sort by home phone
            else if (option == 6)
            {
                
                contactVec = BSTreeVector(tree->Root(), contactVec);
                tempTree = sortedTree(option, contactVec);
                saveAs(outFile, tempTree->Root());
            }
            //sort by office phone
            else if (option == 7)
            {
                
                contactVec = BSTreeVector(tree->Root(), contactVec);
                tempTree = sortedTree(option, contactVec);
                saveAs(outFile, tempTree->Root());
            }
            //sort by email
            else if (option == 8)
            {
                
                contactVec = BSTreeVector(tree->Root(), contactVec);
                tempTree = sortedTree(option, contactVec);
                saveAs(outFile, tempTree->Root());
            }
            //sort by mobile phone
            else if (option == 9)
            {
                
                contactVec = BSTreeVector(tree->Root(), contactVec);
                tempTree = sortedTree(option, contactVec);
                saveAs(outFile, tempTree->Root());
            }
            //sort by street address
            else if (option == 10)
            {
                
                contactVec = BSTreeVector(tree->Root(), contactVec);
                tempTree = sortedTree(option, contactVec);
                saveAs(outFile, tempTree->Root());
            }
            //sort by city
            else if (option == 11)
            {
                
                contactVec = BSTreeVector(tree->Root(), contactVec);
                tempTree = sortedTree(option, contactVec);
                saveAs(outFile, tempTree->Root());
            }
            //sort by state
            else if (option == 12)
            {
                
                contactVec = BSTreeVector(tree->Root(), contactVec);
                tempTree = sortedTree(option, contactVec);
                saveAs(outFile, tempTree->Root());
            }
            //sort by country
            else if (option == 13)
            {
                
                contactVec = BSTreeVector(tree->Root(), contactVec);
                tempTree = sortedTree(option, contactVec);
                saveAs(outFile, tempTree->Root());
            }
            //sort by zip code
            else if (option == 14)
            {
                
                contactVec = BSTreeVector(tree->Root(), contactVec);
                tempTree = sortedTree(option, contactVec);
                saveAs(outFile, tempTree->Root());
            }
            
            
            
            //display status message to user
            cout << "Saving to file..." << endl << endl;
            cout << "File saved successfully!" << endl << endl;
            
            cout << "Sort file by another field? (Y/N)" << endl;
            cin >> choice;
            
            //char input validator
            while (!isalpha(choice))
            {
                cout << "Invalid selection! Please try again" << endl;
                cin >> choice;
                cin.clear();
                cin.ignore(256, '\n');
            }
            
        } while (choice != 'n' && choice != 'N');
        
        //close the file
        outFile.close();
        
    }
    

}


//***********************************************
//                  SAVE AS
//DESC: Saves the database to a new, user
//      input file
//***********************************************
void saveAs(ostream& outFile, Node* node)
{
    //if tree is not empty, recursively save contacts to new file using
    //ostream object outFile
    if (node != nullptr)
    {
        //recursively search entire tree
        saveAs(outFile, node->Left());
        
        //write contacts to file
        outFile << "ID:              " << node->getContacts().getUserID() << endl;
        outFile << "First name:      " << node->getContacts().getFirstName() << endl;
        outFile << "Middle:          " << node->getContacts().getMiddle() << endl;
        outFile << "Last:            " << node->getContacts().getLastName() << endl;
        outFile << "Company name:    " << node->getContacts().getCompanyName() << endl;
        outFile << "Home phone:      " << node->getContacts().getHomePhone() << endl;
        outFile << "Office phone:    " << node->getContacts().getOfficePhone() << endl;
        outFile << "Email:           " << node->getContacts().getEmail() << endl;
        outFile << "Mobile phone:    " << node->getContacts().getMobilePhone() << endl;
        outFile << "Street addess:   " << node->getContacts().getAddress() << endl;
        outFile << "City:            " << node->getContacts().getCity() << endl;
        outFile << "State:           " << node->getContacts().getState() << endl;
        outFile << "Country:         " << node->getContacts().getCountry() << endl;
        outFile << "Zip code:        " << node->getContacts().getZipCode() << endl;
        //write affiliates to file
        if (!node->getContacts().getAffiliates().empty())
        {
            vector<Affiliates> affVec = node->getContacts().getAffiliates();
            //display affiliates
            for (int i = 0; i < affVec.size(); i++)
            {
                outFile << "Affiliate #" << i + 1 << ":   " << affVec[i].getName()
                << ", " << affVec[i].getPhone() << ", " << affVec[i].getEmail() << ";" << endl;
            }
        }
        outFile << "|" << endl;

        
        //recursively traverse entire tree
        saveAs(outFile, node->Right());
    }
}



//***********************************************
//                  BSTReeVector
//DESC: Inserts records from binary search tree
//      into a temporary vector of Contacts.
//      Function will recursively traverse tree
//***********************************************
vector<Contacts> BSTreeVector(Node* node, vector<Contacts> &contactVec)
{
    //check if database is empty
    if (node != nullptr)
    {
        //add contacts to the vector contactVec
        contactVec.push_back(node->getContacts());
        //recursively traverse entire tree
        BSTreeVector(node->Left(), contactVec);
        BSTreeVector(node->Right(), contactVec);
    }
    
    //return database vector
    return contactVec;
}



//***********************************************
//                  sortedTree
//DESC: Inserts records from temporary vector of
//      Contacts into a new, temporary binary
//      search tree. Records are inserted in sorted order of
//      user's choice of field by setting said field
//      as the new key.
//***********************************************
BSTree* sortedTree(int option, vector<Contacts> &c)
{
    BSTree *tempTree = new BSTree;  //create new BSTree object tempTree
    Contacts temp;                  //Create new Contacts object temp
    
    if (option == 1)
    {
        //sort the vector
        cout << "Sorting the database..." << endl << endl;
        
        //add vector to database
        for (int i = 0; i < c.size(); i++)
        {
            tempTree->addNode(c[i].getUserID(), c[i]);
        }
    }
    else if (option == 2)
    {
        //sort the vector
        cout << "Sorting the database..." << endl << endl;

        //add vector to database
        for (int i = 0; i < c.size(); i++)
        {
            tempTree->addNode(c[i].getFirstName(), c[i]);
        }
    }
    else if (option == 3)
    {
        //sort the vector
        cout << "Sorting the database..." << endl << endl;
        
        //add vector to database
        for (int i = 0; i < c.size(); i++)
        {
            tempTree->addNode(c[i].getMiddle(), c[i]);
        }
    }
    else if (option == 4)
    {
        //sort the vector
        cout << "Sorting the database..." << endl << endl;
        
        //add vector to database
        for (int i = 0; i < c.size(); i++)
        {
            tempTree->addNode(c[i].getLastName(), c[i]);
        }
    }
    else if (option == 5)
    {
        //sort the vector
        cout << "Sorting the database..." << endl << endl;
        
        //add vector to database
        for (int i = 0; i < c.size(); i++)
        {
            tempTree->addNode(c[i].getCompanyName(), c[i]);
        }
    }
    
    else if (option == 6)
    {
        //sort the vector
        cout << "Sorting the database..." << endl << endl;
        
        //add vector to database
        for (int i = 0; i < c.size(); i++)
        {
            tempTree->addNode(c[i].getHomePhone(), c[i]);
        }
    }
    
    else if (option == 7)
    {
        //sort the vector
        cout << "Sorting the database..." << endl << endl;
        
        //add vector to database
        for (int i = 0; i < c.size(); i++)
        {
            tempTree->addNode(c[i].getOfficePhone(), c[i]);
        }
    }
    
    else if (option == 8)
    {
        //sort the vector
        cout << "Sorting the database..." << endl << endl;
        
        //add vector to database
        for (int i = 0; i < c.size(); i++)
        {
            tempTree->addNode(c[i].getEmail(), c[i]);
        }
    }
    
    else if (option == 9)
    {
        //sort the vector
        cout << "Sorting the database..." << endl << endl;
        
        //add vector to database
        for (int i = 0; i < c.size(); i++)
        {
            tempTree->addNode(c[i].getMobilePhone(), c[i]);
        }
    }
    
    else if (option == 10)
    {
        //sort the vector
        cout << "Sorting the database..." << endl << endl;
        
        //add vector to database
        for (int i = 0; i < c.size(); i++)
        {
            tempTree->addNode(c[i].getAddress(), c[i]);
        }
    }
    else if (option == 11)
    {
        //sort the vector
        cout << "Sorting the database..." << endl << endl;
        
        //add vector to database
        for (int i = 0; i < c.size(); i++)
        {
            tempTree->addNode(c[i].getCity(), c[i]);
        }
    }
    else if (option == 12)
    {
        //sort the vector
        cout << "Sorting the database..." << endl << endl;
        
        //add vector to database
        for (int i = 0; i < c.size(); i++)
        {
            tempTree->addNode(c[i].getState(), c[i]);
        }
    }
    else if (option == 13)
    {
        //sort the vector
        cout << "Sorting the database..." << endl << endl;
        
        //add vector to database
        for (int i = 0; i < c.size(); i++)
        {
            tempTree->addNode(c[i].getCountry(), c[i]);
        }
    }
    else if (option == 14)
    {
        //sort the vector
        cout << "Sorting the database..." << endl << endl;
        
        //add vector to database
        for (int i = 0; i < c.size(); i++)
        {
            tempTree->addNode(c[i].getZipCode(), c[i]);
        }
    }
    
    //return the sorted tree
    return tempTree;
}




#endif /* functions_h */
