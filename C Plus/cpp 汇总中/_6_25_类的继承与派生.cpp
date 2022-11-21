/*********** 类的继承与派生 ,  一个问题的两个不同角度
    保持已有类的特性而构造新类的过程称为继承。
    在已有类的基础上新增特性而产生新类的过程称为派生。
    被继承的已有类称为基类(或父类)派生出的新类称为派生类。
    继承的目的:
        实现代码重用。
    派生的目的:
        当新的问题出现,原有程序无法解决(或不能完全解决)时,需要对原有程序进行改造。
    子类像父类观察 已有的代码重复使用
        对基类是内部访问，通过派生类对象对基类外部访问。

    派生类声明
        class 派生类名:继承方式 基类名
        {
            成员声明;
        }
    三种继承方式
        公有继承、私有继承、保护继承
    
    
    不同继承方式的影响主要体现在:
        1、派生类成员对基类成员的访问权限
        2、通过派生类对象对基类成员的访问权限

    公有继承(public)
        1、基类的public和protected成员的访问属性在派生类中保持不变,但基类的private成员不可直接访问。
        2、派生类中的成员函数可以直接访问基类中的public和protected成员,但不能直接访问基类的private成员。
        3、通过派生类的对象只能访问基类的public成员。

    私有继承(private)
        1、基类的public和protected成员都以private身份出现在派生类中,但基类的private成员不可直接访问
        2、派生类中的成员函数可以直接访问基类中的public和protected成员,但不能直接访问基类的private成员。
        3、通过派生类的对象不能直接访问基类中的任何成员。

    保护继承(protected)
        1、基类的public和protected成员都以protected身份出现在派生类中,但基类的private成员不可直接访问。
        2、派生类中的成员函数可以直接访问基类中的public和protected成员,但不能直接访问基类的private成员。
        3、通过派生类的对象不能直接访问基类中的任何成员
        protected 成员的特点与作用：
            对建立其所在类对象的模块来说,它与private成员的性质相同。
            对于其派生类来说,它与public成员的性质相同。
            既实现了数据隐藏,又方便继承,实现代码重用。


类型兼容规则
    一个公有派生类的对象在使用上可以被当作基类的对象,反之则禁止。具体表现在:
        1、派生类的对象可以隐含转换为基类对象。
        2、派生类的对象可以初始化基类的引用。
        3、派生类的指针可以隐含转换为基类的指针。
    通过基类对象名、指针只能使用从基类继承的成员。

单继承与多继承
    基类与派生类的对应关系
        单继承
            1、派生类只从一个基类派生。
        多继承
            2、派生类从多个基类派生。
        多重派生
            3、由一个基类派生出多个不同的派生类。
        多层派生
            1、派生类又作为基类,继传派生新的类。
    多继承时派生类的声明
        class 派生类名:继承方式1 基类名1, 继承方式2 基类名2,....
        {
            成员声明;
        }
    继承方式 是public、protected 、private, 每个的继承方式 ，是对应的基类名的方式 ，可以不一样。

派生类的构造、析构函数
    继承时的构造函数
        1、基类的构造函数不被继承,派生类中需要声明自己的构造函数。
        2、定义构造函数时,只需要对本类中新增成员进行初始化,对继承来的基类成员的初始化,自动调用基类构造函数完成。
        3、派生类的构造函数需要给基类的构造函数传递参数
    单一继承时的构造函数
        派生类名::派生类名(基类所需的形参,本类成员所需的形参):基类名(参数表)
        {
            本类成员初始化赋值语句;
        };

    多继承时的构造函数
        派生类名::派生类名(参数表):基类名1(基类1初始化参数表),基类名2(基类2初始化参数表), 基类名n(基类n初始化参数表)
        {
            本类成员初始化赋值语句;
        } 
    总结
        派生类与基类的构造函数
            当基类中声明有缺省构造函数或未声明构造函数时,
            派生类构造函数可以不向基类构造函数传递参数,也可以不声明,
            构造派生类的对象时,基类的缺省构造函数将被调用。
        派生类与基类的构造函数
            当需要执行基类中带形参的构造函数来初始化基类数据时,
            派生类构造函数应在初始化列表中为基类构造函数提供参数。
    
    多继承且有内嵌对象时的构造函数
        派生类名::派生类名(形参表):基类名1(参数),基类名2(参数), 基类名n(参数),新增成员对象的初始化
        {
            本类成员初始化赋值语句;
        }
    构造函数的执行顺序
        1.调用基类构造函数,调用顺序按照它们被继承时声明的顺序(从左向右)。
        2.对成员对象进行初始化,初始化顺序按照它们在类中声明的顺序。
        3.执行派生类的构造函数体中的内容。
    拷贝构造函数
        若建立派生类对象时没有编写拷贝构造函数,编译器会生成一个隐含的拷贝构造函数,
        该函数先调用基类的拷贝构造函数,再为派生类新增的成员对象执行拷贝。
        例如: C::C(C &c1): B(c1) {...}
    继承时的析构函数
        1、析构函数也不被继承,派生类自行声明
        2、声明方法与一般(无继承关系时)类的析构函数相同。
        3、不需要显式地调用基类的析构函数,系统会自动隐式调用。
        4、析构函数的调用次序与构造函数相反。
派生类成员的标识与访问
    同名隐藏规则
        当派生类与基类中有相同成员时:*
            1、若未强行指明,则通过派生类对象使用的是派生类中的同名成员。
            2、如要通过派生类对象访问基类中被隐藏的同名成员,应使用基类名限定。
    二义性问题
        1、在多继承时,基类与派生类之间,或基类之间出现同名成员时,将出现访问时的二义性(不确定性)一一采用虚函数(参见第8章)或同名隐藏规则来解决。
        2、当派生类从多个基类派生,而这些基类又从同个基类派生,则在访问此共同基类中的成员时,将产生二义性一一采用虚基类来解决。
        编译器无法确定使用的是哪一类这现象称为二义性
        采用虚基类解决
   二义性问题举例(一)
        class A { public: void f();};
        class B { public: void f();  g()};
        class C:public A, piblic B { public: void g(); void h();};
        //如果定义:C c1;
        //则cl.f()具有二义性
        //而cl.g()无二义性(同名隐藏)
        //这里的系统会不确定是A的还是B的
    解决方法一: 用类名来限定 c1.A::f()或c1.B::f()
    解决方法二: 同名隐藏 在C中声明一个同名成员函数f(),f()再根据需要调用A::f()或B::f()
    
    二义性问题举例(二)
        class B { public int b; }
        class B1: public B {private: int b1;}
        class C: public B1,public B2
        {
            public: int f();
            private: int d;
        }
            有二义性:
            C c 
            c.b 
            c.B::b
            无二义性:
            c.B1::b
            c.B2::b
            //这样又出现一个问题重复性(冗余性)和访问数据不一致
虚基类
    虚基类的引入
        用于有共同基类的场合
    声明
        以virtual修饰说明基类
        例: class Bl:virtual public B
    作用
        1、主要用来解决多继承时可能发生的对同一基类继承多次而产生的二义性问题.
        2、为最远的派生类提供唯一的基类成员,而不重复产生多次拷贝
        称为虚继承在一开始就设置成虚基类虚基类
    举例
        class B { public: int b; };
        class B1: virtual public B { public: int b1;};
        class B2: virtual public B ( public: int b2;};
        class C: public B1, public B2 { public: float d: };
        //下面的访问是正确的:
            C cobj;
            cobi.b;   
虚基类及其派生类构造函数
    1、建立对象时所指定的类称为最(远)派生类。
    2、虚基类的成员是由最派生类的构造函数通过调用虚基类的构造函数进行初始化的。
    3、在整个继承结构中,直接或间接继承虚基类的所有派生类,都必须在构造函数的成员初始化表中给出对虚基类的构造函数的调用。如果未列出,则表示调用该虚基类的默认构造函数。
    4、在建立对象时,只有最派生类的构造函数调用虚基类的构造函数该派生类的其他基类对虚基类构造函数的调用被忽略。   
***********/
#pragma region  示例7-1公有继承(public)
class Point {//基类Point类的定义
    public: //公有通数成员
        void initPoint(float x= 0, float y= 0){
            this->x = x;
            this->y = y;
        }
        void move(float offX, float offY){
            x+= offX;
            y+= offY;
        }
        float getX() const { return x;}
        float getY() const { return y;}
        float x, y;
}; 
class Rectangle: public Point {//派生类定义部分
    public: //新增公有函数成员
        void initRectangle(float x, float y, float w, float h){
            initPoint(x, y); //调用基类公有成员函数
            this->w = w;
            this->h = h;
        }
        float getH() const { return h; }
        float getW() const { return w;}
        private: //新增私有数据成员
            float w, h;
};
#include <iostream>
#include <cmath>
using namespace std;
int main(){
    Rectangle rect; //定义Rectangle类的对象
    //设置矩形的数据
    rect.initRectangle (2, 3, 20, 10);
    rect.move(3,2); //移动矩形位置
    cout << "The data of rect(x,y,w,h): "<< endl;
    //输出矩形的特征参数
    cout << rect.getX() <<"," << rect.getY() << ","<< rect.getW() <<"," << rect.getH() << endl;
    return 0;    
}
#pragma endregion

