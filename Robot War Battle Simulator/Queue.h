#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Queue {
private:
    vector<string> elements;

public:
    Queue();
    void push(const string& element);
    void pop();
    string front() const;
    bool empty() const;
    size_t size() const;
    vector<string>::iterator begin();
    vector<string>::iterator end();
};

#endif // QUEUE_H
