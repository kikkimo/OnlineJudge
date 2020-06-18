#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void nextPermutation(vector<int>& nums) {
	auto first = nums.begin();
	auto last = nums.end();
	auto next = last;
	if (first == last || first == --next)
		return;

	for (;;)
	{
		//从最右侧开始找，找到A_i < A_i+1
		auto next1 = next;
		if (*--next < *next1)
		{
			auto mid = last;	//从最右找A_j > A_i
			do					//这里 A_i = *next
			{					// A_j = * mid
				--mid;
			} while (!(*next < *mid));		
			iter_swap(mid, next);		//交换A_i,A_j
			reverse(next1, last);
			return;
		}
		if (next == first)		//字典序逆序
		{
			reverse(first, last);
			return;
		}
	}
}

int main()
{
	vector<int> n = {1,1,5};
	for (int i = 0; i < n.size(); ++i)
	{
		cout << n[i] << " ";
	}
	cout << "\n";
	nextPermutation(n);
	for (int i = 0; i < n.size(); ++i)
	{
		cout << n[i] << " ";
	}
	cout << "\n";
	return 0;
}