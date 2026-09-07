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
void battleRound(int &playerHp,int &enemyHp,int enemyAttack,int playerAttack)
{
   attack(enemyHp,playerAttack);
   if(!isDead(enemyHp))
{
   showHp("敌人",enemyHp);
   attack(playerHp,enemyAttack);
   if(!isDead(playerHp))
   {
    showHp("玩家",playerHp);
   }
}
}

int main()
{
Player player{100,30};
Enemy enemy{80,20};
while(player.hp>0 && enemy.hp>0)
{
   battleRound(player.hp,enemy.hp,player.attack,enemy.attack);
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