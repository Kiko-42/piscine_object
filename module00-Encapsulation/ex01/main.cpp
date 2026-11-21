#include "Graph.hpp"
#include "Graph_test.hpp"
#include <exception>
#include <iostream>

int main()
{
    // Demo
    try {
        Graph g(Vector2(10,10));
        g.addPoint(Vector2(1,1));
        g.print();
    } catch (const std::exception& e) {
        std::cout << "Demo Error: " << e.what() << std::endl;
    }

    //Test Runner
    try {
        Graph_test::runGraphTest();
    } catch (const std::exception& e) {
        std::cout << "Unit Test Error: " << e.what() << std::endl;
    }

    return 0;
}
