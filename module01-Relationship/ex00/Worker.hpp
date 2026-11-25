#ifndef WORKER_HPP
#define WORKER_HPP

class Worker
{
public:
    Worker(): coordonnee(), stat(){};
private:
    class Position
    {
        int x, y, z;
    };
    class Statistic
    {
        int level;
        int exp; //Positionのx,y,zの定義と同じように１行で書くべきか？でもPositionのx,y,zは変数として三位一体感が強いが、statisticに対してのlevel, expは一体感が薄いから別で定義するほうがいいのではないかと感じた。変数定義を１行で書くべきかどうかの基準についてC++の正しい基準や考え方を知りたい
    };

    Position coordonnee;
    Statistic stat;
};

#endif

