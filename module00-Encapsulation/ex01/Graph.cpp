#include "Graph.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

Graph::Graph(const Vector2& size) :size(size)
{
    if (!(size.x <= MAX_SIZE && size.x > 0 && size.y <= MAX_SIZE && size.y > 0))
    {
        throw std::invalid_argument(""); //OutOfRange?
    }
}
void Graph::addPoint(const Vector2& point)
{
    if (!(0 <= point.x && point.x < MAX_SIZE && 0 <= point.y && point.y < MAX_SIZE))
    {
        throw std::out_of_range(""); //OutOfRange?
    }
    points.push_back(point);
}

void Graph::print() const
{
    int width  = static_cast<int>(std::floor(size.x + 0.5f));
    int height = static_cast<int>(std::floor(size.y + 0.5f));
    std::vector<std::vector<bool> > paper(height, std::vector<bool>(width, false));
    //lookpu points and store 四捨五入した値
    for (Points::const_iterator it=points.begin();it!=points.end();it++)
    {
        int x = std::floor(it->x);
        int y = std::floor(it->y);
        paper[y][x] = true;
    }
    // output each y line
    for (int y=size.y-1;y>=0;y--)
    {
        std::ostringstream oss;
        for (int x=0;x<size.x;x++)
        {
            if (paper[y][x])
            {
                oss << "X";
                continue;
            }
            oss << ".";
         }
         std::cout << oss.str() << std::endl;
    }
}

