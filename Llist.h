//
// Created by 党鸿博 on 2020-09-22.
//

#ifndef DATASTRUCTION_LLIST_H
#define DATASTRUCTION_LLIST_H

#include "Link.h"

struct listUnit {
    int vertex;
    double weight;
};

template <class Elem, class T>
class LList {
public:
    Link<Elem,T> * head;
    LList();
};

template <class Elem, class T>
LList<Elem, T> :: LList() {
    head = new Link<Elem,T>();
}


#endif //DATASTRUCTION_LLIST_H
