

#include "BSTree.h"
#include "Node.h"
#include <iostream>
using namespace std;

// Constructor
BSTree::BSTree() {
    root = nullptr;
}

// Destructor
BSTree::~BSTree() {
    if (root !=nullptr)
        freeNode(root);
}

// Free the node
void BSTree::freeNode(Node* leaf)
{
    if ( this->Root() == leaf)
    {
        
    }
    else if ( leaf != nullptr )
        
    {
        freeNode(leaf->Left());
        freeNode(leaf->Right());
        delete leaf;
    }
    
}

// Add a node
void BSTree::addNode(string key, Contacts newContact)
{
    // No elements. Add the root
    if ( root == nullptr )
    {
        Node* n = new Node();
        n->setKey(key);
        root = n;
        n->setContacts(newContact);     //added 4/10/17
    }
    else
    {
        addNode(key, root, newContact); //added 4/10/17
    }
}

// Add a node (private)
void BSTree::addNode(string key, Node* leaf, Contacts newContact)   //added 4/11/17
{
    if ( key <= leaf->Key() )
    {
        if ( leaf->Left() != nullptr )
            addNode(key, leaf->Left(), newContact);
        else
        {
            Node* n = new Node();
            n->setKey(key);
            n->setParent(leaf);
            leaf->setLeft(n);
            n->setContacts(newContact); //added 4/11/17
        }
    }
    else
    {
        if ( leaf->Right() != nullptr )
            addNode(key, leaf->Right(), newContact);
        else {
            Node* n = new Node();
            n->setKey(key);
            n->setParent(leaf);
            leaf->setRight(n);
            n->setContacts(newContact); //added 4/10/17
        }
    }
}

// Find a node
Node* BSTree::findNode(string key, Node* root)
{
    //check if node is equal to nullptr
    if (root != nullptr)
    {
        //if node is equal to key, then return the node
        if (root->Key() == key)
            return root;
        
        //if key is less than node, then traverse left side of BSTree
        else if (key < root->Key())
            return findNode(key, root->Left());
        
        //if key is greater than or equal to node, then traverse
        //right side of BSTree
        else
            return findNode(key, root->Right());
    }
    //if node is equal to nullptr, return nullptr
    else
        return root;
    
}


// Print the BSTree
void BSTree::printPreorder(Node* root)
{
    //check if node points to nullptr
    if (root != nullptr)
    {
        cout << root->Key() << " ";     //visit and display nodes
        printPreorder(root->Left());    //traverse left subtree of root
        printPreorder(root->Right());   //traverse right subtree of root
    }
}

void BSTree::printInorder(Node* root)
{
    //check if node points to nullptr
    if (root != nullptr)
    {
        //as long as node doesn't point to nullptr
        printInorder(root->Left());     //traverse left subtree of node's root
        
        //Print contact object to display the records
        cout << root->getContacts();     //visit and display nodes
                                        //added getContacts() 4/10/17
        printInorder(root->Right());    //traverse right subtree of node's root
    }
    
}

void BSTree::printPostorder(Node* root)
{
    //check if node points to nullptr
    if (root != nullptr)
    {
        printPostorder(root->Left());   //traverse left subtree
        printPostorder(root->Right());  //traverse right subtree
        cout << root->Key() << " ";     //visit and display nodes
    }
}

// Find the node with min key
// Traverse the left sub-BSTree recursively
// till left sub-BSTree is empty to get min
Node* BSTree::min(Node* node)
{
    Node* tempNode = node;
    if ( node == nullptr )
        tempNode = nullptr;
    else if ( node->Left() )
    {
        tempNode = min(node->Left());
    }
    else
        tempNode = node;
    
    return tempNode;
}

// Find the node with max key
// Traverse the right sub-BSTree recursively
// till right sub-BSTree is empty to get max
Node* BSTree::max(Node* node)
{
    Node * tempNode = node;
    if ( node == nullptr )
        tempNode = nullptr;
    else if ( node->Right() )
        tempNode = max(node->Right());
    else
        tempNode = node;
    
    return tempNode;
}

// Find successor to a node
// Find the node, get the node with max value
// for the right sub-BSTree to get the successor
Node* BSTree::successor(string key, Node *node)
{
    
    
    Node *successor = nullptr;
    Node *current  = root;
    if(root == nullptr)
        return NULL;
    
    while(current->Key() != key){
        /* If node value is greater than the node which are looking for, then go to left sub tree
         Also when we move left, update the successor pointer to keep track of lst left turn */
        
        if(current->Key() >key){
            successor = current;
            current= current->Left();
        }
        /* Else take right turn and no need to update successor pointer */
        else
            current = current->Right();
    }
    /*Once we reached at the node for which inorder successor is to be found, check if it has right sub tree, if yes then find the minimum in that right sub tree and return that node
     
     Else last left turn taken node is already stored in successor pointer and will be returned*/
    if(current && current->Right()){
        successor = min(current->Right());
    }
    
    return successor;
}

// Find predecessor to a node
// Find the node, get the node with max value
// for the left sub-BSTree to get the predecessor
Node* BSTree::predecessor(string key, Node *node)
{
    
    Node* current = findNode(key, node);
    
    if (current == nullptr)
    { return nullptr; }
    
    if (current->Left() !=nullptr)
    {
        return max(current->Left());
    } else
        
    {
        Node *tempParent = current->Parent();
        while (tempParent !=nullptr) {
            if (current == tempParent->Right() ){
                break;
            }
            current = tempParent;
            tempParent = current->Parent();
        }
        return tempParent;
    }
}


void BSTree::deleteNode(string key)
{
    if (deleteNode(Root(), key) == nullptr)
        setRoot(nullptr);
}

//deleteNode (Private)
Node* BSTree::deleteNode(Node* root, string key)
{
    
    /* Given a binary search tree and a key, this function deletes the key
     and returns the new root */
    
    
    if(root == nullptr) return root;
    else if(key < root->Key())
        root->setLeft( deleteNode(root->Left(),key));
    else if(key > root->Key())
        root->setRight( deleteNode(root->Right(), key) );
    else {
        // Case 1: No Child
        if(root->Left() == nullptr && root->Right() == nullptr){
            delete root;
            root = nullptr;
            // Case 2: one child
        } else if(root->Left() == nullptr){
            Node *temp = root;
            root = root->Right();
            delete temp;
        } else if(root->Right() == nullptr){
            Node *temp = root;
            root = root->Left();
            delete temp;
        } else{
            Node *temp = min(root->Right());
            root->setKey(temp->Key());
            root->setContacts(temp->getContacts());
            root->setRight(deleteNode(root->Right(), temp->Key()));
        }
    }
    return root;
    
}
