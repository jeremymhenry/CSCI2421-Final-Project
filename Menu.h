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

#ifndef Menu_h
#define Menu_h

#include "functions.h"
#include "BSTree.h"
#include "Node.h"
#include <string>
#include <fstream>


using namespace std;

void Menu()
{
    
    Contacts contact;   //instantiate Contacts object contact
    int selection;      //holds user menu selection
    string file;        //holds file name
    string fieldSearch;
    BSTree *currentTree = new BSTree;
    Node *node = new Node;
    
    cout << "-------------------------------------" << endl;
    cout << "\t\tWELCOME!" << endl;
    cout << "This program will allow you to create" << endl;
    cout << "and manage your own records database." << endl;
    cout << "LET'S GET STARTED!" << endl;
    cout << "-------------------------------------" << endl;
    
    do
    {
        //Display menu options for user
        cout << "\t\tMAIN MENU" << endl;
        cout << "1. Read in records from file. " << endl;
        cout << "2. Insert new record" << endl;
        cout << "3. Search for a record" << endl;
        cout << "4. Modify a record" << endl;
        cout << "5. Delete a record" << endl;
        cout << "6. Sort records" << endl;
        cout << "7. Display records" << endl;
        cout << "8. Save records to file" << endl;
        cout << "9. Exit" << endl << endl;
        cout << "Selection: ";
        cin >> selection;
        cout << endl;
        
        switch (selection)
        {
            //read input from file
            case 1:
                //prompts user to enter the name of the file
                //call function readFromFile()
                cout << "Enter name of the file to be read in: " << endl;
                cin >> file;
                readFromFile(currentTree, file);
                break;
            case 2:
                //call addRecord() function
                addRecord(currentTree);
                break;
            case 3:
                search(currentTree);
                break;
            case 4:
                //call modifyRecord() function
                currentTree = modifyRecord(currentTree);
                break;
            case 5:
                //call deleteRecord() function
                currentTree = deleteRecord(currentTree);
                break;
            case 6:
                //call sortRecord() function
                currentTree = sortRecords(currentTree);
                break;
            case 7:
                //calls displayRecords function
                displayRecords(currentTree);
                break;
            case 8:
                //call saveToFile() function
                save(node, currentTree, file);
                break;
            //exit program
            case 9:
                cout << "Goodbye!" << endl;
                delete currentTree;
                break;
            //input validation
            default:
                cout << "Invalid selection! Please try again" << endl << endl;
                break;
                
        }
        
    } while (selection != 9);   //repeat menu options unless user selects option 8
    
}



#endif /* Menu_h */
