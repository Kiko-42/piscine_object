#include "Worker.hpp"
#include <algorithm>

void Worker::giveTool(Tool *tool)
{
    Worker *prev_user = tool->user;
    if (prev_user)
    {
        Tools &old = prev_user->tools;
        old.erase(std::remove(old.begin(), old.end(), tool), old.end());
    }
    tools.push_back(tool);
    tool->user = this;
}

