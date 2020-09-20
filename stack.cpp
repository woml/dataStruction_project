#include "stack.h"


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
    Node <T> * tep = new Node<T>(it,topNode);
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
    if(num == 0) return true;
    return false;
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