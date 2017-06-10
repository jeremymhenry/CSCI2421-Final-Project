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

#ifndef Affiliates_h
#define Affiliates_h
#include <string>
using namespace std;


class Affiliates
{
private:
    //Member variables
    string name;            //holds affiliate name
    string phoneNumber;     //holds affiliate phone number
    string email;           //holds affiliate email
    
public:
    //Mutator functions
    Affiliates();   //Default Constructor
    void setName(string _name);
    void setPhone(string _phoneNumber);
    void setEmail(string email);
    
    //Accessor functions
    string getName();
    string getPhone();
    string getEmail();
    
    
};
 

#endif /* Affiliates_h */
