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
                c = b / a + 1;      //�µİ��������ķ�ĸ
                a = a - b%a;        //ͨ�ֺ�����õ��ķ���
                //��Ϊ��b=na+x,��ͨ�ֿɵ÷���Ϊac-b,c=n+1�����Ϊna+a-na-x=a-x,��x=b%a�����Է���Ϊa-b%a
                b = b*c;            //ͨ�ֺ�ķ�ĸ
                cout << 1 << "/" << c << "+";
                if (b%a == 0){      //�ж����µõ����ǲ��ǰ�������
                    b = b / a;
                    a = 1;
                }
            }
        }
        cout << 1 << "/" << b << endl;
    }
    return 0;
}