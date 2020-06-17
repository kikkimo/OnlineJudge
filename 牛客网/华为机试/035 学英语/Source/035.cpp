#include <iostream>
#include <string>
using namespace std;

//0-19
string map0[] = {
    "zero","one","two","three","four","five","six","seven","eight","nine",
    "ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen",
    "eighteen","nineteen" };

//20-90
string map1[] = {
    " "," ","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};

string map2[] = {"and","hundred","thousand","million","billion"};


string Parse_0_99(int num)
{
    string s = "";
    if(num >= 100 || num < 0)
        return s;
    if(0 <= num && num <= 19)
        s = map0[num];
    else
        if(20 <= num && num <= 99)
        {
            int a = num % 10;
            int b = num / 10;
            if(a)
                s = map1[b] + " " + map0[a];
            else
                s = map1[b];
        }
    return s;
}

string Parse_0_999(int num)
{
    string s = "";
    if(num >= 1000 || num < 0)
        return s;
    
    int b = num / 100;
    int a = num % 100;
    
    if(b)
    {
        if(a)
            s = map0[b] + " hundred and " + Parse_0_99(a);
        else
            s = map0[b] + " hundred";
    }
    else
        s = Parse_0_99(a);
        
    return s;
}

string Parse(long num)
{
    if(num < 0 || num > 999999999)
        return "error";
    
    if(0 == num)
        return "zero";
    
    int a = num % 1000;
    num = num / 1000;
    int b = num % 1000;  //thousand 
    num = num / 1000;
    int c = num % 1000;  //million
    int d = num / 1000;  //billion
    
    string s = "";
    if(d)
        s = map0[d] + " billion";
    
    if(c)
    {
        if(s.length() != 0)
            s = s + " " + Parse_0_999(c) + " million";
        else
            s = Parse_0_999(c) + " million";
    }
    
    if(b)
    {
        if(s.length() != 0)
            s = s + " " + Parse_0_999(b) + " thousand";
        else
            s = Parse_0_999(b) + " thousand";
    }
    
    if(a)
    {
        if(s.length() != 0)
            s = s + " " + Parse_0_999(a);
        else
            s = Parse_0_999(a);
    }
    
    return s;
}

int main()
{
    long num;
    while(cin >> num)
    {
        string s = Parse(num);
        cout << s << endl;
    }
    return 0;
}