#include <iostream>
#include "Game.h"
Game::Game(std::string playername, int playerhp, int playermaxHp, int playerattack, int playerdefense,
           std::string enemyname, int enemyhp, int enemymaxhp, int enemyattack) : 
           player(playername, playerhp, playermaxHp, playerattack, playerdefense), enemy(enemyname, enemyhp, enemymaxhp, enemyattack) {}
void Game::showplayerhp()
{
    std::cout << player.getname()<<"血量：" << player.gethp();
    std::cout << std::endl;
}
void Game::showenemyhp()
{
    std::cout << enemy.getname()<<"血量：" << enemy.gethp();
    std::cout << std::endl;
}
void Game::playerattackenemy()
{
    std::cout <<player.getname()<< "发动攻击，造成" << player.getattack() << "点伤害!" << std::endl;
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
            if (player.gethp() >= player.getmaxhp())
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
                std::cout << "药剂不足!"<<std::endl;
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
        std::cout <<player.getname()<< "胜利!" << std::endl;
        player.reward();
        return;
    }
    std::cout <<player.getname()<< "失败!";
}
void Game::enemyattackplayer()
{
    int endhurt;
    int enddefense;
    std::cout <<enemy.getname()<< "发动攻击" << std::endl;
    std::cout <<player.getname()<< "防御为" << player.getdefense() << std::endl;
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
    std::cout <<player.getname()<< "受到" << endhurt << "点伤害" << std::endl;
    std::cout << "防御挡掉了" << enddefense << "点伤害" << std::endl;
}
void attack(Character &attacker, Character &target)
{
    int damage = attacker.getattack();
    damage = attacker.getattack() - target.getdefense();
    if (target.getdefense() >= attacker.getattack())
    {
        damage = 1;
    }
    target.takedamage(damage);
}