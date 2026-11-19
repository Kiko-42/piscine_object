#include "Graph_test.hpp"
#include "Graph.hpp"
#include "Vector2.hpp"
#include <limits>
#include <stdexcept>


void Graph_test::runGraphTest()
{
    testGraphSize();
    testGraphSizeZero();
    testGraphSizeNegative();
    testGraphSizeNaN();
    testGraphSizeOverMax();
    //testAddPoint();
    //testAddPoint();
}

static void expectInvalidSize(float x, float y)
{
    try {
        Graph g(Vector2(x, y));
    } catch (const std::invalid_argument&) {
        return;
    }
    throw std::runtime_error("size should be refused");
}

void Graph_test::testGraphSize()
{
    expectInvalidSize(1, 1);
    expectInvalidSize(6, 6);
    expectInvalidSize(10, 10);
}

void Graph_test::testGraphSizeZero()
{
    expectInvalidSize(0, 1);
    expectInvalidSize(1, 0);
    expectInvalidSize(0, 0);
}

void Graph_test::testGraphSizeNegative()
{
    expectInvalidSize(-1, 1);
    expectInvalidSize(1, -1);
    expectInvalidSize(-1, -1);
}

void Graph_test::testGraphSizeNaN()
{
    float nan = std::numeric_limits<float>::quiet_NaN();

    expectInvalidSize(nan, 1);
    expectInvalidSize(1, nan);
    expectInvalidSize(nan, nan);
}

void Graph_test::testGraphSizeOverMax()
{
    float inf = std::numeric_limits<float>::infinity();

    expectInvalidSize(inf, 1);
    expectInvalidSize(1, inf);
    expectInvalidSize(inf, inf);
}
