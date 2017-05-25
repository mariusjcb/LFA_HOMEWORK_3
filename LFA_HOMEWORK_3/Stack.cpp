//
//  Stack.cpp
//  LFA_HOMEWORK_3
//
//  Created by Marius Ilie on 17/05/17.
//  Copyright © 2017 Marius Ilie. All rights reserved.
//

#include "Stack.hpp"

template <class T>
Stack<T>::Stack()
{
    top = NULL;
}

template <class T>
Stack<T>::~Stack()
{
    StackNode *nodePtr, *nextNode;
    // position nodePtr at the top of the stack
    nodePtr = top;
    // traverse the list deleting each node
    while (nodePtr != NULL)
    {
        nextNode = nodePtr->next;
        delete nodePtr;
        nodePtr = nextNode;
    }
}

template <class T>
void Stack<T>::push(T item)
{
    StackNode *newNode; // pointer to a new node
    // allocate a new node and store num there.
    newNode = new StackNode;
    newNode->Value = item;
    // if there are no nodes in the list
    // make newNode the first node.
    if (isEmpty())
    {
        top = newNode;
        newNode->next = NULL;
    }
    else // otherwise, insert NewNode before top
    {
        newNode->next = top;
        top = newNode;
    }
}

template <class T>
bool Stack<T>::pop(T &item)
{
    StackNode *temp; // temporary pointer
    // first make sure the stack isn't empty
    if (isEmpty())
    {
        return false;
    }
    else // pop value off top of the stack
    {
        item = top->Value;
        temp = top->next;
        delete top;
        top = temp;
        return true;
    }
}

template <class T>
bool Stack<T>::isEmpty()
{
    bool status;
    if (!top)
    {
        status = true;
    }
    else
    {
        status = false;
    }
    return status;
}

template<class T>
T Stack<T>::getTop()
{
    return top->Value;
}
