#include <iostream>
#include <vector>
#include <windows.h>
#include <time.h>
using namespace std;

//我的实现
int maxArea2(vector<int>& height) {
	int size = height.size();
	if (size < 2)
		return 0;
	if (size == 2)
		return min(height[0],height[1]);

	int MaxArea = 0;
	int MaxHeight = height[0];
	int MaxPos = 0;
	for (int i = 1 ; i < size ; i++)
	{
		//最大面积查找分为2段，第一段是从0到MaxPos分别计算与当前新加垂线围成的面积
		for (int j = 0 ; j < MaxPos ; j++)
		{
			int area = min(height[j],height[i])*(i-j);
			if (MaxArea < area) MaxArea = area;
		}
		//第二段直接是MaxHeight乘以其对应垂线与当前垂线的距离
		int area2 = min(height[MaxPos],height[i])*(i-MaxPos);
		if (MaxArea < area2) MaxArea = area2;
		if (height[i] > MaxHeight)
		{
			MaxHeight = height[i];
			MaxPos = i;
		}
	}
	return MaxArea;
 }


//其实思路和快速排序很类似
int maxArea(vector<int> &height)
{
	int j=height.size()-1,i=0,mx=0;	
	while(i<j)
	{
		mx=max(mx,((j-i)*(min(height[i],height[j]))));
		if(height[i]<height[j]) 
			i++;
		else 
			j--;
	}
	return mx;
 }


void main()
{
	srand(time(NULL));
	int size = rand() % 10 + 5;
	vector<int> hei;
	cout << "height array : \r\n";
	for (int i = 0 ; i < size ; i++)
	{
		int h = rand() % 20 + 1;
		hei.push_back(h);
		cout << h << "  ";
		if ((i+1) % 5 == 0)
			cout << "\r\n";
	}
	cout << "\r\n" << "MaxArea : " << maxArea2(hei) << endl;
	cout << "\r\n" << "MaxArea2 : " << maxArea(hei) << endl;

}