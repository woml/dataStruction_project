#include "graph.h"

#define INFINITY 1000000
#define UNVISITED -2

Graph :: Graph(int numVert) {
    numVertex = numVert;
    numEdge = 0;
    Indegree = new int[numVertex];
    Mark = new int[numVertex];
    for (int i = 0; i < numVertex; i++) {
        Mark[i] = UNVISITED;
        Indegree[i] = 0;
    }
}

Graph :: ~Graph() {
    delete [] Mark;
    delete [] Indegree;
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

int Graph :: Weight(Edge oneEdge) {
    return oneEdge.weight;
}

bool Graph ::isEdge(Edge oneEdge) {
    if(oneEdge.weight > 0 && oneEdge.weight < INFINITY && oneEdge.to >= 0) return true;
    else return false;
}
