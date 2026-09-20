#include <iostream>
using namespace std;
class Player
{
private:
    int hp;
    int attack;
    int defense;
    int maxhp;
public:
   Player(int chp,int cattack,int cdefense,int cmaxhp)
   :hp(chp),
   attack(cattack),
   defense(cdefense),
   maxhp(cmaxhp)
   {
   }
void show()
    {
        cout<<"玩家当前血量为:"<<hp<<endl;       
        cout<<"攻击为:"<<attack<<endl;  
        cout<<"防御为:"<<defense<<endl;  
    }
void takeDamage(int damage)
    {
        if(hp-damage<=0)
        {
            hp=0;
            return;
        }
        hp-=damage;
    }
void heal(int count)
{
     if(hp+count>=maxhp)
     {
        hp=maxhp;
        return;
     }
     hp+=count;
}
int gethp()
    {
        return hp;
    }
int getattack()
    {
        return attack;
    }
int getdefense()
    {
        return defense;
    }
};
int main()
{
    Player player(100,30,10,20);
    player.show();
    cout<<player.gethp()<<endl;
    cout<<player.getattack()<<endl;
    cout<<player.getdefense()<<endl;
}