int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        if(nums.size() == 1) return 1;
        int nElement = nums[0]-1;
        int nCount = 0;
        for(int i = 0 ; i < nums.size() ; i++)
        {
            if(nums[i] != nElement)
            {
                nElement = nums[i];
                nums[nCount] = nums[i];
                nCount++;
            }
        }
        return nCount;
    }