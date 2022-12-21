/**
 * @author  liurhui
 * @version 1.0
 * @copyright 版权
 * @remarks  备注
 */

#pragma region srand示例
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
int main(){
    srand( unsigned( time(0) ) );//srand(time(NULL));
    for(int j = 0; j < 10; j++)
        cout << "No." << j+1 << ":" << int(random(0,10)) << endl;
    return 0;
} 
double random(double start,double end){
    return start + (end - start) * rand() / (RAND_MAX + 1.0);
}
#pragma endregion


#pragma region for语句
int main()
{
    char shap = 'A';
    // 外层循环控制行(行数,换行)
    // 内层循环控制列(列数,列的图形)
    for (int i = 0; i < 4; i++)
    {
        for (int j = 9; j <= 2 - i; j++)
        {
            cout << " ";
        }
        for (int j = 0; j <= 2 * i; j++)
        {
            cout << (char)shap++; //  char 强制转换为字符
        }
        cout << endl;
    }
}
/*  输出结果
   A
  BCD
 EFGHI
JKLMNOP
 *****
  ***
   *
 */

int main()
{
    // 外层循环控制行(行数,换行)
    // 内层循环控制列(列数,列的图形)
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j <= 2 - i; j++)
        {
            cout << "";
        }
        for (int j = 0; j <= 2 * i; j++)
        {
            cout << (char)('A' + i); // 强制把*号转换为字符
        }
        cout << endl;
    }
}
/*  输出结果
   A
  BBB
 CCCCC
DDDDDDD
 *****
  ***
   *
 */
#pragma endregion
#pragma region for已知循环次数用for  实例化就是 有类有对象有访问的数据
#include <iostream>
using namespace std;
int main(void)
{
    int n, k;
    cout << "Enter a positive integer:";
    cin >> n;
    cout << "Number " << n << " Factors:";
    for (k = 1; k <= n; k++)
        if (n % k == 0)
            cout << k << " ";
    cout << endl;
}
#pragma endregion
#pragma region for要求:读入一系列整数,统计出正整数个i 和负整数个数j,读入0则结束。
#include <iostream>
using namespace std;
int main(void)
{
    int i = 0, j = 0, n;
    cout << "请输入若干个整数(输入0则结束): ";
    cin >> n;
    while (n != 0)
    {
        if (n > 0)
            i++;
        if (n < 0)
            j++;
        cin >> n;
    }
    cout << "正整数个数 " << i << " 负整个数:" << j << endl;
}
#pragma endregion


#pragma region 枚举示例
#include <iostream>
using namespace std;
enum game_result {
    WIN,
    LOSE,
    TIE,
    CANCEL
}; // 胜 负 平局 比赛取消 四种情况
int main(){
    game_result result;
    enum game_result omit = CANCEL;
    int count;
    for (count = WIN; count <= CANCEL; count++)
    {
        result = (game_result)count;
        if (result == omit)
        {
            cout << "The game was played";
            if (result == WIN)
                cout << "and we won!";
            if (result == LOSE)
                cout << "and we lost.";
            cout << "\n";
        }
    }
    return 0;
}
#pragma endregion

#pragma region 反序重构成新的数获得回文数
// 要求： 寻找并输出11~999之间的数m,它满足m,m2和m3均为回文数。
/*    回文:各位数字左右对称的整数。
    例如:11满足上述条件
        112=121, 113=1331。
    分析：
        10取余的方法,从最低位开始,依次取出该数的各位数字。
        按反序重新构成新的数,比较与原数是否相等,若相等,则原数为回文。
*/
// 解题思路找出规律： 构造新整数的方法:例如: 12345 -> 54321
/*
12345 -> 5      12345%10=5  0*10+5=5        12345/10=1234
12345 -> 54     1234%10=4   5*10+4=54       1234/10=123
12345 -> 543    123%10=3    54*10+3=543     123/10=12
12345 -> 5432   12%10=2     543*10+2=5432   12/10=1
12345 -> 54321  1%10=1      5432*10+1=54321 1/10=0
*/

