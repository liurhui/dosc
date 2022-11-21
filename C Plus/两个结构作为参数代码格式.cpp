//头文件声明语句 文件名 coordin.h
#findef COORDIN_H_
#define  COORDIN_H_

struct polar
{
    double distance;
    double angle;
};
struct rect
{
    double x;
    double y;
};
polar rect_to_polar(rect xypos);
void show_polar(polar dapos);

#endif


//声明结构     函数定义源代码文件 file2.cpp
#include <iostream>
#include <cmath>
#include "coordin.h" // 必须把头文件导入 编译才通过

//结构类型函数调用另一个结构的参数作为形参
polar rect_to_polar(rect xypos)
{
    using namespace std;
    polar answer;

    answer.distance = sqrt(xypos.x * xypos.x + xypos.y * xypos.y);
    answer.angle = atan2(xypos.y, xypos.x);
    return answer;
}

//显示函数 其形参为 上一段函数的结构polar返回值
void show_polar (polar dapos)
{
    using namespace std;
    const dobule Rad_to_deg = 57.29577951; //只是定义一个限定符的 double类型的变量

    cout << "distance = " << dapos.distance;
    cout << ",angle = " << dapos.angle*Rad_to_deg;
    cout << "degress\n";
}

//主代码文件  写执行的代码段      文件名file1.cpp
#include<iostream>
#include"coordin.h"
using namespace std;
int main ()
{
    rect rplace;
    polar pplace;

    while(cin >> rplace.x >>rplace.y)
    {
    pplace = rect_to_polar(rplace);
    show_polar(pplace);
    }
    return 0;
}

Student * find (Student* head, int id)  // 链表头    ，要查找的结构数据成员类型
{
    Student * p = head;
    while(p)
    {
        if (p ->id ==id) //符合条件
        {
            /* code */
        }
    }
}