/*********** 
 基类的public 和protected看起来像是派生类的私有的东西可以调用，private就调用不了 。
要是调用private 必需是他给的接口 通过间接方式调用 
如果是派生类对象的话 对基类的 public  protected  private  这三个是一个都不能直接访问
 
***********/
#pragma region 示例7-2用派生类
class Rectangle: private Point {
    //派生类定义部分
    public: //新增公有函数成员
        void initRectangle(float x, float y, float w, float h) {
            initPoint(x, y); //调用基类公有成员函数
            this->w = w;
            this->h = h;
        }
        void move(float offX, float offY) {
            Point::move(offX, offY); 
        } 
        float getX() const { return Point::getX();}
        float getY() const { return Point::getY(); }
        float getH() const { return h; } 
        float getW() const { return w;}
    private: //新增私有数据成员
        float w, h;
};
// 派生类中调用基类的函数是在派生类在定义   对象：：move (形参)
#include <iostream>
#include <cmath>
using namespace std;
int main(){
    Rectangle rect; //定义Rectangle类的对象
    rect.initRectangle(2, 3, 20, 10); //设置矩形的数据
    rect.move(3,2);//移动矩形位置
    cout << "The data of rect(x,y.w.h): "<< endl;
    cout << rect.getX() <<", "  //输出矩形的特征参数
        << rect.getY() <<", "  
        << rect.getW()<< ", "
        << rect.getH() << endl;
        return 0;
}

