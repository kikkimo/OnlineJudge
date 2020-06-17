#include <iostream>
#include <string>
#include <vector>
using namespace std;

//s²»Îª"joker JOKER"
int GetPokerType(string & s)
{
    vector<int> vec_Poker;
    char buf[20] = { 0 };
    while((int)s.length() > 0 && sscanf(s.c_str(),"%s",buf))
    {
        string st = buf;
        int nlen1 = st.length();
        s = s.substr(nlen1,s.length() - nlen1);
        s.erase(0,s.find_first_not_of(' '));
        if(nlen1 == 1)
        {
            if(st[0] >= '3' && st[0] <= '9')
            {
                int val = st[0] - '0';
                vec_Poker.push_back(val);
            }
            else{
                switch(st[0])
                {
                    case '2':
                        vec_Poker.push_back(20);
                        break;
                    case 'J':
                        vec_Poker.push_back(11);
                        break;
                    case 'Q':
                        vec_Poker.push_back(12);
                        break;
                    case 'K':
                        vec_Poker.push_back(13);
                        break;
                    case 'A':
                        vec_Poker.push_back(14);
                        break;
                }
            }
        }
        else{
            if(st == "10")
                vec_Poker.push_back(10);
			else
				if(st == "joker")
					vec_Poker.push_back(30);
				else
					if(st == "JOKER")
						vec_Poker.push_back(40);

        }
    }
    
    if((int)vec_Poker.size() == 1)
    {
        char ch = 'A' + vec_Poker[0];
        s = ch;
        return 1;
    }
    
    if((int)vec_Poker.size() == 2)
    {
        if(vec_Poker[0] == vec_Poker[1])
        {
            char ch = 'A' + vec_Poker[0];
            s = ch;
            return 2;
        }
    }
    
    if((int)vec_Poker.size() == 3)
    {
        if(vec_Poker[0] == vec_Poker[1] &&
          vec_Poker[1] == vec_Poker[2])
        {
            char ch = 'A' + vec_Poker[0];
            s = ch;
            return 3;
        }
    }
    
    if((int)vec_Poker.size() == 4)
    {
        if(vec_Poker[0] == vec_Poker[1] &&
          vec_Poker[1] == vec_Poker[2] &&
          vec_Poker[2] == vec_Poker[3])
        {
            char ch = 'A' + vec_Poker[0];
            s = ch;
            return 4;
        }
    }
    
    if((int)vec_Poker.size() == 5)
    {
        if(vec_Poker[4] == vec_Poker[3] + 1 &&
           vec_Poker[3] == vec_Poker[2] + 1 &&
           vec_Poker[2] == vec_Poker[1] + 1 &&
           vec_Poker[1] == vec_Poker[0] + 1)
        {
            char ch = 'A' + vec_Poker[0];
            s = ch;
            return 5;
        }
    }
    
    s = "";
    return -1;
}

int main()
{
    string str;
    while(getline(cin,str))
    {
        char sz1[100] = { 0 };
        char sz2[100] = { 0 };
        sscanf(str.c_str(),"%[^-]-%[^-]",sz1,sz2);
        string s1 = sz1,s2 = sz2;
        if("joker JOKER" == s1 || "joker JOKER" == s2)
        {
            cout << "joker JOKER" << endl;
            continue;
        }
        int pos = 0;
        int n1 = GetPokerType(s1);
        int n2 = GetPokerType(s2);
        
        if(-1 == n1 || -1 == n2)
        {
            cout << "ERROR" << endl;
            continue;
        }
        
        bool bOk = true;
        if(4 == n1)
        {
            if(4 == n2)
                pos = ( s2[0] > s1[0] ? 1 : 0);
            else
                pos = 0;
        }
        else
        {
            if(4 == n2)
                pos = 1;
            else
            {
                if(n1 != n2)
                    bOk = false;
                else
                    pos = ( s2[0] > s1[0] ? 1 : 0);
            }
        }
        
        if(bOk)
        {
            if(pos)
                cout << sz2 << endl;
            else
                cout << sz1 << endl;
        }
        else
            cout << "ERROR" << endl;
    }
    return 0;
}