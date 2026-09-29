#include "Character.h"
Character::Character(int ghp,int gmaxHp,int gattack,int gdefense):
hp(ghp),
maxhp(gmaxHp),
attack(gattack),
defense(gdefense),
level(1){}
int Character::gethp()
{
    return hp;
}
int Character::getattack()
{
    return attack;
}
int Character::getdefense()
{
    return defense;
}
int Character::getmaxhp()
{
    return maxhp;
}
void Character::takedamage(int damage)
{
    hp-=damage;
}
bool Character::isDead()
{
    return hp<=0;
}