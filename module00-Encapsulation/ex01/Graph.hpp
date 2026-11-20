#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Vector2.hpp"
#include <vector>

class Graph
{
public:
    typedef std::vector<Vector2> Points;

    static const int MAX_SIZE = 10;

    Graph(const Vector2& size);
    void addPoint(const Vector2& point);
    void print() const;
private:
    Graph(const Graph&);
    const Vector2 size;
    Points points;
};
#endif
