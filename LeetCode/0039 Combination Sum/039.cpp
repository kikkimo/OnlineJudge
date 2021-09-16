#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	vector<vector<int>> result;
	size_t size = candidates.size();
	if (0 == size)
		return result;
	sort(candidates.begin(), candidates.end());
	if (target < candidates[0])
		return result;
	vector<vector<vector<int>>> dp(1 + target, vector<vector<int>>());
	for (size_t i = 0; i < size && candidates[i] <= target; i++)
		dp[candidates[i]].push_back(vector<int>(1, candidates[i]));
	//dp[i]表示target取值为i时表达式计算的结果
	for (int i = 1 ; i <= target; ++i)
	{
		if (candidates[0] <= i)
		{
			for (int j = 0 ; j < size && candidates[j] <= i; ++j)
			{
				int subTarget = i - candidates[j];
				auto lastBag = dp[subTarget];
				for (auto & buffer : lastBag)
				{
					//省去了排序查重,保证buffer中顺序始终为由小到大
					if (buffer[buffer.size() - 1] <= candidates[j])
					{
						buffer.push_back(candidates[j]);
						dp[i].push_back(buffer);
					}
				}
			}				
		}
	}
	result = dp[target];
	return result;
}

int main()
{
	vector<int> candidates1 = { 1,2};
	int target1 = 1;
	vector<vector<int>> res1 = combinationSum(candidates1, target1);
	for (auto & buffer : res1)
	{
		cout << "[";
		for (auto & num : buffer)
		{
			cout << num << " ";
		}
		cout << "]\n";
	}
	cout << "\n\n\n";
	vector<int> candidates2 = { 2, 3, 5 };
	int target2 = 8;
	vector<vector<int>> res2 = combinationSum(candidates2, target2);
	for (auto& buffer : res2)
	{
		cout << "[";
		for (auto& num : buffer)
		{
			cout << num << " ";
		}
		cout << "]\n";
	}
	return 0;
}