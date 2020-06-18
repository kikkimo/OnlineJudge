#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
using namespace std;

//全排列版本对单词队列很大时超时，因为全排列速度慢
class PermSolution {
public:
	int strStr(string& haystack, string& needle, const int startPos = 0) {
		size_t lenstack = haystack.size();
		size_t lensub = needle.size();
		if (lensub > lenstack)
			return -1;
		for (int i = startPos; i <= lenstack - lensub; ++i)
		{
			int count = 0;
			int i0 = i;
			for (int j = 0; j < lensub; ++j)
			{
				if (needle[j] == haystack[i0])
				{
					count++;
					i0++;
				}
				else
					break;
			}
			if (count == lensub)
				return i;
		}
		return -1;
	}

	template <typename _Iter>
	bool get_next_perm(_Iter first, _Iter last) {
		auto next = last;
		//1个元素或者没有元素
		if (first == last || first == --next) {
			return false;
		}
		for (;;) { // 从右侧开始找到一个连续元素满足字典序
			auto next_1 = next;
			if (*--next < *next_1) { // 找到了满足字典序的连续元素
				auto mid = last;	//从右侧找到一个大于A_i的元素,记为A_j
				do {				//这里A_j=*mid , A_i=*next
					--mid;
				} while (!(*next < *mid));
				std::iter_swap(next, mid); //交换A_i与A_j
				std::reverse(next_1, last);	//对A_i+1到队列尾的元素进行反转
				return true;
			}
			if (next == first) { // 队列中元素纯递减，进行还原
				//			std::reverse(first, last);
				return false;
			}
		}
	}
	vector<int> findSubstring(string s, vector<string>& words) {
		int len = s.size();
		size_t wordSize = words.size();
		if (0 == len || wordSize == 0)
		{
			vector<int> buffer;
			return buffer;
		}
		bool bFind = true;
		for (int i = 0; i < wordSize; ++i)
		{
			if (-1 == strStr(s, words[i]))
			{
				bFind = false;
				break;
			}
		}
		if (!bFind)
		{
			vector<int> buffer;
			return buffer;
		}
		vector<int> result;
		sort(words.begin(), words.end());
		do
		{
			std::string wordStr;
			for (int i = 0; i < wordSize; ++i)
			{
				wordStr += words[i];
			}
			int nPos = 0;
			for (;;)
			{
				nPos = strStr(s, wordStr, nPos);
				if (nPos == -1)
					break;
				else
					result.push_back(nPos++);
			}
		} while (get_next_perm(words.begin(), words.end()));
		return result;
	}
};

