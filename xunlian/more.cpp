#include <iostream>
using namespace std;
struct Enemy
{
    int hp;
};
Enemy* spawnenemy()
{
    int hp;
    cout<<"请输入敌人血量"<<endl;
    cin>>hp;
    Enemy *p=new Enemy{hp};
    return p;
}
void attack(Enemy*enemy)
{
    if(enemy->hp>0){
    cout<<"敌人当前血量为:"<<enemy->hp<<endl;
    }
    enemy->hp-=30;
}
void destoryEnemy(Enemy*&enemy)
{
    cout<<"敌人已经死亡"<<endl;
    delete enemy;
    enemy=nullptr;
}
int main()
{
    for(int i=0;i<3;i++)
    {
        Enemy*enemy=spawnenemy();
        while(true)
        {
            attack(enemy);
            if(enemy->hp<=0)
            {
                destoryEnemy(enemy);
                break;
            }
        }
    }
    return 0;
}
/*void attack(Enemy* target)
{
    // 你写
    if(!target)
    {
        cout<<"没有目标！";
        return;
    }
    target->hp-=30;
}
int main()
{
    Enemy goblin{100};

    Enemy* target = nullptr;

    target = &goblin;

    attack(target);

    cout << goblin.hp;
}*/

/*void attack(Enemy* target)
{
    if(!target)
        return;

    target->hp -= 30;
}

int main()
{
    Enemy enemyA{100};
    Enemy enemyB{80};

    Enemy* target = nullptr;
    target=&enemyA;
    attack(target);
    target=&enemyB;
    attack(target);
    target=nullptr;
    attack(target);
    // 从这里开始，你写 5 行左右
}*/

