// Hash table with chaining 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include "hash.hpp"

using namespace std;

void deleteHelper(node* head);

 HashTable::HashTable(int bsize){
     tableSize = bsize;
     node** myArray = new node*[bsize]; 
     table = myArray;
 }

void deleteHelper(node* head){
    if(head == NULL)
        return;
    deleteHelper(head->next);
    delete (head);
}

// iterate through the table then delete nodes recursively
 HashTable::~HashTable(){
     for(int i = 0; i < tableSize; ++i){
         deleteHelper(table[i]);
     }
     delete[] table;
 }

// insert/ add a key to ADT
bool HashTable::insert(int key){
    unsigned int hashKey = hashFunction(key);  // get hashKey
    // create node
    node* newNode = new node;
    newNode->key = key;
    newNode->next = NULL;

    if(table[hashKey] == NULL){ // if no node at that location in the table yet add node
        table[hashKey] = newNode;
        return true;
    }
    else{
        node* head = table[hashKey];
        while(head->next != NULL){  // find the end of the linked list
            numOfcollision++;  // increment the number of collisions once per loop
            head = head->next;
        }
        head->next = newNode;
        return true;
    }
}

void HashTable::printTable(){
    for(int i = 0; i < tableSize; ++i){
        if(table[i] != NULL){
            node* head = table[i];
            while(head != NULL){
                cout << head->key << " ";
                head = head->next;
            }
        }
    }
    cout << endl;
}

int HashTable::getNumOfCollision(){
    return numOfcollision;
}

// reset number of collisions
// this wil be handy in the driver file
void HashTable::resetCollision(){
    numOfcollision = 0;
}

// hash function H(x) = x mod m where m is the table size
// m = 40009
unsigned int HashTable::hashFunction(int key){
    return key % tableSize;
}

node* HashTable::searchItem(int key){
    unsigned int hashKey = hashFunction(key);
    node* head = table[hashKey];
    while(head->key != key){
        numOfcollision++;
        head = head->next;
    }
    return head;
}

// code to test hash.cpp

// int main(){
//     HashTable table(40009);
//      for(int i = 0; i < 40000; ++i){
//          table.insert(rand() % 40000);
//      }
//     table.insert(4);
//     table.insert(44);
//     table.printTable();
//     int num = table.getNumOfCollision();
//     cout << "num of col: " << num << endl;
//     node* myNode = table.searchItem(39712);
//     cout << "search: " << myNode->key << endl;

//     return 0;
// }