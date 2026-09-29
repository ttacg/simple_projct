#pragma once

class Character
{
protected:

    int hp;
    int maxhp;
    int attack;
    int defense;
    int level;
public:
    Character(int ghp, int gmaxHp, int gattack, int gdefense);
    int gethp();
    int getattack();
    void takedamage(int damage);
    int getdefense();
    int getmaxhp();
    bool isDead();
};