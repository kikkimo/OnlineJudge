#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _tagStudent{
    string strName;
    int    score;
    int    index;
}Student;

bool compDesc(const Student & a,const Student & b)
{
    if(a.score == b.score)
        return a.index < b.index;
    else
        return a.score > b.score;
}

bool compAsc(const Student & a,const Student & b)
{
    if(a.score == b.score)
        return a.index < b.index;
    else
        return a.score < b.score;
}

int main()
{
    int num,type;
    while(cin >> num >> type)
    {
        if(0 == num)
            continue;
        vector<Student> student;
        for(int i = 0 ; i < num ; i ++)
        {
            string name;
            int score;
            cin >> name >> score;
            Student stu;
            stu.strName = name;
            stu.score = score;
            stu.index = i;
            student.push_back(stu);
        }
        if(0 == type)
            sort(student.begin(),student.end(),compDesc);
        else
            sort(student.begin(),student.end(),compAsc);
        for(int i = 0 ; i < (int)student.size() ;i++)
            cout << student[i].strName << " " << student[i].score << endl;
    }
    return 0;
}