#include <iostream>
using namespace std;
bool symm(long n)
{
    long i, m;
    i = n;
    m = 0;
    while (i)
    {
        m = m * 10 + i % 10;
        i = i / 10;
    }
    return (m == n);
}
int main()
{
    bool symm(long n);
    long m;
    for (m = 11; m < 1000; m++)
    {
        if (symm(m) && symm(m * m) && symm(m * m * m))
        {
            cout << "m=" << m << "m*m=" << m * m << "m*m*m=" << m * m * m << endl;
        }
    }
}
#pragma endregion

#pragma region 嵌套调用  结果 3 4平方和 25
int fun1(int x, int y)
{
    int fun2(int m);
    return (fun2(x) + fun2(y));
}
int fun2(int m)
{
    return (m * m);
} 
#pragma endregion

#pragma region 递归调用(函数直接或间接地调用自身，称为递归调用)
/*
    先递推 : 等于从未知 得到结果 4!=4*3! -> 3!=3*2! -> 2!=2*1! -> 1!=1*0! -> 0!=1 
    再回归 : 等于把结果 依次返回 4!=4*3!=24 <- 3!=3*2!=6 <- 2=2*1!=2 <- 1!=1*0!=1 <- 0!=1 
    实现递归函数
*/
#include <iostream>
using namespace std;
long fac(int n){
    long f;
    if (n < 0){
        cout << "n<0,data error!" << endl;
    }else if (n == 0){
        f = 1;
    }else{
        f = fac(n - 1) * n;
    }
    return (f);
}
int main(){
    long fac(int n);
    int n;
    long y;
    cout << "Enter a positive integer:";
    cin >> n;
    y = fac(n);
    cout << n << "!=" << y << endl;
}
#pragma endregion

#pragma region  要求:用递归法计算从n个人中选择k个人组成,一个委员会的不同组合数。
#include <iostream>
using namespace std;
int comm(int n, int k){
    if (k > n)
        return 0;              // 不合理情况pass
    else if (n == k || k == 0) // 如5人选5人组成，或没人组成 都只有一种组合数。
        return 1;
    else
        return comm(n - 1, k) + comm(n - 1, k - 1); // 4，3 + 4，2
};
int main(){
    int n, k;
    int comm(int n, int k);
    cin >> n >> k;
    cout << comm(n, k) << endl;
};
#pragma endregion

#pragma region 递归实现 汉诺塔递归调用问题（猩猩移盘子）
#include <iostream>
using namespace std;
void move(char getone, char putone){
    cout << getone << "-->" << putone << endl;
};
void hanoi(int n, char one, char two, char three){
    void move(char getone, char putone);
    if(n == 1){
        move(one, three);
    }else{
        hanoi(n - 1, one, three, two);
        move(one, three);
        hanoi(n - 1, two, one, three);
    }
};
int main(){
    void hanoi(int n, char one, char two, char three);
    int m;
    cout << "Enter the number of diskes:";
    cin >> m;
    cout << "the steps to moving " << m << "diskes:" << endl;
    hanoi(m, 'A', 'B', 'C');
};
#pragma endregion

#pragma region 示例 类重载运算符
class Fraction {
    public:
        Fraction() : num(1), den(1) {}
        Fraction(int n, int d) : num(n), den(d) {}
        // 重载加号操作符 2/3+ 3
         /*    Fraction operator + (const Fraction& other)
            {
                Fraction result;
                result.den = den * other.den; // 分母相乘
                result.num= num * other.den + den * other.num; // 分子
                return result;
            }  */
        // 重载全局操作符
        friend Fraction operator+(const Fraction &a, const Fraction &b) {
            Fraction result;
            result.den = a.den * b.den;                 // 分母相乘
            result.num = a.num * b.den + a.den * b.num; // 分子
            return result;
        };

    private:
        int num; // 分子
        int den; // 分母
};
int main()
{
    Fraction fa(2, 3);
    Fraction fb(3, 5);
    Fraction fc = fa + fb;
    return 0;
}
#pragma endregion

