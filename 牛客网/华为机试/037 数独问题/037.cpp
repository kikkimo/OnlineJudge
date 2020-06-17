#include <iostream>
#include <vector>
#include <memory.h>
using namespace  std;


//���к���
void fillNumber(bool **** pflag, int row,int col, int val)
{
	if (col < 0 || col >= 9)
		return;

	if (row < 0 || row >= 9)
		return;

	bool *** flag = *pflag;
	//���ȸ�ָ��Ԫ�ظ�ֵ
	int i,j,k;
	for(i = 0 ; i < 9 ; i++)
	{
		if ( i+1 == val )
			flag[row][col][i] = 1;
		else
			flag[row][col][i] = 0;
	}

	//��ε�row������Ԫ��ȡֵȥ��val
	for (k = 0; k < 9 ; k++)
	{
		if (k != col)
			flag[row][k][val-1] = 0;
	}

	//��col������Ԫ��ȡֵȥ��val
	for (j = 0; j < 9 ; j ++)
	{
		if (j != row)
			flag[j][col][val-1] = 0;
	}

	//��Ӧ��3��3��������Ԫ��ȡֵȥ��val
	int nRow = row / 3;
	int nCol = col / 3;
	for (i = 0 ; i < 3 ; i++ )
	{
		for (j = 0; j < 3 ; j++)
		{
			int ni = i + nRow * 3;
			int nj = j + nCol * 3;
			if ( ni == row && nj == col)
				flag[ni][nj][val-1] = 1;
			else
				flag[ni][nj][val-1] = 0;
		}
	}
}

