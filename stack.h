#ifndef STACK_H
#define STACK_H

#include "node.h"
#include <cstdio>

template <class T>
class Stack {
    private:
        Node <T> * topNode;
        int num;
    public:
        Stack();
        ~Stack();
        void push(const T it);
        bool pop();
        T top();
        bool isEmpty();
        void clear();
};

#endif