#pragma region 示例 函数模板 template
// 函数声明
template <typename T>
void Swap(T &, T &);
// 实例化
template <typename T>
void Swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}
#pragma endregion

// tips： 任意一个数字，在除以100之后的余数最大为99（不能除尽的情况下的最大），最小为0（即能够除尽）所以其运算结果的取值范围是0-99

#pragma region 示例引用 经典swap 函数   refrence
#include <iostream>
using namespace std;
void Swap1(int, int);
void Swap2(int *, int *);
void Swap3(int &, int &);
int main(){
    int num1 = 10, num2 = 5;
    Swap1(num1, num2);
    cout << "执行Swap1后: " << num1 << "\t" << num2 << endl;
    Swap2(&num1, &num2);
    cout << "执行Swap2后: " << num1 << "\t" << num2 << endl;
    Swap3(num1, num2);
    cout << "执行Swap3后: " << num1 << "\t" << num2 << endl;
}
void Swap1(int num1, int num2)
{
    // 结果 num1=10 num2=5 不变，因为函数没有将值返回，所以只是改变，但是值不变。
    int temp;
    temp = num1;
    num1 = num2;
    num2 = temp;
}
void Swap2(int *p1, int *p2)
{
    // 结果 num1=5 num2=10 变化了，因为函数传递的是地址，通过直接修改地址存储的值。
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
void Swap3(int &ref1, int &ref2)
{
    // 结果 num1=10 num2=5 变化了，因为这个是引用  效果与指针一样。
    int temp;
    temp = ref1;
    ref1 = ref2;
    ref2 = temp;
}
#pragma endregion

#pragma region 示例函数返回引用, 以下代码的输出结果是 ?
// 生命周期结束后就会被其他函数的给替换  要注意不要返回局部变量的引用 return 只能返回值不能做运算
int &sum()
{
    int num = 10;
    int &rNum = num;
    return rNum;
};
void test()
{
    int x = 1, y = 2, z = 3;
};
int main()
{
    // result是局部变量的引用
    int &result = sum();
    test(); // 另一个函数将覆盖先前函数栈上的教据
    cout << "result = " << result << endl; //输出：result =3
}

#pragma endregion

/**
 * 跟某人聊天-负责字符串的拼接(聊天格式)
 * @param toName 聊天对象的名称
 * @param content 聊天的内容
 * @return按某规定的格式拼接聊天信息后的字符串
 */
#pragma region 示例2函数返回引用
string chatTo(const string &toName, const string &content);
// string chat Fromconst strings fromName, const strings contont);
int main()
{
    string toName, content, chatMsg;
    cout << "请输入对方的名称: ";
    getline(cin, toName);
    cout << "请输入发送给对方的聊天信息: ";
    getline(cin, content);
    chatMsg = chatTo(toName, content);
    cout << chatMsg << endl;
}
// 这里用const 目的:在函数内部不能随意更改赋值。
string chatTo(const string &toName, const string &content)
{
    string msg = "x 你悄对[" + toName + "]: " + content;
    return msg;
}
#pragma endregion

 




#pragma region memset 作用是将某一块内存中的内容全部设置为指定的值， 这个函数通常为新申请的内存做初始化工作。
// 函数  memset(数组名,数组个数, 数组大小) 必需加个头文件string.h

#include <iostream>
#include <string.h>
using namespace std;
int main()
{
  char buffer[]="Helloworld\n";
    cout<<"Buffer before memset:"<<buffer<<endl;
    memset(buffer,'*',sizeof(buffer));
    cout<<"Buffer after memset:"<<buffer<<endl;
    return 0;
}
/*
Buffer before memset:Helloworld
Buffer after memset:***********
*/
#pragma endregion



/*********** 析构函数区别  实例化类用new 还是普通实例化
这里的new 分配在堆内存空间
栈内存与堆内存
    栈 系统分配,用完就走不处理自动释放,速度快,但是内存占用过多容易溢出。
    堆 内存自己分配，速度相比 栈慢但是差不多。
    堆内存 的析构，比栈的先执行。
析构函数来 判断栈用来多少内存，结束用就是释放内存的，配套用注意在哪个空间内。如果是，栈内存自动释放。堆内存则堆加 ，delete去释放。

析构函数
    1、对象过期时自动调用的特殊成员函数
    2、析构函数一般用来完成清理工作
    3、析构函数的名称是在类名前加 ~  ，且只能有一个以及没有参数。

***********/
#pragma region 注意 访问符.和 指针->的使用场景
class Student
{
public:
    Student();
    Student(string, string);
    ~Student();

    void ShowInfo();
}

Student stu1("马化腾", "普通家庭");
stu1.ShowInfo();

Student *stu2 = new Student("马云", "悔创阿里");
stu2->ShowInfo();
delete stu2; // 堆内存需要手动去释放

#pragma endregion 




  
 
 

 











 
 


友元类
/*
    若一个类A为另一个类B的友元类,则A类的所有成员函数都是B类的友元函数,都能访问B类的私有和保护成员。
    友元关系不能传递，只是单向的。且不被继承。
    如B被A 声明为友元，则B可以访问A的私有和保护数据，而A是不能访问B的。

 */
class A
{
    friend class B; // B可以访问所有A ，目的 共享数据保护
    publiç : void Display()
    {
        cout << x << endl;
    }

private:
    int x;
} class B
{
public:
    void Set(int i);
    void Display();

private:
    A a;
};

void B::Set(int i)
{
    a.x = i;
}
void B::Display()
{
    a.Display();
}

常对象(cosnt)
必须进行初始化, 不能被更新。
                    cosnt int n = 10; // cosnt  类型说明符 对象名;
class A
{
public:
    A(int i, int j) : x(i), y(j) {}

private:
    int x, y;
};
const A a(3, 4); // a是常对象,不能被更新
/*
    常成员函数
        -使用const关键字说明的函数。
        -常成员函数不更新对象的数据成员,也不能调用类中的非常成员函数。
        -常成员函数说明格式:类型说明符 函数名(参数表) const;
        这里,const是函数类型的一个组成部分,因此在实现部分也要带const关键字。
        -const关键字可以被用于参与对重载函数的区分
    通过常对象只能调用它的常成员函数。
    常数据成员
        -使用const说明的数据成员。
 */
// 常成员函数示例1
#include <iostream>
using namespace std;
class R
{
public:
    R(int rl, int r2)
    {
        R1 = rl;
        R2 = r2;
    }
    void print();
    void print() const;

private:
    int R1, R2;
};
void R::print()
{
    cout << R1 << ":" << R2 << endl;
}
void R::print() const
{
    cout << R1 << ";" << R2 << endl;
}
int main()
{
    R a(5, 4);
    a.print(); // 调用void print()
    const R b(20, 52);
    b.print(); // 调用void print() const  常对象才能调用常成员函数
}

// 常成员函数示例2
const int A::b = 10;
A::A(int i) : a(i), r(a) {}
void A::print()
{
    cout << a << ":" << b << ":" << r << endl;
}
int main()
{
    /*
        建立对象a和b,并以100和0作为初值,
        分别调用构造函数过构造函数的初始化列表给对象的常数据成员赋初值
    */
    A al(100), a2(0);
    a1.print();
    a2.print();
}

// 比如参数类型很复杂是个类对象，要调用构造函数用实参初始化形参 时间比较久，避免形参修改实参值。
// 被引用的对象不能被更新
const 类型说明符 &引用名
// 常引用做形参，不会更改实参。
#include <iostream>
    using namespace std;
void display(const double &r);
int main()
{
    double d(9.5);
    display(d);
    return 0;
}
void display(const double &r)
// 常引用做形参,在函数中不能更新r所引用的对象。
{
    cout << r << endl;
}

多文件和编译预处理命令

外部变量与外部函数
/*
    外部变量:可以为多个源文件所共享的全局变量
        -在其他源文件中,用extern关键字声明后使用
    外部函数:在所有类之外声明的函数(非成员函数),可以在不同的编译单元中被调用
    将变量和函数限制在编译单元内:
        -使用static关键字使用
        -匿名的命名空间
*/
标准C++ 类与组件分为6类
    /*
        输入输出类
        容器类与ADT (抽象数据类型)
        存储管理类
        算法
        错误处理
        运行环境支持
     */
    编译预处理命令
        /*
        #include 包含指令将一个源文件嵌入到当前源文件中该点处。
            -#include<文件名>
                按标准方式搜索,文件位于C++系统目录的include子目录下
            -#include"文件名"
                首先在当前目录中搜索,若没有,再按标准方式搜索。
        #define宏定义指令
            -定义符号常量,很多情况下已被const定义语句取代。
            -定义带参数宏,已被内联函数取代。
        #undef
            -删除由#define定义的宏,使之不再起作用。
         */
        条件编译指令
#if 常量表达式
            // 当" 常量表达式" 非零时编译
            程序正文1
#elif 常量表达式2
            程序正文2
#else
            // 当" 常量表达式" 为零时编译
            程序正文3
#endif

#ifndef HEAD_H
#define HEAD_H
#endif

#pragma region define跟 inline的微妙
#define S(num) num *num      // 当使用S(num)的地方，就自动被替换成 num * num
    int result1 = S(5 + 10); // 特殊之处实际上是求平方， 5 + 10 * 5 + 10  但是*号优先级高就变成了 5+50+10 =65;
inline int A(int);
int A(int num)
{
    return num * num; //  inline 就是比 define解决了 优先级的问题，
};
int result2 = A(5 + 10); //  15*15 =225

#pragma endregion

/*********** 指针
 &变量名  取地址
void *   任意类型
int  &p   地址
int  *p   取值

    空指针( null pointer ) ,就是不指向任何对象。
    例：
      int *ptr1 = nullptr; //等价 int *ptr1 = 0;
      int *ptr2= 0; //直接将ptr2初始化为字面常量0

void*	比较两个地址是否相等
指向常量的 const double& ref = 100;  //这样是常量的，指向变量开头。不加const。
***********/

关于内存地址
采用 &通过变量名、地址访问。
    指针变量概念
        指针：内存地址，用于间接访问内存单元。
            指针变量：用于存放地址的变量
    // 例如：
    static int i;
static int *i_pointer = &i; // i_pointer 指向整型变量的指针
// 指针变量 例：
// 举例 i 存放在地址2000里 其值是3，  *i_pointer  其i_pointer 指向了值为3的地址2000， *
i = 3;
*i_pointer = 3; // 即i_pointer == 地址2000  因为 *i_pointer 是等于3。

指针变量的初始化
存储类型 数据类型 *指针名 = 初始值;
按存储类型分为4种 : 自动变量auto 静态变量static 寄存器变量 register 外部变量 extern

                    注意事项 : -用变量地址作为初值时,
                               该变量必须在指针初始化之前已说明过,
                               且变量类型应与指针类型一致。 - 可以用一个已赋初值的指针去初始化另一个指针变量。 - 不要用一个内部 auto变量去初始化static指针。 指针名 = 地址 -“地址”中存放的数据类型与指针类型必须相符。 - 向指针变量赋的值必须是地址常量或变量,
                                                                                                                                                             不能是普通整数。但可以赋值为整数0,
                                                                                                                                                             表示空指针。 - 指针的类型是它所指向变量的类型,
                                                                                                                                                             而不是指针本身数据值的类型,
                                                                                                                                                             任何一个指针本身的数据值都是unsigned long int型。 - 允许声明指向void类型的指针。该指针可以被赋予任何类型对象的地址。
                                                                                                                                                                                                                     普通整数就是没有类型的常量

// 示例 1 指针变量的赋值运算
#include <iostream>
                                                                                                                                                                 using namespace std;
int main()
{
    int i;                            // 定义int型数i
    int *ptr = &i;                    // 取i的地址给ptr
    i = 10;                           // int型数赋初值
    cout << "i= " << i << endl;       // 输出int型数的值
    cout <<."*ptr= " << *ptr << endl; // 输出int型指针所指地址的内容
    return 0;
}
/*结果
    i=10; *ptr=10
*/

// 示例2 void类型指针的使用
#include <iostream>
using namespace std;
int main()
{
    // void voidObject;错,不能声明void类型的变量
    void *pv : // 对,可以声明void类型的指针
               int i = 5;
    pv = &i;                            // void类型指针指向整型变量
    int *pint = static cast<int *>(pv); // pv加强制类型转换
    // void类型指针赋值给int类型指针
    cout << "*pint = " << *pint << endl;
    return 0;
}

指向常量的指针 （只能当指针但可以修改为别的地址）
    // 不能通过指针来改变所指对象的值，但指针本身可以改变，可以指向另外的对象。
    int a;
const int *pl = &a; // pl是指向常量的指针
int b;
pl = &b; // 正确,p1本身的值可以改变
*pl = 1; // 编译时出错,不能通过pl改变所指的对象

指针类型的常量（不但是指针且只读不可修改）
int a;
int *const p2 = &a;
p2 = &b; // 错误，p2是指针常量，值不能改变

指针变量的关系运算
/*
    -指向相同类型数据的指针之间可以进行各种关系运算。
    -指向不同数据类型的指针,以及指针与一般整数变量之间的关系运算是无意义的。
    -指针可以和零之间进行等于或不等于的关系运算。
    例如: p==0或p!=0
*/
指针变量赋的值必须是地址常量或变量，不能是普通整数。但可以赋值为整数0，表示空指针。
指向数组元素的指针
声明与赋值
int a[10], *pa;
pa = &a[0];
或 pa = a; // 取第0个数组的地址 就是整个数组的地址

通过指针引用数组元素
*pa就是a[0].*(pa + 1) 就是a[1], ...,
    *(pa + i) 就是a[i].a[i], *(pa + i), *(a + i), pa[i] 都是等效的。 不能写a++, 因为a是数组首地址是常量。

    申请的一段内存空间没有名字 把这段地址起始地址赋给指针变量 这样更快捷 Point *pa[2]; // 由pa[0],pa[1]两个指针组成

// 示例1 利用指针数组存放单位矩阵
#include <iostream>
using namespace std;
int main()
{
    int line1[] = {1, 0, 0}; // 矩阵的第一行
    int line2[] = {0, 1, 0}; // 矩阵的第二行
    int line3[] = {0, 0, 1}; // 矩阵的第三行
    // 定义整型指针数组并初始化
    int *pLine[3] = {line1, line2, line3};
    cout << "Matrix test:" << endl;
    // 输出单位矩阵
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0 : j < 3; j++)
        {
            cout << pLine[i][j] << "";
            << cout << endl;
        }
    }
    return 0; // pLine的I 是哪一个数组的意思 ,起始地址 j是这个数组里第几个元素  看起来像一个二维数组
}

