/***********  动态申请 内存操作符 new
    功能:
        在程序执行期间,申请用于存放T类型对象的内存空间,并依初值列表赋以初值。
    结果值:
        成功:T类型的指针,指向新分配的内存;
        失败:抛出异常。
    申请失败返回0    
    手动释放内存： delete  指针p  
        释放指针p所指向的内存，p必须是new操作的返回值。 

    释放数组内存  delete[] 

程序内存分配：
    1、栈区(stack)
        1、由编译器自动分配释放,一般存放函数的参数值、局部变量的值等。
        2、操作方式类似数据结构中的找，先进后出。

    2、堆区(heap)
        1、一般由程序员分配释放,若程序不释放,程序结束时可能由操作系统回收。
        2、注意:与数据结构中的堆是两回事,分配方式类似链表。

    3、全局区(静态区-static)
        1、全局变量和静态变量是存储在一起的。
        2、程序结束后由系统释放。

    4、文字常量区
        1、常量字符串就放在这里,程序结束有由系统释放。

    5、程序代码区
        1、存放函数体的二进制代码。
***********/
#pragma region 程序内存分配
#include <iostream> 
using namespace std;
int numl= 0; //全局初始化区
int * ptr1; //全局未初始化区
int main()
{
    //栈区
    int num2;
    //栈区
    char str[] = "老九君";
    //栈区
    char * ptr2; //老九君\0在常量区,ptr3在栈区
    char * ptr3 = "老九君"; //全局(静态)初始化区
    static int num3= 1024; //分配的内存在堆区
    ptr1 = new int[10];
    ptr2 = new char[20];
    //注意: ptr1和ptr2本身是在栈区中的
    return 0;
}
#pragma endregion


#pragma region 二维数组指针
#include <iostream> 
using namespace std;
int main(){
    int * p = new int[10];
    //使用指针创建二维数组
    int (*p2) [3] = new int[5][3];
    p2[3][2] = 998;
    for(int i = 0; i< 5; i++){
        for(int j = 0; j< 3; j++){
            cout << p2[i][j] << ',' << endl; //数组二维输出
            // cout <<*(*(p2+i) + j) << ','; //指针 显示二维地址
        }
            cout << endl;
    }
}
#pragma endregion

/***********
    这段代码求的是6月6号 是哪个星座 
    由于每个月有分隔开两个星座所以新创一个数值存放每月的分隔日期，
    用输入的月份的下标来查询当月的分隔数如果除的尽整数就是ture 除不尽就是flash  
    对应的 就是 1和0 就正好是下标
***********/
#pragma region 星座二维数组
#include <iostream> 
using namespace std;
string constell_names[12] [2] = {
    {"山羊座","水瓶座"},//一月
    {"水瓶座","双鱼座"},//二月
    {"双鱼座","白羊座"},//三月
    {"白羊座","金牛座"},//四月
    {"金牛座","双子座"},//五月
    {"双子座","巨蟹座"},//六月
    {"巨蟹座","狮子座"},//七月
    {"狮子座","处女座"},//八月
    {"处女座","天秤座"},//九月
    {"天秤座","天竭座"},//十月
    {"天竭座","射手座"},//十一月
    {"射手座","山羊座"} //十二月
};
    //低维,输入的值减1;高维,输入的日期除以数组[输入的月份减1]
    /*各月份的跨星座日期*/
    int constell_dates[] {20, 19, 21, 20, 21, 22, 23, 23, 23, 24, 23, 22};
    cout << constell_names [value_birth_month-1][value_birth_date/constell_dates [value_birth_month-1]] << endl;
#pragma endregion


#pragma region 示例6-16delete手动释放内存
#include <iostream> 
using namespace std;
class Point{
    public:
        Point(): x(0), y(0) {
            cout<<"Default Constructor called."<<endl;
        }
        Point(int x, int y) : x(x), y(y){
            cout<< "Constructor called."<<endl;
        }
        ~Point(){
             cout<<"Destructor called."<<endl;
        }
        int getX() const { return x;}
        int getY() const { return y;}
        void move(int newX, int newY){
            x= newX;
            y= newY;
        }
    private:
        int x, y;
};
int main(){
    cout << "Step one: " << endl;
    Point *ptrl =new Point;//调用缺省构造函数
    delete ptrl; //删除对象,自动调用析构函数
    cout << "Step two: " << endl;
    ptrl = new Point(1,2);
    delete ptrl;
    return 0;
}

/* 动态申请空间    两个整型的数据成员 8个字节  且把起始地址赋值给ptr1，释放内存空间 不是删除指针。
有参数 调用有参数的构造函数，没参数调用没参数的构造函数 释放。 */

/* 运行结果
Step One:
    Default Constructor called.
    Destructor called.
Step Two: 
    Constructor called.
    Destructor called.
 */
#pragma endregion




