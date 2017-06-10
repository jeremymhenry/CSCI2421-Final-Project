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
 
 Status:    Compiles on Xcode and the csegrid.
 
 */
#include <stdio.h>
#include "Affiliates.h"
using namespace std;


//Default Constructor
Affiliates::Affiliates()
{
    name = " ";
    email = " ";
    phoneNumber = " ";
}

//Mutator functions
void Affiliates::setName(string _name)
{
    name = _name;
}

void Affiliates::setEmail(string _email)
{
    email = _email;
}

void Affiliates::setPhone(string _phoneNumber)
{
    phoneNumber = _phoneNumber;
}


//Accessor functions
string Affiliates::getName()
{
    return name;
}

string Affiliates::getPhone()
{
    return phoneNumber;
}

string Affiliates::getEmail()
{
    return email;
}
 

