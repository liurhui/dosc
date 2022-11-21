/***********  虚函数 
静态绑定与动态绑定
    绑定
        程序自身彼此关联的过程,确定程序中的操作调用与执行该操作的代码间的关系。
    静态绑定
        绑定过程出现在编译阶段,用对象名或者类名来限定要调用的函数。
    动态绑定
        绑定过程工作在程序运行时执行,在程序运行时才确定将要调用的函数。    
虚函数
    1、虚函数是动态绑定的基础。
    2、是非静态的成员函数。
    3、在类的声明中,在函数原型之前写virtual。
    4、virtual只用来说明类声明中的原型,不能用在函数实现时。
    5、具有继承性,基类中声明了虚函数,派生类中无论是否说明,同原型函数都自动为虚函数。
    6、本质:不是重载声明而是覆盖。
    7、调用方式:通过基类指针或引用,执行时会根据指针指向的对象的类,决定调用哪个函数。

虚析构函数
    为什么需要虚析构函数?
        1、可能通过基类指针删除派生类对象;
        2、如果你打算允许其他人通过基类指针调用对象的析构函数(通过delete这样做是正常的),就需要让基类的析构函数成为虚函数,否则执行delete的结果是不确定的。
        //纯虚函数与抽象类没有函数体的
抽象类
    作用
        1、抽象类为抽象和设计的目的而声明,将有关的数据和行为组织在一个继承层次结构中,保证派生类具有要求的行为。
        2、对于暂时无法实现的函数,可以声明为纯虚函数,留给派生类去实现。  
    注意
        1、抽象类只能作为基类来使用。
        2、不能声明抽象类的对象。
        3、构造函数不能是虚函数,析构函数可以是虚函数。  
    带有纯虚函数的类称为抽象类:
        class 类名
        {
            virtual类型 函数名(参数表)=0;
            //纯虚函数
            ...
        }
***********/ 
  
#pragma region 示例8-4有虚基类时的构造函数举例
#include <iostream> 
using namespace std;
class Base1 {//基Basel定义
    public:virtual void display() const; //虚a数 
    void Base1::display() const {
        cout << "Basel::display()" << endl;
    }
};
class Base2: public Base1 {
    //公有派生类Base2定义
    public:
        void display() const;//覆盖基类的虚函数
};
void Base2::display() const {
    cout << "Ba'se2::display()" << endl;
    //公有派生类Derived定义
};
class Derived: public Base2 {
    public:
        void display () const; //覆盖基类的虚函数
};
void Derived::display() const {
    cout << "Derived::display()" << endl;
};
//参数为指向基类对象的指针
void fun(Base1 *ptr){
    ptr->display(); //"对象指针->成员名”
}
int main () {//主函数
    Base1 base1;//定义Basel类对象
    Base2 base2; //定义Base 2类对象
    Derived derived; //定义Derived类对象
    fun(&base1);//用Base1对象的指针调用fun函数
    fun(&base2);//用Base2对象的指针调用fun函
    fun (&derived); //用Derived对象的指针调用fun函数数
    return 0;
}   
/* 运行结果: 
Basel::display() 
Base2::display () 
Derived::display()
 */
#pragma endregion



#pragma region 示例8-5抽象类
#include <iostream> 
using namespace std;
class Basel {//基类Basel定义
    public:
        virtual void display() const = 0; //纯虚函数
};
class Base2: public Basel {//公有派生类Base2定义
    public:
    //覆盖基类的虚函数
        void display() const {  cout << "Base2::display()" << endl;}
};
class Derived: public Base2 {//公有派生类Derived定义
    public:
    //覆盖基类的虚函数
        void display() const { cout << "Derived::display()" << endl;}
};
void fun(Basel *ptr) {
    ptr->display(); //"对象指针->成员名"
}

int main() {//主函数
    Base2 base2; //定义 Base2类对象
    Derived derived;//定义Derived类对象
    fun(&base2); //用Base2对象的指针调用fun函数
    fun(&derived);//用Derived对象的指针调用fun函数
    return 0;
}
#pragma endregion



