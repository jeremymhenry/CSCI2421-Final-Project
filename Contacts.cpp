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


#include <stdio.h>
#include "Contacts.h"
using namespace std;


//Default Constructor
Contacts::Contacts()
{
    userID = " ";
    firstName = " ";
    middle = " ";
    lastName = " ";
    companyName = " ";
    homePhone = " ";
    officePhone = " ";
    email = " ";
    mobilePhone = " ";
    address = " ";
    city = " ";
    state = " ";
    zipCode = " ";
    country = " ";
}

//Mutator functions
void Contacts::setUserID(string _userID)
{
    userID = _userID;
}
void Contacts::setFirstName(string _firstName)
{
    firstName = _firstName;
}
void Contacts::setMiddle(string _middle)
{
    middle = _middle;
}
void Contacts::setLastName(string _lastName)
{
    lastName = _lastName;
}
void Contacts::setCompany(string _companyName)
{
    companyName = _companyName;
}
void Contacts::setHomePhone(string _homePhone)
{
    homePhone  = _homePhone;
}
void Contacts::setOfficePhone(string _officePhone)
{
    officePhone = _officePhone;
}
void Contacts::setEmail(string _email)
{
    email = _email;
}
void Contacts::setMobilePhone(string _mobilePhone)
{
    mobilePhone = _mobilePhone;
}
void Contacts::setAddress(string _address)
{
    address = _address;
}
void Contacts::setCity(string _city)
{
    city = _city;
}
void Contacts::setState(string _state)
{
    state = _state;
}
void Contacts::setZip(string _zipCode)
{
    zipCode = _zipCode;
}
void Contacts::setCountry(string _country)
{
    country = _country;
}


//Accessor functions
string Contacts::getUserID()
{
    return userID;
}
string Contacts::getFirstName()
{
    return firstName;
}
string Contacts::getMiddle()
{
    return middle;
}
string Contacts::getLastName()
{
    return lastName;
}
string Contacts::getCompanyName()
{
    return companyName;
}
string Contacts::getHomePhone()
{
    return homePhone;
}
string Contacts::getOfficePhone()
{
    return officePhone;
}
string Contacts::getEmail()
{
    return email;
}
string Contacts::getMobilePhone()
{
    return mobilePhone;
}
string Contacts::getAddress()
{
    return address;
}
string Contacts::getCity()
{
    return city;
}
string Contacts::getState()
{
    return state;
}
string Contacts::getZipCode()
{
    return zipCode;
}
string Contacts::getCountry()
{
    return country;
}

void Contacts::addAffiliate(Affiliates aff)
{
    affVec.push_back(aff);
}

void Contacts::clearAffiliate(Affiliates aff)
{
    affVec.clear();
}




//Overloaded << operator to display contacts
//pass in affVec as function parameter
//then call displayAffiliates using affVec as parameter
ostream &operator << (ostream &out, Contacts contacts)
{
    out << "ID:             " << contacts.getUserID() << endl;
    out << "First Name:     " << contacts.getFirstName() << endl;
    out << "Middle:         " << contacts.getMiddle() << endl;
    out << "Last Name:      " << contacts.getLastName() << endl;
    out << "Company name:   " << contacts.getCompanyName() << endl;
    out << "Home Phone:     " << contacts.getHomePhone() << endl;
    out << "Office Phone:   " << contacts.getOfficePhone() << endl;
    out << "Email:          " << contacts.getEmail() << endl;
    out << "Mobile:         " << contacts.getMobilePhone() << endl;
    out << "Street Address: " << contacts.getAddress() << endl;
    out << "City:           " << contacts.getCity() << endl;
    out << "State:          " << contacts.getState() << endl;
    out << "ZIP Code:       " << contacts.getZipCode() << endl;
    out << "Country:        " << contacts.getCountry() << endl;
    contacts.displayAffiliates(contacts.getAffiliates());
    
    out << endl;
    
    
    return out;
}

//display affiliate database from Affiliates vector
void Contacts::displayAffiliates(vector<Affiliates> affVec)
{
    if (!affVec.empty())
    {
        //display affiliates
        for (int i = 0; i < affVec.size(); i++)
        {
            cout << "Affiliate #" << i + 1 << ":   " << affVec[i].getName()
            << ", " << affVec[i].getPhone() << ", " << affVec[i].getEmail() << ";" << endl;
        }
    }
}


