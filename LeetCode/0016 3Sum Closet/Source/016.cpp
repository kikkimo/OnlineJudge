#include <IOSTREAM>
#include <vector>
#include <algorithm>
using namespace std;

int threeSumClosest(vector<int>& nums, int target) 
{
	int result =0;
    int size = nums.size();
	if (size <= 3)
	{
		for (int i = 0 ; i < size ; i ++)
			result += nums[i];
		return result;
	}
	
	sort(nums.begin(),nums.end());
	
	int nLastNum = 0;
	int nMinDistance = 2147483647;  //INT_MAX
	
	for(int i = 0 ; i < size ; i++)
	{
		if( i!=0 )
		{
			while(i < size && nLastNum == nums[i]) i++;
			if (i == size)
				break;
			else
				nLastNum = nums[i];
		}
		else
			nLastNum = nums[i];
	
		int targetClosest = target-nums[i];
		
		int front = i + 1;
		int back = size - 1; 
		while(front < back && front > 0 && back > 0 && front < size && back < size)
		{
			int sum = nums[front] + nums[back];
			if(sum == targetClosest)
			{
				result = target;
				return result;
			}
			
			if(sum > targetClosest)
			{
				int nDistance = sum - targetClosest;
				if (nDistance < nMinDistance)
				{
					nMinDistance = nDistance;
					result = nums[front] + nums[back] + nums[i];
				}
				back--;
			}
			if(sum < targetClosest)
			{
				int nDistance = targetClosest - sum;
				if (nDistance < nMinDistance)
				{
					nMinDistance = nDistance;
					result = nums[front] + nums[back] + nums[i];
				}
				front++;
			}
		}
	}
	return result;
	
}


void main()
{
	vector<int> nums;
	nums.push_back(1);
	nums.push_back(1);
	nums.push_back(1);
	nums.push_back(1);
	int target = 0;

	cout << threeSumClosest(nums,target) << endl;
}