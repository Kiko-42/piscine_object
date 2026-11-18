#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Vector2.hpp"
#include <vector>

class Graph
{
public:
    Graph(Vector2 size);
    void addPoint(Vector2);
    void print() const;
private:
    Graph(const Graph&);
    Graph& operator=(const Graph&);
    const Vector2 size;
    std::vector<Vector2> points;
};
#endif
