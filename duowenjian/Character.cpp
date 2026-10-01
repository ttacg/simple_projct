#include "Character.h"
Character::Character(std::string gname,int ghp,int gmaxHp,int gattack,int gdefense):
name(gname),
hp(ghp),
maxhp(gmaxHp),
attack(gattack),
defense(gdefense),
level(1){}
std::string Character::getname()
{
    return name;
}
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