// 示例2 二维数组
#include <iostream>
using namespace std;
int main()
{
    int array2[3][3] = {{11, 12, 13}, {21, 22, 23}, {31, 32, 33}};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0 : j < 3; j++)
        {
            cout << *(*(array2 + i) + j) << ""; // 逐个输出二维数组第i行元素值
        }
        cout << endl;
    }
    return 0; // （array2）是二维数组的起始地址 加i就是哪一行的元素 加j是哪一列的元素
}

指针与函数关系
以指针作为函数参数
以地址方式传递数据, 可以用来返回函数处理结果。
                        实参是数组名时形参可以是指针。
// 形参接受实参传递过来的数组的起始地址

// 要求:读入三个浮点数,将整数部分和小数部分分别输出
#include <iostream>
    using namespace std;
void splitFloat(float x, int *intPart, float *fracPart)
{
    // 取x的整数部分
    *ntPart = static_cast<int>(x);
    // 取x的小数部分
    *fracPart = x - *intPart;
}
int main()
{
    cout << "Enter 3 float point numbers:" << endl;
    for (int i = 0; i < 3; i++)
    {
        float x, f;
        int n;
        cin >> x;
        splitFloat(x, &n, &f); // 变量地址作为实参
        cout << "Integer Part =" << n
             << " Fraction Part = " << f << endl;
    }
    return 0;
}
// 示例 输出数组元素的内容和地址
#include <iostream>
#include <iomanip>
using namespace std;
void arrayPtr(long *p, int n)
{
    cout << "In func, address of array is" << p << endl;
    cout << "Accessing array using pointers" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << " Address for index " << i << "is" << p + i;
        cout << " Value is " << *(p + i) << endl;
    }
}
int main()
{
    long list[5] = {50, 60, 70, 80, 90};
    cout << "In main, address of array is" << list << endl;
    cout << endl;
    arrayPtr(list, 5);
    return 0;
}
/* 输出结果
In main, address of array is 0012FF50
In func, address of array is 0012FF50
Accessing array using pointers
    Address for index 0 is 0012FF50 Value is 50
    Address for index 1 is 0012FF54 Value is 60
    Address for index 2 is 0012FF58 Value is 70
    Address for index 3 is 0012FF5C Value is 80
    Address for index 4 is 0012FF60 Value is 90
 */