#pragma endregion

#pragma region 示例7-3保护继承(protected)
/* class A {
    protected: int x;
};
int main () {
    A a;
    a.x = 5; //错误
}
 */
class A{  // protected 成员的特点与作用
    protected: 
        int x;
};
class B: public A{
    public:
        void function();
};
void B:function() {
     x= 5; //正确
 }
#pragma endregion

#pragma region 示例类型兼容规则
#include <iostream> 
using namespace std;
class Base1 {//基类Base1定义
    public:
        void display() const {
            cout << "Base1::display()"<<endl;
        }
};
class Base2: public Base1 {//公有派生类Base2定义
    public:
        void display() const{
            cout << "Base2::display()" << endl;
        }
};
class Derived: public Base2 {//公有派生类Derived定义
    public:
        void display() const {
            cout << "Derived::display()" << endl;
        }
};
void fun(Base1 *ptr) {//参数为指向基类对象的指针
    ptr->display(); //对象指针->成员名
}
int main() {//主函数
    Base1 base1;//明Base1类对象
    Base2 base2; //明Base2类对象
    Derived derived; //声明Derived类对象
    
    fun(&base1); //用Base1对象的指针调用fun函数
    fun(&base2); //用Base2对象的指针调用fun函数
    fun(&derived); //用Derived对象的指针调用fun函数
    return 0;
} 
#pragma endregion