//深度优先遍历查找解，对于word列表很大依然超时，尴尬！
class SolutionDFS {
public:
	int strStr(string& haystack, string& needle, const int startPos = 0) {
		size_t lenstack = haystack.size();
		size_t lensub = needle.size();
		if (lensub > lenstack)
			return -1;
		for (int i = startPos; i <= lenstack - lensub; ++i)
		{
			int count = 0;
			int i0 = i;
			for (int j = 0; j < lensub; ++j)
			{
				if (needle[j] == haystack[i0])
				{
					count++;
					i0++;
				}
				else
					break;
			}
			if (count == lensub)
				return i;
		}
		return -1;
	}
	bool GetNextNeighbor(const vector<vector<int>>& matchIndexList,	//每个单词的索引列表
		const vector<vector<int>>& matrix,		//词的邻接矩阵
		const std::vector<bool>& bVisited,	//词是否访问过
		const int & wordlength,			//单词长度
		const int& lastWordIndex,		//上一个词的序号 matchIndexList.i
		const int& lastIndex,			//上一个词的索引的序号 matchIndexList.i.j
		int & nextWordIndex,		//下一个词的序号
		int & nextIndex)			//下一个词的索引的序号
	{
		size_t wordSize = matchIndexList.size();
		for (int i = nextWordIndex; i < wordSize ; ++i)
		{
			if (lastWordIndex == i || bVisited[i] || matrix[lastWordIndex][i] == 0)
				continue;
			if (i == nextWordIndex)
			{
				for (int j = nextIndex + 1; j < matchIndexList[i].size(); ++j)
				{
					if (matchIndexList[lastWordIndex][lastIndex] + wordlength ==
						matchIndexList[i][j] )
					{
						nextWordIndex = i;
						nextIndex = j;
						return true;
					}
				}
			}
			else
			{
				for (int j = 0; j < matchIndexList[i].size(); ++j)
				{
					if (matchIndexList[lastWordIndex][lastIndex] + wordlength ==
						matchIndexList[i][j])
					{
						nextWordIndex = i;
						nextIndex = j;
						return true;
					}
				}
			}
		}
		return false;
	}
	//深度优先遍历
	void DFS(vector<int> & result,		//保存结果
		const vector<vector<int>>& matchIndexList,	//每个单词的索引列表
		const vector<vector<int>>& matrix,		//词的邻接矩阵
		const int wordlength,					//一个单词长度
		int pos)								//第一个单词的序号
	{
		int wordSize = matchIndexList.size();
		for (int i = 0 ; i < matchIndexList[pos].size() ; ++i)
		{
			std::vector<bool> bVisited(wordSize, false);
			stack<pair<int, int>> myStack;
			myStack.push(pair<int, int>(pos, i));
			int nextWordIndex = 0;
			int nextIndex = -1;
			while (!myStack.empty()) {
				pair<int, int> last = myStack.top();
				int lastWordIndex = last.first;
				int lastIndex = last.second;
				bVisited[lastWordIndex] = true;

				bool bFindNeighbor = false;
				bFindNeighbor = GetNextNeighbor(matchIndexList, matrix, bVisited,
						wordlength, lastWordIndex, lastIndex, nextWordIndex, nextIndex);
				
				if (bFindNeighbor)
				{
					myStack.push(pair<int, int>(nextWordIndex, nextIndex));
					bVisited[nextWordIndex] = true;
					if (wordSize != myStack.size())
					{
						nextWordIndex = 0;
						nextIndex = -1;
						continue;
					}
					else
					{
						int index = matchIndexList[pos][i];
						if (find(result.begin(),result.end(),index) == result.end())
						{
							result.push_back(index);
						}
						//由于符合条件的一个结果第一个单词的索引只是唯一的，因此对于第一个单词的一个索引
						//只存在唯一解，不需要回溯寻找其后续解
						continue;
					}
				}
				else
				{
					pair<int, int> last = myStack.top();
					nextWordIndex = last.first;
					nextIndex = last.second;
					bVisited[nextWordIndex] = false;
					myStack.pop();		//回溯
				}
			}
		}
	}
	vector<int> findSubstring(string s, vector<string>& words) {
		int len = s.size();
		size_t wordSize = words.size();
		if (0 == len || wordSize == 0)
		{
			vector<int> buffer;
			return buffer;
		}
		//对于1个单词的特例需要单独处理
		if (wordSize == 1)
		{
			vector<int> result;
			int nPos = 0;
			for (;;)
			{
				nPos = strStr(s, words[0], nPos);
				if (nPos == -1)
					break;
				else
					result.push_back(nPos++);
			}
			return result;
		}
		bool bFind = true;
		int sumlength = 0;
		for (int i = 0; i < wordSize; ++i)
		{
			sumlength += words[i].length();
			if (-1 == strStr(s, words[i]))
			{
				bFind = false;
				break;
			}
		}
		if (!bFind || sumlength > s.length())
		{
			vector<int> buffer;
			return buffer;
		}
		vector<vector<int>> matchIndexList(wordSize);
		for (int i = 0 ; i < wordSize ; ++i)
		{
			int nPos = 0;
			for (;;)
			{
				nPos = strStr(s, words[i], nPos);
				if (nPos == -1)
					break;
				else
					matchIndexList[i].push_back(nPos++);
			}
		}
		int wordlength = words[0].length();
		//words的邻接矩阵
		vector<vector<int>> matrix(wordSize, vector<int>(wordSize, 0));
		for (int i = 0 ; i < wordSize ; ++i)
		{
			for (int j = i + 1 ; j < wordSize ; ++j)
			{
				if (matrix[i][j] && matrix[i][j])
					continue;
				for (int m = 0 ; m < matchIndexList[i].size() ; ++ m)
				{
					for (int n = 0 ; n < matchIndexList[j].size(); ++n)
					{
						if (matchIndexList[i][m] + wordlength == matchIndexList[j][n] ||
							matchIndexList[j][n] + wordlength == matchIndexList[i][m])
						{
							matrix[i][j] = 1;
							matrix[j][i] = 1;
						}
					}
				}
			}
		}
		vector<int> result;
		for (int i = 0 ; i < wordSize ; ++i)
		{
			DFS(result, matchIndexList, matrix, wordlength, i);
		}
		return result;
	}
};

