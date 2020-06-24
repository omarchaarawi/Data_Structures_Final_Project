// Hash table with linear probing
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

// delete nodes recursively
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

    while(table[hashKey] != NULL){
        // update hashKey until empty spot found
        numOfcollision++;
        hashKey = (hashKey + 1) % (tableSize - 1);  // increment hashKey by one and perfrom modulo division to account for circular array
    }
    table[hashKey] = newNode;
    return true;
}

void HashTable::printTable(){
    for(int i = 0; i < tableSize; ++i){
        if(table[i] != NULL){
            cout << table[i]->key << " ";
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
    node* myNode = table[hashKey];
    while(myNode->key != key){
        numOfcollision++;
        hashKey = (hashKey + 1) % (tableSize - 1);
        myNode = table[hashKey];
    }
    return myNode;
}

// code to test hash.cpp

// int main(){
//     HashTable table(40009);
//     //  for(int i = 0; i < 40000; ++i){
//     //      table.insert(rand() % 40000);
//     //  }
//     table.insert(4);
//     table.insert(44);
//     table.printTable();
//     int num = table.getNumOfCollision();
//     cout << "num of col: " << num << endl;
//     node* myNode = table.searchItem(44);
//     cout << "search: " << myNode->key << endl;

//     return 0;
// }