指向常量的指针做形参
#include <iostream>
using namespace std;
const int N = 6;
void print(const int *p, int n);
int main()
{
    int array[N];
    for (int i = ; i < N; i++)
    {
        cin >> array[i];
        print(array, N);
    }
    return 0;
}
void print(const int *p, int n)
{
    cout << "[" << *p;
    for (int i = 1; i < n; i++)
        cout < < < < *(p + i);
    cout << "]" << endl;
}

/***********函数模块化
    函数三要素：返回值类型、函数名、参数列表。
    // return_type 返回值类型 // functionName 函数名  // (parameterList) 参数列表
    return_type functionName(parameterList)
    {
        //函数体
    }

函数指针
        double (*ptrCalc)(double, double)
        简化声明  typedef double (*ptrCalc)(double, double)  ptrCalc ptrFunc;
***********/

指针型函数
当函数的返回值是地址时, 该函数就是指针型函数。 声明形式 存储类型 数据类型 *函数名() 指向函数的指针 含义 : 数据指针指向数据存储区, 而函数指针指向的是程序代码存储区。 声明形式 存储类型 数据类型 (*函数指针名)();
// 示例 函数指针
#include <iostream>
using namespace std;
void printStuff(float)
{
    cout << "This is the print stuff function." << endl;
}
void printMessage(float data)
{
    cout << "The data to be listed is " << data << endl;
}
void printFloat(float data)
{
    cout << "The data to be printed is " << data << endl;
}
const float PI = 3.14159f;
const float TWO_PI = PI * 2.0f;
int mian()
{                                   // 主函数
    void (*functionPointer)(float); // a数指针
    printStuff(PI);
    functionPointer = printStuff;
    functionPointer(PI); // 函数指针调用
    functionPointer = printMessage;
    functionPointer(TWO_PI); // 函数指针调用
    functionPointer(13.0);
    functionPointer = printFloat; // 函数指针调用
    functionPointer(PI);          // 函数指针调用
    printFloat(PI);
    return 0;
}
/*
    This is the print stuff function.
    This is the print stuff function.
    The data to be listed is 6.28318
    The data to be listed is 13
    The data to be printed is 3.14159
    The data to be printed is 3.14159
 */

