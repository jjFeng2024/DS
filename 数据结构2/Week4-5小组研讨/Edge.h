// Edge.h：边的定义
#ifndef EDGE_H
#define EDGE_H

template <class WeightType>
struct Edge {
    int v1, v2;
    WeightType weight;
    Edge(int f = -1, int t = -1, WeightType w = 0) : v1(f), v2(t), weight(w) {}
};

#endif