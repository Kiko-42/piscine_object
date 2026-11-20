#include "Graph.hpp"
#include "Graph_test.hpp"

int main()
{
    Graph g(Vector2(10,10));

    g.addPoint(Vector2(1,1));

    g.print();

    return 0;
}
