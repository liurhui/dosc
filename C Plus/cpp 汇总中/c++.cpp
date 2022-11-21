/**
 * @author  liurhui
 * @version 1.0
 * @copyright 版权
 * @remarks  备注
 */

/*********** 字节长度
    

类型    说明符  位数    数值值范围
短整    short   16      -32768 ~ 3276
基本    int     32      -231~ (231-1)
长整    long    32      -231~ (231-1)
无符号 
unsigned short 16       0~655350
usigned [int] 32        0~(232-1)
unsigned long 32        0~(232-1)


sizeof  // 查，运算符的位长，是几个字节。

1、隐含转换 中 在运算当中 参与的操作数类型不一致，则按 低类型转为高类型
    低  char 、 short、 int、 unsigned long、  float、  double、  高

2、单和双引号的区别
    "a"  ==  a \0
    "CHINA"  == C H I N A \0
    'a'  ==  a

3、变量初始化
    int c =5  和  int c(5)  一样 意思是整型变量c初始化为5，类似于 int c =5;

bool  // 布尔1个字节 
1、char  // 默认8位   2、char16_t  //16位   3、char32_t  //32位      /n是char类型
short  // 2字节   
int  // 整型4字节 
long  // 4字节
float // 4字节  3.4*10+-38    7位有效数字
double  // 8个字节   1.7*10+-308  15位有效数字
long double // 8字节 1.7*10+-308  15位有效数字







***********/ 

/*********** 类型转换、头文件
// 在数字后面加f就是转换为浮点型
cout << fixed //强制以小数的方式显示
cout << setprecision(2)    //控制显示的精度2位  同时需要 用到头文件 #include<iomanip>


计算用 #include<cmath>

#include<windows.h>
SetConsoleTitle(“改变控制台输出窗口的名称”);

定义的变量名是什么类型 在cin时候就是被对应的读取到。

设置setw()  用到头文件   #include<iomanip>
在输出时候默认显示是右对齐的  要左对齐加cout << left;
cout << setfill('_');  填充下划线

srand // 随机数 用到库 #include<cstdlib>   = rand()%10
srand（time(NULL)） // 用到库 #inlcude<(ctime)>   时间函数
***********/ 

