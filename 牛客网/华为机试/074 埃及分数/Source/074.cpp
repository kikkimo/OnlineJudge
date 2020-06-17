#include<iostream>
#include<string>
using namespace std;
int main(){
    char ch;
    int a, b;
    while (cin >> a >> ch >> b)
    {
        while (a != 1){
            if (b % (a - 1) == 0){
                cout << 1 << "/" << b / (a - 1) << "+";
                a = 1;
            }
            else{
                int c;
                c = b / a + 1;      //新的埃及分数的分母
                a = a - b%a;        //通分后相减得到的分子
                //因为：b=na+x,由通分可得分子为ac-b,c=n+1则分子为na+a-na-x=a-x,而x=b%a，所以分子为a-b%a
                b = b*c;            //通分后的分母
                cout << 1 << "/" << c << "+";
                if (b%a == 0){      //判断最新得到的是不是埃及分数
                    b = b / a;
                    a = 1;
                }
            }
        }
        cout << 1 << "/" << b << endl;
    }
    return 0;
}