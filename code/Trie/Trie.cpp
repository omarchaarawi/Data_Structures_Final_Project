#include "Trie.hpp"
#include <string>
#include <iostream>
using namespace std;



node* createNode();  // create node helper function
void deleteHelper(node* temp);
void displayListHelper(node* temp, string myString[], int level);
bool isLeaf(node* temp);

// Constructor for trie
Trie::Trie(){
    root = createNode();
}


// insert a new key
void Trie::add(int shipment){
    string key = to_string(shipment);
    int level;  // level in this case also refers to decimal place in integer
    // for example in the number 8186, level 0 = int 8, level 1 = 1, level 2 = 8, level 3 = 6
    int length = key.size();  // get number of digits in shipment number
    int index;

    node* trav = root;  // create node to traverse trie

    for(level = 0; level < length; level++){
        index = (key[level] - 48);  // index is the number at that level/place in the digit
        if(trav->children[index] == NULL){  // if no node at that index create one
            trav->children[index] = createNode();
        }
        trav = trav->children[index];
    }
    trav->is_key = true;  // at final leaf, set is_key to true so that we know that that path spells out a shipment integer
}

// function for creating a node and initializing it
node* createNode(){
    node* newNode = new node;
    newNode->is_key = false; 
    for(int i = 0; i < I; i++){
        newNode->children[i] = NULL;
    }
    return newNode;
}

// function that tells us if the current node is a leaf node
bool isLeaf(node* temp){
    return temp->is_key != false;
}

// helper function for displaying the list recursively
void displayListHelper(node* temp, char myString[], int level){
    if(isLeaf(temp)){
        myString[level] = '\0';
        cout << myString << " ";

    }
    int i;
    for(i = 0; i < I; i++){
        if(temp->children[i]){  // if a node exists here add that index which is the next digit in the shipment to the shipment number
            string str = to_string(i);
            myString[level] = str[0];
            displayListHelper(temp->children[i], myString, level + 1);  // recurse
        }
    }
}

// display all the numbers in the Trie
void Trie::displayList(){
    if(root == NULL){  // check that trie is not empty first
        cout << "List is empty!" << endl;
        return;
    }
    char myString[20];  // we set the digits here to 20, that should be enough
    int level = 0;
    cout << "Items in Trie: ";
    displayListHelper(root, myString, level);
    cout << endl;
}

// deletes all the nodes in the Trie recursively
void deleteHelper(node* temp){
    for (int i = 0; i < I; ++i){
        if(temp->children[i] != NULL){
            deleteHelper(temp->children[i]);
        }
    }
    delete temp;
}


void Trie::deleteList(){
    cout << "Deleting Trie!" << endl;
    deleteHelper(root);
    root = NULL;
}

// search for the shipment in the trie and return true if found
bool Trie::search(int shipment){
    if(root == NULL){
        cout << "List is empty!" << endl;
        return false;
    }
    else{
        string key = to_string(shipment);
        int level;
        int length = key.size();
        int index;
        
        node* trav = root;

        for(level = 0; level < length; level++){
            index = (key[level] - 48);
            if(!trav->children[index])
                return false;
            
            trav = trav->children[index];
        }
        return trav->is_key;
    }
}

// code used to make sure everything is working fine

// int main(){
//     Trie T;
//     // for(int i = 0; i < 10; ++i){
//     //     LL.add(i);
//     // }
//     // LL.displayList();
//     for(int i = 0; i < 10; i++){
//         int j = (i * 6) + 1;
//         T.add(j);
//         cout << j << " ";
//     }
//     cout << endl;
//         for(int i = 0; i < 10; i++){
//         int j = (i * 6) + 1;
//         cout << T.search(j) << " ";
//     }
//     cout << endl;

//     T.displayList();
//     T.deleteList();
//     T.displayList();
// }