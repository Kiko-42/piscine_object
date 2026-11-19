#include "Graph.hpp"
#include <stdexcept>

Graph::Graph(const Vector2& size) :size(size) 
{
    if (!(size.x > 0 && size.x <= MAX_SIZE && size.y > 0 && size.y <= MAX_SIZE))
    {
        throw std::invalid_argument("");
    }
}

void Graph::addPoint(Vector2& point)
{
    if (!(point.x >= 0 && point.x <= MAX_SIZE - 1 && point.y >= 0 && point.y <= MAX_SIZE - 1))
    {
        throw std::out_of_range("");
    }
    points.push_back(point);
}

void Graph::print() const
{
    // MAX_SIZEのboolの2次元配列paperを作る : O(N^2)
    // for文でpointsを1つ1つ探索し四捨五入しつつ、paper[y][x]にtrueを置く : O(N)

    // paperを1つ1つ見ていき、osstreamに追加する : O(N)
    // 出力する
}
