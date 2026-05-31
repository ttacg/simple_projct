#include <iostream>
#include <vector>
using namespace std;
    vector<int> ts(vector<int>&nums,int target)
{
    for(int i=0;i<nums.size();++i)
    {
        for(int j=i+1;j<nums.size();++j)
        {
            if(nums[i]+nums[j]==target)
            {
                return {i,j};
            }
        }
    }
    return {};
} 
ostream& operator <<(ostream&cou,const vector<int>&re)
{
    for(const auto& r:re)
    {
        cou<<r<<' ';
    }
    return cou;
}
int main()
{
    vector<int> nums{1,2,3,4};
    vector<int> result=ts(nums,4);
    cout<<result<<endl;
    system("pause");
    return 0;
}