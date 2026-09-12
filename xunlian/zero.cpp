#include <iostream>
using namespace std;
struct Player
{
     int hp;
    int maxhp;
    int attack;
    int defense;
    int level;
    int gold;
    int potion;
        Player(int ghp, int gmaxHp, int gattack, int gdefense)
    {
        // 初始化成员
        hp=ghp;
        maxhp=gmaxHp;
        attack=gattack;
        defense=gdefense;
        level=1;
        gold=0;
        potion=3;
    }
};
struct Enemy
{
    int hp;
    int attack;
};
void playerusedrug(Player &player,int recover)
{
    int endcare;  
   if(player.hp+recover>player.maxhp)
   {
    endcare=player.maxhp-player.hp;
   }
   else
   {
    endcare=recover;
   }
   player.hp+=endcare;
   cout<<"回复血量为"<<endcare;
}
void playerattackenemy(Player player,Enemy &enemy)
{
   cout<<"玩家发动攻击，造成"<<player.attack<<"点伤害!"<<endl;
   enemy.hp-=player.attack;
}
void showHp(string name,int hp)
{
    cout<<name<<"当前血量为:"<<hp;
    cout<<endl;
}
bool isDead(int hp)
{
    return hp <= 0;
}
void playeraction(Player &player,Enemy &enemy)
{
    while(true)
 {
    cout<<"1.攻击"<<endl;
    cout<<"2.使用药水"<<endl;
    int choice;
    cin>>choice;
        if(choice==1)
    {
        playerattackenemy(player,enemy);
        break;
    }
    else if(choice==2)
    {
        if(player.potion>0)
        {
        playerusedrug(player,25);
        player.potion--;

        break;
        }
        else
        {
            cout<<"药剂不足!";
        }
    }
 }
}
void reward(Player &player)
{
    player.gold+=30;
    int end;
    if(player.hp+20>=player.maxhp)
    {
        end=player.maxhp-player.hp;
    }
    else
    {
        end=20;
    }
    player.hp+=end;
    cout<<"回复血量:"<<end<<endl;
    cout<<"获得30金币!";
}
void enemyattackplayer(Enemy enemy,Player &player)
{
    int endhurt;
    int enddefense;
    cout<<"敌人发动攻击"<<endl;
    cout<<"玩家防御为"<<player.defense<<endl;
    if(player.defense>=enemy.attack)
    {
        endhurt=1;
    }
    else
    {
        endhurt=enemy.attack-player.defense;
    }
    enddefense=enemy.attack-endhurt;
    player.hp-=endhurt;
    cout<<"玩家受到"<<endhurt<<"点伤害"<<endl;
    cout<<"防御挡掉了"<<enddefense<<"点伤害";
}
void battleRound(Player &player,Enemy &enemy)
{
   playeraction(player,enemy);
   if(isDead(enemy.hp))
{
    return;

}
   showHp("敌人",enemy.hp);
   enemyattackplayer(enemy,player);
   if(isDead(player.hp))
   {
    return;
   }
   showHp("玩家",player.hp);
}
void combat(Player &player,Enemy &enemy)
{
    showHp("玩家",player.hp);
    showHp("敌人",enemy.hp);
    while(player.hp>0 && enemy.hp>0)
{
   battleRound(player,enemy);
}
    showHp("玩家",player.hp);
if(isDead(enemy.hp))
{
    cout<<"玩家胜利!"<<endl;
    reward(player);
    return;
}
    cout<<"玩家失败!";
}
int main()
{
Player player(100,100,30,10);
Enemy enemy{80,20};
combat(player,enemy);
}