//
// Created by 党鸿博 on 2020-09-22.
//

#ifndef DATASTRUCTION_EDGE_H
#define DATASTRUCTION_EDGE_H

class Edge {
public:
    int from, to;
    double  weight;
    Edge();
    Edge(int f, int t, double w);
};

Edge :: Edge() {
    from = to = -1;
    weight = 0.0;
}

Edge :: Edge(int f, int t, double w) {
    from = f;
    to = t;
    weight = w;
}

#endif //DATASTRUCTION_EDGE_H
