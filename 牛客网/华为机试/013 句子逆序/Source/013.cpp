#include <iostream>
#include <vector>
using namespace std;

int main()
{
    string str;
    while(getline(cin,str))
    {
        int nlen = str.length();
        if(0 == nlen)
            continue;
        
        vector<string> wordsvec;
        string word;
        for(int i = 0 ; i < nlen ; i++)
        {
            char ch = str[i];
            if(ch != ' ')
                word += ch;
            else
            {
                wordsvec.push_back(word);
                word = "";
            }
        }
        if(word != "") wordsvec.push_back(word);
        if(wordsvec.size() == 0) continue;
        for(int i = wordsvec.size()-1 ; i>=0 ; i--)
        {
            if(i != 0)
                cout << wordsvec[i] << " ";
            else
                cout << wordsvec[i];
        }
    }
    return 0;
}