#ifndef WORKER_HPP
#define WORKER_HPP

#include "Tool.hpp"
#include <vector>

typedef std::vector<Tool *> Tools;

class Worker
{
public:
    Worker(): coordonnee(), stat(){};

    void giveTool(Tool *tool);

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

    Tools tools;
};

#endif

