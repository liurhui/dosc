#### namespace 名字

分配各自的空间不串扰 相同的函数名 调用时 区分是谁空间里的 函数

```C
using namespace 
```

#### const 

##### C语言中 

1、局部常量可以通过指针取地址取转换值 

```C
int*p =(int*)&m_b
```

2、 全局只读不能修改

3、 默认是外部链接   外部文件不extern   当前文件加上 extern 访问到其他文件的const变量

##### C++ 

1、只有用普通变量初始化 const 变量时通过 指针可以修改  直接赋值不可修改

```C
int a =10;
const int b= a;
int *p =(int *)&b;
*p=1000;  //  cosnt int b 将修改为1000
--------------------------------------
    const int b =10;  //  只读不可修改
```

2、必须在外部文件加 extern  本文件才能访问 外部的 const 

3、使用结构 使用 指针也能修改const的值

```CPP
struct Person
{
    string m_Name;
    int m_Age;
}
void test()
{
    const Preson p1;
    // p1 m _Name ="名字";  // 错误
    -------------------------------
    Person *p=(Person*)&p1;    //成功写法
    p->m_Name ="名字";
    (*p).m_Age = 18;
}
```

#### 卸载宏常量

  \#define A 20 

  #undef A     //卸载宏常量A  目的 结束作用域 

#### 引用

左值 &  为引用

2、数组引用

```CPP
int arr[100];
int (&pArr)[100]=arr;
```

3、typedef的别名引用

```CPP
typedef int (ARRAYREF)[100];
ARRAYREF&pArr2=arr;
```

####  静态成员变量 和  函数

作用  1、共享  值   2、不同类对象 赋值都会覆盖之前的值  

定义      在类 public中 定义 satatic变量   

初始化  在全局中初始化  

问题：  但不能在 构造函数中定义 否则调用不到

```CPP
class Person
{
public:
	static int m_Age; //加入static就是 静态成员变量 ，会共享数据
	//静态成员变量，在类内声明，类外进行初始化
	//静态成员变量 也是有权限的	

private:
	static int m_other; //私有权限 在类外不能访问
	static void func2()
	{
		cout << "func2调用" << endl;
	}
};
int  Person::m_Age = 0; //类外初始化实现
int  Person::m_other = 10;

void test01()
{
	//1 通过对象访问属性
	Person p1;
	p1.m_Age = 10;
    Person p2;
	p2.m_Age = 20;   //最后 p1的值和p2 的m_Age的值都为 20
    //2 通过类名访问属性
	cout << "通过类名访问Age" << Person::m_Age << endl;
	//cout << "other = " << Person::m_other << endl; //私有权限在类外无法访问
```



```CPP
//静态成员函数
//不可以访问  普通成员变量
//可以访问 静态成员变量
	static void func()
	{
		m_Age = 100;
		cout << "func调用" << endl;
	};
	//普通成员函数 可以访问普通成员变量，也可以访问静态成员变量
	void myFunc()
	{
		m_A = 100;
		m_Age = 100;
	}
	
	//静态成员函数调用
	p1.func();
	p2.func();
	Person::func();
	//静态成员函数 也是有权限的
	//Person::func2();
```



#### 类的大小

只有非静态 成员变量算在sizeof里 



