#include <iostream>
#include <vector>
using namespace  std;

#define PRINTF_IN_FILE 0

void PrintSoduku(vector< vector<char> >& board)
{
	FILE * fp = NULL;
	if (PRINTF_IN_FILE)
		 fp = fopen("..\\source\\out.txt","a+");
	for (int i = 0  ; i < board.size() ; i++)
	{
		for (int j = 0 ; j < board[i].size() ; j++)
		{
			char ch = board[i][j];
			cout << ch << " ";
			if (PRINTF_IN_FILE) fprintf(fp,"%c ",ch);
		}
		cout<<endl;
		if (PRINTF_IN_FILE) fprintf(fp,"\r\n");
	}
	if (PRINTF_IN_FILE) fprintf(fp,"\r\n\r\n");
	if (PRINTF_IN_FILE) fclose(fp);
	cout<<endl;
}

void PrintSoduku(int SudokuNum[][9])
{
	if (PRINTF_IN_FILE == 0)
		return;
	FILE * fp = fopen("..\\source\\bad.txt","a+");
	for (int i = 0  ; i < 9 ; i++)
	{
		for (int j = 0 ; j < 9 ; j++)
		{
			if (SudokuNum[i][j])
				fprintf(fp,"%d ",SudokuNum[i][j]);
			else
				fprintf(fp,". ");
		}
		fprintf(fp,"\r\n");
	}
	fprintf(fp,"\r\n\r\n");
	fclose(fp);
}

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
bool IsBadCase(vector< vector<char> >& board,int row,int col,int value)		
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
	
	for (i = 0 ; i < board.size() ; i++)
	{
		vector<char> strRow = board[i];
		for (j = 0 ; j < 9 ; j ++)
		{
			char ch = strRow[j];
			if (ch != '.')
			{
				int val = ch - '0';
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
		PrintSoduku(SudokuNum);
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
					PrintSoduku(SudokuNum);
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
					PrintSoduku(SudokuNum);
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

void solveSudoku(vector< vector<char> >& board) {
	if (board.size() != 9)
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

	for (i = 0 ; i < board.size() ; i++)
	{
		vector<char> strRow = board[i];
		for (j = 0 ; j < 9 ; j ++)
		{
			char ch = strRow[j];
			if (ch != '.')
			{
				int val = ch - '0';
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
					board[i][j] = val + '0';
					SolveNumSize--;
					PrintSoduku(board);
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
					board[i][j] = val + '0';
					SolveNumSize--;
					PrintSoduku(board);
				}
			}
		}

		if (LastSolveNumSize == SolveNumSize)
		{
			PrintSoduku(board);
			//�������������޷������������Ҫ������������
			if (SolveNumSize != 0)		//�������������������п�λ����Ҫ��������
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
								if (IsBadCase(board,i,j,k+1) == false)
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
							board[i][j] = nValue + '0';
							SolveNumSize--;
							PrintSoduku(board);
							bOk = true;
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

bool CheckSudoku( vector<vector<char> >& board)
{
	//�����������Ч������ָ���С��17���ض��ǲ���������
	int nNumCount = 0;
	for (int i  = 0 ; i < 9 ; i ++)
	{
		for (int j = 0 ; j < 9 ; j ++)
		{
			char ch = board[i][j];
			if (ch != '.')
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
			char ch = board[nRow][nCol];
			int val = 0;
			if (ch != '.')
			{
				val = ch - '0';
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
			char ch = board[nRow][nCol];
			int val = 0;
			if (ch != '.')
			{
				val = ch - '0';
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
					char ch = board[ni][nj];
					int val = 0;
					if (ch != '.')
					{
						val = ch - '0';
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

bool isValidSudoku(vector< vector<char> >& board) {
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

	char s[] = {
		    '.','.','.','.','.','.','2','3','4',
			'.','1','.','.','.','.','.','.','.',
			'.','.','.','.','.','.','5','6','.',
			'.','.','.','.','.','.','.','.','.',
			'.','.','.','.','.','.','.','.','.',
			'.','.','.','.','.','.','.','.','.',
			'.','8','.','.','.','.','.','.','.',
			'.','.','.','7','9','.','.','.','.',
			'.','.','.','.','.','.','.','8','.'
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

	vector< vector<char> > board;

	for (int i = 0 ; i < 9 ; i++)
	{
		vector<char> str;
		for (int j = 0 ; j < 9 ; j++)
			str.push_back(s[i*9+j]);
		board.push_back(str);
	}

	PrintSoduku(board);

	solveSudoku(board);

	PrintSoduku(board);
	cout << "������Ч�ԣ�" << isValidSudoku(board) << endl;

}