#pragma region 举例:多继承时派生类的声明
class A {
    public: 
        void setA(int);
        void showA() const;
    private: 
        int a;
};
class B {
    public: 
        void setB(int);
        void showB() const;
    private: 
        int b;
};
class C: public A, private B {
    public: 
        void setC(int, int, int);
        void showC() const;
    private :
        int c;
  };
    void A::setA(int x){
         a=x;
     };
    void B::setB(int x) {
        b=x;
    };
    void C::setC(int x, int y, int z) {
        //派生类成员直接访问基类的
        //公有成员
        setA(x);
        setB(y);
        c = z;
}

//其他函数实现略
int main(){
     C obj;
     obj.setA(5);
     obj.showA();
     obj.setC(6,7,9);
     obj.showC();
     // obj.setB(6);错误
     //obj.showB(); 错误
     return 0;
}
#pragma endregion

#pragma region 举例:单一继承时的构造函数
#include<iostream>
using namespace std;  
class B {
    public: 
    B();
    B(int i);
    ~B();
    void print() const;
    private: 
        int b;
    };
B::B(){
    b=0;
    cout << "B's default constructor called." << endl;
} 
B::B(int i){
   b=i;
   cout << "B's constructor called." << endl; 
} 
B::~B() {
    cout << "B's destructor called." << endl;
}
void B::print() const {
 cout <<b<< endl;
}
class C: public B {
    public:
        C();
        C(int i, int j);
        ~C();
        void print() const;
    private: 
        int c;
    };
C::C(){
    c=0;
    cout << "C's default constructor called." << endl;
}
C::C(int i,int j): B(i) {
    c= j;
    cout<< "C's constructor called." << endl;
}
C::~C(){
    cout << "C's destructor called." << endl;
}
void C::print() const {
    B::print();
    cout <<c << endl;
}
// 创建派生类C
int main(){
    C obj(5, 6);
    obj.print();
     return 0;
}
#pragma endregion

#pragma region 示例7-4 派生类构造函数举例
#include <iostream> 
using namespace std;
class Base1{ //基类Basel,构造通数有参数
    public:
        Base1(int i) {cout << "Constructing Basel " <<i<< endl; }
};
class Base2{ //基类Base2,构造函数有参数
    public:
        Base2(int j) {cout << "Constructing Base2 " <<j<< endl;}
};        
class Base3 { //基类Base3,构造函数无参数
    public:
        Base3() { cout << "Constructing Base3 *" << endl;} //拷贝构造函数}
};
class Derived: public Base2, public Base1, public Base3{//派生新类Derived,注意基类名的顺序
    public: //派生类的公有成员
        Derived(int a, int b, int c, int d): Base1(a), member2(d), member1(c), Base2(b){}
        //注意基类名的个数与顺序,
        //注意成员对象名的个数与顺序
    private: //派生类的私有成员对象
        Base1 member1;
        Base2 member2;
        Base3 member3;
};
int main(){
    Derived obj(1, 2, 3, 4);
    return 0;
}
/* 运行结果: 第一回是按派生类的顺序 第二回按派生类成员对象的顺序
constructing Base2 2
constructing Base1 1
constructing Base3 *
constructing Base1 3 
constructing Base2 4 
constructing Base3 *
 */
#pragma endregion

