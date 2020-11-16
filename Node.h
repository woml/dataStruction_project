//
// Created by 党鸿博 on 2020-09-22.
//

#ifndef DATASTRUCTION_NODE_H
#define DATASTRUCTION_NODE_H

template <class T>
class Node {
public:
    T value;
    Node <T> * next;
    Node(T n, Node<T> * nextP = NULL);
};

template <class T>
Node<T> :: Node(const T n, Node<T> * nextP) {
    value = n;
    next = nextP;
}

#endif //DATASTRUCTION_NODE_H
