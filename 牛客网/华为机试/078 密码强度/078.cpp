#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    while(cin >> str)
    {
        int score = 0;
        int nlen = str.length();
        if(nlen <= 4)
            score += 5;
        else
            if(nlen <= 7)
                score += 10;
            else
                score += 25;
        
        //Ð¡Ð´¡¢´óÐ´¡¢Êý×Ö¡¢·ûºÅ
        int count[4] = { 0 };
        for(int i = 0 ; i < nlen ; i++)
        {
            if('a'<=str[i]&&str[i]<='z')
                count[0]++;
            else
                if('A'<=str[i]&&str[i]<='Z')
                    count[1]++;
                else
                    if('0'<=str[i]&&str[i]<='0')
                        count[2]++;
                    else
                        count[3]++;
        }
        
        if(0 == count[0])
        {
            if(count[1])
                score += 10;
        }
        else
        {
            if(count[1])
                score += 20;
            else
                score += 10;
        }
        
        if(1 == count[2])
            score += 10;
        else
            if(count[2] > 1)
                score += 20;
        
        if(1 == count[3])
            score += 10;
        else
            if(count[3] > 1)
                score += 25;
        
        if(count[0]&&count[1]&&count[2]&&count[3])
            score += 5;
        else
            if((count[0]||count[1])&&count[2]&&count[3])
                score += 3;
            else
                if((count[0]||count[1])&&count[2])
                    score += 2;
        
        if(score >= 90)
            cout << "VERY_SECURE" << endl;
        else
            if(score >= 80)
                cout << "SECURE" << endl;
            else
                if(score >= 70)
                    cout << "VERY_STRONG" << endl;
                else
                    if(score >= 60)
                        cout << "STRONG" << endl;
                    else
                        if(score >= 50)
                            cout << "AVERAGE" << endl;
                        else
                            if(score >= 25)
                                cout << "WEAK" << endl;
                            else
                                cout << "VERY_WEAK" << endl;
    }
    return 0;
}