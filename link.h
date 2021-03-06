#ifndef LINK_H
#define LINK_H

#include <cstdio>

template <class Elem, class T>
class Link {
    private:
        T LinkValue;            //站点的名称
        T LinkValue2[5];        //属于几号线
        bool tranfer;
        int transfer_num;
    public:
        Elem element;
        Link * next;
        Link(const Elem & elemval, Link * nextval = NULL);
        Link(Link * nextval = NULL);
        void SetLinkValue(T v, T n);            //非换乘站设置结点函数
        void SetLinkValue(T v, T n, int i);     //换乘站设置结点函数
        int transfer_Num();                     //若是换乘车站，返回之前一共设置了多少站 若不是 返回0
        T visit_Link_Value();                   //访问此结点的站点名称
        bool isTransfer();                      //返回是不是换乘车站 是->true 否->false
        T VisitValue();                         
};

#endif 