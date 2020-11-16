//
// Created by 党鸿博 on 2020-09-22.
//

#ifndef DATASTRUCTION_LINK_H
#define DATASTRUCTION_LINK_H

#include <cstdio>

template <class Elem, class T>
class Link {
private:
    T LinkValue;                //站点的名称
    int * LinkValue2;          //属于几号线
    bool transfer;
public:
    Elem element;
    Link * next;
    Link(const Elem & elemval, Link * nextval = NULL);
    Link(Link * nextval = NULL);
    void SetLinkValue(T v, int n);                      //非换乘站设置结点函数
    void SetLinkValue(int n, int a, int b);               //换乘站设置结点函数
    void SetLinkValue(int n, int a, int b, int c);        //换乘站设置结点函数
    T visit_Link_Value();                               //访问此结点的站点名称
    bool isTransfer();                                  //返回是不是换乘车站 是->true 否->false
    T VisitValue();                                     //返回站点名字
};

template <class Elem, class T>
Link<Elem, T> :: Link(const Elem & elemval, Link * nextval) {
    element = elemval;
    next = nextval;
    bool transfer = false;                            //初始化 不是换乘站
    int transfer_num = 0;                           //初始化可换乘数量为0
    LinkValue2 = new int[5];
    for (int i = 0; i < 5; i++) LinkValue2[i] = -1;
}
template <class Elem, class T>
Link<Elem, T> :: Link(Link * nextval) {
    next = nextval;
    bool transfer = false;                            //初始化 不是换乘站
    int transfer_num = 0;                           //初始化可换乘数量为0
    LinkValue2 = new int[5];
    for (int i = 0; i < 5; i++) LinkValue2[i] = -1;
}

template <class Elem, class T>
void Link<Elem, T> :: SetLinkValue(T v, int n) {
    LinkValue = v;
    LinkValue2[0] = n;
}

template <class Elem, class T>
void Link<Elem, T> :: SetLinkValue(int n, int a, int b) {      //重载 可以换乘两站函数
    LinkValue2[0] = a;
    LinkValue2[1] = b;
    transfer = true;
}

template<class Elem, class T>
void Link<Elem, T> :: SetLinkValue(int n, int a, int b, int c) {      //重载 可以换乘三站函数
    LinkValue2[0] = a;
    LinkValue2[1] = b;
    LinkValue2[2] = c;
    transfer = true;
}


template <class Elem, class T>
bool Link<Elem, T> :: isTransfer() {
    return transfer;
}

template <class Elem, class T>
T Link<Elem, T> :: visit_Link_Value() {
    return LinkValue;
}


template <class Elem, class T>
T Link<Elem, T> :: VisitValue() {
    return LinkValue;
}



#endif //DATASTRUCTION_LINK_H
