#pragma once
#include "Player.h"
#include "Enemy.h"
class Game
{
    private:
    Player player;
    Enemy enemy;
    public:
    Game(std::string playername,int playerhp,int playermaxHp,int playerattack,int playerdefense,std::string enemyname,int enemyhp,int enemymaxhp,int enemyattack);
    void showplayerhp();
    void showenemyhp();
    void playerattackenemy();
    void playeraction();
    void battleRound();
    void combat();
    void enemyattackplayer();
};