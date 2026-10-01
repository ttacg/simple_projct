#pragma once
#include "Character.h"
class Enemy :public Character
{
public:
Enemy(std::string name,int ghp,int gmaxhp,int gattack);
};
