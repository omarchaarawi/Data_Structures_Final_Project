#pragma once

#include <string>

using namespace std;

struct Node{
    int key;
    Node* left = NULL;
    Node* right = NULL;
};

class IdTree{   // class for BST of tracking IDs
    private:
        Node* root;

    public:
        IdTree();   // Constructor
        ~IdTree();  // Destructor
        void addNode(int key);
        void printInventory();
        Node* search(int key);


};