//�ڲ���ȫ������row�С�col������value��֤ʵΪ�����case,����falseһ����Ч������true��һ����Ч
bool BadCase(vector< vector<int> >& board,int row,int col,int value)		
{
	bool bRe = true;
	if (row < 0  || row >= 9 || col < 0 || col >= 9 || value < 1 || value > 9)
		return bRe;

	int i,j,k;
	bool *** flag =  new bool ** [9];
	for (i = 0 ; i < 9 ; i++)
	{
		flag[i] = new bool *[9];
		for (j = 0 ; j < 9 ; j ++)
		{
			flag[i][j] = new bool[9];
			for (k = 0 ; k < 9 ; k++)
				flag[i][j][k] = 1;			//���Ƚ���־ȫ��Ϊ��Ч
		}
	}

	char map[9][9] = { 0 };
	int SolveNumSize = 81;
	int SudokuNum[9][9] = { 0 };
	
	for (i = 0 ; i < (int)board.size() ; i++)
	{
		vector<int> vec_Row = board[i];
		for (j = 0 ; j < 9 ; j ++)
		{
			int val = vec_Row[j];
			if (val)
			{
				
				fillNumber(&flag,i,j,val);
				SudokuNum[i][j] = val;
				if (map[i][j] != 1)
				{
					SolveNumSize --;
					map[i][j] = 1;
				}
			}
		}
	}

	//row�С�col�����
	if (map[row][col] == 0)
	{
		map[row][col] = 1;
		fillNumber(&flag,row,col,value);
		SolveNumSize--;
		SudokuNum[row][col] = value;
	}
	else
		return bRe;
	

	//������������
	int nCountTimes = 0;
	int LastSolveNumSize = SolveNumSize;
	while(SolveNumSize > 0 && nCountTimes ++ < 100)
	{
		//���μ��ÿ��λ��Ԫ��ȡֵ�Ƿ�Ψһ����Ψһ�򽫸ô��������
		for (i= 0 ; i < 9 ; i++)
		{
			for (j = 0 ; j < 9 ; j++)
			{
				if (map[i][j] == 1)
					continue;
				int nFlagCount = 0;
				int val = 0;
				for (k = 0 ; k < 9 ; k++)
				{
					if (flag[i][j][k] == 1)
					{
						nFlagCount ++;
						val = k+1;
					}
				}
				if (1 == nFlagCount && map[i][j] == 0)		//Ψһ��ǩ
				{
					map[i][j] = 1;
					fillNumber(&flag,i,j,val);
					SudokuNum[i][j] = val;
					SolveNumSize--;
				}
			}
		}

		for ( i = 0 ; i < 9 ; i ++)
		{
			for (j = 0 ; j < 9 ; j++)
			{
				if (map[i][j] == 1)
					continue;
				
				bool bFind = false;
				int val = -1;
				for (k = 0 ; k < 9 ; k ++)
				{
					//����ô�ͬ������Ԫ�ؾ����ж���Ϊk����ô�ֵ�ض�Ϊk
					int nCountRow = 0;
					for (int nl = 0 ; nl < 9 ; nl ++)
					{
						if (nl != j && flag[i][nl][k] == 0)
							nCountRow++;
					}
					if (nCountRow == 8)
					{
						bFind = true;
						val = k+1;
						break;
					}

					//ͬ������Ԫ�ؾ���Ϊk���ô��ض�Ϊk
					int nCountCol = 0;
					for (int nR = 0 ; nR < 9 ; nR ++)
					{
						if (nR != i && flag[nR][j][k] == 0)
							nCountCol++;
					}
					if (nCountCol == 8)
					{
						bFind = true;
						val = k+1;
						break;
					}

					//ͬ������Ԫ�ؾ���Ϊk���ô��ض�Ϊk
					int nCountBox = 0;
					int nRowIndex = i / 3;
					int nColIndex = j / 3;
					for (int ni = 0 ; ni < 3 ; ni++ )
					{
						for (int nj = 0; nj < 3 ; nj++)
						{
							int nii = ni + nRowIndex * 3;
							int njj = nj + nColIndex * 3;
							if (!( nii == i && njj == j) && flag[nii][njj][k] == 0)
								nCountBox++;
						}
					}
					if (nCountBox == 8)
					{
						bFind = true;
						val = k+1;
						break;
					}

				}

				if (bFind && map[i][j] == 0)		//Ψһ��ǩ
				{
					map[i][j] = 1;
					fillNumber(&flag,i,j,val);
					SudokuNum[i][j] = val;
					SolveNumSize--;
				}
			}
		}

		if (LastSolveNumSize == SolveNumSize)
			break;
		else
			LastSolveNumSize = SolveNumSize;
	}

	for (i = 0 ; i < 9 ; i++)
	{
		for (j = 0 ; j < 9 ; j ++)
		{
			delete [] flag[i][j];
		}
		delete [] flag[i];
	}
	delete [] flag;

	//��������Ϸ��ԣ��Ƿ�����false
	//���ڴ�ʱ������һ�������������������ֿ�������ȷ�ģ���һ�����������
	//�жϷǷ�ֻ��ͨ��ÿһ�С��С����У������ֳ��ֵĴ���Ψһ

	
	//���ÿ��
	for (int nRow  = 0 ; nRow < 9 ; nRow ++)
	{
		int NumCounts[10] = { 0 };
		for (int nCol = 0 ; nCol < 9 ; nCol ++)
		{
			NumCounts[SudokuNum[nRow][nCol]] ++;
			if (SudokuNum[nRow][nCol]  &&  NumCounts[SudokuNum[nRow][nCol]] > 1)
				return false;
		}
	}

	//���ÿ��
	for (int nCol  = 0 ; nCol < 9 ; nCol ++)
	{
		int NumCounts[10] = { 0 };
		for (int nRow = 0 ; nRow < 9 ; nRow ++)
		{
			NumCounts[SudokuNum[nRow][nCol]] ++;
			if (SudokuNum[nRow][nCol]  &&  NumCounts[SudokuNum[nRow][nCol]] > 1)
				return false;
		}
	}

	//���ÿ��
	for (int nBoxRow = 0 ; nBoxRow < 3; nBoxRow ++)
	{
		for (int nBoxCol = 0; nBoxCol < 3; nBoxCol ++)
		{
			int NumCounts[10] = { 0 };
			for (i = 0; i < 3 ; i++)
			{
				for (j = 0; j < 3 ; j ++)
				{
					int ni = nBoxRow * 3 + i;
					int nj = nBoxCol * 3 + j;
					NumCounts[SudokuNum[ni][nj]] ++;
					if (SudokuNum[ni][nj] && NumCounts[SudokuNum[ni][nj]] > 1)
						return false;
				}
			}
		}
	}

	return true;

}