对象指针
对象指针的一般概念
声明形式
类名 *对象指针名;
例如 : Point a(5, 10);
Piont *ptr;
ptr = &a;
int main()
{
    Point a(5, 10);
    Point *ptr;
    ptr = &a;
    int x;
    x = ptr->getX();
    cout << x << endl;
    return 0:
}
class Fred; // 前向引用声明
class Barney
{
    Fred *x; // Fred x;错误:类Fred的声明尚不完善
};
class Fred
{
    Barney y;
};

this指针
    隐含于每一个类的成员函数中的特殊指针。
        明确地指出了成员函数当前所操作的数据所属的对象。
            当通过一个对象调用成员函数时,
    系统先将该对象的地址赋给this指针,
    然后调用成员函数, 成员函数对对象的数据成员进行操作时, 就隐含使用了this指针。

    // 示例 POINT类的GETX函数种的语句
    return x;
相当于 : return this->x;
指向类的非静态成员的指针
通过指向成员的指针只能访问公有成员
声明指向成员的指针
- 声明指向公有数据成员的指针
    类型说明符 类名::指针名;
- 声明指向公有函数成员的指针
    类型说明符 (类名::*指针名)(参数表)
        非静态成员
    指向类的非静态成员的指针
    指向数据成员的指针
    - 说明指针应该指向哪个成员
    指针名 = &类名::数据成员名:
                        -通过对象名(或对象指针)与成员指针结合来访问数据成员
                        对象名
                        .*类成员指针名
                            或:
                                对象指针名->*类成员指针名
                                        指向函数成员的指针
                                    - 初始化
                                    指针名 = &类名::函数成员名;
