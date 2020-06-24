#ifndef HASH_HPP
#define HASH_HPP

#include <string>


using namespace std;

struct node
{
    int key;
    struct node* next;
};

class HashTable
{
    int tableSize;  // No. of buckets (linked lists)

    // Pointer to an array containing buckets
    node* *table;
    int numOfcollision = 0;
    // node* createNode(int key, node* next);
public:
    HashTable(int bsize);  // Constructor

    ~HashTable();  // Destructor

    // inserts a key into hash table
    bool insert(int key);

    // hash function to map values to key
    unsigned int hashFunction(int key);

    void printTable();
    int getNumOfCollision();
    void resetCollision();

    node* searchItem(int key);
};

#endif
