#include "Graph.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

Graph::Graph(const Vector2& size) :size(size)
{
    if (!(this->size.x <= MAX_SIZE && this->size.x > 0 && this->size.y <= MAX_SIZE && this->size.y > 0))
    {
        throw std::invalid_argument("hoge"); //OutOfRange?
    }
}

void Graph::addPoint(const Vector2& point)
{
    if (!(0 <= point.x && point.x < size.x && 0 <= point.y && point.y < size.y))
    {
        throw std::out_of_range("hogehoge");
    }
    points.push_back(point);
}

void Graph::print() const
{
    //convert float to Int to print on ASCII
    const int width = std::ceil(size.x);
    const int height = std::ceil(size.y);
    std::vector<std::vector<bool> > paper(height, std::vector<bool>(width, false));
    for (Points::const_iterator it=points.begin(); it!=points.end(); it++)
    {
        int x = std::floor(it->x);
        int y = std::floor(it->y);
        paper.at(y).at(x) = true;
    }

    for (int y=height-1; y>=0; y--)
    {
        std::ostringstream oss;
        oss << ">& " << y;

        for (int x=0; x<width; x++)
        {
            if (paper[y][x])
            {
                oss << " X";
                continue;
            }
            oss << " .";
        }
        std::cout << oss.str() << std::endl;
    }
    std::ostringstream axis;
    axis << ">&  ";
    for (int x = 0; x < width; x++)
        axis << " " << x;
    std::cout << axis.str() << std::endl;
}

