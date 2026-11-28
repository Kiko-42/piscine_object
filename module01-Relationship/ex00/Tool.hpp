#ifndef TOOL_HPP
#define TOOL_HPP

#include <stddef.h>

class Worker;

class Tool
{
public:
    Tool(): numberOfUses(0){};
    virtual ~Tool(){};

    virtual void use() = 0;
protected:
    Worker *user;
    size_t numberOfUses;
};

#endif
