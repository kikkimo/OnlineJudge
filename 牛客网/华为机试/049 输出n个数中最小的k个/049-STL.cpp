#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n,index;
    while(cin >> n >> index)
    {
        if(0 == n)
            continue;
        vector<int> nums;
        for(int i = 0 ; i < n ; i ++)
        {
            int tmp;
            cin >> tmp;
            nums.push_back(tmp);
        }
        sort(nums.begin(),nums.end());
        if(index > n) index = n;
        for( i = 0 ; i < index ; i ++)
        {
            if(i != index - 1)
                cout << nums[i] << " ";
            else
                cout << nums[i] << endl;
        }
    }
    return 0;
}