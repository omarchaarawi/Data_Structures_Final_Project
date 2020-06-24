#pragma once

#include <iostream>
#include <string>

#define I 10  // 10 for 0-9 integers

using namespace std;

struct node{
    bool is_key;  // true if path is a key
    node *children[I]; 
};

class Trie{
    private:
    node* root;  // pointer to the root of Trie
    
    public:
        Trie();
        void add(int shipment);
        bool search(int shipment);
        void displayList();
        void deleteList();  // will be used to manually delete trie later
};