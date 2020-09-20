#include "llist.h"

template <class Elem, class T>
LList<Elem, T> :: LList() {
    head = new Link<Elem,T>();
}
