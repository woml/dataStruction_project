#include "link.h"

template <class Elem, class T>
Link<Elem, T> :: Link(const Elem & elemval, Link * nextval = NULL) {
    element = elemval;
    next = nextval;
    bool tranfer = NULL;                            //初始化 不是换乘站
    int transfer_num = 0;                           //初始化可换乘数量为0
}
template <class Elem, class T>
Link<Elem, T> :: Link(Link * nextval = NULL) {
    next = nextval;
    bool tranfer = NULL;                            //初始化 不是换乘站
    int transfer_num = 0;                           //初始化可换乘数量为0
}

template <class Elem, class T>
void Link<Elem, T> :: SetLinkValue(T v, T n) {
    LinkValue = v;
    LinkValue2[0] = n;
}

template <class Elem, class T>
void Link<Elem, T> :: SetLinkValue(T v, T n, int i) {      //重载
    LinkValue = v;
    LinkValue2[i+1] = n;
}

template <class Elem, class T>
int Link<Elem, T> :: transfer_Num() {
    return transfer_num;
}

template <class Elem, class T>
bool Link<Elem, T> :: isTransfer() {
    return tranfer;
}

template <class Elem, class T>
T Link<Elem, T> :: visit_Link_Value() {
    return LinkValue;
}


template <class Elem, class T>
T Link<Elem, T> :: VisitValue() {
    return LinkValue;
}