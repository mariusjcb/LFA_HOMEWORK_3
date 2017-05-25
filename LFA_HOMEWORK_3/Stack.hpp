//
//  Stack.hpp
//  LFA_HOMEWORK_3
//
//  Created by Marius Ilie on 17/05/17.
//  Copyright © 2017 Marius Ilie. All rights reserved.
//

#ifndef Stack_hpp
#define Stack_hpp

#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
    // structre for the stack node
    struct StackNode
    {
        T Value; // value in the node
        StackNode *next; // pointer to the next node
    };
    StackNode * top; // pointer to the stack top
public:
    // constuctor
    Stack();
    ~Stack();
    // stack operations
    void push(T);
    bool pop(T &);
    bool isEmpty();
    T getTop();
};

#endif /* Stack_hpp */
