//
// Created by 党鸿博 on 2020-09-22.
//

#ifndef DATASTRUCTION_GRAPH_H
#define DATASTRUCTION_GRAPH_H

#include "Edge.h"

#define INFINITY1 1000000
#define UNVISITED -2

class Graph {
public:
    int numVertex;
    int numEdge;
    int * Mark;
    int * inDegree;
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
    double Weight(Edge oneEdge);
};

Graph :: Graph(int numVert) {
    numVertex = numVert;
    numEdge = 0;
    inDegree = new int[numVertex];
    Mark = new int[numVertex];
    for (int i = 0; i < numVertex; i++) {
        Mark[i] = UNVISITED;
        inDegree[i] = 0;
    }
}

Graph :: ~Graph() {
    delete [] Mark;
    delete [] inDegree;
}

int Graph :: VerticesNum() {
    return numVertex;
}

int Graph :: EdgesNum() {
    return numEdge;
}

int Graph :: FromVertex(Edge oneEdge) {
    return oneEdge.from;
}

int Graph :: ToVertex(Edge oneEdge) {
    return oneEdge.to;
}

double Graph :: Weight(Edge oneEdge) {
    return oneEdge.weight;
}

bool Graph ::isEdge(Edge oneEdge) {
    if(oneEdge.weight > 0.0 && oneEdge.weight < INFINITY1 && oneEdge.to >= 0) return true;
    else return false;
}

#endif //DATASTRUCTION_GRAPH_H
