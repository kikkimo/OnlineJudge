#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vector_int;

vector< vector<int> > fourSum(vector<int>& nums, int target) {
    if(nums.size() < 4)
    {
        vector< vector<int> > vec_buf;
		return vec_buf;
    }
	sort(nums.begin(),nums.end());
	if (nums[0] + nums[1] + nums[2] + nums[3] > target)
	{
		vector< vector<int> > vec_buf;
		return vec_buf;
	}
	size_t size = nums.size();
	if (nums[size-1] + nums[size-2] + nums[size-3] + nums[size-4] < target)
	{
		vector< vector<int> > vec_buf;
		return vec_buf;
	}
	vector< vector<int> > result;
	for (int i = 0 ; i <= size - 4; ++ i)
	{
		int num1 = nums[i];
		for (int j = i+1 ; j <= size - 3 ; ++j )
		{
			int num2 = nums[j];
			int twoSum = target - num1 - num2;
			if (nums[j+1] + nums[j+2] > twoSum || 
				nums[size-1] + nums[size-2] < twoSum)
				continue;
			
			int front = j+1;
			int back = size - 1;
			while (front < back)
			{
				int _twoSum = nums[front] + nums[back];
				if (_twoSum == twoSum)
				{
					vector_int buffer(4);
					buffer[0] = nums[i];
					buffer[1] = nums[j];
					buffer[2] = nums[front];
					buffer[3] = nums[back];
					std::vector<vector_int>::iterator it = find(result.begin(),result.end(),buffer);
					
					if (it == result.end())
					result.push_back(buffer);
					back --;
				}
				else
					if (twoSum > _twoSum)
						front ++;
					else
						back --;
			}
			if (front < back && (nums[front] + nums[back] == twoSum))
			{
//				vector<int> buffer{nums[i],nums[j],nums[front],nums[back]};
//				auto it = find(result.begin(),result.end(),buffer);
				vector_int buffer(4);
				buffer[0] = nums[i];
				buffer[1] = nums[j];
				buffer[2] = nums[front];
				buffer[3] = nums[back];
				std::vector<vector_int>::iterator it = find(result.begin(),result.end(),buffer);

				if (it == result.end())
					result.push_back(buffer);
			}
		}
	}
	return result;
}

int main()
{
	//nums = [-3,-2,-1,0,0,1,2,3]  and target = 0.
	//vector_int nums{-3,-2,-1,0,0,1,2,3};
	vector_int nums(8);
	nums[0] = -3;
	nums[1] = -2;
	nums[2] = -1;
	nums[3] = 0;
	nums[4] = 0;
	nums[5] = 1;
	nums[6] = 2;
	nums[7] = 3;
	int target = 0;
	vector<vector_int> A = fourSum(nums,target);
	for (int i = 0 ; i < A.size() ; ++i)
	{
		for (int j = 0 ; j < A[i].size() ; ++j)
		{
			cout << A[i][j] << "  ";
		}
		cout << "\n";
	}
	return 0;
}