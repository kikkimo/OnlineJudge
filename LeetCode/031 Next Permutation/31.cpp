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
		//�����Ҳ࿪ʼ�ң��ҵ�A_i < A_i+1
		auto next1 = next;
		if (*--next < *next1)
		{
			auto mid = last;	//��������A_j > A_i
			do					//���� A_i = *next
			{					// A_j = * mid
				--mid;
			} while (!(*next < *mid));		
			iter_swap(mid, next);		//����A_i,A_j
			reverse(next1, last);
			return;
		}
		if (next == first)		//�ֵ�������
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