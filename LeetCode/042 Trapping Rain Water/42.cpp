#include <iostream>
#include <vector>
#include <map>

using namespace std;

int trap(vector<int>& height) {
	size_t hgtSize = height.size();
	if (1 >= hgtSize)
		return 0;
	int maxhgt = -1;
	int minhgt = INT_MAX; 
	int i;
	for (i = 0 ; i < hgtSize ; ++i)
		minhgt = height[i] < minhgt ? height[i] : minhgt;

	map<int,int> hgtMap;
	for (i = 0 ; i < hgtSize; ++i)
	{
		height[i] -= minhgt;
		if (height[i])
		{
			hgtMap[i] = height[i];
		}
	}
	int trapped = 0;		// rain water are being trapped.
	if (hgtMap.size() <= 1)
		return trapped;
	for (;;)
	{
		minhgt = INT_MAX; 
		map<int,int>::iterator it;
		for (it = hgtMap.begin() ; it != hgtMap.end() ; ++it)
		{
			int hgt = it->second;
			if (hgt)
				minhgt = hgt < minhgt ? hgt : minhgt;
		}
		if (INT_MAX == minhgt)
			break;
		for (it = hgtMap.begin() ; it != hgtMap.end() ; ++it)
		{
			map<int,int>::iterator next_it = it;
			while(++next_it != hgtMap.end())
			{
				if (next_it->second)
				{
					int hgt = next_it->first - it->first - 1;
					trapped += hgt*minhgt;
					break;
				}
			}
			if (it->second)
				it->second -= minhgt;
		}
	}
	return trapped;
 }

int trap1(vector<int>& height) {
	size_t hgtSize = height.size();
	if (1 >= hgtSize)
		return 0;
	int maxhgt = -1;
	int minhgt = INT_MAX; 
	int i;
	for (i = 0 ; i < hgtSize ; ++i)
		minhgt = height[i] < minhgt ? height[i] : minhgt;
	
	map<int,int> hgtMap;
	for (i = 0 ; i < hgtSize; ++i)
	{
		height[i] -= minhgt;
		if (height[i])
		{
			hgtMap[i] = height[i];
		}
	}
	int trapped = 0;		// rain water are being trapped.
	for (;;)
	{
		if (hgtMap.size() <= 1)
			break;
		map<int,int>::iterator it;
		minhgt = INT_MAX; 
		for (it = hgtMap.begin() ; it != hgtMap.end() ; ++it)
			minhgt = it->second < minhgt ? it->second : minhgt;
		vector<map<int,int>::iterator> erase_it;
		for (it = hgtMap.begin() ; it != hgtMap.end() ; ++it)
		{
			map<int,int>::iterator next_it = it;
			next_it++;
			if (next_it != hgtMap.end())
				trapped = trapped + (next_it->first - it->first - 1) * minhgt;
			it->second -= minhgt;
			if (it->second == 0)
				erase_it.push_back(it);
		}
		for (i = 0 ; i < erase_it.size() ; ++i)
			hgtMap.erase(erase_it[i]);
	}
	return trapped;
 }

int main()
{
	int nums[] = {10527,740,9013,1300,29680,4898,13993};
	vector<int> height(nums,nums+7);
	vector<int> height1(nums,nums+7);
	for (int i = 0 ; i < height.size() ; ++i)
	{
		cout << height[i] << " "; 
	}
	cout << "\n" << trap(height)<< "\n"  << trap1(height1) << "\n";
	return 0;
}