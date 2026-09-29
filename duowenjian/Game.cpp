#include <iostream>
#include "Game.h"
Game::Game(int playerhp, int playermaxHp, int playerattack, int playerdefense, int enemyhp, int gmaxhp, int enemyattack) :
 player(playerhp, playermaxHp, playerattack, playerdefense), enemy(enemyhp, gmaxhp, enemyattack) {}
void Game::showplayerhp()
{
    std::cout << "玩家血量：" << player.gethp();
    std::cout << std::endl;
}
void Game::showenemyhp()
{
    std::cout << "敌人血量：" << enemy.gethp();
    std::cout << std::endl;
}
void Game::playerattackenemy()
{
    std::cout << "玩家发动攻击，造成" << player.getattack() << "点伤害!" << std::endl;
    int damage = player.getattack();
    enemy.takedamage(damage);
}
void Game::playeraction()
{
    while (true)
    {
        std::cout << "1.攻击" << std::endl;
        std::cout << "2.使用药水" << std::endl;
        int choice;
        std::cin >> choice;
        if (choice == 1)
        {
            playerattackenemy();
            break;
        }
        else if (choice == 2)
        {
            if (player.gethp() == player.getmaxhp())
            {
                std::cout << "血量已满，无法使用药剂！" << std::endl;
                continue;
            }
            if (player.getpotion() > 0)
            {
                player.playerusedrug(25);
                player.repotion();
                break;
            }
            else
            {
                std::cout << "药剂不足!";
            }
        }
    }
}
void Game::battleRound()
{
    playeraction();
    if (enemy.isDead())
    {
        return;
    }
    showenemyhp();
    enemyattackplayer();
    if (player.isDead())
    {
        return;
    }
    showplayerhp();
}
void Game::combat()
{
    showplayerhp();
    showenemyhp();
    while (!player.isDead() && !enemy.isDead())
    {
        battleRound();
    }
    showplayerhp();
    if (enemy.isDead())
    {
        std::cout << "玩家胜利!" << std::endl;
        player.reward();
        return;
    }
    std::cout << "玩家失败!";
}
void Game::enemyattackplayer()
{
    int endhurt;
    int enddefense;
    std::cout << "敌人发动攻击" << std::endl;
    std::cout << "玩家防御为" << player.getdefense() << std::endl;
    if (player.getdefense() >= enemy.getattack())
    {
        endhurt = 1;
    }
    else
    {
        endhurt = enemy.getattack() - player.getdefense();
    }
    enddefense = enemy.getattack() - endhurt;
    player.takedamage(endhurt);
    std::cout << "玩家受到" << endhurt << "点伤害" << std::endl;
    std::cout << "防御挡掉了" << enddefense << "点伤害" << std::endl;
}
void attack(Character &attacker, Character &target)
{
    int damage = attacker.getattack();
    if (target.getdefense() >= attacker.getattack())
    {
        damage = 1;
    }
    damage = attacker.getattack() - target.getdefense();
    target.takedamage(damage);
}