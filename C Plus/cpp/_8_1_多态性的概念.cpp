/***********  多态性的概念 
    1、多态性是面向对象程序设计的重要特征之一。
    2、多态性是指发出同样的消息被不同类型的对象接收时有可能导致完全不同的行为。
    多态的实现：
        1、函数重载
        2、运算符重载 
        3、虚函数

虚函数问题举例一一复数的运算
    class Complex {//复数类声明
        public:Complex(double r = 0.0,double i = 0.0) real'= r; imag=i;
    };
    void display() const; //显示复数的值
    private:
        double real;
        double imag;
    } 
运算符重载
    运算符重载运算符重载的实质
        必要性
            C++中预定义的运算符其运算对象只能是基本数据类型,而不适用于用户自定义类型(如类)
        实现机制
            1、将指定的运算表达式转化为对运算符函数的调用,运算对象转化为运算符函数的实参。
            2、编译系统对重载运算符的选择,遵循函数重载的选择原则。
        规则和限制
            1、可以重载C++中除下列运算符外的所有运算符: . .* :: ?:
            2、只能重载C++语言中已有的运算符不可臆造新的。
            3、不改变原运算符的优先级和结合性。
            4、不能改变操作数个数。
            //经重载的运算符,其操作数中至少应该有一个是自定义类型。
        两种形式
            重载为类的非静态成员函数
            重载为非成员函数
运算符函数
    声明形式
        函数类型 operator 运算符(形参)
        {
            ...
        }
    形式参数 自定义为系统没有的 已存在的
    重载为类成员函数时
        1、参数个数=原操作数个数-1(后置++-除外)
        2、重载为非成员函数时参数个数=原操作数个数,且至少应该有一个自定义类型的形参。

前置单目运算符U
    如果要重载U为类成员函数,使之能够实现表达式U oprd,其中oprd为A类对象,则U应被重载为A类的成员函数无形参。
    经重载后表达式 U oprd 相当与oprd.operatorU()
后置单目运算符
    ++和-如果要重载++或-为类成员函数,使之能够实现表达式 oprd++ 或 oprd-- ,其中oprd 为A类对象,则++或…应被重载为A类的成员函数且具有一个int类型形参。
    经重载后,表达式 oprd++相当于oprd.operator ++(0)

运算符非成员函数的设计
    1、函数的形参代表依自左至右次序排列的各操作数。
    2、后置单目运算符++和--的重载函数,形参列表中要增加一个int,但不必写形参名。
    3、如果在运算符的重载函数中需要操作某类对象的私有成员,可以将此函数声明为该类的友元。
    
    双目运算符B重载后
        表达式 oprdl B oprd2  等同于operator B(oprdl,oprd2)
    前置单目运算符B重载后
        表达式Boprd 等同于  operator B(oprd)
    后置单目运算符++和--重载后
        表达式oprd B 等同于  operator B(oprd,0))
    
***********/ 
  
#pragma region 示例8-1有虚基类时的构造函数举例
#include <iostream> 
using namespace std;
class Complex {//复数类定义
    public: //外部接口
        Complex(double r= 0.0, double i= 0.0) : real(r),imag(i) {}; //构造函数
        Complex operator + (const Complex &c2) const; //运算符+重载成员函数
        Complex operator - (const Complex &c2) const; //运算符·重载成员函数
        void display() const; //输出复数
    private: //私有数据成员
        double real; //复数实部
        double imag; //复数虚部
};
Complex Complex::operator + (const Complex &c2) const { //重载运算符函数实现
    return Complex(real + c2.real, imag +c2.imag); //创建一个临时无名对象作为返回值
};
Complex Complex::operator- (const Complex &c2) const { //重载运算符函数实现
    return Complex(real- c2.real, imag - c2.imag); //创建一个临时无名对象作为返回值
};
void Complex::display() const {
    cout << "("<< real <<". "<< imag<< ")" << endl;
};

int main () {//主函数
    Complex c1(5, 4), c2(2, 10), c3; //定义复数类的对象
    cout << "cl= "; 
    c1.display(); 
    cout << "c2 = "; 
    c2.display();
    c3 = c1-c2;//使用重载运算符完成复数减法
    cout << "c3 = cl- c2 = ";
    c3.display();
    c3 = c1 + c2; //使用重载运算符完成复数加法
    cout << "c3 = c1 + c2 = "; 
    c3.display ();
    return 0;
}
/* 程序输出的结果为:
c1 = (5, 4)
c2 = (2, 10)
c3 = c1 - c2 = (3, -6)
c3 = cl + c2 = (7, 14) 
 */
#pragma endregion

/***********
 1、运算符前置++和后置++,重载函数
 2、没有形参,对于后置单目运算符,重载函数需要有一个整型形参。
 3、操作数是时钟类的对象。
 4、实现时间增加1秒钟。
***********/ 

#pragma region 示例8-2前置单目运算符
#include <iostream> 
using namespace std;
class Clock {//钟类声明定义
    public: //外部接口
        Clock(int hour = 0, int minute = 0, int second = 0);
        void showTime() const;
        Clock& operator ++ (); //前置单目运算符重载
        Clock operator ++ (int);//后置单目运算符重载
    private: //私有数据成员
    int hour, minute, second;
};
//前置单目运算符重载函数
Clock & Clock::operator ++ () {
     second ++;
     if (second >= 60) {
        second -= 60;
        minute++;
        if (minute >= 60) {
            minute -= 60;
            hour = (hour + 1) % 24;
        }
     }
     return *this;
};
//后置单目运算符重载
Clock Clock::operator ++ (int){//注意形参表中的整型参数
    Clock old = *this;++(*this); //调用前置“++"运算符
    return old;
}
//其它成员函数的实现略
int main() {
    Clock myClock(23, 59, 59);
    cout << "First time output:";
    myClock.showTime ();
    cout << "Show my Clock++:";
    (myClock++).showTime();
    cout << "Show ++ my Clock:";
    (++ myClock).showTime();
    return 0;
}
/* 程序运行结果为:
First time output: 23:59:59
Show myClock++: 23:59:59
Show ++myClock: 0:0:1
 */

#pragma endregion



/***********
 1、将+、-(双目)重载为非成员函数,并将其声明为复数类的友元,两个操作数都是复数类的常引用。
 2、将<<(双目)重载为非成员函数,并将其声明为复数类的友元,它的左操作数是std::ostream引用,右操作数为复数类的常引用,返回std::ostream引用用以支持下面形式的输出: cout <<a <<b;该输出调用的是: operator <<(operator <<(cout, a), b);形成连续输出 
***********/ 
#pragma region 示例8-3前置单目运算符
#include <iostream> 
using namespace std;
class Complex {//复数类定义
    public: //外部接口
    Complex(double r= 0.0, double i= 0.0) : real(r),imag(i){}//构造函数
    friend Complex operator + (const Complex &cl, const Complex &c2); //运算符+重载
    friend Complex operator - (const Complex &cl, const Complex &c2); //运算符-重载
    friend ostream & operator << (ostream &out, const Complex &c); //运算符<<重载
    private: //私有数据成员
        double real; //复数实部
        double imag; //复数虚部
};
#pragma endregion


