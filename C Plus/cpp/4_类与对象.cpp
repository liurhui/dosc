#pragma region 示例 类定义
#include<iostream>
using namespace std;
class Landowner{
    public: // 公有成员（外部接口）
        Landowner();
        Landowner(string);
        Landowner(string, string, int, long);
        ~Landowner();

        string GetNickName() { return m_NickName; }
        void SetNickName(string val) { m_NickName = val; }

        string GetSex() { return m_Sex; }
        void SetSex(string val) { m_Sex = val; }

        int GetGold() { return m_Gold; }
        void SetGold(int val) { m_Gold = val; }

        long GetExp() { return m_Exp; }
        void SetExp(long val) { m_Exp = val; }

        void ShowInfo();
    protected: // 保护型成员
    private:   // 私有成员
        string m_NickName;
        string m_Sex;
        int m_Gold;
        long m_Exp;
};
#pragma endregion 

#pragma region 类_构造函数与析构函数 示例4-3
/*
  要求：一圆型游泳池如图所示,现在需在其周围建一圆型过道,并在其四周围上栅栏。
  栅栏价格为35元/米,过道造价为20元/平方米。
  过道宽度为3米,游泳池半径由键盘输入。
  要求编程计算并输出过道和栅栏的造价。
*/
#include <iostream>
using namespace std;
const float PI = 3.14159;
const float FencePrice = 35;
const float ConcretePrice = 20;
// 声明类Circle及其数据和方法
class Circle{
private:
    float radius;
public:
    //构造数
    Circle(float r);
    //函数末尾加const的作用,不会修改任何参与运算的变量的值。
    float Circumference() const;  //圆周长
    float Area() const; //圆面积
};

// 用构造函数来初始化 radius
Circle::Circle(float r){
    radius = r;
}
// 计算圆的周长
float Circle::Circumference() const{
    return 2 * PI * radius;
}
// 计算圆的面积
float Circle::Area() const{
    return PI * radius * radius;
}
int main(){
    float radius;
    float FenceCost, ConcreteCost;
    // 提示用户输入半径c
    cout << "Enter the radius of the pool: ";
    cin >> radius;

    // 声明Circle 对象
    Circle Pool(radius);
    Circle PoolRim(radius + 3);
    // 计算栅栏造价并输出
    FenceCost = PoolRim.Circumference() * FencePrice;
    cout << "Fencing Cost is ¥" << FenceCost << endl;
    // 计算过道造价并输出
    ConcreteCost = (PoolRim.Area()-Pool.Area()) * ConcretePrice;
    cout << "Concrete Cost is ¥" << ConcreteCost << endl;
    return 0;
}

#pragma endregion


#pragma region 示例结构体
// 结构体变量的初始化和使用
#include <iostream>
#include <iomanip>
using namespace std;
struct student { // 学生信息结构体
    int num;       // 学号
    char name[20]; // 姓名
    char gender;   // 性别
    int age;       // 年龄
} stu = {97001, "Lin Lin", 'F', 19};
int main() {
    cout << setw(7) << stu.num << setw(20) << stu.name << setw(3) << stu.gender << setw(3) << stu.age;
}
#pragma endregion


#pragma region 示例无名联合体   使用联合体保存成绩信息
#include <string>
#include <iostream>
using namespace std;
class ExamInfo {
    public:
        //按等级成绩
        ExamInfo(string name, char grade) : name(name), mode(GRADE), grade(grade) {}
        //课程成绩是否合格
        ExamInfo(string name, bool pass) : name(name), mode(PASS), pass(pass) {}
        //百分制成绩
        ExamInfo(string name, int percent) : name(name), mode(PERCENTAGE), percent(percent) {}
        //显示成绩
        void show();
    private : 
        string name;
        //枚举类型来方便变量管理   声明为对象mode是数据成员
        enum {
            GRADE,
            PASS,
            PERCENTAGE
        } mode;
        //成绩是不同类型的用联合体 管理
        union {
            char grade;
            bool pass;
            int percent;
        };
};
void ExamInfo::show() {
    cout << name << ": ";
     //根据不同类型来判别成绩用哪种表示
    switch (mode) {
        case GRADE:
            cout << grade;
            break;
        case PASS:
            cout << (pass ? "PASS" : "FAIL");
            break;
        case PERCENTAGE:
            cout << percent;
            break;
    }
    cout << endl;
}
int main()
{
    //3门课程 分别用 等级、通过、数值三种方式输出结果。
    ExamInfo course1("English", 'B');
    ExamInfo course2("Calculus", true);
    ExamInfo course3("C++ Programming", 85);  
    course1.show();
    course2.show();
    course3.show();
    return 0;
}
#pragma endregion













#pragma region 带参构造
// 声明
Student::Student(string name, string desc)
{
    name = name;
    desc = desc;
}
// 调用
Student *stu = new Student("撒贝宁"."北大还行");
stu->ShowInfo();

Student::Student(string name, string desc) : m_Name(name), m_desc(desc)
{
    // 这种叫赋值写法也叫参数列表。  等于  SetName(name);   n_Name = name;
}
#pragma endregion