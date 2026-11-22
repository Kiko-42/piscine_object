#include "Graph.hpp"
#include "Graph_test.hpp"
#include <exception>
#include <iostream>

int main()
{
    // Demo
    try {
        Graph g(Vector2(5, 5));
        g.addPoint(Vector2(0, 0));
        g.addPoint(Vector2(2, 2));
        g.addPoint(Vector2(4, 2));
        g.addPoint(Vector2(2, 4));
        g.print();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    //Test Runner
    try {
        Graph_test::runGraphTest();
    } catch (const std::exception& e) {
        std::cout << "Unit Test Error: " << e.what() << std::endl;
    }

    return 0;
}
