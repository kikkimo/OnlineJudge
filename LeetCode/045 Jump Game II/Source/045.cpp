#include <iostream>
#include <vector>
using namespace std;

int jump(vector<int>& nums) {
	if(nums.size() <= 1 ) return 0;
    if(nums.size() <= 2)
	{
		if (nums[0] == 0)
			return INT_MAX;
		else
			return 1;
	}

	vector<int> costs;		//代价是步数加上序号
	for (int i = 0 ; i < nums.size() ; i++)
	{
		int cost = i + nums[i];
		costs.push_back(cost);
	}

	int nSelctIndex = 0;
	i = nSelctIndex;
	vector<int> select_num;
	select_num.push_back(nums[nSelctIndex]);
	int nStepCount = 1;	
	while (nums[nSelctIndex] + i < nums.size() - 1 )
	{
		int j = nums[nSelctIndex] + nSelctIndex;
		int maxPath = 0;
		for (i = nSelctIndex + 1 ; i <= j ; i++)
		{
			if (costs[i] > maxPath)
			{
				maxPath = costs[i];
				nSelctIndex = i;
			}
		}
		i = nSelctIndex;
		select_num.push_back(nums[nSelctIndex]);
		nStepCount ++;
	}

	for (int m = 0 ; m < select_num.size() ; m++)
	{
		cout << select_num[m] << endl;
	}
	return nStepCount;
 }

void main()
{
	int Q[] = {1,1,1,1};
	int size = sizeof(Q) / sizeof(int);
	vector<int> nums;
	for (int i = 0 ; i < size ; i ++)
		nums.push_back(Q[i]);
	cout << jump(nums) << endl;
}