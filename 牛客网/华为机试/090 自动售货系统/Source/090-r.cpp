#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <cctype>
using namespace std;
 
int A_num[] = { 0,0,0,0,0,0,0 };
int A_price[] = { 0,2,3,4,5,8,6 };
int M_num[] = { 0,0,0,0 };
int M[] = { 1,2,5,10 };
int pay = 0;
 
void process(string str, int pos)
{
    int i, tmp = 0;
    switch (str[pos])
    {
    case 'p':
        for (i = pos + 2; str[i] != ';'; i++)
            tmp = tmp * 10 + str[i] - '0';
        if (tmp != 1 && tmp != 2 && tmp != 5 && tmp != 10)
            cout << "E002:Denomination error" << endl;
        else
        {
            if (tmp > 2 && (M_num[0] + 2 * M_num[1]) < tmp)
                cout << "E003:Change is not enough, pay fail" << endl;
            else if (tmp > 10)
                cout << "E004:Pay the balance is beyond the scope biggest" << endl;
            else if ((A_num[1] + A_num[2] + A_num[3] + A_num[4] + A_num[5] + A_num[6]) == 0)
                cout << "E005:All the goods sold out" << endl;
            else
            {
                pay += tmp;
                switch (tmp)
                {
                case 1:M_num[0]++; break;
                case 2:M_num[1]++; break;
                case 5:M_num[2]++; break;
                case 10:M_num[3]++; break;
                default:
                    break;
                }
                cout << "S002:Pay success,balance="<<pay << endl;
            }
        }
        break;
    case 'q':
        tmp = str[pos + 2] - '0';
        if (tmp == 0)
        {
            for (i = 1; i <= 6; i++)
            {
                cout << "A" << i << " " << A_price[i] << " " << A_num[i] << endl;
            }
        }
        else if (tmp == 1)
        {
            for (int i = 0; i < 4; i++)
                cout << M[i] << " yuan coin number=" << M_num[i] << endl;
        }
        else
            cout << "E010:Parameter error";
        break;
    case 'b':
        tmp = str[pos + 3] - '0';
        if (tmp >= 1 && tmp <= 6)
        {
            if(A_num[tmp]==0)cout << "E007:The goods sold out" << endl;
            else if(pay<A_price[tmp])cout << "E008:Lack of balance" << endl;
            else
            {
                pay -= A_price[tmp];
                cout << "S003:Buy success,balance=" << pay << endl;
            }
        }
        else
            cout << "E006:Goods does not exist" << endl;
        break;
    case 'c':
        if(pay==0)cout << "E009:Work failure" ;
        else
        {
            int cnt[4] = { 0,0,0,0 };
            while ((pay - 10) >= 0 && M_num[3]>0)
            {
                pay -= 10;
                cnt[3]++;
                M_num[3]--;
            }
            while ((pay - 5) >= 0 && M_num[2]>0)
            {
                pay -= 5;
                cnt[2]++;
                M_num[2]--;
            }
            while ((pay - 2) >= 0 && M_num[1]>0)
            {
                pay -= 2;
                cnt[1]++;
                M_num[1]--;
            }
            while ((pay - 1) >= 0 && M_num[0]>0)
            {
                pay -= 1;
                cnt[0]++;
                M_num[0]--;
            }
            for (int i = 0; i < 4; i++)
                cout << M[i] << " yuan coin number=" << cnt[i] << endl;
            pay = 0;
        }
        break;
    default:
        break;
    }
}
 
int main()
{
    string str;
    int tmp;
    int k;
    int len;
    int i;
    while (getline(cin,str))
    {
        cout << "S001:Initialization is successful" << endl;
        tmp = 0;
        k = 1;
        for (i = 2; str[i] != ' '; i++)
        {
            if (str[i] == '-')
            {
                A_num[k++] = tmp;
                tmp = 0;
            }
            else if (isdigit(str[i]))
            {
                tmp = tmp * 10 + str[i] - '0';
            }
        }
        A_num[k] = tmp;
        len = i;
        k = 0;
        tmp = 0;
 
        for (i = len; str[i] != ';'; i++)
        {
            if (str[i] == '-')
            {
                M_num[k++] = tmp;
                tmp = 0;
            }
            else if (isdigit(str[i]))
            {
                tmp = tmp * 10 + str[i] - '0';
            }
        }
        M_num[k] = tmp;
        pay = 0;
 
        for (i = 13; i < str.size();i++)
        {
            if ((i + 1) < str.size() && str[i] == ';')
                process(str, i + 1);
        }
    }
 
    return 0;
}