#pragma region //这里注意,需要判断没钱的情况:强制打工
    srand(time(NULL));
    if(choice == 1){//+体力 +魅力-金钱
    value_array_baseinfo[e] += templ= rand() % 11;
    value_array_baseinfo[2] += temp2 = rand() % 11;
    value_daughter_gold -= temp3 = rand() % 51;
    cout << "学习张无忌好榜样！！！！" << endl;
    cout << "体力+" << temp1 << ",魅力+" << temp2 <<",金钱-" <<temp3<< endl;
#pragma endregion



/*********** 转化进制
正数:  的原码反码补码都是一样的。
负数:才有 原码反码补码   反码除最高位的符号位外 按位取反   补码为反码+1 。
 按位非 ~
 负数二进制转换成10进制， （将二进制取反，然后+1，结果为负） 例： 0000 0010 +1 ---> 11   --->  -3
 例：2 = 0000 0010
    左移  (2 << 3)  2^4  =16    10000
    右移  (2 >> 2)  2^2  =4     100

左移后，低位补0，高位舍弃。
右移后，低位舍弃，高位 无符号补0，有符号补"符号位"
 
 ^   按位异或 不同出1 相同出0  一般用于 翻转。
 |   按位或  相同出1 不同出0  一般用于 字节置1
 &   按位与  全1出1 不同出0  一般用于 取指定位

<   < =   >   > =   优先级相同  高 
  ==   ！= 			优先级相同  低


***********/ 

/*********** 语法
    while  (1成立真执行 在判断在执行  0为假执行退出不循环)

***********/ 

#pragma region //for 语句
int main()
{
    char shap = 'A';
    //外层循环控制行(行数,换行)
    //内层循环控制列(列数,列的图形)
    for(int i= e; i< 4; i++)
    {
        for(int j= 9; j <= 2 - i; j++)
        {
            cout << " ";
        }
        for(int j = 0; j <= 2 * i; j++)
        {
            cout << (char)shap++;  //  char 强制转换为字符
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

int main(){
    //外层循环控制行(行数,换行)
    //内层循环控制列(列数,列的图形)
    for(int i = e; i< 4; i++)
    {
        for(int j = 0; j <= 2 - i; j++)
        {
            cout <<"";
        }
        for(int j = e; j <= 2 * i; j++)
        {
            cout <<(char)('A'+ i); // 强制把*号转换为字符
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











// 已知循环次数用for  实例化就是 有类有对象有访问的数据
#include<iostream>
using namespace std;
int main(void){
    int n,k;
    cout << "Enter a positive integer:";
    cin >> n;
    cout << "Number " << n << " Factors:";
    for(k=1;k<=n;k++)
        if(n%k == 0)
            cout << k <<" ";
    cout << endl;
}


// 要求：读入一系列整数，统计出正整数个i 和负整数个数j,读入0则结束。
#include<iostream>
using namespace std;
int main(void){
    int i=0, j=0, n;
    cout << "请输入若干个整数(输入0则结束): ";
    cin >> n;
    while( n!=0){
        if(n>0) i++;
        if(n<0) j++;
        cin >> n;
    }
    cout << "正整数个数 " << i << " 负整个数:" <<j << endl; 
}


typeof 类型定义（为一个已有的数据类型起个别名）
 基本写法 typedef 已有类型名  自定义类型;
 如： type
 typedef double area,volume;
 typedef int natural;
 natural il,i2;
 area a;
 volume v;

枚举
基本写法 enum wekkdy { sun, mon, tue, wed, thu, fri, sat};  //0,1,2,3,4,5,6
如：
#include  <iostream>
using namespace std;
enum game_result { WIN, LOSE, TIE, CANCEL}; // 胜 负 平局 比赛取消 四种情况
int main(){
    game_result result;
    enum game_result omit = CANCEL;
    int count;
    for(count = WIN; count <= CANCEL; count++){
        result = (game_result)count;
        if(result == omit){
            cout << "The game was played";
            if(result ==WIN) cout <<"and we won!";
            if(result ==LOSE) cout <<"and we lost.";
            cout << "\n";
        }
    }
    return 0;
}


反序重构成新的数获得回文数
// 要求： 寻找并输出11~999之间的数m,它满足m,m2和m3均为回文数。
/*    回文:各位数字左右对称的整数。
    例如:11满足上述条件
        112=121, 113=1331。
    分析：
        10取余的方法,从最低位开始,依次取出该数的各位数字。
        按反序重新构成新的数,比较与原数是否相等,若相等,则原数为回文。 
*/
//解题思路找出规律： 构造新整数的方法:例如: 12345 -> 54321
/* 
12345 -> 5      12345%10=5  0*10+5=5        12345/10=1234
12345 -> 54     1234%10=4   5*10+4=54       1234/10=123
12345 -> 543    123%10=3    54*10+3=543     123/10=12
12345 -> 5432   12%10=2     543*10+2=5432   12/10=1
12345 -> 54321  1%10=1      5432*10+1=54321 1/10=0 
*/

#include <iostream>
using namespace std;
bool symm(long n){
    long i,m;
    i=n;m=0;
    while(i){
        m = m*10+i%10;
        i=i/10;
    }
    return (m==n);
}
int main(){
    bool symm(long n);
    long m;
    for(m=11; m<1000; m++){
        if(symm(m)&&symm(m*m)&&symm(m*m*m))
        {
            cout<<"m="<<m<<"m*m="<<m*m<<"m*m*m="<<m*m*m<<endl;
        }
    }
}


嵌套调用
int fun1(int x,int y){
    int fun2(int m);
    return(fun2(x)+fun2(y));
}
int fun2(int m){
    return (m*m);
}
//结果 3 4平方和 25


递归调用
    函数直接或间接地调用自身，称为递归调用
    先递推: 等于从未知 得到结果
    4!=4*3! -> 3!=3*2! -> 2!=2*1! -> 1!=1*0! -> 0!=1 
    再回归: 等于把结果 依次返回
    4!=4*3!=24 <- 3!=3*2!=6 <- 2=2*1!=2 <- 1!=1*0!=1 <- 0!=1 
实现递归函数
#include<iostream>
using namespace std;
long fac(int n){
    long f;
    if(n<0){
        cout << "n<0,data error!" << endl;
    }else if(n==0){
        f=1;    
    }else{
        f =fac(n-1)*n;
    }
    return(f);
}
int main(){
    long fac(int n);
    int n;
    long y;
    cout<<"Enter a positive integer:";
    cin>>n;
    y=fac(n);
    cout<<n<<"!="<<y<<endl;
}
//要求： 用递归法计算从n个人中选择k个人组成，一个委员会的不同组合数。
#include<iostream>
using namespace std;
int main(){
    int n,k;
    int comm(int n,int k);
    cin>> n>>k;
    cout << comm(n,k)<<endl;
}
int comm(int n,int k){
    if(k>n) return 0;  //不合理情况pass
    else if(n ==k||k==0) // 如5人选5人组成，或没人组成 都只有一种组合数。
    return 1;
    else 
    return comm(n-1,k)+comm(n-1,k-1);  //4，3 + 4，2
}

汉诺塔递归调用问题（猩猩移盘子）

#include<iostream>
using namespace std;
void move(char getone,char putone)
{
    cout<< getone<<"-->"<<putone<<endl;
}
void hanoi(int n,char one, char two, char three){
    void move(char getone, char putone);
    if(n==1){
        move(one,three)
    }else{
        hanoi(n-1,one,three,two);
        move(one,three);
        hano1(n-1,two,one,three);
    }
       
}
int main(){
    void hanoi(int n,char one,char two,char three);
    int m;
    cout<<"Enter the number of diskes:";
    cin>>m;
    cout<<"the steps to moving "<<m<<"diskes:"<<endl;
    hanoi(m,'A','B','C');
}


/***********  函数重载
    1、指可以有多个同名的函数。
    2、函数名相同，形参必须个数不同或类型不同
    重载运算符 operator  将构造函的对象加减乘除
    如果变量是private私有成员函数 则加上朋友关键字 friend

重载操作符 [ ]
    函数类型 operator 运算符（形参）{}
        Element& operator [] (Type index){}

    其中,
        (1)名字: operator [],是固定不变的
        (2)返回值:一般应该返回一个子元素的引用,表示返回值是一个“左值”,可读可写
        (3)参数:类型可以自己选择,用于指定元素的下标。不一定要使用int,使用其他类型也可以。

***********/
#pragma region 示例 类重载运算符
class Fraction{
    public:
        Fraction(): num(1), den (1){}
        Fraction(int n, int d) : num(n), den(d){}
        //重载加号操作符 2/3+ 3
    /*     Fraction operator + (const Fraction& other)
        {
            Fraction result;
            resul t.den = den * other.den; // 分母相乘
            resul t.num= num * other.den + den * other.num; // 分子
            return result;
        }  */
        //重载全局操作符
        Fraction operator + (const Fraction& a, cosnt Fraction& b)
        {
            Fraction result;
            resul t.den = a.den * b.den; // 分母相乘
            resul t.num= a.num * b.den + a.den * b.num; // 分子
            return result;
        } 


    public:
        int num; //分子
        int den; //分母
       
};
int main()
{
    Fraction fa(2, 3);
    Fraction fb(3, 5);
    Fraction fc = fa + fb;
    return 0; 
}   
#pragma endregion

/***********  函数模板 (Function Template)
    1、定义时不指定具体的数据类型(使用虚拟类型代替)
    2、就是泛型参数
    返回值类型  函数名(形参列表){}
        template <typename 类型参数1, typename类型参数2> {}
    如果定义数组
        一个无具体类型的数组，在整个函数体中只要类型一样。

***********/
#pragma region 示例 函数模板
// 函数声明
template<typename T> void Swap(T&, T&);
// 实例化
template<typename T>
void Swap(T &a, T&b)
{
    T temp = a;
    a = b;
    b = temp;
}
#pragma endregion



//tips： 任意一个数字，在除以100之后的余数最大为99（不能除尽的情况下的最大），最小为0（即能够除尽）所以其运算结果的取值范围是0-99

/***********  引用 refrence
 可以认为 类似const指针，就是纯粹关联。
1、引用并非对象，只是为一个已存在的对象起的别名。
  int int_value =1024;
    refValue指向 int_value ，是int_value的另一个名字int& refValue = int_value;
    
2、引用必须被初始化
    例： int&refValue2;  //这样没初始化是错误的。 
3、在 常量的时候必须加 const 意为只读模式。否则会改动常量的原始值、指针地址。
4、引用 比 指针工作效率高，所以占内存的数据都要用引用参数。
5、传递数组只能用指针，配合 const。不要用引用。
函数返回引用
    1、不要返回局部变量的引用


***********/
#pragma region 示例引用经典swap 函数
void swap1 (int, int);
void Swap2 (int*, int*);
void Swap3 (int&, int&);
int main() {
    int num1 = 10, num2 = 5;
    Swap1 (num1, num2);
    cout << "执行Swap1后: "<< num1 << "\t"< num2 << endl;
    swap2 (&num1, &num2);
    cout <<"执行Swap2后: "<<num1 << "\t"<<num2 << endl;
    Swap3 (num1, num2);
    cout <<"执行Swap3后: "<<num1 << "\t"<<num2 << endl;
}
void Swap1 (int num1, int num2)
{
    // 结果 num1=10 num2=5 不变，因为函数没有将值返回，所以只是改变，但是值不变。
    int temp;
    temp = num1;
    num1 = num2;
    num2 = temp;
}
void Swap2 (int* p1, int* p2)
{
    // 结果 num1=5 num2=10 变化了，因为函数传递的是地址，通过直接修改地址存储的值。
    int temp;
    temp = *p1;
    *p1 =*p2;
    *p2 = temp;
}
void Swap3 (int& ref1, int& ref2)
{
    // 结果 num1=10 num2=5 变化了，因为这个是引用  效果与指针一样。  
    int temp;
    temp = ref1;
    ref1 = ref2;
    ref2 = temp;
}
#pragma endregion

#pragma region 示例1函数返回引用,以下代码的输出结果是?
// 生命周期结束后就会被其他函数的给替换  要注意不要返回局部变量的引用 return 只能返回值不能做运算
int & sum()
{
    int num = 10;
    int& rNum = num;
    return rNum;
};
void test(){
    int x = 1, y = 2,z = 3;
};
int main(){
    //result是局部变量的引用
    int& result = sum();
    test();//另一个函数将覆盖先前函数栈上的教据
    cout << "result = " << result << endl;
}


#pragma endregion

/**
 * 跟某人聊天-负责字符串的拼接(聊天格式)
 * @param toName 聊天对象的名称
 * @param content 聊天的内容
 * @return按某规定的格式拼接聊天信息后的字符串
 */
#pragma region 示例2函数返回引用
string chatTo (const strings toName, const string& content);
//string chat Fromconst strings fromName, const strings contont);
int main(){
    string toName, content, chatMsg;
    cout << "请输入对方的名称: ";
    getline (cin, toName);
    cout <<"请输入发送给对方的聊天信息: ";
    getline (cin, content);
    chatMsg chatTo (toName, content);
    cout << endl << chatMsg << endl;
}
// 这里用const 目的:在函数内部不能随意更改赋值。
string chatto (const string& toName, const string& content)
{
    string msg= "x 你悄对[" + toName + "]: "+ content;
    return msg;
}
#pragma endregion



/*********** 对象
 public   修饰的成员在任何地方都可以访问
 private  修饰的成员只能够在类中或者有元函数中可以访问
 protected 修饰的成员可以在类中函数、子类函数及友元函数中访问
 

 类的声明使用
    class/struct关键字声明类型
        class 类名();
            class LandOwner();
        struct 类名0;
            struct Hero();
    注意:
        1、class方式声明的类型与struct声明的美型仅仅是形式上不同
        2、其唯一的区别在干使用class声明的类型默认成员是私有的)，
        而struct声明的类型默认成员是公有的(public);
 :: 是类作用符
     返回类型类名::类名(对象成员所需的形参，本类成员形参):对象1(参数),对象2(参数), ...{ 本类初始化 }

 函数定义
   返回类型类名::函数名(){  //函数操作   }
   void LandOwner::ShowScore(){   cout << score <<endl;  } 
***********/
#pragma region  示例 类定义
using namespace std;
class Landowner
{
    public:  // 公有成员（外部接口）
        Landowner ();
        LandOwner (string);
        Landowner (string, string, int, long);
        ~Landowner ();
        string GetNickName () { return m_NickName;  }
        void SetNickName (string val) { mNickName = val; }
        string GetSex () { return m_Sex;}
        void SetSex (string val) { m_Sex= val; }
        int GetGold() { return m Gold; }
        void SetGold (int val) { m_Gold = val; }
        long GetExp () { return m_Exp; }
        void SetExp (long val) { m_Exp = val; }
        void ShowInfo ();
    protected: // 保护型成员
    private:  // 私有成员
        string m_NickName;
        string m_Sex;
        int Gold;
        long m_Exp;
};
#pragma endregion

#pragma region  示例 类作用符
    void Clock::SetTime(int NewH, int NewM,int NewS)
    {
        Hour = NewH;
        Minute =NewM;
        Second =NewS;
    }
    void Clock::ShowTime()
    {
        cout<<Hour<<":"<<Minute<<":"<<Second;
    }
#pragma endregion


/*********** 构造函数  
    1、可以不加括号  
    2、定义构造函数为default  
        xxx() =default; //本质跟让系统默认调用是一个意思。
带参构造
    类名::构造(类型1 参数1, 类型2 参数2, ...) {
        // 相关初始化代码
    }
执行顺序
    1、默认构造  无参数即默认
    2、有参数 按调用顺序执行


***********/
#pragma region  库函数meset
//函数  memset(数组名,数组个数, 数组大小) 必需加个头文件memory.h
 memset(cards, 0, sizeof(cards));
#pragma endregion
#pragma region  带参构造
    // 声明
    Student::Student(string name, string desc)
    {
        name = name;
        desc = desc;
    }
    // 调用
    Student* stu = new Student("撒贝宁". "北大还行");
    stu->ShowInfo();

  Student::Student(string name, string desc) :m_Name(name), m_desc(desc)
  {
    // 这种叫赋值写法也叫参数列表。  等于  SetName(name);   n_Name = name;
  }
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
#pragma region 注意  访问符. 和 指针 ->的使用场景
class Student
{
    public:
        Student();
        Student(string,string);
        ~Student();
        
        void ShowInfo();
}

Student stu1("马化腾","普通家庭");
stu1.ShowInfo();

Student* stu2 = new Student("马云","悔创阿里");
stu2->ShowInfo();
delete stu2; // 堆内存需要手动去释放

#pragma endregion


/*  
  要求：一圆型游泳池如图所示,现在需在其周围建一圆型过道,并在其四周围上栅栏。
  栅栏价格为35元/米,过道造价为20元/平方米。
  过道宽度为3米,游泳池半径由键盘输入。
  要求编程计算并输出过道和栅栏的造价。
*/
#pragma region 类例子
#include <iostream> 
using namespace std;
const float PI = 3.14159;
const float FencePrice =35;
const float ConcretePrice =20;
//声明类Circle及其数据和方法
class Circle {
    private: 
        float radius;
    public:
        Circle(float r);//构造数
        float Circumference() const: //圆周长
        float Area() const; //圆面积
}
// 类的实现
// 构造函数初始化数据成员radius
Circle::Circle(float r){
    radius=r
}
// 计算圆的周长
float Circle::Circumference() const {
    return 2 * PI* radius;
}
// 计算圆的面积
float Circle::Area() const {
    return PI* radius * radius;
}
void main (){
    float radius;
    float FenceCost, ConcreteCost;
    //提示用户输入半径c
    out<<"Enter the radius of the pool: ";
    cin>>radius;
    
    //声明Circle 对象
    Circle Pool(radius);
    Circle PoolRim(radius + 3);
    // 计算栅栏造价并输出
    FeceCost =PoolRim.Circumference()* FencePrice;
    cout << "Fencing Cost is ¥" << FenceCost << endl;
    //计算过道造价并输出
    ConcreteCost = (PoolRim.Area()Pool.Area())*ConcretePrice;
    cout << "Concrete Cost is ¥" << ConcreteCost << endl;
}

#pragma endregion



/***********  前向引用声明
 class B;//前向引用声明
 class A{
    public:
        void f(B b);
 };
 class B{
    public:
        void g(A a);
 };
向前引用声明注意事项
    使用前向引用声明虽然可以解决一些问题,但它并不是万能的。
    需要注意的是,尽管使用了前向引用声明,
    但是在提供一个完整的类声明之前,不能声明该类的对象,也不能在内联成员函数中使用该类的对象。
***********/
#pragma region  前向引用声明 错误示例    
    class Fred; // 前向引用声明
    class Barney{
        Fred x; // 错误： 类Fred的声明尚不完善
    };
    class Fred{
        Barney y;
    };
#pragma endregion

#pragma region  前向引用声明 正确示例 
    class Fred; //前向引用声明
    class Barney {
        public:
            void method(){
                x->yabbaDabbaDo();//错误: Fred类的对象在定义之前被使用
            }
        private:
            Fred* x; //正确,经过前向引用声明,可以声明Fred类的对象指针
    }       
    class Fred {
        public:
            void yabbaDabbaDo();
        private:
        Barney* y;
    }
#pragma endregion




/*********** 结构体
struct{
    // 公有成员
    protected:
    // 保护成员
    private:
    // 私有成员
};
***********/
#pragma region 示例结构体
// 结构体变量的初始化和使用
#include <iostream>
#include <iomanip>
using namespace std;
struct student //学生信息结构体
{
    int num; //学号
    char name[20]; //姓名
    char gender; //性别
    int age; //年龄
}
stu={ 97001, "Lin Lin", 'F', 19 };
int main()
{
    cout<<setw(7)<<stu.num<<setw(20)<<stu.name<<setw(3)<<stu.gender<<setw(3)<<stu.age;
} 
#pragma endregion


/*********** 联合体(共享同一组内存单元)
    是一种特殊形态的类，默认访问属性是public，全部数据成员共享同一组内存单元。
语法： 联合名 联合变量名;
引用写法： 联合名.成员名
  union Mark {
    char grade;
    bool pass;
    int percent;
  } 

无名联合
    union {
        int i;
        float f;
    }
// 在程序中可以这样使用:
    i=10;
    f=2.2;
***********/
#pragma region  示例联合体
#include <string> 
#include <iostream> 
using namespace std;
class ExamInfo{
    public:
        ExamInfo(string name, char grade): name(name),mode(GRADE), grade(grade){}
        ExamInfo(string name, bool pass): name(name),mode(PASS), pass(pass){}
        ExamInfo(string name, int percent): name(name).mode(PERĞENTAGE), percent(percent){}
    void show():
    private: 
        string name;
        enum {
            GRADE,
            PASS, 
            PERCENTAGE
        } mode;
        union{
             char grade;
             bool pass;
             int percent;
        };
};
void Examlnfo::show(){
    cout<<name<<": ";
    switch (mode){
        case GRADE: cout<<grade;
            break;
        case PASS: cout<<(pass?"PASS":"FAIL");
            break;
        case PERCENTAGE: cout<<percent;
            break;
    }
    cout<<endl;
}
int main() {
    ExamInfo coursel("English", 'B');
    ExamInfo course2("Calculus", true);
    ExamInfo course3("C++ Programming", 85);
    coursel.show();
    course2.show();
    course3.show();
    return 0;
}
#pragma endregion


/*********** 函数原型的作用域    与可见性
    局部作用域
        函数形参列表中形参的作用域,从形参列表中的声明处开始,到整个函数体结束之处为止
    函数体内声明的变量,其作用域从声明处开始,一直到声明所在的块结束的大括号为止
    在块中声明的标识符,其作用域自声明处起,限于块中。
***********/
void fun(int a){
    int b(a);
    cin>>b;
    if(b>0){
        int c;
        ...
    }
}
/*********** 类作用域
    类作用于特定的成员名。
    类X的m成员具有类作用域,对m的访问方式如下:
        如果在X的成员函数中没有声明同名的局部作用域标识符,那么在该函数内可以访问成员m。
        通过表达式x.m或者X::m访问。
        通过表达式ptr->m

    类作用域 三种写法
        X.m X::m ptr ->m
***********/

/*********** 命名空间作用域
namespace 命名空间名{
        命名空间内的各种声明(函数声明、类声明、....)
}
引用其他命名空间的标识符：
    命名空间名::表示符号
直接引用其他命名空间的标识符
    using 命名空间名::标识符名;
    using namespace 命名空间名;
std命名空间:包含了C++标准程序库的所有标识符
命名空间允许嵌套
    namespace OuterNs{
        namespace InnerNs{
            class SomeClass(...);
        }
    }
引用SomeClass类:
    OuterNs::InnerNs::SomeClass
全局命名空间:
    默认的命名空间,显式声明的命名空间之外声明的标识符都在一个全局命名空间中
匿名命名空间:
    需要显式声明的没有名字的命名空间
    具有命名空间作用域的变量也称为全局变量
***********/
#pragma region  作用域示例
#include <iostream>
using namespace std;
int i; //全局命名空间中的全局变量
namespace Ns{
    int j; //Ns命名空间中的全局变
}
int main{
    i=5: //为全局变量赋值
    Ns::j=6; //为全局变量j赋值
    {
        using namespace Ns: //可以直接引用Ns命名空间的标识符
        int i; //局部变量
        i=7;
        cout<< "i= "<<i<<endl;//输出7
        cout<< "j= "<<j<<endl;
    }
}
#pragma endregion

可见性
    可见性是从对标识符的引用的角度来看标识 符的有效范围
    程序运行到某一点,能够引用到的标识符,就是该处可见的标识符。
    可见性表示从内层作用域向外层作用域“看”能看见什么。

可引用为可见不可引用为不可见

1、标识符应声明在先,引用在后。
2、在同一作用域中,不能声明同名的标识符。
3、在没有互相包含关系的不同作用域中声明的同名标识符,互不影响。
4、如果在两个或多个具有包含关系的作用域中声明了同名标识符,则外层标识符在内层不可见。
    如果某个标识符在外层中声明,且在内层中没有同一
    标识符的声明,则该标识符在内层可见。


对象生存期分为静态和动态

静态
/* 
    这种生存期与程序的运行期相同。
    在命名空间作用域中声明的对象具有静态生存期。
    在函数内部声明静态生存期对象要冠以关键字static。
    -不会随着每次函数的调用而产生一个副本
    -不会随着函数返回而失效(下一次调用时还保持上一回的值)
    -如: static int i=5;
    -未指定初值的基本类型静态变量,初值为0 
*/

// 示例
#include<iostream>
using namespace std;
int i=5; //命名空间作用域  //i具有静态生存期，生存周期为整个周期
int main (){
    cout<<"i="<<i<<endl;
    return 0; 
}

动态
/* 
    局部作用域中声明的,没有用static修饰的对象是动态生存期的对象(习惯称局部生存期对象)。
    诞生于声明点,结束于声明所在的块执行完毕之时。
 */
#include<iostream>
using namespace std;
void fun();
int main (){
    fun();  // i=6; a=2
    fun();  // i=6; a=3
};
void fun() {
    static int a=1; 
    int i=5;
    a++;
    i++;  // i是动态生存期， a是静态生存期 区别：a第二次调用不初始化 ， i动态会被初始化。
    cout<<"i="<<i<<",a= "<<a<<endl;
}

变量的生存期与可见性
#include <iostream> 
using namespace std;
int i=1: //i为全局变量,具有静态生存期。
int main(){
    static int a; //静态局部变量,有全局寿命,局部可见。
    int b=-10; // b, c为局部变量,具有动态生存期。
    int c=0;
    void other(void);
    cout<<"---MAIN---\n"; 
    cout<<" i: "<<i<<" a: "<<a<<"b: "<<b<<" c: "<<c<<endl;  // i:1 ,a:0, b:-10, c:0
    c=c+8;
    other(); // i:33 ,a:4, b:0, c:15
    cout<<"---MAIN---\n";
    cout<<" i: "<<i<<" a: "<<a<<"b: "<<b<<" c: "<<c<<endl; // i:33 ,a:0, b:-10, c:8
    i=i+10;
    other(); // i:75 ,a:6, b:4, c:15
}
void other(void) {
    static int a=2;
    static int b;
        // a,b为静态局部变量,具有全局寿命,局部可见。
        //只第一次进入函数时被初始化。
    int c=10; 
        // C为局部变量,具有动态生存期
        //每次进入函数时都初始化。
    a=a+2; 
    i=i+32; 
    c=c+5;
    cout<<"---OTHER---\n";
    cout<<" i: "<<i<<" a: "<<a<<" b: "<<b<<" c: "<<c<<endl;
    b=a;
}

// 示例 具有静、动态生存期对象的时钟程序
#include<iostream>
using namespace std;
class Clock //时钟类声明
{
    public: //外部接口
    Clock();
    void SetTime(int NewH, int NewM, int NewS): //三个形参均具有函数原型作用域
    void ShowTime ();
    ~Clock(){}
    private: //私有数据成员
    int Hour, Minute, Second;
};
//时钟类成员函数实现
Clock::Clock() //构造数
{
    Hour=0;
    Minute=0;
    Second=0;
} 
void Clock::SetTime(int NewH, int NewM, int NewS)
//三个形参均具有局部作用域
{
    Hour=NewH;
    Minute=NewM;
    Second=NewS;
}
void Clock::ShowTime(){
    cout<<Hour<<":"<<Minute<<":"<<Second<<endl;
}
Clock globClock; 
//声明对象globClock
//具有静态生存期,命名空间作用域
// 由默认构造函数初始化为0:0:0
int main() //主函数
{
    cout<<"First time output:"<<endl;
    //引用具有文件作用域的对象:
    globClock.ShowTime(): //对象的成员函数具有类作用域
    globClock.SetTime(8,30,30);
    Clock myClock(globClock)://声明具有局部作用域的对象myClock
    cout<<"Second time output:"<<endl;
    myClock.ShowTime(): //引用具有局部作用域的对象
}


类的静态成员
/* 
    用关键字static声明
    在每个类只有一个副本,由该类的所有对象共同维护和使用
    具有静态生存期,可以通过类名来访问:类名::标识符
    必须在类外定义和初始化,用(::)来指明所属的类。
    在UML中,静态数据成员加下划线 
*/
// 示例 具有静态数据成员的POINT类
#include <iostream> 
using namespace std;
class Point//引入静态数据成员count来统计Point类对象个数
{
    public:
        Point(int xx=0, int yy=0):X(xx), Y(yy) {count++; }
        Point(Point &p);//复制构造函数
        ~Point(){icount--} // 析构函数
        int GetX() {return X;}
        int GetY() {return Y;}
        void showCount() { cout<<" Objectcount="<<count<<endl;} 
        private:
            int X,Y;
            static int count;
};
Point::Point(Point &p) 
{
    X=p.X;
    Y=p.Y;
    count++;
} 
int Point::count=0;
int main(){
    Point a(4,5);
    cout<<" Point A: "<<a.GetX()<<","<<a.GetY(); //Point A: 4, 5 Object count=1 
    a.showCount();
    Point b(a);
    cout<<"Point B: "<<b.GetX()<<", "<<b.GetY(); //Point B: 4, 5 Object count=2
    b.showCount();
    return 0;
}

类的静态函数成员
/* 
    使用static关键字声明的函数成员
    属于整个类,由该类的所有对象共享
    类外代码可以使用类名和作用域操作符来调用静态成员函数。
    静态成员函数只能引用属于该类的静态数据成员或静态成员函数。
    必须通过对象名才能访问非静态成员
    在UML中,在静态函数成员前添加<<static>>构造型
 */

class A
{
    public:
        static void f(A a);
    private: 
        int x;
}
void A::f(A a){
    cout<<x; //对x的引用是错误的
    cout<<a.x; //正确  静态不允许使用非静态成员 a是形参 以对象形式调用
}

// 示例 具有静态数据、函数成员的Point类
#include <iostream> 
using namespace std;
class Point //Point类声明
{
    public: //外部接口
    Point(int xx=0, int yy=0 ):X(xx), Y(yy) {count++;}
    Point(Point &p): //复制构造函数
    ~Point(){count--;} //析构函数
    int GetX() {return X;} 
    int GetY() {return Y;}
    static void showCount(){
        cout<<" Object count="<<count<<endl;
    }
    private: //私有数据成员
        int X,Y;
        static int count;  //静态的static  
}

Point::Point(Point &p) {
    X=p.X;
    Y=p.Y;
    count++;
}
int Point::count=0;
int main() //主函数实现 
{
    Point a(4,5);//声明对象A
    cout<<"Point A,"<<a.GetX()<<", "<<a.GetY();
    Point::showCount(); //输出对象个数
    Point b(a); //声明对象B
    cout<<"Point B,"<<b.GetX()<<", "<<b.GetY();
    Point:: showCount(); //输出对象个数
    return 0;
    // Point是类名字
}


友元
/* 
    友元是C++提供的一种数据共享机制,可以提高程序的效率和可读性
    友元破坏了数据封装和数据隐藏
    使用关键字friend将其他函数或者类声明为友元
        -友元函数
        -友元类
    通过将一个模块声明为另一个模块的友元,一个模块能够引用到另一个模块中本是被隐藏的信息。
    可以使用友元函数和友元类。
    为了确保数据的完整性,及数据封装与隐藏的原则,需要在共享和封装之间找到一个平衡。
 */
友元函数   
/* 
    友元函数是在类声明中由关键字friend修饰说明的非成员函数,
    在它的函数体中能够通过对象名访问private 和 protected成员。
    作用:增加灵活性,使程序员可以在封装和快速性方面做合理选择。
    访问对象中的成员必须通过对象名。

 */

// 示例：友元函数计算两点距离
#include <iostream>
#include <cmath>
using namespace std;
class Point //Point类声明
{
    public: //外部接口
    Point(int xx=0, int yy=0) {X=xx;Y=yy;} 
    int GetX() {return X;}
    int GetY() {return Y;}
    friend float Distance(Point &a, Point &b);
    private: //私有数据成员
    int X,Y;
};
double Distance( Point& a, Point& b)
{
    double dx=a.X - b.X;
    double dy=a.Y - b.Y;
    return sqrt(dx*dx+dy*dy);
}
int main(){
    Point pl(3.0, 5.0), p2(4.0, 6.0);
    double d=Distance(pl, p2);
    cout<<"The distance is "<<d<<endl;
    return 0;
}

友元类
/* 
    若一个类A为另一个类B的友元类,则A类的所有成员函数都是B类的友元函数,都能访问B类的私有和保护成员。
    友元关系不能传递，只是单向的。且不被继承。
    如B被A 声明为友元，则B可以访问A的私有和保护数据，而A是不能访问B的。 

 */
class A
{
    friend class B; // B可以访问所有A ，目的 共享数据保护
    publiç:
        void Display()
            {cout<<x<<endl;} 
    private:
            int x;
}            
class B
{
    public:
        void Set(int i);
        void Display();
    private:
        A a;
};

void B::Set(int i)
{
    a.x =i;
}
void B::Display()
{
    a.Display();
}



常对象(cosnt)
    必须进行初始化,不能被更新。
    cosnt int n =10;  // cosnt  类型说明符 对象名;
class A{
    public:
        A(int i, int j): x(i), y(j){}
    private: 
        int x, y;
    };
const A a(3,4); //a是常对象,不能被更新
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
#include<iostream>
using namespace std;
class R
{
    public:
        R(int rl, int r2){ R1=rl;R2=r2;}
        void print();
        void print() const;
    private: 
        int R1,R2;
};
void R::print(){
    cout<<R1<<":"<<R2<<endl;
}
void R::print() const
{
    cout<<R1<<";"<<R2<<endl;
}
int main(){
    R a(5,4);
    a.print(); //调用void print()
    const R b(20,52);
    b.print(); //调用void print() const  常对象才能调用常成员函数
} 

// 常成员函数示例2
const int A::b=10;
A::A(int i):a(i),r(a){}
void A::print()
{ cout<<a<<":"<<b<<":"<<r<<endl; }
int main(){
    /*
        建立对象a和b,并以100和0作为初值,
        分别调用构造函数过构造函数的初始化列表给对象的常数据成员赋初值
    */
    A al(100),a2(0);
    a1.print();
    a2.print();
}

// 比如参数类型很复杂是个类对象，要调用构造函数用实参初始化形参 时间比较久，避免形参修改实参值。
// 被引用的对象不能被更新
const 类型说明符 &引用名
// 常引用做形参，不会更改实参。
#include <iostream>
using namespace std;
void display(const double& r);
int main(){
    double d(9.5);
    display(d);
    return 0;
}
void display(const double& r)
//常引用做形参,在函数中不能更新r所引用的对象。
{cout<<r<<endl;}



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
标准C++类与组件分为6类
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
#if  常量表达式
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

#pragma region  define跟 inline的微妙
    #define S(num)   num * num   // 当使用S(num)的地方，就自动被替换成 num * num
    int result1 = S(5 + 10);  // 特殊之处实际上是求平方， 5 + 10 * 5 + 10  但是*号优先级高就变成了 5+50+10 =65;
    inline int A(int);
    int A(int num)
    {
        return num *num;  //  inline 就是比 define解决了 优先级的问题， 
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
    采用& 通过变量名、地址访问。 
指针变量概念
    指针：内存地址，用于间接访问内存单元。
    指针变量：用于存放地址的变量
// 例如： 
static int i;
static int *i_pointer =&i; //i_pointer 指向整型变量的指针
// 指针变量 例：
//举例 i 存放在地址2000里 其值是3，  *i_pointer  其i_pointer 指向了值为3的地址2000， *
i = 3;  *i_pointer =3;   // 即i_pointer == 地址2000  因为 *i_pointer 是等于3。


指针变量的初始化
    存储类型  数据类型 *指针名 = 初始值;
    按存储类型分为4种: 自动变量auto  静态变量static    寄存器变量 register  外部变量 extern

注意事项:
    -用变量地址作为初值时,该变量必须在指针初始化之前已说明过,且变量类型应与指针类型一致。
    -可以用一个已赋初值的指针去初始化另一个指针变量。
    -不要用一个内部 auto变量去初始化static指针。
指针名=地址
    -“地址”中存放的数据类型与指针类型必须相符。
    -向指针变量赋的值必须是地址常量或变量,不能是普通整数。但可以赋值为整数0,表示空指针。
    -指针的类型是它所指向变量的类型,而不是指针本身数据值的类型,任何一个指针本身的数据值都是unsigned long int型。
    -允许声明指向void类型的指针。该指针可以被赋予任何类型对象的地址。
普通整数就是没有类型的常量

//示例 1 指针变量的赋值运算  
#include <iostream>
using namespace std;
int main(){
    int i;//定义int型数i
    int *ptr =&i;//取i的地址给ptr
    i= 10;//int型数赋初值
    cout << "i= "<<i<< endl;//输出int型数的值
    cout <<."*ptr= "<< *ptr << endl;//输出int型指针所指地址的内容
    return 0;
}
/*结果
    i=10; *ptr=10
*/

// 示例2 void类型指针的使用
#include <iostream> 
using namespace std;
int main(){
    //void voidObject;错,不能声明void类型的变量
    void *pv://对,可以声明void类型的指针
    int i=5;
    pv = &i; //void类型指针指向整型变量
    int *pint = static cast<int *>(pv);  // pv加强制类型转换
    //void类型指针赋值给int类型指针
    cout <<"*pint = " << *pint << endl;
    return 0;
}


指向常量的指针 （只能当指针但可以修改为别的地址）
    //不能通过指针来改变所指对象的值，但指针本身可以改变，可以指向另外的对象。
int a;
const int *pl = &a;//pl是指向常量的指针
int b;pl= &b; //正确,p1本身的值可以改变
*pl= 1; //编译时出错,不能通过pl改变所指的对象

指针类型的常量（不但是指针且只读不可修改）
int a;
int* const p2 =&a;
p2 = &b;//错误，p2是指针常量，值不能改变

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
    pa = &a[0]; 或 pa=a; // 取第0个数组的地址 就是整个数组的地址

    通过指针引用数组元素
        *pa就是a[0]. *(pa+1)就是a[1], ... ,
        *(pa+i)就是a[i].
        a[i], *(pa+i), *(a+i), pa[i]都是等效的。
        不能写a++,因为a是数组首地址是常量。 

    申请的一段内存空间没有名字 把这段地址起始地址赋给指针变量  这样更快捷
    Point *pa[2];  // 由pa[0],pa[1]两个指针组成

// 示例1 利用指针数组存放单位矩阵
#include <iostream> 
using namespace std;
int main(){
    int line1[] = {1,0,0}; //矩阵的第一行
    int line2[]=  {0,1,0}; //矩阵的第二行
    int line3[] = {0,0,1}; //矩阵的第三行
    //定义整型指针数组并初始化
    int *pLine[3] = { line1, line2, line3};
    cout <<"Matrix test:" << endl;
    //输出单位矩阵
    for (int i = 0; i < 3; i++) {
        for (int j = 0:j < 3;j++){
            cout << pLine[i][j]<<"";<<cout << endl;
        }
    }
    return 0;  //pLine的I 是哪一个数组的意思 ,起始地址 j是这个数组里第几个元素  看起来像一个二维数组
} 

// 示例2 二维数组
#include <iostream> 
using namespace std;
int main() {
    int array2[3][3]= {{11, 12, 13},{21, 22, 23}, {31, 32, 33} };
    for(int i = 0;i< 3; i++) {
        for(int j = 0:j < 3; j++){
            cout <<*(*(array2 + i) +j) <<""; //逐个输出二维数组第i行元素值
            }
      cout << endl;
    }
    return 0;// （array2）是二维数组的起始地址 加i就是哪一行的元素 加j是哪一列的元素
}


指针与函数关系
    以指针作为函数参数
        以地址方式传递数据,可以用来返回函数处理结果。
    实参是数组名时形参可以是指针。
        //形参接受实参传递过来的数组的起始地址
    
// 要求:读入三个浮点数,将整数部分和小数部分分别输出
#include <iostream> 
using namespace std;
void splitFloat(float x, int *intPart, float *fracPart)
{
    //取x的整数部分
    *ntPart = static_cast<int>(x);
    //取x的小数部分
    *fracPart = x- *intPart;
}
int main(){
    cout << "Enter 3 float point numbers:" << endl;
    for(int i = 0;i< 3; i++) {
        float x, f;
        int n;
        cin >> x;
        splitFloat(x, &n, &f); //变量地址作为实参
        cout << "Integer Part ="<<n
            <<" Fraction Part = " << f << endl;
    }        
    return 0;
}
// 示例 输出数组元素的内容和地址
#include <iostream>
#include <iomanip>
using namespace std;
void arrayPtr(long *p, int n){
    cout << "In func, address of array is" << p << endl;
    cout << "Accessing array using pointers" << endl;
    for (int i = 0; i < n; i++){
        cout <<" Address for index "<<i<< "is" << p + i;
        cout << " Value is " <<*(p +i) << endl;
    }
}
int main() {
    long list[5] ={50, 60, 70, 80, 90};
    cout << "In main, address of array is" << list << endl;
    cout << endl;
    arrayPtr(list,5);
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
#include<iostream>
using namespace std;
const int N = 6;
void print(const int *p, int n);
int main(){
    int array[N];
    for (int i = ;i < N; i++){
        cin>>array[i];
        print(array, N);
    }
    return 0;
}
void print(const int *p, int n) {
    cout <<"["<< *p;
    for (int i = 1; i < n; i++) 
        cout <<<<*(p+i);
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
        当函数的返回值是地址时,该函数就是指针型函数。
    声明形式
        存储类型 数据类型*函数名()
指向函数的指针
    含义:
        数据指针指向数据存储区,而函数指针指向的是程序代码存储区。
    声明形式
        存储类型 数据类型(*函数指针名)();
// 示例 函数指针
#include <iostream> 
using namespace std;
void printStuff(float){
    cout << "This is the print stuff function."<< endl;
}    
void printMessage(float data){
    cout << "The data to be listed is "<< data << endl;
}
void printFloat(float data){
    cout << "The data to be printed is " << data << endl;
}
const float PI=3.14159f;
const float TWO_PI =PI *2.0f;
int mian(){ //主函数
    void (*functionPointer)(float); //a数指针
    printStuff(PI);
    functionPointer = printStuff;
    functionPointer(PI); //函数指针调用
    functionPointer = printMessage;
    functionPointer(TWO_PI); //函数指针调用
    functionPointer(13.0);
    functionPointer = printFloat;//函数指针调用
    functionPointer(PI);//函数指针调用
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
        例如:
            Point a(5,10); Piont *ptr;  ptr=&a;
int main() {
    Point a(5, 10);
    Point *ptr;
    ptr= &a;
    int x;
    x = ptr->getX();
    cout <<x << endl;
    return 0:
}
class Fred; //前向引用声明
class Barney{
  Fred *x; // Fred x;错误:类Fred的声明尚不完善
};
class Fred {
    Barney y;
};

this指针
    隐含于每一个类的成员函数中的特殊指针。
    明确地指出了成员函数当前所操作的数据所属的对象。
    当通过一个对象调用成员函数时,系统先将该对象的地址赋给this指针,
    然后调用成员函数,成员函数对对象的数据成员进行操作时,就隐含使用了this指针。 

// 示例 POINT类的GETX函数种的语句
    return x;  相当于: return this->x;
指向类的非静态成员的指针
    通过指向成员的指针只能访问公有成员
    声明指向成员的指针
        -声明指向公有数据成员的指针
            类型说明符 类名::指针名;
        -声明指向公有函数成员的指针
            类型说明符 (类名::*指针名)(参数表)
非静态成员
    指向类的非静态成员的指针
        指向数据成员的指针
            -说明指针应该指向哪个成员
                指针名= &类名::数据成员名:
            -通过对象名(或对象指针)与成员指针结合来访问数据成员
                对象名.*类成员指针名
                或:
                对象指针名->*类成员指针名
        指向函数成员的指针
            -初始化
                指针名=&类名::函数成员名;
            -通过对象名(或对象指针)与成员指针结合来访问函数成员
                (对象名.*类成员指针名)(参数表)
                或:
                (对象指针名->*类成员指针名)(参数表)
// 示例 访问对象的公有成员函数的不同方式
int main() {
     //主a数
     Point a(4,5); //声明对象A
     Point *pl= &a; //声明对象指针并初始化
     //声明成员函数指针并初始化
     int (Point::*funcPtr)()= Point::getX;
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
class Point {
    //Point类定义
public: //外部接日
    Point(int x = 0, int y = 0) : x(x). y(y) {
        count++;
    }
    Point(const Point &p) : x(p.x), y(p.y) {
        count++;}
    ~Point(){ count--;}
    int getX() const { return x;}
    int getv() const { return y;}
    static int count;
private: //私有数据成员
    int x, y;
}
int Point::count = 0;
int main() {//主函数实现
    //定义一个int型指针,指向类的静态成员
    int *ptr = &Point::count;
    Point a(4, 5); //定义对象a
    cout << "Point A: " << a.getX() <<","<< a.getY();
    cout <<" Object count ="<<*ptr << endl;
    Point b(a): //定义对象b
    cout << "Point B: " << b.getX() <<","<< b.getY();
    cout <<" Object count ="*ptr << endl;
    return 0;
}
// 例6-15通过指针访问类的静态函数成员
#include <iostream> 
using namespace std;
class Point {//Point类定义
    public://外部接口
        Point(int x=0, int y= 0): x(x), y(y) { count++;}
        Point(const Point &p) : x(p.x). y(p.y) {count++;}
        ~Point() {count--;}
        int getX() const { return x;}
        int getY() const { return y;}
        static void showCount(){
            cout <<" Object count = "<< count << endl;
        }
    private: //私有数据成员
        int x, y;
        static int count;
}
int Point::count = 0;
int main() {  //主函数实现
    //定义一个指向函数的指针,指向类的静态成员函数
    void (*funcPtr) () = Point::showCount;
    Point a(4, 5); //定义对象A
    cout << "Point A: " << a.getX() << "."<< a.getY();
    funcPtr(); //输出对象个数,直接通过指针访问静态函数成员
    Point b(a); //定义对象B
    cout << "Point B: " << b.getX() <<". "<< b.getY();
    funcPtr(); //输出对象个数,直接通过指针访问静态函数成员
    return 0;
}


