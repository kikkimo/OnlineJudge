#include <IOSTREAM>
#include <vector>
#include <windows.h>
#include <time.h>
#include <algorithm>

using namespace std;

double findMedianSortedArrays2(vector<int>& nums1, vector<int>& nums2) {
	int nSize1 = nums1.size();
	int nSize2 = nums2.size();
	

	if (nSize1 == 0 && nSize2 == 0)		//队列1为空
		return 0;

	if (nSize1 == 0 )		//队列1为空
	{
		double re2 = 0;
		if (nSize2 % 2)		//奇数
			re2 = nums2[nSize2 / 2];
		else
		{
			re2 = (nums2[nSize2 / 2] + nums2[nSize2 / 2 - 1]) / 2.0;
		}
		return re2;
	}
	if (nSize2 == 0 )		//队列2为空
	{
		double re1 = 0;
		if (nSize1 % 2)		//奇数
			re1 = nums1[nSize1 / 2];
		else
		{
			re1 = (nums1[nSize1 / 2] + nums1[nSize1 / 2 - 1]) / 2.0;
		}
		return re1;
	}

	vector<int> nums;
	vector<int>::iterator iter1 = nums1.begin();
	vector<int>::iterator iter2 = nums2.begin();
	while(iter1 != nums1.end() || iter2 != nums2.end() )
	{
		int i = *iter1;
		int j = *iter2;
		if (i < j)
		{
			if (iter1 != nums1.end())
			{
				nums.push_back(i);
				iter1++;
			}
			else
			{
				nums.push_back(j);
				iter2 ++;
			}
		}
		else
		{
			if (iter2 != nums2.end())
			{
				nums.push_back(j);
				iter2++;
			}
			else
			{
				nums.push_back(i);
				iter1 ++;
			}
		}
	}

	cout << "num : " << nums.size() << "\r\n";
	for (int  i = 0 ; i < nums.size() ; i++)
	{
		int a = nums[i];
		cout << a <<  "  ";
		if ((1+i) % 5 == 0)
			cout << endl;
	}

	double re = 0;
	int nSize = nums.size();
	if (nSize % 2)		//奇数
		re = nums[nSize / 2];
	else
	{
		re = (nums[nSize / 2] + nums[nSize / 2 - 1]) / 2.0;
	}

	return re;
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	int nSize1 = nums1.size();
	int nSize2 = nums2.size();
	
	if (nSize1 == 0 && nSize2 == 0)		//队列1为空
		return 0;
	
	if (nSize1 == 0 )		//队列1为空
	{
		double re2 = 0;
		if (nSize2 % 2)		//奇数
			re2 = nums2[nSize2 / 2];
		else
		{
			re2 = (nums2[nSize2 / 2] + nums2[nSize2 / 2 - 1]) / 2.0;
		}
		return re2;
	}
	if (nSize2 == 0 )		//队列2为空
	{
		double re1 = 0;
		if (nSize1 % 2)		//奇数
			re1 = nums1[nSize1 / 2];
		else
		{
			re1 = (nums1[nSize1 / 2] + nums1[nSize1 / 2 - 1]) / 2.0;
		}
		return re1;
	}
	int nTop1 = 0 , nBottom1 = nSize1 - 1;
	int nTop2 = 0 , nBottom2 = nSize2 - 1;
	int nMiddle1 = (nTop1 + nBottom1) / 2;
	int nMiddle2 = (nTop2 + nBottom2) / 2;
	while(nBottom1 - nTop1 > 1 || nBottom2 - nTop2 > 1)
	{
		nMiddle1 = (nTop1 + nBottom1) / 2;
		nMiddle2 = (nTop2 + nBottom2) / 2;
		if (abs(nums1[nMiddle1] - nums2[nMiddle2]) <= 1)
			break;
		if (nums1[nMiddle1] > nums2[nMiddle2])
		{
			nBottom1 = nMiddle1;
			nTop2 = nMiddle2;
		}
		else
		{
			nTop1 = nMiddle1;
			nBottom2 = nMiddle2;
		}
	}
	double re = (nums1[nMiddle1] + nums2[nMiddle2]) / 2.0;
	return re;
}


int main()
{
	srand(time(NULL));
	vector<int>  nums1;
	vector<int>  nums2;
	int i,j;

	int m = rand() % 10 + 10;
	int n = rand() % 20 + 5;

	for ( i = 0 ; i < m ; i++)
	{
		int a = rand() % 50 + 20;
		nums1.push_back(a);
	}
	for ( j = 0 ; j < n ; j++)
	{
		int a = rand() % 40 + 40;
		nums2.push_back(a);
	}
// 	nums1.push_back(1);
// 	nums1.push_back(3);
// 	nums2.push_back(2);

	sort(nums1.begin(),nums1.end());
	sort(nums2.begin(),nums2.end());

	cout << "num1 : " << nums1.size() << "\r\n";
	for ( i = 0 ; i < nums1.size() ; i++)
	{
		int a = nums1[i];
		cout << a <<  "  ";
		if ((1+i) % 5 == 0)
			cout << endl;
	}
	cout << "\r\nnums2 : " << nums2.size() << "\r\n";
	for ( j = 0 ; j < nums2.size() ; j++)
	{
		int a = nums2[j];
		cout << a <<  "  ";
		if ((j+1) % 5 == 0)
			cout << endl;
	}

	cout << "\r\n";
	double re = findMedianSortedArrays2(nums1,nums2);
	cout << "\r\nmedian : " << re << endl;
	re = findMedianSortedArrays(nums1,nums2);
	cout << "\r\nmedian2 : " << re << endl;
	return 0;
}