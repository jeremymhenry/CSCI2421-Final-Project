


#ifndef NODE_
#define NODE_
#include <iostream>
#include "Contacts.h"
using namespace std;

// A generic tree node class

//Placeholder for a composite data type
class Datatype{
private:
    int number;
    
    
};

//Binary Tree Node
class Node {
private:
    string key;            //holds key
    Datatype data;      //holds data(number)
    Node* left;         //points to left subtree
    Node* right;        //points to right subtree
    Node* parent;       //points to parent in tree
    Contacts contact;
public:
    Node() { key=-1; left=nullptr; right=nullptr; parent = nullptr;};   //Constructor
    
    //mutator functions
    void setKey(string aKey) { key = aKey; };
    void setLeft(Node* aLeft) { left = aLeft; };
    void setRight(Node* aRight) { right = aRight; };
    void setParent(Node* aParent) { parent = aParent; };
    //set contact object to _contact
    void setContacts(Contacts _contact) {contact = _contact;}
    
    //accessor functions
    string Key() { return key; };
    Node* Left() { return left; };
    Node* Right() { return right; };
    Node* Parent() { return parent; };
    //returns Contact object contact
    //allows node object to act as Contacts class object by
    //allowing the node to use the mutator and accessor functions
    //of the Contacts class
    //added 4/11/17
    Contacts& getContacts() {return contact;}
};



#endif