void solveSudoku(vector< vector<int> >& board) {
	if ((int)board.size() != 9)
		return;

	int i,j,k;
	bool *** flag =  new bool ** [9];
	for (i = 0 ; i < 9 ; i++)
	{
		flag[i] = new bool *[9];
		for (j = 0 ; j < 9 ; j ++)
		{
			flag[i][j] = new bool[9];
			for (k = 0 ; k < 9 ; k++)
				flag[i][j][k] = 1;			//���Ƚ���־ȫ��Ϊ��Ч
		}
	}

	char map[9][9] = { 0 };
	int SolveNumSize = 81;

	for (i = 0 ; i < (int)board.size() ; i++)
	{
		vector<int> vecRow = board[i];
		for (j = 0 ; j < 9 ; j ++)
		{
			int val = vecRow[j];
			if (val)
			{
				fillNumber(&flag,i,j,val);
				if (map[i][j] != 1)
				{
					SolveNumSize --;
					map[i][j] = 1;
				}
			}
		}
	}

	int nCountTimes = 0;
	int LastSolveNumSize = SolveNumSize;
	while(SolveNumSize > 0 && nCountTimes < 10)
	{
		//���μ��ÿ��λ��Ԫ��ȡֵ�Ƿ�Ψһ����Ψһ�򽫸ô��������
		for (i= 0 ; i < 9 ; i++)
		{
			for (j = 0 ; j < 9 ; j++)
			{
				if (map[i][j] == 1)
					continue;
				int nFlagCount = 0;
				int val = 0;
				for (k = 0 ; k < 9 ; k++)
				{
					if (flag[i][j][k] == 1)
					{
						nFlagCount ++;
						val = k+1;
					}
				}
				if (1 == nFlagCount && map[i][j] == 0)		//Ψһ��ǩ
				{
					map[i][j] = 1;
					fillNumber(&flag,i,j,val);
					board[i][j] = val;
					SolveNumSize--;
				}
			}
		}

		for ( i = 0 ; i < 9 ; i ++)
		{
			for (j = 0 ; j < 9 ; j++)
			{
				if (map[i][j] == 1)
					continue;
				
				bool bFind = false;
				int val = -1;
				for (k = 0 ; k < 9 ; k ++)
				{
					//����ô�ͬ������Ԫ�ؾ����ж���Ϊk����ô�ֵ�ض�Ϊk
					int nCountRow = 0;
					for (int nl = 0 ; nl < 9 ; nl ++)
					{
						if (nl != j && flag[i][nl][k] == 0)
							nCountRow++;
					}
					if (nCountRow == 8)
					{
						bFind = true;
						val = k+1;
						break;
					}

					//ͬ������Ԫ�ؾ���Ϊk���ô��ض�Ϊk
					int nCountCol = 0;
					for (int nR = 0 ; nR < 9 ; nR ++)
					{
						if (nR != i && flag[nR][j][k] == 0)
							nCountCol++;
					}
					if (nCountCol == 8)
					{
						bFind = true;
						val = k+1;
						break;
					}

					//ͬ������Ԫ�ؾ���Ϊk���ô��ض�Ϊk
					int nCountBox = 0;
					int nRowIndex = i / 3;
					int nColIndex = j / 3;
					for (int ni = 0 ; ni < 3 ; ni++ )
					{
						for (int nj = 0; nj < 3 ; nj++)
						{
							int nii = ni + nRowIndex * 3;
							int njj = nj + nColIndex * 3;
							if (!( nii == i && njj == j) && flag[nii][njj][k] == 0)
								nCountBox++;
						}
					}
					if (nCountBox == 8)
					{
						bFind = true;
						val = k+1;
						break;
					}

				}

				if (bFind && map[i][j] == 0)		//Ψһ��ǩ
				{
					map[i][j] = 1;
					fillNumber(&flag,i,j,val);
					board[i][j] = val;
					SolveNumSize--;
				}
			}
		}

		if (LastSolveNumSize == SolveNumSize)
		{
			nCountTimes ++;
			//�������������޷������������Ҫ������������
			if (SolveNumSize != 0 && nCountTimes < 5)		//�������������������п�λ����Ҫ��������
			{
				bool bOk = false;
				for (i= 0 ; i < 9 ; i++)
				{
					for (j = 0 ; j < 9 ; j++)
					{
						if (map[i][j] == 1)
							continue;
						
						for (k = 0 ; k < 9 ; k ++)
						{
							if (flag[i][j][k] == 1)
							{
								if (BadCase(board,i,j,k+1) == false)
									flag[i][j][k] = 0;
							}
						}
						int nCount = 0;
						int nValue = 0;
						for (k = 0 ; k < 9 ; k ++)
						{
							if (flag[i][j][k] == 1)
							{
								nCount ++;
								nValue = k+1;
							}
						}
						if (nCount == 1)		//�ٴ��ҵ�һ���µ�Ԫ��
						{
							map[i][j] = 1;
							fillNumber(&flag,i,j,nValue);
							board[i][j] = nValue;
							SolveNumSize--;
							bOk = true;
							break;
						}
					}
					if (bOk)
						break;
				}
			}
			else{
				//��ʱ��������Ψһ�⣬�������һ����
				bool bOk = false;
				for (i= 0 ; i < 9 ; i++)
				{
					for (j = 0 ; j < 9 ; j++)
					{
						if (map[i][j] == 1)
							continue;
						
						int nValue = 0;
						for (k = 0 ; k < 9 ; k ++)
						{
							if (flag[i][j][k] == 1)
							{
								if (BadCase(board,i,j,k+1))
								{
									bOk = true;
									nValue = k+1;
									break;
								}
							}
						}
						
						if (bOk)		//�ٴ��ҵ�һ���µ�Ԫ��
						{
							map[i][j] = 1;
							fillNumber(&flag,i,j,nValue);
							board[i][j] = nValue;
							SolveNumSize--;
							break;
						}
					}
					if (bOk)
						break;
				}
			}
		}
		else
			LastSolveNumSize = SolveNumSize;
	}


	for (i = 0 ; i < 9 ; i++)
	{
		for (j = 0 ; j < 9 ; j ++)
		{
			delete [] flag[i][j];
		}
		delete [] flag[i];
	}
	delete [] flag;
	
}

