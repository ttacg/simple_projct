#include <iostream>
using namespace std;
/*cout << "请选择药水：1.小药水  2.大药水" << endl;

int choice;
cin >> choice;
if(choice==1)
{
    playerusedrug(player,25);
}
else if(choice==2)
{
    playerusedrug(player,60)
}*/
/*struct Player
{
    int hp;
    int maxHp;
    int attack;
    int defense;
    int level;
    int gold;
};
Player createplayer(int maxhp,int attack,int defense)
{
    Player player;
    player.hp=player.maxHp=maxhp;
    player.attack=attack;
    player.defense=defense;
    player.level=1;
    player.gold=0;
    return player;
}
struct Enemy
{
    int hp;
    int maxHp;
    int attack;
};
Enemy createenemy(int maxhp,int attack)
{
    Enemy enemy;
    enemy.hp=enemy.maxHp=maxhp;
    enemy.attack=attack;
    return enemy;
}
int main()
{
    Enemy enemy=createenemy(80,20);
}*/
struct Player
{
    int hp;
    int maxHp;
    int attack;
    int defense;
    int level;
    int gold;

    Player(int ghp, int gmaxHp, int gattack, int gdefense)
    {
        // 初始化成员
        hp=ghp;
        maxHp=gmaxHp;
        attack=gattack;
        defense=gdefense;
        level=1;
        gold=0;
    }
};
struct Enemy
{
    int hp;
    int attack;
};
void reward(Player &player)
{
    player.gold+=30;
    int end;
    if(player.hp+20>=player.maxHp)
    {
        end=player.maxHp-player.hp;
    }
    else
    {
        end=20;
    }
    player.hp+=end;
    cout<<"实际回复量为:"<<end<<endl;
    cout<<"获得30金币!";
}
//玩家：90 / 100 HP，40 gold
//实际恢复了20点生命
//当前金币40
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
int main()
{
    Player A(80,100,30,5);
    Player B(120,150,20,10);
    cout<<"玩家A等级"<<A.level<<",金币"<<A.gold;
    cout<<endl;
    cout<<"玩家B等级"<<B.level<<",金币"<<B.gold;
}