#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int numSize = 0;
    while(scanf("%d",&numSize) != EOF)
    {
        if(0 == numSize) break;
        vector<int> nums;
        for(int i = 0 ; i < numSize ; i ++)
        {
            int tmp = 0;
            scanf("%d",&tmp);
            nums.push_back(tmp);
        }
        sort(nums.begin(),nums.end());
        int nCurrentNum = nums[0] - 1;
        vector<int> result;
        for(int i = 0 ; i < numSize ; i ++)
        {
            if(nums[i] != nCurrentNum)
            {
                nCurrentNum = nums[i];
                result.push_back(nCurrentNum);
            }
        }
        for(int i = 0 ; i < result.size() ; i ++)
            printf("%d\n",result[i]);
    }
}