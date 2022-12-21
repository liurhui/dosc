/*********** 数组  (c++定义数组的时候可以不加 =号)
    如：  int  constell_dates[]{20,19,18,17};
    什么是数组：
        具有一定顺序关系的若干相同类型变量的集合体组成数组的变量称为该数组的元素。
    定义数组的同时赋给初值
        例如指定数组长度，且全部赋初始值: static int a[10]=(0,1,2,3,4,5,6,7,8,9);
        例如指定数组长度，一部分赋初始值: static int a[10] =[0,1,2,3,4);
        例如不指定数组长度，全部数组元素赋初值: static int a[] =(1,2,3,4,5};

一维数组的声明
        类型说明符 数组名[常量表达式]; 
    例如:
        int a[10]; 表示a为整型数组,有10个元素:a[0]...a[9] 

    11版本 c++     xx[0] =1;  xx[1] =2;
    低版本 c++   xx.push_back(1);   xx.push_back(2);

***********/


/***********  数组指针
    一个指针占4字节，数组是几个内容*数组类型的字节    数组名为数组的首地址。
    数组名就是这块连续内存单元的首地址
        int num[50]; 
            1、num是数组名,也可以理解成数组的首地址。
            2、num的值与 &num[0]的值 是相同的。
            3、第i+1个元素的地址: 
                &num[i +1]或num +i
            4、第i+1个元素的值: 
                num[i +1] 或*(num +i+ 1)  或 *++num。
            5、为指向数组的指针赋值:
                int * ptr_num = num; 或 int * ptr_num = &num[0];
            6、指针变量可以指向数组元素
                int * ptr_num = &num[4]; 或 int * ptr_num = num + 4;
***********/

 
/*********** 引用 （作用指针是一样的，但是运行机制不一样。也更美化 *变少 被封装在底层里面）
    1、必须先声明,后使用。
    2、只能逐个引用数组元素,而不能一次引用整个数组 
    例如:
        a[0]= a[5] + a[7] - a[2*3];
***********/

#pragma region 引用数组
#include <iostream> 
using namespace std;
int main() {
    int a[10], b[10];
    for(int i = 0;i< 10; i++){
         a[i] =i*2- 1;b[i- i - 1] = a[i];
    }
    for(int i = 0; i< 10; i++) {
        cout << "a[" <<i<<"] ="<<a[i] <<" ";
        cout << "b[" <<I<<"]= "<< b[i] << endl;
    }
    return 0;
}
#pragma endregion

 
#pragma region 斐波拉契数列示例
 #include<iostream>
 using namespace std;
 int main() {
    int i;
    static int f[20]=(1,1);//初始化第0, 1个数
    for(i=2;i<20;i++) //求第2~19个数
    f[i]=f[i-2]+f[i-1];
    for(i=0;i<20:i++) //输出,每行5个数
    {
        if(i%5==0) cout<<endl;
        cout.width(12); //设置输出宽度为12
        cout<<f[i];
    }
    return 0;
 }

#pragma endregion

#pragma region 要求循环从键盘读入 若干组选择题答案,计算并输出每组答案的正确率,直到输入ctrl+z为止。每组连续输入5个答案,每个答案可以是 'a'...'d'。
#include <iostream> 
using namespace std;
int main(){
    const char key[]={'a','c','b','a','d'};
    char c;
    int ques=0,numques=5,numcorrect=0; //correct正确答案  ques问题
    cout<<"Enter the "<<numques<<"question tests:"<<endl;
    while(cin.get(c))
    {
        if(c!= '\n')
        if(c == key[ques]){
            numcorrect++; cout <<"";
        }else
            cout<<"*" ;
        else{
            cout<<" Score"<<float(numcorrect)/numques*100<<"%";
            ques = 0;
            numcorrect = 0;
            cout << endl;
            continue;
        } 
            ques++;
        } 
        return 0;
    } 
/* 运行结果
    acbba
        ** Score 60%
    acbad
        Score 100%
    abbda
        *** Score 40% 
    bdcba
        ***** Score 0%
 */
#pragma endregion

