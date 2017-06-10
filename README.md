# CSCI2421-Final-Project
A simple database system written in C++ for CSCI 2421 - Data Structures.
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************
The purpose of the program is to create a simple database
system which acts as a contact address book. The records
are read in from a file and users will have the option 
of adding/deleting records, sorting, modifying and have
two options to search through the records. The user then
has the option of saving the output to the original file
or saving to a new file.

*******************************************************
*  Source files
*******************************************************
Name: Node.h
	Contains the declaration and definition of the 
	Node class.

Name: BSTree.h
	Contains the declaration of the BSTree class

Name: BSTree.cpp
	Contains the definition of the BSTree class

Name: Contacts.h
	Contains the declaration of the Contacts class. 
	Functions also include adding affiliates to the
	contact class, displaying affiliates and returning
	the affiliates.
	Friend class overloads << operator to display the 
	records.
	Contains the vector that holds the associated 
	affiliates.

Name: Contacts.cpp
	Contains the definition of the Contacts class.

Name: Affiliates.h
	Contains the declaration for the Affiliates class.

Name: Affiliates.cpp
	Contains the definition for the Affiliates class.

Name: Menu.h
	Main driver of the program. Contains a text-menu
	system. Menu options include Reading in records
	from a file, adding records, searching, modifying,
	sorting, deleting and displaying records. User has
	the option to save records to separate file or 
	overwrite current file. Each menu choice will call
	the appropriate function located in "functions.h".

Name: functions.h
	Contains the function definitions for the program
	described above in "Menu.h". Includes additional
	functions.
	BSTreeVector transfers the database from the binary
	search tree into a STL vector.
	sortedTree function transfers the database from the 
	vector back into the binary search tree in sorted 
	order of user's choice. 

Name: main.cpp
	Calls menu() function located in "Menu.h" to 
	initiate the program.

*******************************************************
*  Circumstances of programs
*******************************************************
Compiles on Xcode and csegrid.ucdenver.pvt

*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework.  The homework file is compressed.  
   To uncompress it use the following commands 
       % unzip [HenryFinal]

   Now you should see a directory named homework with the files:
	BSTree.h
	BSTree.cpp
	Node.h
	main.cpp
	Contacts.h
	Contacts.cpp
	Affiliates.h
	Affiliates.cpp
	Menu.h
	functions.h

2. Build the program.

    Change to the directory that contains the file by:
    % cd [HenryFinal] 

    Compile the program by:
    % make

3. Run the program by:
   % ./[henryProj]

4. Delete the obj files, executables, and core dump by
   %./make clean
 