//想到了简单方法，居然还超时....
class Solution3 {
public:
	bool isMatch(const vector<string>& words,	//原单词队列,已排序
		vector<string>& innerWords,				//对比单词队列中属于原单词队列中的单词
		vector<string>& outerWords)				//对比单词队列中不属于原单词队列中的单词
	{
		if (outerWords.size() > 0)
			return false;
		if (innerWords.size() == words.size())
		{
			sort(innerWords.begin(), innerWords.end());
			return (innerWords == words);
		}
		return false;
	}
	bool FirstMatch(const vector<string>& words,	//原单词队列
		const vector<string>& wordsComp,		//对比的单词队列
		vector<string>& innerWords,				//对比单词队列中属于原单词队列中的单词
		vector<string>& outerWords)				//对比单词队列中不属于原单词队列中的单词
	{
		size_t size = words.size();
		if (size != wordsComp.size())
			return false;			//异常
		for (int i = 0; i < size; ++i)
		{
			if (find(words.begin(), words.end(), wordsComp[i]) == words.end())
			{
				//没找到
				outerWords.push_back(wordsComp[i]);
			}
			else
			{
				innerWords.push_back(wordsComp[i]);
			}
		}
		return isMatch(words, innerWords, outerWords);
	}
	bool NextMatch(const vector<string>& words,	//原单词队列
		const string deleteWord,		//wordComp中需要删除的单词
		const string addWord,				//wordComp中新增的单词
		vector<string>& innerWords,				//对比单词队列中属于原单词队列中的单词
		vector<string>& outerWords)				//对比单词队列中不属于原单词队列中的单词
	{
		if (isMatch(words, innerWords, outerWords))		//当innerWords全是原单词队列
		{
			//只需要判断新增词和删去词是否相同
			if (addWord == deleteWord)
			{
				return true;
			}
			else
			{
				//innerWords删去deleteWord, outerWords新增addWord
				auto it = find(innerWords.begin(), innerWords.end(), deleteWord);
				innerWords.erase(it);
				outerWords.push_back(addWord);
				return false;
			}
		}
		else
		{
			//优先从outerWords中删除deleteWord
			auto it = find(outerWords.begin(), outerWords.end(), deleteWord);
			if (it == outerWords.end())		//deleteWord不是是outerWords
			{
				auto it1 = find(innerWords.begin(), innerWords.end(), deleteWord);
				innerWords.erase(it1);
			}
			else
				outerWords.erase(it);

			//判断addWord归属这一次的innerWords还是outerWords
			auto it2 = find(words.begin(), words.end(), addWord);
			if (it2 == words.end()) //是outerWords
				outerWords.push_back(addWord);
			else
				innerWords.push_back(addWord);

			return isMatch(words, innerWords, outerWords);
		}
	}
	vector<int> findSubstring(string s, vector<string>& words) {
		int len = s.size();
		size_t wordSize = words.size();
		vector<int>  result;
		if (0 == len || wordSize == 0)
			return result;

		//由于单词队列中单词长度一致,无需考虑复杂情况
		int wordlength = words[0].length();
		int sumlength = wordlength * wordSize;
		if (sumlength > len)
			return result;

		sort(words.begin(), words.end());
		for (int k = 0; k < wordlength; ++k)
		{
			vector<string> innerWords;				//对比单词队列中属于原单词队列中的单词
			vector<string> outerWords;				//对比单词队列中不属于原单词队列中的单词
			bool bFirstMatch = true;
			for (int i = k; i <= len - sumlength; i += wordlength)	//每次直接偏移一个单词长度
			{
				if (bFirstMatch)
				{
					bFirstMatch = false;
					vector<string> wordComp;				//对比的词组
					for (int j = 0; j < wordSize; ++j)
					{
						auto it = s.begin() + i + j * wordlength;
						string buf(it, it + wordlength);
						wordComp.push_back(buf);
					}
					if (FirstMatch(words, wordComp, innerWords, outerWords))
						result.push_back(i);		// i == k
				}
				else
				{
					auto it = s.begin();
					string deleteWord(it + i - wordlength, it + i);
					string addWord(it + i - wordlength + sumlength, it + i + sumlength);
					if (NextMatch(words, deleteWord, addWord, innerWords, outerWords))
						result.push_back(i);
				}
			}
		}
		sort(result.begin(), result.end());
		return result;
	}
};

