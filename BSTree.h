
#ifndef BSTREE_
#define BSTREE_
#include <iostream>
using namespace std;
#include "Node.h"

// Binary Search Tree class
class BSTree {
private:
    Node* root;                                 //Node root pointer
    
    //add contacts object to addNode class
    //node may act as a object of Contact class
    //added 4/10/17
    void addNode(string key, Node* leaf, Contacts newContact);      //add a node
    
    Node* deleteNode(Node* node, string key);      //delete nodes
    void freeNode(Node* leaf);                  //freeNode
public:
    BSTree();                                   //Default Contructor
    ~BSTree();                                  //Destructor
    Node* Root() { return root; }               //return root
    void setRoot(Node * _root) {root = _root;}  //assign root to _root
    
    //add contacts object to addNode class
    //node may act as a object of Contact class
    //added 4/10/17
    void addNode(string key, Contacts contact);                      //add nodes
                                                                
    Node* findNode(string key, Node* parent);      //search for a node
    void printPreorder(Node* node);             //display nodes in preorder
    void printInorder(Node* node);              //display nodes inorder
    void printPostorder(Node* node);            //display nodes postorder
    
    
    void deleteNode(string key);                   //delete a node
    
    Node* min(Node* node);                      //locate min node
    Node* max(Node* node);                      //locate max mode
    Node* successor(string key, Node* parent);     //locate successor
    Node* predecessor(string key, Node* parent);   //locate predecessor
    
};


#endif