/*********** 执行析构函数：需要申请更多存储空间，用数组方式。
    1、申请多少空间就释放多少空间。
    2、不要去释放 两次。
    动态存储分配
        申请分配:
            new类型名T[数组长度]
            数组长度可以是任何表达式,在运行时计算
            int *intArray = new int[10]; // new创建后返回的是 第一个元素的地址

        释放动态数组
            释放:delete[]数组名p
            释放指针p所指向的数组。p必须是用new分配得到的数组首地址。 

    int * ptr_int = new int;
    short * ptr_short = new short[500];
    delete ptr_int;
    delete [] ptr_short;
***********/
#pragma region  示例6-17申请和释放动态数组
#include<iostream>
using namespace std;
class Point {  //类的声明 
    public:
        Point(): x(0), y(0) {
            cout<<"Default Constructor called."<<endl;
        }
        Point(int x, int y) : x(x), y(y){
            cout<< "Constructor called."<<endl;
        }
        ~Point(){
                cout<<"Destructor called."<<endl;
        }
        int getX() const { return x;}
        int getY() const { return y;}
        void move(int newX, int newY){
            x= newX;
            y= newY;
        }
    private:
        int x, y;
};
int main(){
    Point *ptr = new Point[2]; //创建对象数组
    ptr[0].move(5, 10);//通过指针访问数组元素的成员
    ptr[1].move(15, 20);//通过指针访问数组元素的成员
    cout << "Deleting..." << endl;
    delete[] ptr; //删除整个对象数组
    return 0;
}
/*  输出结果  ptr是指针变量不是 指针常量
Default Constructor called.
Default Constructor called.
Deleting....
Destructor called.
Destructor called.
*/
#pragma endregion

/* 将动态数组封装成类,将创建和删除数组的过程封装成类
    目的：简洁复用，且可以在访问数组元素钱检查下标是否越界。
*/
#pragma region  示例6-18动态数组类
#include <iostream>
#include <cassert>
using namespace std;
class Point{
    public:
        Point(): x(0), y(0) {
            cout<<"Default Constructor called."<<endl;
        }
        Point(int x, int y) : x(x), y(y){
            cout<< "Constructor called."<<endl;
        }
        ~Point(){
            cout<<"Destructor called."<<endl;
        }
        int getX() const { return x;}
        int getY() const { return y;}
        void move(int newX, int newY){
            x= newX;
            y= newY;
        }
    private:
        int x, y;  
};
class ArrayOfPoints {//动态数组类
    public:
        ArrayOfPoints(int size): size(size) {
            points = new Point[size];
        }
        ~ArrayOfPoints() {
            cout << "Deleting..."<< endl;
            delete[] points;
        }
        Point &element(int index) {
            assert(index >= 0 && index < size);
            return points[index];
        }
    private:
        Point *points; //指向动态数组首地址
        int size;//数组大小
};
    
// 知道动态数组首地址，也知道数组大小就可以确定内存空间大小
int main() {
    int count;
    cout << "Please enter the count of points: ";
    cin >> count;
    ArrayOfPoints points(count); //创建对象数组
    //通过访问数组元素的成员
    points.element(0).move(5, 0);
    //通过类访问数组元素的成员
    points.element(1).move(15, 20);
    return 0;
}
/* 输出结果
Please enter the number of points:2 
Default Constructor called.
Default Constructor called.
Deleting.
Destructor called.
Destructor called.
 */
#pragma endregion

/* new 类型名T[第1维长度][第2维长度]...
    如果内存申请成功,new运算返回一个指向新分配内存首地址的指针，是一个T类型的数组,数组元素的个数为除最左边一维外各维下标表达式的乘积。 
    写法：
        char (*fp)[3]; 
        fp= new char[2][3];
*/
#pragma region  示例6-19动态创建多维数组
#include <iostream> 
using namespace std;
int main(){
    float (*cp) [9][8] = new float[8][9][8];
  /*   8个二维数组  这样比较复杂  
    for (int i = 0; i< 8; i++)
         for (int j = 0; j < 9; j++)
            for (int k = 0; k < 8; k++)
            //以指针形式数组元素  
            *(*(*(cp + i) + j) + k) = static_cast<float>(i * 100 +j * 10 + k);
    */
    // 这样比较简单些
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 8; k++)
            //将指针cp作为数组名使用,通过数组名和下标访问数组元素
                cout << cp[i][j][k] << " ";
            cout << endl;
        }
        cout << endl;
    }
    delete[] cp;
    return 0;
}
#pragma endregion




/*********** vector 创建动态数组
    vector存在的原因：
        -将动态数组封装,自动创建和删除。
        -数组下标越界检查。
        -例6-18中封装的ArrayOfPoints也提供了类似功能,但只适用于一种类型的数组。//ArrayOf Points是上面封装的函数  申请释放越界检查
    vector动态数组对象的定义:
        -vector<元素类型>数组对象名(数组长度);
        -例: vector<int> arr(5) 建立大小为5的int数组  //数组对象名为指针
    vector数组对象的使用:
        1、对数组元素的引用
            -与普通数组具有相同形式:
                数组对象名[下标表达式]
            -但vector数组对象名不表示数组首地址
        2、获得数组长度
            -用size函数*数组对象名.size() 
***********/
#pragma region  示例6-20vector创建动态数组
#include <iostream> 
#include <vector> 
using namespace std;
//计算数组arr中元素的平均值
double average(const vector<double> &arr) {
    double sum = 0;
    for (unsigned i = 0; i < arr.size(); i++) 
        sum += arr[i];
    return sum / arr.size();
}
int main() {
    unsigned n;
    cout << "n = ";
    cin >> n;
    vector<double> arr(n);//创建数组对象
    cout << "Please input "<< n <<" realnumbers:"<< endl;
    for (unsigned i = 0; i < n; i++)
        cin >> arr[i];
    cout << "Average= " << average(arr) << endl;
    return 0;
}
#pragma endregion