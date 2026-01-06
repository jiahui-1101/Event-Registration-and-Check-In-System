#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

template <typename T>
class Queue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &d) : data(d), next(NULL) {}
    };

    Node *frontPtr;
    Node *rearPtr;
    int count;

public:
    // Constructor
    Queue()
    {
        frontPtr = NULL;
        rearPtr = NULL;
        count = 0;
    }

    // Destructor
    ~Queue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }

    // Check if queue is empty
    bool isEmpty() const
    {
        return frontPtr == NULL;
    }

    // Return size of queue
    int size() const
    {
        return count;
    }

    // Enqueue (add to rear)
    void enqueue(const T &item)
    {
        Node *newNode = new Node(item);

        if (isEmpty())
        {
            frontPtr = rearPtr = newNode;
        }
        else
        {
            rearPtr->next = newNode;
            rearPtr = newNode;
        }
        count++;
    }

    // Dequeue (remove from front)
    bool dequeue()
    {
        if (isEmpty())
            return false;

        Node *temp = frontPtr;
        frontPtr = frontPtr->next;
        delete temp;
        count--;

        if (frontPtr == NULL)
        {
            rearPtr = NULL;
        }
        return true;
    }

    // Get front element without removing
    bool front(T &out) const
    {
        if (isEmpty())
            return false;
        out = frontPtr->data;
        return true;
    }
};

#endif