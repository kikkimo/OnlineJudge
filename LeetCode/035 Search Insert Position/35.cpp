#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int searchInsert(vector<int>& nums, int target) {
	size_t size = nums.size();
	if (size == 0)
		return 0;
	if (target <= nums[0])
		return 0;
	if (target == nums[size - 1])
		return size - 1;
	if (target > nums[size - 1])
		return size;

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
		if (left + 1 >= right)
		{
			if (nums[left] == target)
				pos = left;
			if (nums[right] == target)
				pos = right;
			break;
		}
	}
	if (pos == -1)
		return left + 1;
	else
		return pos;
}

int main()
{
	vector<int> m1{ 1,3,5,6 };
	cout << searchInsert(m1, 5) << "\n";
	cout << searchInsert(m1, 2) << "\n";
	cout << searchInsert(m1, 7) << "\n";
	cout << searchInsert(m1, 0) << "\n";
	return 0;
}