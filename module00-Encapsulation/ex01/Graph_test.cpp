#include "Graph_test.hpp"
#include "Graph.hpp"
#include "Vector2.hpp"
#include <iostream>
#include <limits>
#include <sstream>
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
    testPrintFractionalSize();
}

static void expectInvalidSize(float x, float y)
{
    try {
        Graph g(Vector2(x, y));
    } catch (const std::invalid_argument&) {
        return;
    }
    throw std::runtime_error("constructor: size should be refused");
}

static void expectValidAddPoint(float x, float y)
{
    Graph g(Vector2(Graph::MAX_SIZE, Graph::MAX_SIZE));
    try {
        g.addPoint(Vector2(x, y));
    } catch (const std::out_of_range&) {
        throw std::runtime_error("addPoint(): this point should not be refused");
    }
}

static void expectInvalidAddPoint(float x, float y)
{
    Graph g(Vector2(Graph::MAX_SIZE, Graph::MAX_SIZE));
    try {
        g.addPoint(Vector2(x, y));
    } catch (const std::out_of_range&) {
        return;
    }
    throw std::runtime_error("addPoint(): this point should be refused");
}

void Graph_test::testGraphSize()
{
    Graph d(Vector2(0.4f, 0.4f));
    Graph a(Vector2(1, 1));
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

    expectInvalidSize(Graph::MAX_SIZE + 0.5f, 1);
}

void Graph_test::testAddPoint()
{
    expectValidAddPoint(0, 0);
    expectValidAddPoint(0.5f, 0.5f);
    expectValidAddPoint(1, 1);
    expectValidAddPoint(Graph::MAX_SIZE, Graph::MAX_SIZE);
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

    expectInvalidAddPoint(Graph::MAX_SIZE + 0.1f, 0);
}

static void expectPrintable(float sizeX, float sizeY, float x, float y)
{
    Graph g(Vector2(sizeX, sizeY));
    g.addPoint(Vector2(x, y));

    std::ostringstream sink;
    std::streambuf* old = std::cout.rdbuf(sink.rdbuf());
    try {
        g.print();
    } catch (...) {
        std::cout.rdbuf(old);
        throw std::runtime_error("print(): accepted point should be printable");
    }
    std::cout.rdbuf(old);
}

void Graph_test::testPrintFractionalSize()
{
    expectPrintable(2.4f, 2.4f, 2.4f, 2.4f);
    expectPrintable(0.4f, 0.4f, 0.4f, 0.4f);
    expectPrintable(2.5f, 2.5f, 1.5f, 1.5f);
    expectPrintable(2.5f, 2.5f, 0, 0);
    expectPrintable(Graph::MAX_SIZE, Graph::MAX_SIZE,Graph::MAX_SIZE, Graph::MAX_SIZE);
}

