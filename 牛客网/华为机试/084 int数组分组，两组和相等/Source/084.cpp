#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#define min(a,b) ((a < b) ? a : b)

//n个数中能否找到若干数和等于sum
bool findArray(vector<int> nums,int sum)
{
    vector<int> positive,negative;
	int nZeros = 0;
	int i,j;
    for(i = 0 ; i < (int)nums.size() ; i++)
    {
        if(nums[i] > 0)
            positive.push_back(nums[i]);
        else
			if (nums[i] == 0)
				nZeros++;
			else
				negative.push_back(nums[i]);
    }

	if (nZeros && sum == 0)		//避免数组全为0
		return true;

    int nSizePosi = positive.size();
	int nSizeNega = negative.size();

	if (0 == nSizeNega)
	{
		if(0 == nSizePosi)
			return (0 == sum);
		else
		{
			//数列全为正整数
			if(sum <= 0)
				return false;

			vector< vector<int> >  dp(1+nSizePosi,vector<int>(1+sum,0));
			for (i = 1 ; i<= nSizePosi ; i++)
			{
				for (j = 1; j <= sum ; j++)
				{
					if(positive[i-1] > j)
						dp[i][j] = dp[i-1][j];
					else
						if (positive[i-1] == j)
							dp[i][j] = 1;
						else
						{
							if (dp[i-1][j] == 1)
								dp[i][j] = 1;
							else
								dp[i][j] = dp[i-1][j-positive[i-1]];
						}
				}
			}
			return dp[nSizePosi][sum];
		}
	}
	else
	{
		if(0 == nSizePosi)
		{
			//数列全为负数
			if(sum >= 0)
				return false;

			sum = -sum;
			vector< vector<int> >  dp(1+nSizeNega,vector<int>(1+sum,0));
			for (i = 1 ; i<= nSizeNega ; i++)
			{
				for (j = 1; j <= sum ; j++)
				{
					if(0 - negative[i-1] > j)
						dp[i][j] = dp[i-1][j];
					else
						if (0 - negative[i-1] == j)
							dp[i][j] = 1;
						else
						{
							if (dp[i-1][j] == 1)
								dp[i][j] = 1;
							else
								dp[i][j] = dp[i-1][j+negative[i-1]];
						}
				}
			}
			return dp[nSizeNega][sum];
		}
		else
		{
			int sum_nega0 = 0 , sum_posi0 = 0;
			for (i = 0 ; i< nSizeNega ; i++)
				sum_nega0 += negative[i];
			for (i = 0 ; i< nSizePosi ; i++)
				sum_posi0 += positive[i];

			if(sum < sum_nega0 || sum > sum_posi0)
				return false;
			if (sum == sum_nega0 || sum == sum_posi0)
				return true;

			int sum_nega,sum_posi;		//最终需要计算的总和

			if (sum == 0)
			{
				sum_posi = min(abs(sum_nega0),sum_posi0);
				sum_nega = 0 - sum_posi;
			}
			else
			{
				if (sum > 0)
				{
					if (sum_posi0 - sum <= abs(sum_nega0))
					{
						sum_posi = sum_posi0;
						sum_nega = sum - sum_posi0;
					}
					else
					{
						sum_posi = abs(sum_nega0) + sum;
						sum_nega = sum_nega0;
					}
				}
				else
				{
					if (sum - sum_nega0 < sum_posi0)
					{
						sum_posi = sum - sum_nega0;
						sum_nega = sum_nega0;
					}
					else
					{
						sum_posi = sum_posi0;
						sum_nega = 0 - sum_posi + sum;
					}
				}
			}

			vector< vector<int> >  dp1(1+nSizePosi,vector<int>(1+sum_posi,0));
			for (i = 1 ; i<= nSizePosi ; i++)
			{
				for (j = 1; j <= sum_posi ; j++)
				{
					if(positive[i-1] > j)
						dp1[i][j] = dp1[i-1][j];
					else
						if (positive[i-1] == j)
							dp1[i][j] = 1;
						else
						{
							if (dp1[i-1][j] == 1)
								dp1[i][j] = 1;
							else
								dp1[i][j] = dp1[i-1][j-positive[i-1]];
						}
				}
			}

			sum_nega = -sum_nega;
			vector< vector<int> >  dp0(1+nSizeNega,vector<int>(1+sum_nega,0));
			for (i = 1 ; i<= nSizeNega ; i++)
			{
				for (j = 1; j <= sum_nega ; j++)
				{
					if(0 - negative[i-1] > j)
						dp0[i][j] = dp0[i-1][j];
					else
						if (0 - negative[i-1] == j)
							dp0[i][j] = 1;
						else
						{
							if (dp0[i-1][j] == 1)
								dp0[i][j] = 1;
							else
								dp0[i][j] = dp0[i-1][j+negative[i-1]];
						}
				}
			}


			if (sum > 0 && dp1[nSizePosi][sum])	
				return true;
			
			if (sum < 0 && dp0[nSizePosi][-sum])
				return true;

			bool bOk = false;
			while(sum_nega > 0)
			{
				// -sum_nega + sum_posi = sum;
				sum_posi = sum + sum_nega;
				if (sum_posi < 0)
					break;

				if (dp0[nSizeNega][sum_nega] && dp1[nSizePosi][sum_posi])
				{
					bOk = true;
					break;
				}
				sum_nega--;
			}
			return bOk;
		}
	}
	return false;
}

int main()
{
	int N;
	while(cin >> N)
	{
		vector<int> vec_3,vec_5,vec_nums;
		int sum_3 = 0, sum_5 = 0, sum_nums = 0;
		int tmp;
		for (int i = 0 ; i < N ; i++)
		{	
			cin >> tmp;
			if(tmp % 3 == 0)
			{
				vec_3.push_back(tmp);
				sum_3 += tmp;
			}
			else
			{
				if(tmp % 5 == 0)
				{
					vec_5.push_back(tmp);
					sum_5 += tmp;
				}
				else
				{
					vec_nums.push_back(tmp);
					sum_nums += tmp;
				}
			}
		}
		tmp = abs(sum_3 - sum_5);
		vec_nums.push_back(tmp);
		sum_nums += tmp;

		bool bOk = false;
		if (sum_nums % 2 == 0)
			bOk = findArray(vec_nums,sum_nums/2);
		vec_3.clear();
		vec_5.clear();
		vec_nums.clear();
		if (bOk)
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}
	return 0;
}