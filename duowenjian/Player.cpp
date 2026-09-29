#include "Player.h"
#include <iostream>

Player::Player(int ghp, int gmaxHp, int gattack, int gdefense):
Character(ghp,gmaxHp,gattack,gdefense)
{
    gold=0;
    potion=3;
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
   std::cout<<"回复血量为"<<endcare<<std::endl;
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
    std::cout<<"回复血量:"<<end<<std::endl;
    std::cout<<"获得30金币!";
    }
    int Player::getpotion()
    {
        return potion;
    }
    void Player::repotion()
    {
         potion--;
    }