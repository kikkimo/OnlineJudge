#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//常规版本
vector<vector<int>> combinationSum2_(vector<int>& candidates, int target) {
	vector<vector<int>> result;
	size_t size = candidates.size();
	if (0 == size)
		return result;
	sort(candidates.begin(), candidates.end());
	if (target < candidates[0])
		return result;
	vector<vector<int>> ** dp = new vector<vector<int>> * [1 + size];
	for (int i = 0 ; i < 1 + size ; ++i)
	{
		dp[i] = new vector<vector<int>>[1 + target]();
	}
	for (int i = 1 ; i <= size; ++i)
	{
		for (int j = 1 ; j <= target ; ++j)
		{
			if (candidates[0] > j)
				continue;
			//当前target比数组中第i个元素小，则不能够放入第i个元素重新计算
			if (j < candidates[i - 1])
				dp[i][j] = dp[i - 1][j];		//直接取前面i-1个元素的解集合
			else
			{
				if (j == candidates[i - 1])
					dp[i][j].push_back(vector<int>(1, candidates[i - 1]));

				//此时dp[i][j]解集由dp[i - 1][j]的解集与
				//dp[i-1][j- candidates[i - 1]]的解决加上元素candidates[i - 1]组成
				for (auto & buffer : dp[i - 1][j - candidates[i - 1]])
				{
					//省去了排序查重,保证buffer中顺序始终为由小到大
					if (buffer[buffer.size() - 1] <= candidates[i - 1])
					{
						buffer.push_back(candidates[i - 1]);
						dp[i][j].push_back(buffer);
					}
				}
				for (auto & buffer : dp[i-1][j])	
				{
					//dp[i-1][j]可能与dp[i-1][j- candidates[i - 1]]加candidates[i - 1]重复
					//由于存入时buffer已经排过序
					if (find(dp[i][j].begin(),dp[i][j].end(),buffer) == dp[i][j].end())
						dp[i][j].push_back(buffer);
				}
			}
		}
	}
	result = dp[size][target];
	for (int i = 0; i < 1 + size; ++i)
	{
		delete [] dp[i];
	}
	delete[] dp;
	return result;
}

vector<string> splitstr(string& str,const char token)
{
	vector<string> res;
	if (str == "")
		return res;

	int start = 0;
	for (;;)
	{
		int end = str.find(token, start);
		if (std::string::npos == end)
			break;
		auto buffer = str.substr(start, end - start);
		res.push_back(buffer);
		start = end + 1;
	}
	return res;
}

//利用字符串存储解集
vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
{
	vector<vector<int>> result;
	size_t size = candidates.size();
	if (0 == size)
		return result;
	sort(candidates.begin(), candidates.end());
	if (target < candidates[0])
		return result;
	string** dp = new string * [1 + size];
	for (int i = 0 ; i < 1 + size ; ++i)
	{
		dp[i] = new string[1 + target];
	}
	for (int j = 1; j <= target ; ++j)
	{
		if (candidates[0] > j)
			continue;
		for (int i = 1; i <= size; ++i)
		{
			if (j == candidates[i - 1])
			{
				dp[i][j] = to_string(candidates[i - 1]);
				dp[i][j] += " ;";		//一个解集中的一个解由‘;’号分割
				break;					//只赋值一次
			}
		}
	}
	for (int j = 1; j <= target; ++j)
	{
		if (candidates[0] > j)
			continue;
		for (int i = 1; i <= size; ++i)
		{
			//当前target比数组中第i个元素小，则不能够放入第i个元素重新计算
			if (j < candidates[i - 1])
				dp[i][j] = dp[i - 1][j];		//直接取前面i-1个元素的解集合
			else
			{	
				if (!dp[i - 1][j].empty())
				{
					dp[i][j] += dp[i - 1][j];
				}
				//此时dp[i][j]解集由dp[i - 1][j]的解集与
				//dp[i-1][j- candidates[i - 1]]的解决加上元素candidates[i - 1]组成
				if (!dp[i - 1][j - candidates[i - 1]].empty())
				{
					auto strlist1 = splitstr(dp[i - 1][j - candidates[i - 1]],';');
					auto strlist2 = splitstr(dp[i][j], ';');
					for (auto & buffer : strlist1)
					{
						//取出buffer中最后一个数,最后一个数要不大于candidates[i-1]
						int len = buffer.length();
						int pos = buffer.rfind(" ",len-2);
						string strlastNum = buffer.substr(pos + 1, len - pos - 1);
						if (stoi(strlastNum) <= candidates[i - 1])
						{
							//一个解中的数字以空格隔开
							buffer = buffer + to_string(candidates[i - 1]) + " ";
							if (find(strlist2.begin(),strlist2.end(),buffer) == strlist2.end())
								dp[i][j] = dp[i][j] + buffer + ";";
						}
					}
				}
			}
		}
	}
	if (!dp[size][target].empty())
	{
		auto strlist = splitstr(dp[size][target], ';');
		for (auto & buffer : strlist)
		{
			auto numlist = splitstr(buffer, ' ');
			vector<int> nums;
			for (int i = 0 ; i < numlist.size() ; ++i)
			{
				nums.push_back(std::stoi(numlist[i]));
			}
			result.push_back(nums);
		}
	}
	for (int i = 0; i < 1 + size; ++i)
	{
		delete [] dp[i];
	}
	delete[] dp;
	return result;
}

int main()
{	
	vector<int> candidates1 = { 10,1,2,7,6,1,5 };
	int target1 = 8;
	vector<vector<int>> res1 = combinationSum2(candidates1, target1);
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
	vector<int> candidates2 = { 2,5,2,1,2 };
	int target2 = 5;
	vector<vector<int>> res2 = combinationSum2(candidates2, target2);
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