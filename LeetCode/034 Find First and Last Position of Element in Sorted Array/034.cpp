#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//时间复杂度O(logn)实现数字查找
vector<int> searchRange(vector<int>& nums, int target) {
	vector<int> result(2);
	size_t size = nums.size();
	if (0 == size)
	{
		result[0] = -1;
		result[1] = -1;
		return result;
	}
	if (1 == size)
	{
		if (nums[0] == target)
		{
			result[0] = 0;
			result[1] = 0;
		}
		else
		{
			result[0] = -1;
			result[1] = -1;
		}
		return result;
	}
	int left = 0;
	int right = size - 1;
	int pos = -1;
	for (;;)
	{
		int mid = left + right;
		mid = (mid >> 1);
		if (nums[mid] == target)
		{
			pos = mid;
			break;
		}
		if (nums[mid] < target)
			left = mid;
		else
			right = mid;
		if (left == right - 1 || left == right)
		{
			if (nums[left] == target)
				pos = left;
			if (nums[right] == target)
				pos = right;
			break;
		}
	}
	if (pos == -1)
	{
		result[0] = -1;
		result[1] = -1;
		return result;
	}
	for (int m = pos ; m >= 0 ; m--)
	{
		if (nums[m] == target)
			result[0] = m;
		else
			break;
	}
	for (int m = pos; m < size; m++)
	{
		if (nums[m] == target)
			result[1] = m;
		else
			break;
	}
	return result;
}

int main()
{
	vector<int> n = { 2,2 };
	vector<int> m = searchRange(n,1);
	cout << m[0] << "," << m[1] << "\n";
	return 0;
}