- 通过对象名(或对象指针)与成员指针结合来访问函数成员(对象名.*类成员指针名)(参数表)
    或:
        (对象指针名->*类成员指针名)(参数表)
    // 示例 访问对象的公有成员函数的不同方式
    int main()
{
    // 主a数
    Point a(4, 5);  // 声明对象A
    Point *pl = &a; // 声明对象指针并初始化
    // 声明成员函数指针并初始化
    int (Point::*funcPtr)() = Point::getX;
    //(1)使用成员函数指针访问成员函数
    cout << (a.*funcPtr)() << endl;
    //(2)使用成员函数指针和对象指针访问成员函数
    cout << (pl->*funcPtr)() << endl;
    //(3)使用对象名访问成员函数
    cout << a.getX() << endl;
    //(4)使用对象指针访问成员函数
    cout << pl->getX() << endl;
    return 0;
}

指向类的静态成员的指针
*对类的静态成员的访问不依赖于对象
    *可以用普通的指针来指向和访问静态成员
// 例6-14通过指针访问类的静态数据成员
#include <iostream>
    using namespace std;
class Point
{
    // Point类定义
public: // 外部接日
    Point(int x = 0, int y = 0) : x(x).y(y)
    {
        count++;
    }
    Point(const Point &p) : x(p.x), y(p.y)
    {
        count++;
    }
    ~Point() { count--; }
    int getX() const { return x; }
    int getv() const { return y; }
    static int count;

private: // 私有数据成员
    int x, y;
} int Point::count = 0;
int main()
{ // 主函数实现
    // 定义一个int型指针,指向类的静态成员
    int *ptr = &Point::count;
    Point a(4, 5); // 定义对象a
    cout << "Point A: " << a.getX() << "," << a.getY();
    cout << " Object count =" << *ptr << endl;
    Point b(a) : // 定义对象b
                 cout << "Point B: " << b.getX() << "," << b.getY();
    cout << " Object count =" * ptr << endl;
    return 0;
}
// 例6-15通过指针访问类的静态函数成员
#include <iostream>
using namespace std;
class Point
{       // Point类定义
public: // 外部接口
    Point(int x = 0, int y = 0) : x(x), y(y) { count++; }
    Point(const Point &p) : x(p.x).y(p.y) { count++; }
    ~Point() { count--; }
    int getX() const { return x; }
    int getY() const { return y; }
    static void showCount()
    {
        cout << " Object count = " << count << endl;
    }

private: // 私有数据成员
    int x, y;
    static int count;
} int Point::count = 0;
int main()
{ // 主函数实现
    // 定义一个指向函数的指针,指向类的静态成员函数
    void (*funcPtr)() = Point::showCount;
    Point a(4, 5); // 定义对象A
    cout << "Point A: " << a.getX() << "." << a.getY();
    funcPtr();  // 输出对象个数,直接通过指针访问静态函数成员
    Point b(a); // 定义对象B
    cout << "Point B: " << b.getX() << ". " << b.getY();
    funcPtr(); // 输出对象个数,直接通过指针访问静态函数成员
    return 0;
}
