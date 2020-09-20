#ifndef LINK_H
#define LINK_H

#include <cstdio>

template <class Elem, class T>
class Link {
    private:
        T LinkValue;
    public:
        Elem element;
        Link * next;
        Link(const Elem & elemval, Link * nextval = NULL);
        Link(Link * nextval = NULL);
        void SetLinkValue(T v);
        T VisitValue();
};

#endif 