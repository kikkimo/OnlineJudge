#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    string str;
    while(getline(cin,str))
    {
        vector<string> vec_str;
        int nlen = str.length();
        do{
            char szval[128] = { 0 };
            while((int)str.length() > 0 && sscanf(str.c_str(),"%[^\" ]",szval))
            {
                string s = szval;
                int len1 = s.length();
                nlen = str.length();
                vec_str.push_back(s);
                if(nlen >= len1)
                {
                    str = str.substr(len1,nlen-len1);
                    str.erase(0,str.find_first_not_of(' '));
                }
            }
            nlen = str.length();
            if(nlen)
            {
                int pos = str.find('\"',1);
                if(pos == -1) 
                    break;
                else
                {
                    string s = str.substr(1,pos-1);
                    str = str.substr(pos+1,nlen-pos-1);
                    vec_str.push_back(s);
                    str.erase(0,str.find_first_not_of(' '));
                }
            }
			nlen = str.length();
        }while(nlen);
        cout << (int)vec_str.size() << endl;
        for(int i = 0 ; i < (int)vec_str.size() ; i++)
            cout << vec_str[i] << endl;
    }
    return 0;
}