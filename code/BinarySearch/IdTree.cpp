#include "IdTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void deleteTree(Node *noodle); // Initialize function to delete tree
void printTree(Node* node);  // helper function to print out tree recursively
Node* addNodeHelper(Node* currNode, int key);  // helper functon to addNode recursively
Node* createNode(int key); //helper function that creates node once we know where to put it

// MovieNode: node struct that will be stored in the IdTree BST
IdTree::IdTree() {
  root = NULL;
}

IdTree::~IdTree() {
  deleteTree(root); // Use recursive deleteTree function to delete tree
}

// Print all the tracking IDs that have been assembled in the BST in order
void IdTree::printInventory() {
  if(root == NULL){
    cout << "Tree is empty." << endl;
  } else{
    printTree(root);
  }
  cout << endl;
}
void printTree(Node* node){
    if(node != NULL){
      printTree(node->left);
      cout << node->key << " ";   
      printTree(node->right);
    }
}

// add node 
void IdTree::addNode(int key) {
  // create the node
  root = addNodeHelper(root, key);
}

Node* createNode(int key) { 
  Node* newNode = new Node;
  newNode->key = key;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

Node* addNodeHelper(Node* currNode, int key) {
  if(currNode == NULL)
    return createNode(key);
  else if(currNode->key < key)  // compare currNode->title agains insert node title, if 1, go right
    currNode->right = addNodeHelper(currNode->right, key);
  else if(currNode->key > key)  // go left
    currNode->left = addNodeHelper(currNode->left, key);
  return currNode;
}

// compare keys until node is reached containing key of importance
// returns pointer to that node
Node* IdTree::search(int key) {
  Node* temp = root;
  while(true){
    if(temp->left == NULL && temp->right == NULL){
      cout << "key not found." << endl;
      return NULL;
    }
    else if (temp->key == key)
      break;
    else if(temp->key > key){ // go left
      temp = temp->left;
      if(temp->key == key){
        break;
      } 
    }
    else if(temp->key < key){ // go right
      temp = temp->right;
      if(temp->key == key)
        break;
    }
  }
  return temp;
}

void deleteTree(Node *node)
{
    if (node == NULL) return;
    else{
      if(node != NULL){
        deleteTree(node->left);
        deleteTree(node->right);
      }
     delete node;
     node = NULL;
    }
}


// //Code for testing IdTree.cpp code
// int main(){
//   IdTree Tree;
//   Tree.printInventory();
//   for (int i = 0; i < 20; ++i){
//     Tree.addNode(rand()%1000);
//   }
//   Tree.printInventory();
//   Node* myNode = Tree.search(544);
//   cout << myNode->key << endl;
//   return 0;
// }