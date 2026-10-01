#pragma once
#include <string>

class Character
{
protected:
    std::string name;
    int hp;
    int maxhp;
    int attack;
    int defense;
    int level;

public:
    Character(std::string gname,int ghp, int gmaxHp, int gattack, int gdefense);
    std::string getname();
    int gethp();
    int getattack();
    void takedamage(int damage);
    int getdefense();
    int getmaxhp();
    bool isDead();
};