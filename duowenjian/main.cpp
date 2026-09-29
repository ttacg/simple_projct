#include <iostream>
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
using namespace std;
class Game
{
    private:
    Player player;
    Enemy enemy;
    public:
    Game(int playerhp,int playermaxHp,int playerattack,int playerdefense,int enemyhp,int gmaxhp,int enemyattack):
    player(playerhp,playermaxHp,playerattack,playerdefense),enemy(enemyhp,gmaxhp,enemyattack){}
    void showplayerhp();
    void showenemyhp();
    void playerattackenemy();
    void playeraction();
    void battleRound();
    void combat();
    void enemyattackplayer();
};
void Game::playerattackenemy()
{
   cout<<"玩家发动攻击，造成"<<player.getattack()<<"点伤害!"<<endl;
   int damage=player.getattack();
   enemy.takedamage(damage);
}
void Game::enemyattackplayer()
{
    int endhurt;
    int enddefense;
    cout<<"敌人发动攻击"<<endl;
    cout<<"玩家防御为"<<player.getdefense()<<endl;
    if(player.getdefense()>=enemy.getattack())
    {
        endhurt=1;
    }
    else
    {
        endhurt=enemy.getattack()-player.getdefense();
    }
    enddefense=enemy.getattack()-endhurt;
    player.takedamage(endhurt);
    cout<<"玩家受到"<<endhurt<<"点伤害"<<endl;
    cout<<"防御挡掉了"<<enddefense<<"点伤害"<<endl;
}
void Game::showplayerhp()
{
    cout<<"玩家血量："<<player.gethp();
    cout<<endl;
}
void Game::showenemyhp()
{
    cout<<"敌人血量："<<enemy.gethp();
    cout<<endl;
}
void attack(Character &attacker,Character &target)
{
    int damage=attacker.getattack();
    if(target.getdefense()>=attacker.getattack())
    {
        damage=1;
    }
    damage=attacker.getattack()-target.getdefense();
    target.takedamage(damage);
}
void Game::playeraction()
{
    while(true)
 {
    cout<<"1.攻击"<<endl;
    cout<<"2.使用药水"<<endl;
    int choice;
     cin>>choice;
        if(choice==1)
    {
        playerattackenemy();
        break;
    }
    else if(choice==2)
    {
        if(player.gethp()==player.getmaxhp())
        {
            cout<<"血量已满，无法使用药剂！"<<endl;
            continue;
        }
        if(player.getpotion()>0)
        {
        player.playerusedrug(25);
        player.repotion();
        break;
        }
        else
        {
            cout<<"药剂不足!";
        }
    }
 }
}
void Game::battleRound()
{
   playeraction();
   if(enemy.isDead())
{
    return;

}
   showenemyhp();
   enemyattackplayer();
   if(player.isDead())
   {
    return;
   }
   showplayerhp();
}
void Game::combat()
{
    showplayerhp();
    showenemyhp();
    while(!player.isDead() && !enemy.isDead())
{
   battleRound();
}
    showplayerhp();
if(enemy.isDead())
{
    cout<<"玩家胜利!"<<endl;
    player.reward();
    return;
}
    cout<<"玩家失败!";
}
int main()
{
Game game(100,100,30,10,80,80,20);
game.combat();
}