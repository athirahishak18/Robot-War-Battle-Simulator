#include "Queue.h"

Queue::Queue() {}


void Queue::push(const string& element)
{
    elements.push_back(element);
}

void Queue::pop()
{
    if (!empty())
    {
        elements.erase(elements.begin());
    }
}

string Queue::front() const
{
    if (!empty())
    {
        return elements.front();
    }
    return "";
}

bool Queue::empty() const
{
    return elements.empty();
}

size_t Queue::size() const
{
    return elements.size();
}

vector<string>::iterator Queue::begin()
{
    return elements.begin();
}

vector<string>::iterator Queue::end()
{
    return elements.end();
}
