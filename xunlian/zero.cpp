#include <iostream>
using namespace std;
struct Player
{
    int hp;
    int attack;
};
struct Enemy
{
    int hp;
    int attack;
};
void playerattackenemy(Player player,Enemy &enemy)
{
   cout<<"玩家发动攻击，造成："<<player.attack<<"点伤害!"<<endl;
   enemy.hp-=player.attack;
}
void enemyattackplayer(Enemy enemy,Player &player)
{
    cout<<"敌人发动攻击，造成："<<enemy.attack<<"点伤害!"<<endl;
    player.hp-=enemy.attack;
    
}
void showHp(string name,int hp)
{
    cout<<name<<"当前血量为:"<<hp;
    cout<<endl;
}
void attack(int& hp, int damage)
{
    hp -= damage;
}

bool isDead(int hp)
{
    return hp <= 0;
}
void battleRound(Player &player,Enemy &enemy)
{
   playerattackenemy(player,enemy);
   if(!isDead(enemy.hp))
{
   showHp("敌人",enemy.hp);
   enemyattackplayer(enemy,player);
   if(!isDead(player.hp))
   {
    showHp("玩家",player.hp);
   }
}
}

int main()
{
Player player{100,30};
Enemy enemy{80,20};
while(player.hp>0 && enemy.hp>0)
{
   battleRound(player,enemy);
}
if(isDead(enemy.hp))
   {
    cout<<"玩家获胜！";
   }
  else
   {
    cout<<"玩家失败！";
   }
}