void PrintSoduku(vector< vector<int> > & board)
{
	if ((int)board.size() != 9)
		return;

	for (int i = 0 ; i < (int)board.size() ; i ++)
	{
		vector<int> vec_row = board[i];
		for (int j = 0 ; j < (int)vec_row.size() ; j++)
		{
			if (j != (int)vec_row.size() -1)
				cout << board[i][j] << " ";
			else
				cout << board[i][j] << "\n";
		}
	}
}

bool CheckSudoku( vector<vector<int> >& board)
{
	//�����������Ч������ָ���С��17���ض��ǲ���������
	int nNumCount = 0;
	for (int i  = 0 ; i < 9 ; i ++)
	{
		for (int j = 0 ; j < 9 ; j ++)
		{
			int val = board[i][j];
			if (val)
				nNumCount ++;
		}
	}
	if (nNumCount < 17) return false;
	//��������Ϸ��ԣ��Ƿ�����false
	//���ڴ�ʱ������һ�������������������ֿ�������ȷ�ģ���һ�����������
	//�жϷǷ�ֻ��ͨ��ÿһ�С��С����У������ֳ��ֵĴ���Ψһ
	//���ÿ��
	for (int nRow  = 0 ; nRow < 9 ; nRow ++)
	{
		int NumCounts[10] = { 0 };
		for (int nCol = 0 ; nCol < 9 ; nCol ++)
		{
			int val = board[nRow][nCol];
			if (val)
			{
				NumCounts[val] ++;
				if (val  &&  NumCounts[val] > 1)
					return false;
			}
		}
	}
	
	//���ÿ��
	for (int nCol  = 0 ; nCol < 9 ; nCol ++)
	{
		int NumCounts[10] = { 0 };
		for (int nRow = 0 ; nRow < 9 ; nRow ++)
		{
			int val = board[nRow][nCol];
			if (val)
			{
				NumCounts[val] ++;
				if (val  &&  NumCounts[val] > 1)
					return false;
			}
		}
	}
	
	//���ÿ��
	for (int nBoxRow = 0 ; nBoxRow < 3; nBoxRow ++)
	{
		for (int nBoxCol = 0; nBoxCol < 3; nBoxCol ++)
		{
			int NumCounts[10] = { 0 };
			for (int i = 0; i < 3 ; i++)
			{
				for (int j = 0; j < 3 ; j ++)
				{
					int ni = nBoxRow * 3 + i;
					int nj = nBoxCol * 3 + j;
					int val = board[ni][nj];
					if (val)
					{
						NumCounts[val] ++;
						if (val  &&  NumCounts[val] > 1)
							return false;
					}
				}
			}
		}
	}
	
	return true;
}

