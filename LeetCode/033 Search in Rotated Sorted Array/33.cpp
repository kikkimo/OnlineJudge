#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int search(vector<int>& nums, int first, int last, int target)
{
	if (last < first)
		return -1;
	if (first == last)
	{
		return (target == nums[first]) ? first : -1;
	}
	while (first < last - 1)
	{
		int mid = ((first + last) >> 1);
		if (nums[first] >= target && target >= nums[mid] ||
			nums[first] <= target && target <= nums[mid])
		{
			last = mid;
		}
		else
			first = mid;
	}
	if (target == nums[first])
		return first;
	if (target == nums[last])
		return last;
	return -1;
}

int GetPivot(vector<int>& nums)
{
	int first = 0;
	int last = nums.size() - 1;
	if (first == last || first == (last - 1))
		return first;
	for (;;)
	{
		int mid = ((first + last) >> 1);
		if (mid == first)
			return first;
		if (mid == last)
			return last;
		if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1] && 
			nums[mid] > nums[first])
			return mid+1;
		if (nums[mid] < nums[mid - 1] && nums[mid] < nums[mid + 1] &&
			nums[mid] < nums[first])
			return mid;
		if ((nums[mid] > nums[mid - 1] && nums[first] < nums[mid - 1]) ||
			(nums[mid] < nums[mid - 1] && nums[first] > nums[mid - 1]))
			first = mid;
		else
			last = mid;
	}
}

//时间复杂度O(logn)实现数字查找
int search(vector<int>& nums, int target) {
	size_t size = nums.size();
	if (0 == size)
		return -1;
	if (1 == size)
	{
		return (nums[0] == target ? 0 : -1);
	}
	int pivot = GetPivot(nums);
	int n = search(nums, 0, pivot - 1, target);
	if (n != -1)
		return n;
	n = search(nums, pivot, size - 1, target);
	if (n != -1)
		return n;
	return -1;
}

int main()
{
	vector<int> n = { 4, 5, 6, 7, 0, 1, 2 };
	int m = search(n,1);
	cout << m << "\n";
	return 0;
}