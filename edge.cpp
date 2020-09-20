#include "edge.h"

Edge :: Edge() {
    from = to = -1;
    weight = 0;
}

Edge :: Edge(int f, int t, int w) {
    from = f;
    to = t;
    weight = w;
}