//对Solution3中版本采用map比较，构建单词词频直方图
class Solution {
public:
	bool isMatch(const map<string, int>& wordHis,				//原单词队列直方图
		const map<string, int>& innerHis,						//inner单词直方图
		const map<string, int>& outerHis)
	{
		if (outerHis.size() > 0)
			return false;
		size_t  size = wordHis.size();
		if (innerHis.size() != size)
			return false;
		return (wordHis == innerHis);
	}
	bool FirstMatch(const vector<string>& words,	//原单词队列
		const vector<string>& wordsComp,		//对比的单词队列
		map<string,int> & wordHis,				//原单词队列直方图
		map<string,int> & innerHis,				//inner单词直方图
		map<string, int> & outerHis)			//outer单词直方图
	{
		size_t size = words.size();
		if (size != wordsComp.size())
			return false;			//异常
		for (int i = 0; i < size; ++i)
		{
			if (wordHis.find(words[i]) == wordHis.end())
			{
				//没找到
				wordHis[words[i]] = 1;
			}
			else
			{
				wordHis[words[i]]++;
			}
		}
		for (int i = 0 ; i < size ; ++i)
		{
			if (wordHis.find(wordsComp[i]) == wordHis.end())
			{
				//outerHis
				if (outerHis.find(wordsComp[i]) != outerHis.end())
					outerHis[wordsComp[i]] ++;
				else
					outerHis[wordsComp[i]] = 1;
			}
			else
			{
				//innerHis
				if (innerHis.find(wordsComp[i]) != innerHis.end())
					innerHis[wordsComp[i]] ++;
				else
					innerHis[wordsComp[i]] = 1;
			}
		}
		return isMatch(wordHis, innerHis, outerHis);
	}
	bool NextMatch(const string deleteWord,		//wordComp中需要删除的单词
		const string addWord,				//wordComp中新增的单词
		const map<string, int>& wordHis,	//原单词队列直方图
		map<string, int>& innerHis,			//inner单词直方图
		map<string, int>& outerHis)			//outer单词直方图
	{
		if (isMatch(wordHis, innerHis, outerHis))		//当innerWords全是原单词队列
		{
			//只需要判断新增词和删去词是否相同
			if (addWord == deleteWord)
			{
				return true;
			}
			else
			{
				//innerHis删去deleteWord, outerHis新增addWord
				auto it = innerHis.find(deleteWord);
				if (it->second == 1)
					innerHis.erase(it);
				else
					it->second--;
				
				auto it1 = outerHis.find(addWord);
				if (it1 != outerHis.end())
				{
					it1->second++;
				}
				else
					outerHis[addWord] = 1;

				return false;
			}
		}
		else
		{
			//优先从outerWords中删除deleteWord
			auto it = outerHis.find(deleteWord);
			if (it == outerHis.end())		//deleteWord不是是outerHis
			{
				auto it1 = innerHis.find(deleteWord);
				if (it1->second == 1)
					innerHis.erase(it1);
				else
					it1->second--;
			}
			else
			{
				if (it->second == 1)
					outerHis.erase(it);
				else
					it->second--;
			}

			//判断addWord归属这一次的innerHis还是outerHis
			auto it2 = wordHis.find(addWord);
			if (it2 == wordHis.end()) //是outerHis
			{
				if (outerHis.find(addWord) == outerHis.end())
				{
					outerHis[addWord] = 1;
				}
				else
					outerHis[addWord]++;
			}
			else
			{
				if (innerHis.find(addWord) == innerHis.end())
				{
					innerHis[addWord] = 1;
				}
				else
					innerHis[addWord]++;
			}

			return isMatch(wordHis, innerHis, outerHis);
		}
	}
	vector<int> findSubstring(string s, vector<string>& words) {
		int len = s.size();
		size_t wordSize = words.size();
		vector<int>  result;
		if (0 == len || wordSize == 0)
			return result;

		//由于单词队列中单词长度一致,无需考虑复杂情况
		int wordlength = words[0].length();
		int sumlength = wordlength * wordSize;
		if (sumlength > len)
			return result;

		sort(words.begin(), words.end());
		for (int k = 0; k < wordlength; ++k)
		{
			map<string, int> wordHis;
			map<string, int> innerHis;				//对比单词队列中属于原单词队列中的单词
			map<string, int> outerHis;				//对比单词队列中不属于原单词队列中的单词
			bool bFirstMatch = true;
			for (int i = k; i <= len - sumlength; i += wordlength)	//每次直接偏移一个单词长度
			{
				if (bFirstMatch)
				{
					bFirstMatch = false;
					vector<string> wordComp;				//对比的词组
					for (int j = 0; j < wordSize; ++j)
					{
						auto it = s.begin() + i + j * wordlength;
						string buf(it, it + wordlength);
						wordComp.push_back(buf);
					}
					if (FirstMatch(words, wordComp,wordHis,innerHis,outerHis))
						result.push_back(i);		// i == k
				}
				else
				{
					auto it = s.begin();
					string deleteWord(it + i - wordlength, it + i);
					string addWord(it + i - wordlength + sumlength, it + i + sumlength);
					if (NextMatch(deleteWord, addWord, wordHis, innerHis, outerHis))
						result.push_back(i);
				}
			}
		}
		sort(result.begin(), result.end());
		return result;
	}
};

int main()
{
	Solution solution;
	string s = "wordgoodgoodgoodbestword";
	vector<string> words = { "word", "good", "best", "word" };
	vector<int> n = solution.findSubstring(s, words);
	for (int i = 0; i < n.size(); ++i)
	{
		cout << n[i] << " ";
	}
	cout << "\n";
	return 0;
}