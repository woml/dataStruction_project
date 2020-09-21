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
        T VisitNode(int i);
};

#endif