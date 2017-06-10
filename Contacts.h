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


#ifndef Contacts_h
#define Contacts_h

#include <iostream>
#include <vector>
#include "Affiliates.h"

using namespace std;


class Contacts
{
private:
    //Member variables
    string userID;             //changed 4/10/17
    string firstName;
    string middle;
    string lastName;
    string companyName;
    string homePhone;
    string officePhone;
    string email;
    string mobilePhone;
    string address;
    string city;
    string state;
    string zipCode;
    string country;
    vector<Affiliates> affVec;
    
public:
    //Mutator functions
    Contacts();     //Default Constructor
    void setUserID(string _userID);
    void setFirstName(string _firstName);
    void setMiddle(string _middle);
    void setLastName(string _lastName);
    void setCompany(string _companyName);
    void setHomePhone(string _homePhone);
    void setOfficePhone(string _officePhone);
    void setEmail(string _email);
    void setMobilePhone(string _mobilePhone);
    void setAddress(string _address);
    void setCity(string _city);
    void setState(string _state);
    void setZip(string _zipCode);
    void setCountry(string _country);
    
    //Accessor functions
    string getUserID();
    string getFirstName();
    string getMiddle();
    string getLastName();
    string getCompanyName();
    string getHomePhone();
    string getOfficePhone();
    string getEmail();
    string getMobilePhone();
    string getAddress();
    string getCity();
    string getState();
    string getZipCode();
    string getCountry();
    
    //include affiliates in contact database
    void addAffiliate(Affiliates aff);
    void clearAffiliate(Affiliates aff);
    void displayAffiliates(vector<Affiliates> vec);
    vector<Affiliates> getAffiliates() {return affVec;}
    
    //Overloaded << operator to display the database
    friend ostream &operator << (ostream &out, Contacts contacts);
    
    
};



#endif /* Contacts_h */
