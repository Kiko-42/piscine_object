#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Vector2.hpp"
#include <vector>

class Graph
{
public:
    Graph(const Vector2& size);
    void addPoint(Vector2& point);
    void print() const;
private:
    static const int MAX_SIZE = 10;
    Graph(const Graph&);
    const Vector2 size;
    std::vector<Vector2> points;
};
#endif
