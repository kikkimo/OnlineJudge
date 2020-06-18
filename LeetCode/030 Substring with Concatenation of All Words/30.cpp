#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
using namespace std;

//ȫ���а汾�Ե��ʶ��кܴ�ʱ��ʱ����Ϊȫ�����ٶ���
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
		//1��Ԫ�ػ���û��Ԫ��
		if (first == last || first == --next) {
			return false;
		}
		for (;;) { // ���Ҳ࿪ʼ�ҵ�һ������Ԫ�������ֵ���
			auto next_1 = next;
			if (*--next < *next_1) { // �ҵ��������ֵ��������Ԫ��
				auto mid = last;	//���Ҳ��ҵ�һ������A_i��Ԫ��,��ΪA_j
				do {				//����A_j=*mid , A_i=*next
					--mid;
				} while (!(*next < *mid));
				std::iter_swap(next, mid); //����A_i��A_j
				std::reverse(next_1, last);	//��A_i+1������β��Ԫ�ؽ��з�ת
				return true;
			}
			if (next == first) { // ������Ԫ�ش��ݼ������л�ԭ
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

//������ȱ������ҽ⣬����word�б�ܴ���Ȼ��ʱ�����Σ�
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
	bool GetNextNeighbor(const vector<vector<int>>& matchIndexList,	//ÿ�����ʵ������б�
		const vector<vector<int>>& matrix,		//�ʵ��ڽӾ���
		const std::vector<bool>& bVisited,	//���Ƿ���ʹ�
		const int & wordlength,			//���ʳ���
		const int& lastWordIndex,		//��һ���ʵ���� matchIndexList.i
		const int& lastIndex,			//��һ���ʵ���������� matchIndexList.i.j
		int & nextWordIndex,		//��һ���ʵ����
		int & nextIndex)			//��һ���ʵ����������
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
	//������ȱ���
	void DFS(vector<int> & result,		//������
		const vector<vector<int>>& matchIndexList,	//ÿ�����ʵ������б�
		const vector<vector<int>>& matrix,		//�ʵ��ڽӾ���
		const int wordlength,					//һ�����ʳ���
		int pos)								//��һ�����ʵ����
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
						//���ڷ���������һ�������һ�����ʵ�����ֻ��Ψһ�ģ���˶��ڵ�һ�����ʵ�һ������
						//ֻ����Ψһ�⣬����Ҫ����Ѱ���������
						continue;
					}
				}
				else
				{
					pair<int, int> last = myStack.top();
					nextWordIndex = last.first;
					nextIndex = last.second;
					bVisited[nextWordIndex] = false;
					myStack.pop();		//����
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
		//����1�����ʵ�������Ҫ��������
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
		//words���ڽӾ���
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

//�뵽�˼򵥷�������Ȼ����ʱ....
class Solution3 {
public:
	bool isMatch(const vector<string>& words,	//ԭ���ʶ���,������
		vector<string>& innerWords,				//�Աȵ��ʶ���������ԭ���ʶ����еĵ���
		vector<string>& outerWords)				//�Աȵ��ʶ����в�����ԭ���ʶ����еĵ���
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
	bool FirstMatch(const vector<string>& words,	//ԭ���ʶ���
		const vector<string>& wordsComp,		//�Աȵĵ��ʶ���
		vector<string>& innerWords,				//�Աȵ��ʶ���������ԭ���ʶ����еĵ���
		vector<string>& outerWords)				//�Աȵ��ʶ����в�����ԭ���ʶ����еĵ���
	{
		size_t size = words.size();
		if (size != wordsComp.size())
			return false;			//�쳣
		for (int i = 0; i < size; ++i)
		{
			if (find(words.begin(), words.end(), wordsComp[i]) == words.end())
			{
				//û�ҵ�
				outerWords.push_back(wordsComp[i]);
			}
			else
			{
				innerWords.push_back(wordsComp[i]);
			}
		}
		return isMatch(words, innerWords, outerWords);
	}
	bool NextMatch(const vector<string>& words,	//ԭ���ʶ���
		const string deleteWord,		//wordComp����Ҫɾ���ĵ���
		const string addWord,				//wordComp�������ĵ���
		vector<string>& innerWords,				//�Աȵ��ʶ���������ԭ���ʶ����еĵ���
		vector<string>& outerWords)				//�Աȵ��ʶ����в�����ԭ���ʶ����еĵ���
	{
		if (isMatch(words, innerWords, outerWords))		//��innerWordsȫ��ԭ���ʶ���
		{
			//ֻ��Ҫ�ж������ʺ�ɾȥ���Ƿ���ͬ
			if (addWord == deleteWord)
			{
				return true;
			}
			else
			{
				//innerWordsɾȥdeleteWord, outerWords����addWord
				auto it = find(innerWords.begin(), innerWords.end(), deleteWord);
				innerWords.erase(it);
				outerWords.push_back(addWord);
				return false;
			}
		}
		else
		{
			//���ȴ�outerWords��ɾ��deleteWord
			auto it = find(outerWords.begin(), outerWords.end(), deleteWord);
			if (it == outerWords.end())		//deleteWord������outerWords
			{
				auto it1 = find(innerWords.begin(), innerWords.end(), deleteWord);
				innerWords.erase(it1);
			}
			else
				outerWords.erase(it);

			//�ж�addWord������һ�ε�innerWords����outerWords
			auto it2 = find(words.begin(), words.end(), addWord);
			if (it2 == words.end()) //��outerWords
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

		//���ڵ��ʶ����е��ʳ���һ��,���迼�Ǹ������
		int wordlength = words[0].length();
		int sumlength = wordlength * wordSize;
		if (sumlength > len)
			return result;

		sort(words.begin(), words.end());
		for (int k = 0; k < wordlength; ++k)
		{
			vector<string> innerWords;				//�Աȵ��ʶ���������ԭ���ʶ����еĵ���
			vector<string> outerWords;				//�Աȵ��ʶ����в�����ԭ���ʶ����еĵ���
			bool bFirstMatch = true;
			for (int i = k; i <= len - sumlength; i += wordlength)	//ÿ��ֱ��ƫ��һ�����ʳ���
			{
				if (bFirstMatch)
				{
					bFirstMatch = false;
					vector<string> wordComp;				//�ԱȵĴ���
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

//��Solution3�а汾����map�Ƚϣ��������ʴ�Ƶֱ��ͼ
class Solution {
public:
	bool isMatch(const map<string, int>& wordHis,				//ԭ���ʶ���ֱ��ͼ
		const map<string, int>& innerHis,						//inner����ֱ��ͼ
		const map<string, int>& outerHis)
	{
		if (outerHis.size() > 0)
			return false;
		size_t  size = wordHis.size();
		if (innerHis.size() != size)
			return false;
		return (wordHis == innerHis);
	}
	bool FirstMatch(const vector<string>& words,	//ԭ���ʶ���
		const vector<string>& wordsComp,		//�Աȵĵ��ʶ���
		map<string,int> & wordHis,				//ԭ���ʶ���ֱ��ͼ
		map<string,int> & innerHis,				//inner����ֱ��ͼ
		map<string, int> & outerHis)			//outer����ֱ��ͼ
	{
		size_t size = words.size();
		if (size != wordsComp.size())
			return false;			//�쳣
		for (int i = 0; i < size; ++i)
		{
			if (wordHis.find(words[i]) == wordHis.end())
			{
				//û�ҵ�
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
	bool NextMatch(const string deleteWord,		//wordComp����Ҫɾ���ĵ���
		const string addWord,				//wordComp�������ĵ���
		const map<string, int>& wordHis,	//ԭ���ʶ���ֱ��ͼ
		map<string, int>& innerHis,			//inner����ֱ��ͼ
		map<string, int>& outerHis)			//outer����ֱ��ͼ
	{
		if (isMatch(wordHis, innerHis, outerHis))		//��innerWordsȫ��ԭ���ʶ���
		{
			//ֻ��Ҫ�ж������ʺ�ɾȥ���Ƿ���ͬ
			if (addWord == deleteWord)
			{
				return true;
			}
			else
			{
				//innerHisɾȥdeleteWord, outerHis����addWord
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
			//���ȴ�outerWords��ɾ��deleteWord
			auto it = outerHis.find(deleteWord);
			if (it == outerHis.end())		//deleteWord������outerHis
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

			//�ж�addWord������һ�ε�innerHis����outerHis
			auto it2 = wordHis.find(addWord);
			if (it2 == wordHis.end()) //��outerHis
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

		//���ڵ��ʶ����е��ʳ���һ��,���迼�Ǹ������
		int wordlength = words[0].length();
		int sumlength = wordlength * wordSize;
		if (sumlength > len)
			return result;

		sort(words.begin(), words.end());
		for (int k = 0; k < wordlength; ++k)
		{
			map<string, int> wordHis;
			map<string, int> innerHis;				//�Աȵ��ʶ���������ԭ���ʶ����еĵ���
			map<string, int> outerHis;				//�Աȵ��ʶ����в�����ԭ���ʶ����еĵ���
			bool bFirstMatch = true;
			for (int i = k; i <= len - sumlength; i += wordlength)	//ÿ��ֱ��ƫ��һ�����ʳ���
			{
				if (bFirstMatch)
				{
					bFirstMatch = false;
					vector<string> wordComp;				//�ԱȵĴ���
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