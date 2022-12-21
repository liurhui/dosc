//vscode测试mingw 是都正常工作
#include <iostream>
#include <vector>
#include <string>

using namespace std;
/* int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
 for (const string& word : msg)
 {
        cout << word << " ";
 }
    cout << endl;
} */

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
    cout << "Enter the radius of the pool: " ;
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