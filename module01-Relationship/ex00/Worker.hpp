#ifndef WORKER_HPP
#define WORKER_HPP

#include "Tool.hpp"
#include <vector>

class Worker
{
public:
    Worker(): coordonnee(), stat(){};

private:
    struct Position
    {
        int x, y, z;
    };
    struct Statistic
    {
        int level;
        int exp;
    };

    Position coordonnee;
    Statistic stat;

    std::vector<Tool *> tools; 
};

#endif

