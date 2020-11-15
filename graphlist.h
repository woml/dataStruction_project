#ifndef GRAPHIST_H
#define GRAPHIST_H

#include "graph.h"
#include "llist.h"

template <class T>
class GraphList : public Graph {
    private:
        LList <listUnit,T> * graList;
    public:
        GraphList(int numVert);
        Edge FirstEdge(int oneVertex);
        Edge NextEdge(Edge preEdge);
        void setEdge(int from, int to, int weight);
        void delEdge(int from, int to);
        void SetNode(int i, T v, T n);
        bool is_Station_Repeat(int n, T s);                     //判断此结点是否已经在编号中了，如果已经在编号中，则不重复添加
        T VisitNode(int i);
};

#endif