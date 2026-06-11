#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

    // Destructor to clean up memory
    LinkedList::~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Method to add a node to the end of the list
    void LinkedList::addNode(string type, string id, int x, int y) {
        Node* newNode = new Node(type, id, x, y);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Method to print all nodes in the list
    void LinkedList::printList()
    {
        Node* current = head;
        cout << "LinkedList:" << endl;
        while (current) {
            cout << "Robot " << current->robotType << " " << current->robotID << " at (" << current->posX << "," << current->posY << ")" << endl;
            current = current->next;
        }
    }
