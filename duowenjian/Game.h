#pragma once
#include "Player.h"
#include "Enemy.h"
class Game
{
    private:
    Player player;
    Enemy enemy;
    public:
    Game(int playerhp,int playermaxHp,int playerattack,int playerdefense,int enemyhp,int gmaxhp,int enemyattack);
    void showplayerhp();
    void showenemyhp();
    void playerattackenemy();
    void playeraction();
    void battleRound();
    void combat();
    void enemyattackplayer();
};