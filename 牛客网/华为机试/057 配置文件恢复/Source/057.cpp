#include <iostream>
#include <string>
using namespace std;

string command_str1[6] = {"reset","reset","board","board","reboot","backplane"};
string command_str2[6] = {"","board","add","delet","backplane","abort"};

string show(int i)
{
    string s;
    switch(i)
    {
        case 0:s = "reset what"; break;
        case 1:s = "board fault"; break;
        case 2:s = "where to add"; break;
        case 3:s = "no board at all";break;
        case 4:s = "impossible";break;
        case 5:s = "install first";break;
        default:s = "unkown command";break;
    }
    return s;
}

int commandLine(string cmd,string & s1,string & s2)
{
    int nlen = cmd.length();
    if(0 == nlen)
        return 0;
    
    string s = "";
    int index = 0;
    int nCount = 0;
    for(int i = 0 ; i < nlen ; i++)
    {
        if(cmd[i] != ' ')
            s += cmd[i];
        else
        {
            if(s!="")
            {
                nCount++;
                index++;
                if(index == 1)
                    s1 = s;
                else
                    if(index == 2)
                        s2 = s;
                s = "";
            }
        }
    }
    if(s!="")
    {
        nCount++;
        index++;
        if(index == 1)
            s1 = s;
        else
            if(index == 2)
                s2 = s;
         s = "";
    }
    return nCount;
}

int main()
{
    string str;
    while(getline(cin,str))
    {
        string s1,s2;
        int n = commandLine(str,s1,s2);
        if(n < 1 || n > 2)
            cout << show(-1) << endl;
        
        if(n == 1)
        {
            string strcmd = command_str1[0];
            if(strcmd.find(s1)!=string::npos)
                cout << show(0) << endl;
            else
                cout << show(-1) << endl;
        }
        else
        {
            int count = 0;
            int index;
            for(int i = 1 ; i <= 5 ;i++)
            {
                string str1 = command_str1[i];
                string str2 = command_str2[i];
                if(str1.find(s1)!=string::npos && str2.find(s2)!=string::npos )
                {
                    count ++;
                    index = i;
                }
            }
            if(count != 1)
                cout << show(-1) << endl;
            else
                cout << show(index) << endl;
        }
    }
    return 0;
}