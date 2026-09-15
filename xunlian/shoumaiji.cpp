#include <iostream>
#include <string>
using namespace std;
struct Product
{
    int point;
    string item;
    int price;
    int kuchun;
    /*Product(int corder,string citem,int cprice,int ckuchun)
    {
        order=corder;
        item=citem;
        price=cprice;
        kuchun=ckuchun;
    }*/
};
struct Buyer
{
   int money;
   Buyer(int cmoney)
   {
      money=cmoney;
   }
};
void showup(Product product[],Buyer buyer)
{
    for(int i=0;i<=2;i++){
    cout<<"编号："<<product[i].point<<" "<<"商品名称："<<product[i].item<<" "<<"价格："<<product[i].price<<" "<<"库存："<<product[i].kuchun<<endl;
    }
    cout<<"拥有金额："<<buyer.money<<endl;
}
int choose(Product product[],Buyer &buyer,int count)
{
     int order;
     showup(product,buyer);
   cout<<"请输入下列数字："<<"0是退出"<<" "<<"1是购买"<<endl;
   cin>>order;
   if(order==0)
   {
    return 0;
   }
   else if(order==1)
   {
    int buy1,buy2,buy3;
    showup(product,buyer);
    cout<<"请输入购买商品的编号："<<endl;
    cin>>buy1;
    while(true){
    if(buy1<1 ||buy1>count)
    {
        cout<<"请输入正确编号"<<endl;
        cin>>buy1;
    }
    else{
        break;
    }
    }
     cout<<"请输入要购买的数量："<<endl;
     cin>>buy2;
     while(true){
     if(buy2<=0 ||buy2>product[buy1-1].kuchun)
     {
        cout<<"请输入正确数量"<<endl;
        cin>>buy2;
     }
     else{
        break;
     }
    }
    cout<<"确定购买按1,取消按2。"<<endl;
    cin>>buy3;
    if(buy3==1)
    {
        if(product[buy1-1].price*buy2<=buyer.money){
        product[buy1-1].kuchun-=buy2;
        buyer.money-=product[buy1-1].price*buy2;
         return 1;
        }
      else{
        cout<<"金额不够。"<<endl;
        return 2;
      }
    }
    else{
        return 2;
    }
   }
   else 
   {
    return 2;
   }
}
void buy(Product product[],Buyer &buyer,int count)
{
    while(true)
    {
      int Order=choose(product,buyer,count);
      if(Order==0)
      {
        break;
      }
      else if(Order==2)
      {
        continue;
      }
    }
}
int main()
{
    Buyer buyer{10};
   Product products[3]={{1,"可乐",3,5},{2,"雪碧",2,4},{3,"王老吉",5,3}};
   int count=sizeof(products)/sizeof(products[0]);
   cout<<"这是一个售货机"<<endl;
   buy(products,buyer,count);
}