bool isValidSudoku(vector< vector<int> >& board) {
	if (CheckSudoku(board) == false)
		return false;
	else
		solveSudoku(board);
	
	return CheckSudoku(board);
}



void main()
{

// 	char s[] = { '5','3','.','.','7','.','.','.','.',
// 		'6','.','.','1','9','5','.','.','.',
// 		'.','9','8','.','.','.','.','6','.',
// 		'8','.','.','.','6','.','.','.','3',
// 		'4','.','.','8','.','3','.','.','1',
// 		'7','.','.','.','2','.','.','.','6',
// 		'.','6','.','.','.','.','2','8','.',
// 		'.','.','.','4','1','9','.','.','5',
// 		'.','.','.','.','8','.','.','7','9'};

// 	char s[] = {
// 		'.','.','9','7','4','8','.','.','.',
// 			'7','.','.','.','.','.','.','.','.',
// 			'.','2','.','1','.','9','.','.','.',
// 			'.','.','7','.','.','.','2','4','.',
// 			'.','6','4','.','1','.','5','9','.',
// 			'.','9','8','.','.','.','3','.','.',
// 			'.','.','.','8','.','3','.','2','.',
// 			'.','.','.','.','.','.','.','.','6',
// 			'.','.','.','2','7','5','9','.','.'
// 	};

	int s[] = {
			7,2,6,9,0,4,0,5,1,
0,8,0,6,0,7,4,3,2,
3,4,1,0,8,5,0,0,9,
0,5,2,4,6,8,0,0,7,
0,3,7,0,0,0,6,8,0,
0,9,0,0,0,3,0,1,0,
0,0,0,0,0,0,0,0,0,
9,0,0,0,2,1,5,0,0,
8,0,0,3,0,0,0,0,0
	};

// 	char s[] = {
// 		'.','3','.','.','7','.','.','.','.',
// 		'.','.','.','1','9','5','.','.','.',
// 		'.','9','8','.','.','.','.','6','.',
// 		'8','.','.','.','6','.','.','.','3',
// 		'4','.','.','8','.','3','.','.','1',
// 		'7','.','.','.','2','.','.','.','6',
// 		'.','6','.','.','.','.','2','8','.',
// 		'.','.','.','4','1','9','.','.','5',
// 		'.','.','.','.','8','.','.','7','.'
// 	};

	vector< vector<int> > board;

	for (int i = 0 ; i < 9 ; i++)
	{
		vector<int> line;
		for (int j = 0 ; j < 9 ; j++)
			line.push_back(s[i*9+j]);
		board.push_back(line);
	}

	if(isValidSudoku(board))
		PrintSoduku(board);


}