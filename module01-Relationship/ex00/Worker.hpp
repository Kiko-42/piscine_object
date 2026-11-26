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

    //TODO: Toolのリファレンスをもたせた方がシンプルに扱えそうだと思ってTool &をvectorに持たせようとしたらエラーになった。なんでだろう.エラーメッセージ見る感じ、vectorのテンプレート的にpointerしか入れれない?
    std::vector<Tool &> tools; 
};

#endif

