#include <cstdio>
#include "node.h"

template <class T>
Node<T> :: Node(const T n, Node<T> * nextP = NULL) {
    value = n;
    next = nextP;
}
