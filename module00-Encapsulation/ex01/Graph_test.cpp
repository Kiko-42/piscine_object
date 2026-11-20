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
    testAddPoint();
    testAddPointOutOfRangeNegative();
    testAddPointNaN();
    testAddPointOutOfRangeMaxSize();
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

static void expectValidAddPoint(float x, float y)
{
    Graph g(Vector2(Graph::MAX_SIZE, Graph::MAX_SIZE));
    try {
        g.addPoint(Vector2(x, y));
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("size should not be refused");
    }
}

static void expectInvalidAddPoint(float x, float y)
{
    Graph g(Vector2(Graph::MAX_SIZE, Graph::MAX_SIZE));
    try {
        g.addPoint(Vector2(x, y));
    } catch (const std::invalid_argument&) {
        return;
    }
    throw std::runtime_error("size should be refused");
}

void Graph_test::testGraphSize()
{
    Graph a(Vector2(1, 1));
    Graph b(Vector2(6, 6));
    Graph c(Vector2(Graph::MAX_SIZE, Graph::MAX_SIZE));
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

void Graph_test::testAddPoint()
{
    expectValidAddPoint(0, 0);
    expectValidAddPoint(6, 6);
    expectValidAddPoint(Graph::MAX_SIZE-1, Graph::MAX_SIZE-1);
}

void Graph_test::testAddPointOutOfRangeNegative()
{
    expectInvalidAddPoint(-1, 1);
    expectInvalidAddPoint(1, -1);
    expectInvalidAddPoint(-1, -1);
}

void Graph_test::testAddPointNaN()
{
    float nan = std::numeric_limits<float>::quiet_NaN();

    expectInvalidAddPoint(nan, 1);
    expectInvalidAddPoint(1, nan);
    expectInvalidAddPoint(nan, nan);
}

void Graph_test::testAddPointOutOfRangeMaxSize()
{
    float inf = std::numeric_limits<float>::infinity();

    expectInvalidAddPoint(inf, 1);
    expectInvalidAddPoint(1, inf);
    expectInvalidAddPoint(inf, inf);
}


