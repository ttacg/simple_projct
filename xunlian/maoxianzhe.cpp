#include <iostream>
#include <vector>
#include <string>
using namespace std;
class news
{
private:
   string name;
   int level;
   int gold;
public:
news(string cname,int clevel,int cgold):
name(cname),
level(clevel),
gold(cgold)
{
}
news(){};
void import(vector<news> &panel);
void show(const vector<news> &panel);
void find(const vector<news> &panel);
void deletenew(vector<news> &panel);
};
void news::import(vector<news> &panel)
{
        string name;
        int level;
        int gold;
        cout<<"请输入悬赏名称："<<endl;
        cin>>name;
        cout<<"请输入怪物等级："<<endl;
        cin>>level;
        cout<<"请输入悬赏金币："<<endl;
        cin>>gold;
        news enemy(name,level,gold);
        panel.push_back(enemy);
        cout<<"登记成功！"<<endl;
    
}
void news::show(const vector<news> &panel)
{
    if(!panel.size())
    {
        return;
    }
    cout<<"悬赏信息如下："<<endl;
    for(size_t i=0;i<panel.size();i++)
    {
        cout<<i+1<<" "<<"悬赏名称："<<" "<<panel[i].name<<" ";
        cout<<"等级："<<panel[i].level<<" ";
        cout<<"悬赏金："<<panel[i].gold<<endl;
    }
}
void news::find(const vector<news> &panel)
{  
    string name;
    cout<<"请输入要查找的悬赏名字：";
    cin>>name;
    for(size_t i=0;i<panel.size();i++)
    {
        if(panel[i].name==name)
        {
            cout<<"已找到，悬赏信息如下：";
            cout<<panel[i].name<<" ";
            cout<<panel[i].level<<" ";
            cout<<panel[i].gold<<endl;
            return;
        }
        if(i==panel.size()-1)
        {
            cout<<"未找到悬赏信息！"<<endl;
        }
    }
}
void news::deletenew(vector<news> &panel)
{ 
    string name;
    cout<<"请输入要删除的悬赏名字：";
    cin>>name;
    for(size_t i=0;i<panel.size();i++)
    {
        if(panel[i].name==name)
        {
           panel.erase(panel.begin()+i);
           cout<<"已删除悬赏！"<<endl;
           return;
        }
        if(i==panel.size()-1)
        {
            cout<<"未找到悬赏"<<endl;
        }
    }
}
int main()
{
   news panel;
   vector<news> panels;
while(true)
{
    cout<<" ===== 冒险者公会 ====="<<endl;
cout<<"1. 登记悬赏"<<endl;
cout<<"2. 查看全部悬赏"<<endl;
cout<<"3. 搜索悬赏"<<endl;
cout<<"4. 完成悬赏"<<endl;
cout<<"5. 退出"<<endl;
cout<<"请选择："<<endl;
int nums;
cin>>nums;
    if(nums==1)
    {
        panel.import(panels);
        continue;
    }
    else if(nums==2)
    {
        panel.show(panels);
        continue;

    }
    else if(nums==3)
    {
        panel.find(panels);
        continue;

    }
    else if(nums==4)
    {
        panel.deletenew(panels);
        continue;

    }
    else if(nums==5)
    {
        break;
    }
}
}