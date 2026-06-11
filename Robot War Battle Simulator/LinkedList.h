#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>


using namespace std;

// Define a Node structure for the linked list
struct Node {
    string robotType;
    string robotID;
    int posX;
    int posY;
    Node* next;

    // Constructor to initialize the node
    Node(string type, string id, int x, int y) : robotType(type), robotID(id), posX(x), posY(y), next(nullptr) {}
};

// Define a LinkedList class to manage the nodes
class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    // Constructor to initialize an empty list
    LinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor to clean up memory
    ~LinkedList();

    // Method to add a node to the end of the list
    void addNode(string type, string id, int x, int y);

    // Method to print all nodes in the list
    void printList();
};

#endif // LINKEDLIST_H
