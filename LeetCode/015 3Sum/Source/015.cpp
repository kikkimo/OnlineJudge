class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int size = nums.size();
        if(size < 3) return result;
        sort(nums.begin(),nums.end());
/*        if(nums[0] > 0 || nums[size-1] < 0) return result;
        if(nums[0] == 0 && nums[size-1] == 0)
        {
            vector<int> res(3,0);
            result.push_back(res);
            return result;
        }
  */    int nLastNum = 0;
        for(int i = 0 ; i < size ; i++)
        {
            if( i!=0 )
            {
                while(nLastNum == nums[i]) i++;
                nLastNum = nums[i];
            }
            else
                nLastNum = nums[i];               
            int target = -nums[i];
            if(target < 0) break;   //��Ϊ�Ѿ������ˣ���ǰ����������ֻ���������ң��������϶��ȵ�ǰ����
            int front = i + 1;
            int back = size - 1;    //����two sum�ķ�������֤���hash��ʽ���죬hash��ʽ��Ҫ����ظ�������
            while(front < back)
            {
                int sum = nums[front] + nums[back];
                if(sum == target)
                {
                    vector<int> res;
                    res.push_back(nums[i]);
                    res.push_back(nums[front]);
                    res.push_back(nums[back]);
                    result.push_back(res);
                    while(nums[front] == res[1]) front ++;
                    while(nums[back] == res[2]) back --;
                }
                if(sum > target) back--;
                if(sum < target) front++;
            }
        }
	    return result;
    }
};