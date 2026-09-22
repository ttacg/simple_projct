#include <iostream>
using namespace std;
class Player
{
private:
     int hp;
    int maxhp;
    int attack;
    int defense;
    int level;
    int gold;
    int potion;
public:
        Player(int ghp, int gmaxHp, int gattack, int gdefense):
        hp(ghp),
        maxhp(gmaxHp),
        attack(gattack),
        defense(gdefense)
     {
        level=1;
        gold=0;
        potion=3;
     }
    void playerusedrug(int recover);
    void reward();
    int getPlayerattack();
    int getPlayerhp();
    int getpotion();
    int getdefense();
    void repotion();
    int gethp();
    int getmaxhp();
    void rehp(int endhurt);
};
class Enemy
{
private:
    int hp;
    int attack;
public:
Enemy(int ghp,int gattack):
hp(ghp),
attack(gattack)
{

}
    int getEnemyattack();
    int getEnemyhp();
    void newHp(int damage);
};
 int Player::getPlayerattack()
    {
        return attack;
    }
int Player::getPlayerhp()
{
    return hp;
}
 int Enemy::getEnemyattack()
 {
    return attack;
 }
int Enemy::getEnemyhp()
  {
    return hp;
  }
int Player::getpotion()
{
    return potion;
}
int Player::getdefense()
{
    return defense;
}
int Player::getmaxhp()
{
    return maxhp;
}
void Player:: repotion()
{
    potion--;
}
void Player::rehp(int endhurt)
{
     hp-=endhurt;
}
int Player::gethp()
{
    return hp;
}

void Enemy::newHp(int damage)
   {
        hp-=damage;
   }
void Player::playerusedrug(int recover)
{
    int endcare;  
   if(hp+recover>maxhp)
   {
    endcare=maxhp-hp;
   }
   else
   {
    endcare=recover;
   }
   hp+=endcare;
   cout<<"回复血量为"<<endcare<<endl;
}
void playerattackenemy(Player player,Enemy &enemy)
{
   cout<<"玩家发动攻击，造成"<<player.getPlayerattack()<<"点伤害!"<<endl;
   int damage=player.getPlayerattack();
   enemy.newHp(damage);
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
void Player::reward()
{
    gold+=30;
    int end;
    if(hp+20>=maxhp)
    {
        end=maxhp-hp;
    }
    else
    {
        end=20;
    }
    hp+=end;
    cout<<"回复血量:"<<end<<endl;
    cout<<"获得30金币!";
}
void enemyattackplayer(Enemy enemy,Player &player)
{
    int endhurt;
    int enddefense;
    cout<<"敌人发动攻击"<<endl;
    cout<<"玩家防御为"<<player.getdefense()<<endl;
    if(player.getdefense()>=enemy.getEnemyattack())
    {
        endhurt=1;
    }
    else
    {
        endhurt=enemy.getEnemyattack()-player.getdefense();
    }
    enddefense=enemy.getEnemyattack()-endhurt;
    player.rehp(endhurt);
    cout<<"玩家受到"<<endhurt<<"点伤害"<<endl;
    cout<<"防御挡掉了"<<enddefense<<"点伤害";
}
void battleRound(Player &player,Enemy &enemy)
{
   playeraction(player,enemy);
   if(isDead(enemy.getEnemyhp()))
{
    return;

}
   showHp("敌人",enemy.getEnemyhp());
   enemyattackplayer(enemy,player);
   if(isDead(player.gethp()))
   {
    return;
   }
   showHp("玩家",player.gethp());
}
void combat(Player &player,Enemy &enemy)
{
    showHp("玩家",player.gethp());
    showHp("敌人",enemy.getEnemyhp());
    while(player.gethp()>0 && enemy.getEnemyhp()>0)
{
   battleRound(player,enemy);
}
    showHp("玩家",player.gethp());
if(isDead(enemy.getEnemyhp()))
{
    cout<<"玩家胜利!"<<endl;
    player.reward();
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