#pragma region 例7-5 派生类析构函数举例
#include <iostream> 
using namespace std;
class Base1 { //基类Basel.构造通数有参数
    public:
        Base1(int i) {cout << "Constructing Basel "<<i<< endl; } 
        ~Base1() { cout << "Destructing Basel" << endl;}
};     
class Base2 { //基类Base2,构造函数有参数
    public:
        Base2(int j) { cout << "Constructing Base2 "<<j<< endl;} 
        ~Base2() { cout << "Destructing Base2" << endl;} 
};
class Base3 {//基类Base3,构造函数无参数
    public:
        Base3(){ cout << "Constructing Base3"<< endl;} 
        ~Base3() { cout << "Destructing Base3" << endl; }
};
class Derived: public Base2, public Base1, public Base3 { 
    //派生新类Derived,注意基类名的顺序
    public: //派生类的公有成员
        Derived(int a, int b, int c, int d): Base1(a), member2(d), memberl(c), Base2(b){}
        //注意基类名的个数与顺序,注意成员对象名的个数与顺序
    private: //派生类的私有成员对象
        Base1 member1;
        Base2 member2;
        Base3 member3;
};
int main() {
    Derived obj(1, 2, 3, 4);
    return 0;
} 
/* 继承时的析构函数例7-5运行结果   释放时后是反序的先入最后出的思维
 Constructing Base2 2 
 Constructing Base1 1 
 Constructing Base3 * 
 Constructing Base1 3 
 Constructing Base2 4
  Constructing Base3 * 
  Destructing Base3 
  Destructing Base2 
  Destructing Base1
  Destructing Base3 
  Destructing Base1 
  Destructing Base2
 */
#pragma endregion

#pragma region 示例7-6多继承同名隐藏举例1
#include <iostream> 
using namespace std;
class Base1 {//定义基类Base1 
    public:
        int var;
        void fun() {cout << "Member of Basel" << endl;}
};
class Base2 {//定义基类Base2
    public:
        int var;
        void fun () { cout << "Member of Base2" << endl;}
};
class Derived: public Base1, public Base2 {//定义派生类Derived
    public:
        int var; //同名数据成员
        void fun() { cout << "Member of Derived" << endl;}//同名函数成员
};
        //在实际中通为私有的继承Basel Base2
int main() {
    Derived d;
    Derived *p = &d;
    d.var= 1; //对象名.成员名标识
    d.fun(); //访问Derived类成员
    d.Base1::var = 2; //作用域分辨符标识
    d.Base1::fun(); //访问Base1基类成员
    p->Base2::var = 3; //作用域分辨符标识
    p-> Base2::fun(); //访问Base2基类成员
    return 0;
} 
#pragma endregion

#pragma region 示例7-8 虚基类
#include <iostream> 
using namespace std;
class Base0 { //定义基类Base0
    public:
        int var0;
        void fun0() { cout << "Member of Base0" << endl;}
};
class Base1: virtual public Base0 { //定义派生类Basel
    public: //新增外部接口
        int var1;
};
class Base2: virtual public Base0 {//定义派生类Base2
    public: //新增外部接口
        int var2;
};
class Derived: public Base1, public Base2 {//定义派生类Derived
    public: //新增外部接口
        int var;
        void fun () {cout << "Member of Derived" << endl;}
};
int main() {//程序主数
    Derived d; //定义Derived类对象d
    d.var0 = 2; //直接访问虚基类的数据成员
    d.fun0(); //直接访问虚基类的函数成员
    return 0;
}
#pragma endregion

#pragma region 示例7-9 有虚基类时的构造函数举例
// 直接基类的Base1  Base2   间接基类是Base0
#include <iostream> 
using namespace std;
class Base0 { //定义基类Base0
    public:
        Base0(int var):var0(var){}
        int var0;
        void fun0() { cout << "Member of Base0" << endl;}
};
class Base1: virtual public Base0 { //定义派生类Basel
    public: //新增外部接口
        Base1(int var):Base0(var){}
        int var1;
};
class Base2: virtual public Base0 {//定义派生类Base2
    public: //新增外部接口
        Base2(int var):Base0(var){}
        int var2;
};
class Derived: public Base1, public Base2 {//定义派生类Derived
    public: //新增外部接口
        Derived(int var):Base0(var):Base1(var):Base2(var){}
        int var;
        void fun () {cout << "Member of Derived" << endl;}
};
int main() {//程序主数
    Derived d(1); //定义Derived类对象d
    d.var0 = 2; //直接访问虚基类的数据成员
    d.fun0(); //直接访问虚基类的函数成员
    return 0;
}

#pragma endregion
