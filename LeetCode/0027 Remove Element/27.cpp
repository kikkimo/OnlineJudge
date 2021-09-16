#include <iostream>

using namespace std;

int removeElement(vector<int>& nums, int val) {
	int count = 0;
	int front = 0;
	int back = nums.size() - 1;
	while(front <= back)
	{
		if (nums[front] != val)
		{
			count++;
			front++;
			continue;
		}
		else
		{
			
			swap(nums[back],nums[front]);
			back--;
		}
	}
	return count;
}