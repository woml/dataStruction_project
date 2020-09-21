#include "link.h"

template <class Elem, class T>
Link<Elem, T> :: Link(const Elem & elemval, Link * nextval = NULL) {
    element = elemval;
    next = nextval;
    bool tranfer = NULL;
    int transfer_num = 0;
}
template <class Elem, class T>
Link<Elem, T> :: Link(Link * nextval = NULL) {
    next = nextval;
    bool tranfer = NULL;
    int transfer_num = 0;
}

template <class Elem, class T>
void Link<Elem, T> :: SetLinkValue(T v, T n) {
    LinkValue = v;
    LinkValue2[0] = n;
}

template <class Elem, class T>
void Link<Elem, T> :: SetLinkValue(T v, T n, int ) {      //重载
    LinkValue = v;
    LinkValue2[0] = n;
}

template <class Elem, class T>
T Link<Elem, T> :: VisitValue() {
    return LinkValue;
}