#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Enemy
{
    string name;
    int hp;
};
void find(const vector<Enemy> &enemies)
{
    string target;
    cout<<"请输入要寻找敌人的名字：";
    cin>>target;
    for(size_t i=0;i<enemies.size();i++)
    {
       
        if(enemies[i].name==target)
        {
            cout<<"找到目标！"<<endl;
            cout<<enemies[i].name<<"的信息如下："<<endl;
            cout<<enemies[i].name<<" "<<enemies[i].hp;
            cout<<endl;
            break;
        }
        if(i==enemies.size()-1)
        {
            cout<<"未找到目标！";
        }
    }
}
void show(const vector<Enemy> &enemies)
{
    for(size_t i=0;i<enemies.size();i++)
    {
        cout<<"敌人信息如下："<<endl;
        cout<<enemies[i].name<<" ";
        cout<<enemies[i].hp<<" ";
        cout<<endl;
    }
}
void import(vector<Enemy> &enemies,int n)
{
     for(int i=0;i<n;i++)
    {
        string name;
        int hp;
        cout<<"请输入敌人名字：";
        cin>>name;
        cout<<"请输入敌人血量：";
        cin>>hp;
        cout<<endl;
        enemies.push_back({name,hp});
    }
}
void deleteenemy(vector<Enemy> &enemies)
{
     string target2;
     cout<<"请输入要删除敌人的名字：";
     cin>>target2;
     for(size_t i=0;i<enemies.size();i++)
     {
        if(enemies[i].name==target2)
        {
            enemies.erase(enemies.begin()+i);
            break;
        }
     }
     cout<<endl;
}
int main()
{
    vector<Enemy> enemies;
    import(enemies,3);
    show(enemies);
    find(enemies);
    deleteenemy(enemies);
    show(enemies);
}