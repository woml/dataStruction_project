#include "link.h"

template <class Elem, class T>
Link<Elem, T> :: Link(const Elem & elemval, Link * nextval = NULL) {
    element = elemval;
    next = nextval;
}
template <class Elem, class T>
Link<Elem, T> :: Link(Link * nextval = NULL) {
    next = nextval;
}

template <class Elem, class T>
void Link<Elem, T> :: SetLinkValue(T v) {
    LinkValue = v;
}

template <class Elem, class T>
T Link<Elem, T> :: VisitValue() {
    return LinkValue;
}