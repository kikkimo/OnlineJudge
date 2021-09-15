class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        if(nums.size() == 0) return 1;
        int * flag = new int[nums.size()];
        memset(flag,0,sizeof(int)*nums.size());
        for(int i = 0 ; i < nums.size() ; i++)
        {
            if(nums[i] >= 1 && nums[i] <= nums.size())
                flag[nums[i]-1] = 1;
        }
        int result = 1;
        for(int i = 0 ; i < nums.size() ; i ++)
        {
            if(flag[i] == 0)
            {
                result = i+1;
                break;
            }
            else
                result++;
        }
        delete [] flag;
        flag = NULL;
        return result;
    }
};