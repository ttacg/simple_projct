#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Enemy
{
    private:
    int hp;
    int attack;
    public:
    Enemy(int chp,int cattack):hp(chp),attack(cattack){}
};
class Player
{
private:
    int hp;
    int attack;

public:
    Player(int chp,int cattack) : hp(chp),attack(cattack) {}

    void showHp()
    {
        cout << hp << endl;
        cout<<attack<<endl;
    }
};
class Game
{
private:
Player player;
Enemy enemy;
public:
Game(int chp,int cattack,int ehp,int eattack):player(chp,cattack),enemy(ehp,eattack){}
void showplayer()
{
    player.showHp();
}
};
int main()
{
  Game game(200,30,100,20);
  game.showplayer();
}