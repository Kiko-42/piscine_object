#ifndef GRAPH_TEST_HPP
#define GRAPH_TEST_HPP

class Graph_test
{
public:
    static void runGraphTest();
private:
    static void testGraphSize();
    static void testGraphSizeZero();
    static void testGraphSizeNegative();
    static void testGraphSizeNaN();
    static void testGraphSizeOverMax();
    static void testAddPoint();
};
#endif