#pragma region 要求对调20个数组
#include <iostream> 
using namespace std;
int main() {
    int a[10], b[10];
    for(int i = 0; i < 10; i++) {
        a[i]=i*2-1;
        b[i0 -i-1] = a[i];
    }
    for(int i = 0; i < 10; i++){
        cout << "a[" <<i<<"="<<a[i] <<" ";
        cout << "b[" <<l<< "] ="<<b[i]<< endl;
    }
    return 0;
}
/* 输出结果
    a[0]= -1  b[0] = 17
    a[0]= 1  b[0] = 15
    a[0]= 3  b[0] = 13
    a[0]= 5  b[0] = 11
    a[0]= 7  b[0] = 9
    a[0]= 9  b[0] = 7
    a[0]= 11  b[0] = 5
    a[0]= 13  b[0] = 3
    a[0]= 15  b[0] = 1
    a[0]= 17  b[0] = -1
 */
#pragma endregion


 
/*********** 使用数组名作为函数参数
    1、数组名作参数,形、实参数都应是数组名,类型要一样,传送的是数组首地址。
    2、对形参数组的改变会直接影响到实参数组。
    3、主函数中初始化一个矩阵并将每个元素都输出,然后调用子函数,分别计算每一行的元素之和,
    4、将和直接存放在每行的第一个元素中,返回主函数之后输出各行元素的和。
***********/
#pragma region 数组名作为函数参数 
#include <iostream> 
using namespace std;
void rowSum(int a[][4],int nRow){
    for (int i = 0; i < nRow;i++) {
        for(int j= 1;j <4;j++)a[i][0] += a[i][j];
    }
}
int main(){//主函数
    int table[3][4] = {
        {1, 2,3, 4},
        {2, 3, 4, 5}, 
        {3, 4, 5, 6}
    };//声明并初始化数组
//输出数组元素
for (int i = 0; i< 3; i++) {
    for (int j = 0;j < 4;j++)
    cout << table[i][j]<<" ";
    cout << endl;
}
    rowSum(table, 3): //调用子函数,计算各行和
    //输出计算结果
    for (int i = 0; i< 3; i++) 
    cout << "Sum of row"<<i<<"is"<< table[i][0] << endl;
    return 0;
}
/* 输出为 
1   2   3   4
2   3   4   5
3   4   5   6
Sum of row 0 is 10 
Sum of row 1 is 14
Sum of row 2 is 18
 */
#pragma endregion




/*********** 对象数组
    声明： 类名  数组名[元素个数];
    访问方法: 通过下标访问 数组名[下标].成员名
    对象数组初始化 比较麻烦需要 调用类构造函数
对象数组初始化
    数组中每一个元素对象被创建时，系统都会调用类构造函数初始化该对象。
    Point A[2]={Point(1,2).Point(3,4)};
    如果没有初始化则默认调用构造函数
    
数组元素所属类的构造函数
    不声明构造函数，则采用默认构造函数。
    各元素对象的初值要求为相同的值时，可以声明具有默认形参值的构造函数。
    各元素对象的初值要求为不同的值时，需要声明带形参的构造函数。
    当数组中每一个对象被删除时，系统都要调用一次析构函数。
***********/ 

#pragma region  示例6-3对象数组示例 (类的定义、条件定义, 放在Point.h 头文件中)
//Point.h    
#ifndef POINT_H
#define POINT_H
class Point { //类的定义
    public: //外部接口
        Point();
        Point(int x, int y);
        ~Point();
        void move(int newX,int InewY);
        int getX() const {
            return x;
        } 
        int getY() const {
            return y;
        } 
        static void showCount(); //静态函数成员
    private: //私有数据成员
        int x, y;
};
#endif //_POINT_H

//Point.cpp
#include<iostream>
#include "Point.h" 
using namespace std;
Point::Point() {
    x=y=0;
    count<<"Default Constructor called." <<endl;
}
Point::Point(int x, int y) : x(x),y(y){
    cout << "Constructor called." << endi;
}
Point::~Point(){
    cout << "Destructor called."<< endl;
}    
void Point::move(int newX,int newY){
    cout << "Moving the point to(" << newx <<","<<newY<< <")"<< endl; 
    x= newX;
    y= newY;
}

// main.cpp
#include "Point.h" 
#include <iostream> 
using namespace std;
int main(){
    cout << "Entering main..." << endl;
    Point a[2];
    for(int i = 0; i< 2; i++)
        a[i].move(i + 10, i +20);
    cout << "Exiting main..." << endl;
    return 0;
}


/* 运行结果：
Entering main...              Exiting main...
Default Constructor called.   Destructor called.
Default Constructor called.   Destructor called.
Moving the point to (10, 20) 
Moving the point to (11, 21)
 */

#pragma endregion
