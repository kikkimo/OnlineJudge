#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	bool isValidSudoku(vector<vector<char>>& board) {
		for (int nRow = 0; nRow < 9; nRow++)
		{
			int NumCounts[10] = { 0 };
			for (int nCol = 0; nCol < 9; nCol++)
			{
				char ch = board[nRow][nCol];
				int val = 0;
				if (ch != '.')
				{
					val = ch - '0';
					NumCounts[val] ++;
					if (val && NumCounts[val] > 1)
						return false;
				}
			}
		}
		//检查每列
		for (int nCol = 0; nCol < 9; nCol++)
		{
			int NumCounts[10] = { 0 };
			for (int nRow = 0; nRow < 9; nRow++)
			{
				char ch = board[nRow][nCol];
				int val = 0;
				if (ch != '.')
				{
					val = ch - '0';
					NumCounts[val] ++;
					if (val && NumCounts[val] > 1)
						return false;
				}
			}
		}
		//检查每宫
		for (int nBoxRow = 0; nBoxRow < 3; nBoxRow++)
		{
			for (int nBoxCol = 0; nBoxCol < 3; nBoxCol++)
			{
				int NumCounts[10] = { 0 };
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						int ni = nBoxRow * 3 + i;
						int nj = nBoxCol * 3 + j;
						char ch = board[ni][nj];
						int val = 0;
						if (ch != '.')
						{
							val = ch - '0';
							NumCounts[val] ++;
							if (val && NumCounts[val] > 1)
								return false;
						}
					}
				}
			}
		}
		return true;
	}
};

int main()
{
	return 0;
}