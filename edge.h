#ifndef EDGE_H
#define EDGE_H

class Edge {
    public:
        int from, to, weight;
        Edge();
        Edge(int f, int t, int w);
};

#endif