#include "LinkedList.hpp"

using namespace std;

void deleteHelper(Node* head);  // helper function that recursively deletes list

// Constructor for LinkedList
LinkedList::LinkedList(){
    head = NULL;
}

// insert a new node
void LinkedList::add(int shipment){
    if(head == NULL){  // if LinkedList is empty
        head = new Node;
        head->key = shipment;
        head->next = NULL;
    }
    else{
        Node* temp = head;
        while(temp->next != NULL){  // find the end of the list
            temp = temp->next;
        }
        Node* newNode = new Node;
        newNode->key = shipment;
        newNode->next = NULL;
        temp->next = newNode;    // add node to Linked List
    }
}

// Function for displaying contents of Linked List
void LinkedList::displayList(){
    Node* temp = head;
    if(temp == NULL){
        cout << "List is empty!" << endl;
        return;
    }
    while(true){
        cout << temp->key << "->";
        temp = temp->next;
        if(temp == NULL) break;
    }
    cout << endl;
}

// helper function for recursively deleting LL
void deleteHelper(Node* head){
    if(head == NULL)
        return;
    deleteHelper(head->next);
    delete (head);
}

void LinkedList::deleteList(){
    cout << "Deleting Linked List!" << endl;
    deleteHelper(head);
    head = NULL;
}

// searches for the node containing shipment number 
Node* LinkedList::search(int shipment){
    if(head == NULL){  // check list is not empty
        cout << "List is empty!" << endl;
        return NULL;
    }
    else{
        Node* temp = head;
        while(true){
            // if node->key is shipment number return that node
            // else move to next node and check
            if(temp->key == shipment)  
                return temp;
            else if(temp->next == NULL && temp->key != shipment){
                cout << "Could not find: " << shipment << endl;
                return NULL;
            }
            temp = temp->next;  
        }
    }
}

// code used to make sure everything is working fine before moving on 

// int main(){
//     LinkedList LL;
//     for(int i = 0; i < 10; ++i){
//         LL.add(i);
//     }
//     LL.displayList();
//     Node* found = LL.search(8);
//     cout << found->key << endl;
//     LL.deleteList();
//     LL.displayList();
// }