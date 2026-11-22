#include "Graph.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

Graph::Graph(const Vector2& size) :size(size)
{
    if (!(this->size.x <= MAX_SIZE && this->size.x > 0 && this->size.y <= MAX_SIZE && this->size.y > 0))
    {
        throw std::invalid_argument("Error: size must be greater than 0 and at most MAX_SIZE");
    }
}

void Graph::addPoint(const Vector2& point)
{
    if (!(0 <= point.x && point.x <= size.x && 0 <= point.y && point.y <= size.y))
    {
        throw std::out_of_range("Error: point is outside the graph");
    }
    points.push_back(point);
}

static int digits(int n)
{
    int d = 1;
    while (n >= 10)
    {
        n /= 10;
        d++;
    }
    return d;
}

void Graph::print() const
{
    //convert float to Int to print on ASCII
    const int width = static_cast<int>(std::floor(size.x)) + 1;
    const int height = static_cast<int>(std::floor(size.y)) + 1;
    std::vector<std::vector<bool> > paper(height, std::vector<bool>(width, false));

    // store true where each point
    for (Points::const_iterator it=points.begin(); it!=points.end(); it++)
    {
        int x = static_cast<int>(std::floor(it->x));
        int y = static_cast<int>(std::floor(it->y));
        paper.at(y).at(x) = true;
    }

    const int yw = digits(height - 1);
    const int xw = digits(width - 1);
    for (int y=height-1; y>=0; y--)
    {
        std::ostringstream oss;
        oss << ">& " << std::setw(yw) << y;
        for (int x = 0; x < width; x++)
            oss << " " << std::setw(xw) << (paper[y][x] ? 'X' : '.');
        std::cout << oss.str() << std::endl;
    }
    std::ostringstream axis;
    axis << ">& " << std::setw(yw) << "";
    for (int x = 0; x < width; x++)
        axis << " " << std::setw(xw) << x;
    std::cout << axis.str() << std::endl;
}

