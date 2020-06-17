#include <iostream>
#include <string>
using namespace std;

bool match(string s1,string s2)
{
    int nlen1 = s1.length();
    int nlen2 = s2.length();
    if(0 == nlen1)
    {
        if(0 == nlen2)
            return true;
        else
            return false;
    }
    if(0 == nlen2)
    {
        bool bf = true;
        for(int i = 0 ; i < nlen1 ; i++)
        {
            if(s1[i]!='*')
            {
                bf = false;
                break;
            }   
        }
        return bf;
    }
    
    int npos1 = 0,npos2 = 0;
    bool bOk = true;
    bool bRe = false;
    while(npos1 < nlen1 && npos2 < nlen2)
    {
        if(s1[npos1] != '*' && s1[npos1] != '?')
        {
            if(s1[npos1] != s2[npos2])
            {
                bOk = false;
                break;
            }
            else{
                npos1 ++;
                npos2 ++;
                continue;
            }
        }
        else
            if(s1[npos1] == '?')
            {
               npos1 ++;
               npos2 ++;
               continue; 
            }
            else
            {
                if(npos1 == nlen1 - 1)
                {
                    bRe = true;
                    break;
                }                
                npos1++;
                char ch1 = s1[npos1];

				bool flag = false;
				while(ch1 == '?' || ch1 == '*')
                {
                    if(npos1 == nlen1 - 1 && npos2 != nlen2)
                    {
                        bRe = true;
                        break;
                    }
 
                    if (npos2 == nlen2)
                    {
                        flag = true;
                        break;
                    }
                         
                    npos1++;
                    if(ch1 == '?')
                        npos2++;
                    ch1 = s1[npos1];
                }
				if (bRe || flag)
					break;
				//
                while(npos2 < nlen2 && s2[npos2] != ch1)
                    npos2++;

                if(npos2 == nlen2)
                {
                    bOk = false;
                    break;
                }
                
				string sub1 = s1.substr(npos1,nlen1-npos1);
				string sub2 = s2.substr(npos2,nlen2-npos2);

				while(1)
				{
					if (match(sub1,sub2))
					{
						bRe = true;
						break;
					}
					else
					{
						npos2++;
						while(npos2 < nlen2 && s2[npos2] != ch1)
							npos2++;
						
						if(npos2 == nlen2)
						{
							bOk = false;
							break;
						}
						sub1 = s1.substr(npos1,nlen1-npos1);
						sub2 = s2.substr(npos2,nlen2-npos2);
					}
				}
				if(bRe)
					break;
            }
    }
    if(!bOk)
        return false;
    if(bRe)
        return true;
    
    if(npos1 == nlen1)
    {
        if(npos2 == nlen2)
            return true;
        else
            return false;
    }
    else
    {
        bool bf = true;
        for(int i = npos1 ; i < nlen1 ; i++)
        {
            if(s1[i]!='*')
            {
                bf = false;
                break;
            }   
        }
        return bf;
    }
    
}

int main()
{
    string s1,s2;
	
    while(cin >> s1 >> s2)
    {
        if(match(s1,s2))
            cout << "true" << endl;
        else
            cout << "false" << endl;
    }
    return 0;
}