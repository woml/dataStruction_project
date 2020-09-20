#ifndef  NODE_H
#define  NODE_H

#include <cstdio>

template <class T>
class Node {
    public:
        T value;
        Node <T> * next;     
        Node(const T n, Node<T> * nextP = NULL);
};

#endif