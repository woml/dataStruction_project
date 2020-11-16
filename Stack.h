//
// Created by 党鸿博 on 2020-09-22.
//

#ifndef DATASTRUCTION_STACK_H
#define DATASTRUCTION_STACK_H

#include "Node.h"

template <class T>
class Stack {
private:
    Node <T> * topNode;
    int num;
public:
    Stack();
    ~Stack();
    void push(T it);
    bool pop();
    T top();
    bool isEmpty();
    void clear();
};

template <class T>
Stack<T> :: Stack() {
    num = 0;
    topNode = NULL;
}

template <class T>
Stack<T> :: ~Stack() {
    clear();
}

template <class T>
void Stack<T> :: push(const T it) {
    auto * tep = new Node<T>(it,topNode);
    topNode = tep;
    num++;
}

template <class T>
bool Stack<T> :: pop() {
    Node <T> * tep;
    if(num == 0) return false;
    num--;
    tep = topNode;
    topNode = topNode->next;
    delete tep;

    return true;
}

template <class T>
T Stack<T> :: top() {
    return topNode->value;
}

template <class T>
bool Stack<T> :: isEmpty() {
    return num == 0;
}

template <class T>
void Stack<T> :: clear() {
    Node <T> * tmp;
    while(topNode != NULL) {
        tmp = topNode;
        topNode = topNode->next;
        delete tmp;
    }
    num = 0;
}

#endif //DATASTRUCTION_STACK_H
