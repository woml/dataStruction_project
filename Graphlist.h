//
// Created by 党鸿博 on 2020-09-22.
//

#ifndef DATASTRUCTION_GRAPHLIST_H
#define DATASTRUCTION_GRAPHLIST_H

#include "Llist.h"
#include "Graph.h"

template <class T>
class GraphList : public Graph {
private:
    LList <listUnit,T> * graList;
public:
    GraphList(int numVert);
    Edge FirstEdge(int oneVertex);
    Edge NextEdge(Edge preEdge);
    void setEdge(int from, int to, double weight);
    void delEdge(int from, int to);
    void SetNode(int i, T v, int n);
    void SetNode(int i, int n, int a, int b);               //重载，n为可换乘总数，a,b为可换乘线路编号
    void SetNode(int i, int n, int a, int b, int c);        //重载，n为可换乘总数，a,b,c为可换乘线路编号
    void SetNumVertex(int i);                               //设置结点数的总数
    bool is_Station_Repeat(int n, T s);                     //判断此结点是否已经在编号中了，如果已经在编号中，则不重复添加
    int node_rank_ret(T s, int n);                          //返回名称为s的站点的编号，n是所有站总数
    T VisitNode(int i);
};
template <class T>
GraphList<T> :: GraphList(int numVert):Graph(numVert) {
    graList = new LList <listUnit,T>[numVertex];
}

template <class T>
Edge GraphList<T> :: FirstEdge(int oneVertex) {
    Edge myEdge;
    myEdge.from = oneVertex;
    Link<listUnit,T> * temp = graList[oneVertex].head;
    if(temp->next != NULL) {
        myEdge.to = temp->next->element.vertex;
        myEdge.weight = temp->next->element.weight;
    }
    return myEdge;
}

template <class T>
Edge GraphList<T> :: NextEdge(Edge preEdge) {
    Edge myEdge;
    myEdge.from = preEdge.from;
    Link <listUnit,T> * temp = graList[preEdge.from].head;
    while(temp->next != NULL && temp->next->element.vertex <= preEdge.to) {
        temp = temp->next;
    }
    if(temp->next != NULL) {
        myEdge.to = temp->next->element.vertex;
        myEdge.weight = temp->next->element.weight;
    }
    return myEdge;
}

template <class T>
void GraphList<T> :: setEdge(int from, int to, double weight) {
    Link<listUnit,T> * temp = graList[from].head;
    while(temp->next != NULL && temp->next->element.vertex < to) {
        temp = temp->next;
    }
    if(temp->next == NULL) {
        temp->next = new Link<listUnit,T>();
        temp->next->element.vertex = to;
        temp->next->element.weight = weight;
        numEdge++;
        inDegree[to]++;
        return;
    }
    if(temp->next->element.vertex == to) {                                  //不是新增加边 而是将原有的边改值
        temp->next->element.weight = weight;
        return;
    }
    if(temp->next->element.vertex > to) {                                   //此时也是新加边，但是为了边按编号从小到大的顺序，所以要插在中间
        Link<listUnit,T> * other = temp->next;
        temp->next = new Link<listUnit,T>;
        temp->next->element.vertex = to;
        temp->next->element.weight = weight;
        temp->next->next = other;
        numEdge++;
        inDegree[to]++;
        return;
    }
}

template <class T>
void GraphList<T> :: delEdge(int from, int to) {
    Link<listUnit,T> * temp = graList[from].head;
    while(temp->next != NULL && temp->next->element.vertex < to) {
        temp = temp->next;
    }
    if(temp->next == NULL) return;
    if(temp->next->element.vertex > to) return;
    if(temp->next->element.vertex == to) {
        Link<listUnit,T> * other = temp->next->next;
        delete temp->next;
        temp->next = other;
        numEdge--;
        inDegree[to]--;
        return;
    }
}

template <class T>
void GraphList<T> :: SetNode(int i, T v, int n) {
    graList[i].head->SetLinkValue(v, n);

}

template <class T>
void GraphList<T> :: SetNode(int i, int n, int a, int b) {          // i是编号为i的站点  n是可换乘总数 a、b是可换乘线路名称
    graList[i].head->SetLinkValue(n,a,b);
}

template <class T>
void GraphList<T> :: SetNode(int i, int n, int a, int b, int c) {   //重载，i是编号为i的站点，n为可换乘总数，a,b,c为可换乘线路编号
    graList[i].head->SetLinkValue(n,a,b,c);
}

template<class T>
void GraphList<T> :: SetNumVertex(int i) {
    numVertex = i;
}

template <class T>
bool GraphList<T> :: is_Station_Repeat(int n, T s) {
    for (int i = 0; i < n; i++) {
        if(graList[i].head->visit_Link_Value() == s) return true;        //访问编号为i的站点的名称 和 此时要输入的站点名称比较 如果相同 则返回有重复=true
    }
    return false;   //没有重复
}

template <class T>
int GraphList<T> :: node_rank_ret(T s, int n) {                          //返回名称为s的站点的编号，n是所有站总数
    for (int i = 0; i < n; i++) {
        std :: string a = graList[i].head->visit_Link_Value();
        if(graList[i].head->visit_Link_Value() == s) {
            return i;           //访问编号为i的站点的名称 和 此时要输入的站点名称比较 如果相同 则返回有重复=true
        }
    }
    return -1;                                                          //没有找到 即不存在该名称的结点
}

template <class T>
T GraphList<T> ::  VisitNode(int i) {
    return graList[i].head->VisitValue();
}


#endif //DATASTRUCTION_GRAPHLIST_H
