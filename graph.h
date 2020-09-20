#ifndef GRAPH_H
#define GRAPH_H

#include "edge.h"

class Graph {
    public:
        int numVertex;
        int numEdge;
        int * Mark;
        int * Indegree;
        Graph(int numVert);
        ~Graph();
        int VerticesNum();
        int EdgesNum();
        Edge FirstEdge(int oneVertex);
        Edge NextEdge(Edge preEdge);
        bool setEdge(int fromVertex, int toVertex);
        bool delEdge(int fromVertex, int tovertex);
        bool isEdge(Edge oneEdge);
        int FromVertex(Edge oneEdge);
        int ToVertex(Edge oneEdge);
        int Weight(Edge oneEdge);
};

#endif