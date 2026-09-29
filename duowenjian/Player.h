#pragma once
#include "Character.h"
class Player:public Character
{
private:
    int gold;
    int potion;
public:
    Player(int ghp, int gmaxHp, int gattack, int gdefense);
    void playerusedrug(int recover);
    void reward();
    int getpotion();
    void repotion();
};