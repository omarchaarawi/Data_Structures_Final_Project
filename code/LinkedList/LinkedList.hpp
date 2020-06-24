#pragma once

#include <iostream>
#include <string>


using namespace std;

struct Node{
    int key;
    Node *next;
};

class LinkedList{
    private:
    Node* head;  // pointer to the head of the linked list
    public:
        LinkedList();
        void add(int shipment);
        Node* search(int shipment);
        void displayList();
        void deleteList();
};