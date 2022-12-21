#pragma region 对象的声明周期 示例5-2变量的生存期与可见性
#include <iostream>
using namespace std;
int i = 1;// i为全局变量,具有静态生存期。
int main(){
    static int a; // 静态局部变量,有全局寿命,局部可见。
    int b = -10;  // b, c为局部变量,具有动态生存期。
    int c = 0;
    void other(void);
    cout << "---MAIN---\n";
    cout << " i: " << i << " a: " << a << "b: " << b << " c: " << c << endl; // i:1 ,a:0, b:-10, c:0
    c = c + 8;
    other(); // i:33 ,a:4, b:0, c:15
    cout << "---MAIN---\n";
    cout << " i: " << i << " a: " << a << "b: " << b << " c: " << c << endl; // i:33 ,a:0, b:-10, c:8
    i = i + 10;
    other(); // i:75 ,a:6, b:4, c:15
}
void other(void) {
    static int a = 2;
    static int b;
    // a,b为静态局部变量,具有全局寿命,局部可见。
    // 只第一次进入函数时被初始化。
    int c = 10;
    // C为局部变量,具有动态生存期
    // 每次进入函数时都初始化。
    a = a + 2;
    i = i + 32;
    c = c + 5;
    cout << "---OTHER---\n";
    cout << " i: " << i << " a: " << a << " b: " << b << " c: " << c << endl;
    b = a;
}


#pragma endregion

#pragma region 对象的声明周期示例5-3 具有静、动态生存期对象的时钟程序
#include <iostream>
using namespace std;
class Clock{ // 时钟类声明
    public: // 外部接口
        //构造函数
        Clock(); 
        void SetTime(int NewH, int NewM, int NewS); // 三个形参均具有函数原型作用域
        void ShowTime();
        //析构函数
        ~Clock() {}

    private: // 私有数据成员
        int Hour, Minute, Second;
};
// 时钟类成员函数实现
Clock::Clock(){ // 构造数
    Hour = 0;
    Minute = 0;
    Second = 0;
}
void Clock::SetTime(int NewH, int NewM, int NewS){
// 三个形参均具有局部作用域

    Hour = NewH;
    Minute = NewM;
    Second = NewS;
}
void Clock::ShowTime(){
    cout << Hour << ":" << Minute << ":" << Second << endl;
}
// 1、声明对象globClock
// 2、具有静态生存期,命名空间作用域
// 3、由默认构造函数初始化为0:0:0
Clock globClock;

int main(){ // 主函数
    cout << "First time output:" << endl; 
    // 引用具有文件(也就是全局但是只在本文件)作用域的对象:
    globClock.ShowTime();// 对象的成员函数具有类作用域
    globClock.SetTime(8, 30, 30);

    // 声明具有局部作用域的对象myClock
    Clock myClock(globClock); 
    cout << "Second time output:" << endl;
    myClock.ShowTime(); // 引用具有局部作用域的对象
}
/*
First time output:
0:0:0
Second time output:
8:30:30
*/
#pragma endregion

#pragma region 类的静态成员 示例5-4 具有静态数据成员的POINT类
#include <iostream>
using namespace std;
class Point {// 引入静态数据成员count来统计Point类对象个数
    public:
        // 构造函数
        Point(int xx = 0, int yy = 0) : X(xx), Y(yy) { count++; }
        // 复制构造函数
        Point(Point &p);     
        // 析构函数
        ~Point() { count--; } 
        int GetX() { return X; }
        int GetY() { return Y; }
        void showCount() { cout << " Objectcount=" << count << endl; }
    private:
        int X, Y;
        static int count;
};
Point::Point(Point &p){
    X = p.X;
    Y = p.Y;
    count++;
}
// 由于cout 是静态的所以得在class 外的全局位置定义初值
int Point::count = 0;
int main() {
    Point a(4, 5);
    cout << " Point A: " << a.GetX() << "," << a.GetY(); // Point A: 4, 5 Object count=1
    a.showCount();
    Point b(a);
    cout << "Point B: " << b.GetX() << ", " << b.GetY(); // Point B: 4, 5 Object count=2
    b.showCount();
    return 0;
}
#pragma endregion

#pragma region 类的静态成员 示例5-5 具有静态数据、函数成员的POINT1类
#include <iostream>
using namespace std;
class Point1 {// Point1类声明
    public: // 外部接口
        Point1(int xx = 0, int yy = 0) : X(xx), Y(yy) { count++; }
        // 复制构造函数
        Point1(Point1 &p);
         // 析构函数
        ~Point1() {  count--;}
        int GetX() { return X; }
        int GetY() { return Y; }
        static void showCount(){ cout << " Object count=" << count << endl;}

    private: // 私有数据成员
        int X, Y;
        static int count; // 静态的static
};

Point1::Point1(Point1 &p)
{
    X = p.X;
    Y = p.Y;
    count++;
}
int Point1::count = 0;
int main() // 主函数实现
{
    Point1 a(4, 5); // 声明对象A
    cout << "Point A," << a.GetX() << ", " << a.GetY();
    Point1::showCount(); // 输出对象个数
    Point1 b(a);         // 声明对象B
    cout << "Point B," << b.GetX() << ", " << b.GetY();
    Point1::showCount(); // 输出对象个数
    return 0;
    // Point是类名字
}
#pragma endregion

#pragma region 类的友元 示例5-6 友元函数计算两点距离
#include <iostream>
#include <cmath>
using namespace std;
class Point3 {// Point3类声明
    public: 
        Point3(int xx = 0, int yy = 0) {
            X = xx;
            Y = yy;
        }
        int GetX() { return X; }
        int GetY() { return Y; }
        friend double Distance(Point3 &a, Point3 &b);
    private:  
        int X, Y;
};
double Distance(Point3 &a, Point3 &b){
    double dx = a.X - b.X;
    double dy = a.Y - b.Y;
    return sqrt(dx * dx + dy * dy);
}
int main(){
    Point3 pl(3.0, 5.0), p2(4.0, 6.0);
    double d = Distance(pl, p2);
    cout << "The distance is " << d << endl;
    return 0;
}
#pragma endregion

