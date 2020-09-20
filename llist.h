#ifndef LLIST_H
#define LLIST_H

#include "link.h"

template <class Elem, class T>
class LList {
    public:
        Link<Elem,T> * head;
        LList();
};

struct listUnit {
    int vertex;
    int weight;
};


#endif