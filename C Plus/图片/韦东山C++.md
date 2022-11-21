g++ -o   xxx     xxxx.cpp                      ./xxx 

函数参数 是指针 
    则内部只能用.  不能用 ->

C++对struct 进行扩展   可以在结构体里直接写函数   且把创造出了新 东西叫类class

```c
类首字母大写
    this->    当前对象的参数  
    就近原则  当前行的 参数x离传入参数x行更近则 对应的是传入参数x 那么另一个则是类的变量x 就是 this->x //常用于private成员x 时需要通过这种手段      this->x 就是私有变量x 
```

实例化 就是创建了构造函数对象

```c
比如
    class Person {   //有类
private:
	char *name;
	int age;
	char *work;
public:
	Person() {	}   //有构造函数
};
在主函数里实例化
int main(int argc, char **argv)
{
    Person per1;   //这样就叫实例化   per1是对象名
	return 0;
}
  
所有的类可以当作struct 看待 就是只是声明而已 当要使用的时候才定义
```





###### 基础的三文件的主次关系

```c
在类外定义类的函数  加作用域  类::   void  类::xxx()
   
分离成三个基础文件   .h   .cpp     main.cpp 
    
    .h 放给main 用的类的定义
    .cpp  是实现 基于.h定义的内容来写  基本是实现所定义的函数
    main  是调用public的 函数
    
那么这么多文件就得使用Makefile关联文件了
    $< 是指第一个依赖
    $^ 是指全部的依赖文件
    $@ 是依赖文件的宿主
    
通常 以 %.o     %.cpp     用通配符%指相同类型的文件  
 注意一点： 
    	所有不是顶格的 都是tab按出来的不是空格
    
xxx.cpp  中包含 #include "xxx.h"     
main.cpp  中包含 #include "xxx.h"
    
```

###### namepace 命名空间

```c
多个.cpp  多个.h  如果都是相同的函数名， 当main.cpp 调用的时候就不知道是谁的函数了。所以引入命名空间

  .h  
2、   namspace X{
    class Xxx{
        private:
        public:
    };
    void xxxx(void);
} 

实现.cpp
    
2、   namspace X{
    所有的实现函数写在括号里
} 

那么 main.cpp
    
3、 using X:: Xxx;    Xxx是类名   声明命名空间对应的类
 using Y:: Cat;   
 int main(int argc, char **argv)
{
//    X:: xxx 对象;           //以作用域的方式去调用被命名的类的函数  但是这样很啰嗦
4、  Xxx 对象;  
5、    对象.xxxx();        //这样写省去每次都写作用域  
  Cat 对象:
     对象.xxxx();
}

3、4、5、还是太麻烦那么直接
    using namspace A;

命名空间  global namespace   等于用 using 说  把这个类的某些函数导入到main 文件里  而using namspace是直接把整个类都导入   为了是多个文件都有相同名的函数造成冲突用命名空间去解决这个问题
    
经典的 using naspace std;    标准的命名空间 给cout endl用的
  using naspace std; 可以在  .cpp 里去单独的声明  那main.cpp 就不会全部都被声明
      
```

###### C++可以根据传参参数类型、个数不一样来重载同名函数 ，不能通过返回值来重载同名函数

```c
如图下示
double add(int a, double b)   
{
	cout<<"add int+double"<<endl;
	return (double)a+b;
}

double add(double b, int a)
{
	cout<<"add double+int"<<endl;
	return (double)a+b;
}

```

###### &a    *a   这样在C里叫指针    C++  直接  a      &b  效果一样叫引用

​	如果不是在函数里定义引用 ，则在定义的时候就需要初始化  &c = a;    初始化时赋值只能是变量 不能是值

引用最重要的就是以地址的形式 作为参数 那么只会用4字节  如果 参数是个函数 不用引用那么传参时候需要非常多的字节。  引用达到了简化 参数字节的效果只要4字节效率很高

```c
  int add_one(int *a)
{
	*a = *a + 1;
	return *a;
}
	int add_one_ref(int &b)
{
	b = b+1;
	return b;
}
int main(int argc, char **argv)
{
	int a = 99;
    int &c = a;
	cout<<add_one(&a)<<endl;
	cout<<"a = "<<a<<endl;

	cout<<add_one_ref(a)<<endl;
	cout<<"a = "<<a<<endl;
    
    C++;
    cout<<"aa = "<<C<<endl;
	return 0;
}

a 100
a= 99
100
a= 100
aa= 101   
```

###### 构造函数

 构造函数就是跟类名一样的函数

其中 per. xxxx()   //xxxx是成员函数这样可以调用到class的成员函数

只要是 类.对象   对象. xxx   其中xxx基本上就是构造函数  也可能是成员函数

```c
主要是 多次调用变成一次调用多个内容 免去啰嗦的代码 不同参数则调用不同的构造 构造的特点是运行时被创建这样在代码空间上的节省
  class Person {
private:
	char *name;
	int age;
	char *work;
public:
	Person() {cout <<"Pserson()"<<endl;}
	Person(char *name) {}
	Person(char *name) 
	{
		cout <<"Pserson(char *)"<<endl;
		this->name = name;
	}
	Person(char *name, int age, char *work = "none") 
	{
		cout <<"Pserson(char*, int)"<<endl;
		this->name = name;
		this->age = age;
		this->work = work;
	}//这种就是参数默认值写法 用于被调用时只传了2个参数的情况有效的利用函数
};    

int main(int argc, char **argv)
{
	Person per("zhangsan", 16);
	Person per2;   //这样是对应 Person()  无参数
	Person per3();  //这样带括号写是声明函数 不是调用

    这两种写法都是调用无参构造函数
	Person *per4 = new Person;   //这样是调用无参构造
	Person *per5 = new Person();  //这样是调用无参构造

	Person *per6 = new Person[2];  //这种数组 

	Person *per7 = new Person("lisi", 18, "student");  //这种是三个参数的构造函数
	Person *per8 = new Person("wangwu", 18);   //这种是两个参数使用默认参数的构造函数

	per.printInfo();  
	per7->printInfo();
	per8->printInfo();

	delete per4;  //delete是手动释放 一般new出来的需要手动释放 
	delete per5;
	delete []per6;   //数组 在前面加[]
	delete per7;
	delete per8;

	return 0;
}
以上是输出是如下
 Pserson(char*, int)    //对应Person per("zhangsan", 16);
 Pserson()   
 Pserson()
 Pserson()   
 Pserson() 
 Pserson()
 Pserson(char*, int)
 Pserson(char*, int)
name = zhangsan, age = 16, work = none   //对应per.printInfo();
name = lisi, age = 18, work = student     //对应 per7->printInfo();
name = wangwu, age = 18, work = none    //对应 per8->printInfo();
    
```

###### 分配空间给成员变量name  分配的是堆空间

```c
原本char *name; 是一个字符的要存放字符串
Person(char *name, int age, char *work = "none") 
	{
		this->name = new char[strlen(name) + 1]; //每次不同的字符串创建相应的长度来存放达到了空间正确分配  所以使用char来定义 name  根据name有多大 把private的 char* name 就分配多大空间
		strcpy(this->name, name);
	}    
```

###### 析构函数 在子函数里实例化   分配空间有什么区别

​	子函数就是除main以外的普通函数  

```c
在main里面 程序运行结束会自动回收空间 
    在其他的子函数里跑这些代码 的区别
free -m    linux查看当前的内存大小
 得出结论：
    在子函数运行的时候 在运行完毕后会自动释放所有空间，这时候才释放掉new 出来的空间 本应该在调用完就释放掉new的空间的
    所以我们得需要手动释放  避免在运行期间没有内存用 通常叫内存泄漏就是之前分配的空间没被及时回收
所以出现了析构函数
    
    1、构造函数被调用
    2、当被调用所处的 外层函数执行完毕后，有析构函数 那么就会被自动释放
    3、如果是 new 的析构函数那么 得手动delete释放
    4、如果 一个函数里同时调用 构造以及 new的构造 那么接着写delete new出来的构造则顺序 是析构最后被执行因为要做当前函数被运行结束才立马执行析构
    
    5、只要记住 是new出来的空间  就只能用 delete去手动释放 否则main执行完毕也不会释放
    6、 构造函数  即使不写析构函数 也可以使用 是因为系统默认会加析构函数
```

```c
借用 析构函数来 释放构造函数  的方法   
	1、 由于构造函数自己会释放所以 要处理下   //参考 person6.cpp
			this->xxx =NULL;   //xxx是 当前这个构造没有的参数 那么就不要去释放
	2、 在析构里释放 new 所用到的参数
        ~person()
    {
        if (this->name) delete this->name;   //判断的目的是 避免参数不存在而去释放
        if (this->work) delete this->work;
    }
为什么需要这样写 因为可以达到一调用完有参构造函数立马去释放 而析构是所有构造一起用的 那么对无参的构造函数就得去 不执行释放参数。 
```



###### 拷贝构造函数  同时出现内存释放两次的原因

由于per是 对象  per2也是对象   而per2是想把per的内容都来拿，有拷贝的现象，这种行为叫做拷贝构造函数

但是只是 值拷贝 。不是开辟空间 存放值， 所有档per释放 ，per2在用值或释放都会出错。

那么我们自己去写拷贝构造函数 说白了 开辟空间复制内容 到自己开辟的空间里放着。per释放掉也不影响。

```c
Person per("zhangsan", 18);   
Person per2(per);  //这里没有定义过一个参数是per的构造函数 ，那么就会调用默认的拷贝构造函数 将拷per函数拷贝给per2

所以per2 的执行的内容将和 per一样   //实际上是调用了默认的拷贝构造函数
    
  默认拷贝构造函数会造成的问题：  
    由于都是构造函数所以 当 per释放的时候 所分配给内容的空间被释放了， 同时 per2也去释放一次，所以释放了两次。 那么 per2释放的空间实际上不存在。解决这个问题得写一个拷贝构造函数不用默认的
    
写一个拷贝构造函数格式如下    
Person(Person &per) 
	{
		cout <<"Pserson(Person &)"<<endl;
		this->age = per.age;  //age直接给 是因为定义 的是 int age 字节够用了

		this->name = new char[strlen(per.name) + 1];  //分配的空间大小用per的参数大小来做大小
		strcpy(this->name, per.name);

		this->work = new char[strlen(per.work) + 1];
		strcpy(this->work, per.work);
	}
```

###### 析构释放的先后顺序

```c
1、在main 之前先定义的构造函数先运行
2、到main内容
    1、按顺序 先定义的先运行  
    2、遇到for 进入for 调用某个函数
    	1、函数里面也是按顺序运行
    3、 函数运行完 先释放掉 
    	1、释放顺序 非static的就先释放 如果是delete 先delete  //static不释放  因为只释放局部变量
  		2、如果在次循环了 那么static 不会去实例化一次 因为已经存在了 
    4、在顺序执行完for的其他内容
    5、释放按最后运行的先析构 在往上  最后是static  顺序也是最后运行的先释放知道最先运行的最后释放。 
    
    
总结就是 
    全局变量 先实例化
    局部变量先释放
    静态变量 不释放  当再次运行则不实例化因为存在了
```

###### 私有变量如果是构造函数 那么是先调用 还是说构造函数先调用

```c
class Student {  
private:
	Person father;   // 发现是按顺序 只要是构造函数 先定义先运行
	Person mother;
public:
	Student()
	{
		cout<<"Student()"<<endl;
	}
};
```

###### 定义有参构造 必须要先定义无参构造

```c
因为 定义了有参构造函数  系统将不帮我们定义无参构造函数  //会直接报错
```

###### 构造函数初始化私有成员变量

如果是私有成员对象  那么初始化时给的参数作为 对象的参数。

```c
Student(int id, char *father, char *mother, int father_age = 40, int mother_age = 39) : mother(mother, mother_age), father(father, father_age)
	{
		cout<<"Student(int id, char *father, char *mother, int father_age = 40, int mother_age = 39)"<<endl;
	}

只是这里的成员变量 是构造函数所以遵守构造函数的规则
1、： 冒号后面写成员变量 且给传参  这种行为叫给成员变量初始化 把 当前的参数作为成员变量的值
2、 运行 的顺序跟冒号写的顺序无关  按照定义的顺序来运行 
3、 析构的顺序是按谁最后运行的谁先析构 最先定义的最后析构    
```

###### 静态成员

​	静态的目的是比如累计 这种 在前面的值上一直做累计来用  

​	静态成员函数只能调用静态成员变量  。调用不了非静态的成员变量

```c
在 private 里 用 static的就叫静态成员 这个参数被多个构造函数实例化 时候共用
    等于 静态成员属于所有 实例化对象  共用的变量
一般静态成员变量 利用静态成员函数来用
 class Person {
private:
	static int cnt;

public:
	static int getCount(void) 
	{ 
		return cnt; 
	}
};

int Person::cnt = 0; /* 定义和初始化 */ 因为原本声明的时候并没有初始化也没有定义  注意放在main外面定义的类成员变量不是全局变量 实际上是在类的类名空间里 。不能在main里定义否则报错
    

在main里面这样所有的实例化对象不用 通过  .的方式去调用
int main(int argc, char **argv)
{
    
	Person::getCount()  采用 作用域的方式
	return 0;
}

-----------------------------
 在类外定义静态成员函数
int Person::getCount(void) 
{ 
	return cnt; 
}
 
```

###### 友元

​	为什么需要友元： 因为main 里面使用的类对象的参数 是先给private的话 那么普通函数需要使用参数就得通过成为好友的方式获得 private权限 拿到参数

```c
就是当一个类外的普通的构造对象函数想使用 构造函数实例化的对象给类的private 成员传递的参数 的时候。由于类外没有权限去访问类的private成员参数 那么使用友元的方式。使用私有成员 这样不用很啰嗦的通过类内的普通函数去返回 私有变量 给外部用。
  public:
    friend Point add(Point &p1, Point &p2);   在类里面 以 friend开头 定义类外的对象函数 那么就可以直接使用到 私有变量
		}  	    
```

###### 非友元

```c
需要使用 私有变量的值  得在类里面进行 get    set   两步骤才能拿到值
public:
 int getX(){ return x; }
 int getY(){ return y; }
 void setX(int x){ this->x = x; }
 void setY(int y){ this->y = y; }   
}

```



###### 重载

```c
Point operator+(Point &p1, Point &p2)    // 重载加号函数名 operator+
{
Point n;
	n.x = p1.x+p2.x;
	n.y = p1.y+p2.y;
    
}    
 //目的 让对象可以进行加法
    
 1、在mian里面写了   
    Point sum = p1+p2;   //对象p1+p2 这样需要重载 使用重载函数 去做计算

```

###### 重载2

```c
//目的 p1++    ++p1
两者区别：  执行的顺序不一样
    1、   b= ++a;    //a=a+1;   b=a;
	2、	 b= a++;	//b=a;		a=a+1;
同一个文件里 需要重载两次++  可以使用不同参数个数来实现两个重载函数
    
 /* Point p(1,2); ++p; */
Point operator++(Point &p)
{
	cout<<"++p"<<endl;
	p.x += 1;
	p.y += 1;
	return p;
}

/* Point p(1,2); p++;      两个参数 一个参数封装好了 对应先++还是 后++*/
Point operator++(Point &p, int a)   
{
	cout<<"p++"<<endl;
	Point n;
	n = p;
	p.x += 1;
	p.y += 1;
	return n;	
}   
int main(int argc, char **argv)
{
	Point p1(1, 2);
	Point p2(2, 3);

	Point n = ++p1;    ->     //Point operator++(Point &p)
	Point m = p2++;    ->     //Point operator++(Point &p, int a) 
	return 0;
}
```

###### 重载3

```c
临时对象
    在++p 中由于系统认为我们进行运算后 的对象是需要使用的，所以会帮我们创建一次对象在析构掉，称为临时对象 如果我们只是需要进行++ 那么就不需要让系统帮我们创建在析构，造成浪费时间。

 /* Point p(1,2); ++p; */
Point operator++(Point &p)
{
	cout<<"++p"<<endl;
	p.x += 1;
	p.y += 1;
	return p;   //   返回  Point(const Point& p)
}

/* Point p(1,2); p++;      两个参数 一个参数封装好了 对应先++还是 后++*/
Point operator++(Point &p, int a)   
{
	cout<<"p++"<<endl;
	Point n;      //  由于我们自己创建的临时对象 所以系统不会再去创建一个临时对象
	n = p;
	p.x += 1;
	p.y += 1;
	return n;	
}       

解决方法  用引用的方式
  Point& operator++(Point &p)  
```

###### 返回用对象或引用是否影响 值的结果

​	前++  返回引用      后++ 返回临时对象n

```c

    1、如果是 前++ 我们返回的反正是 ++后的值所以返回P 是没事的
    2、后++就只能返回临时对象，因为我们要的值是 在计算前的 如果返回引用那么返回的将是p也就是变成返回自己 那就错误了 另外 不能返回  n对象 因为n调用后就销毁了所以只能返回值
  Point operator++(Point &p, int a)   正确   返回值 n    
  Point& operator++(Point &p, int a)  错误  不能返回 对象n        
    
 1、引用效率高 在不影响结果的前提下使用
 2、 临时变量 在函数执行时创建 执行完毕时被销毁。只返回值效率低
```



###### 成员函数

注意重载 << 运算符函数 是不能够放入 类里面的 因为 参数类型的原因

```c
在类外写函数的时候需要两个参数      //类内只要1个   参考代码 point7.cpp
    则在类里面写函数的时候 由于 mian里面实例化对象的参数是成员变量。
采用this ->x +p.x    //一个参数用 成员变量 另一个参数 应该是传进来的参数 。所以会有点变化 
    
    
    int main(int argc, char **argv)
{
	Point p1(1, 2);
	Point p2(2, 3);
	Point m, n;

	m = p1 + p2; /* m = p1.operator+(p2);   就相当于 p1被当成成员变量看 所以传参的时候参数变成一个了 */
    
   原本在类外写函数是
       Point operator+(Point &p1, Point &p2)
{
	cout<<"Point operator+(Point &p1, Point &p2)"<<endl;
	Point n;
	n.x = p1.x+p2.x;
	n.y = p1.y+p2.y;
	return n;
}
    
  在类里面写  改成
     Point operator+(Point &p)
	{
		cout<<"operator+"<<endl;
		Point n;
		n.x = this->x + p.x;
		n.y = this->y + p.y;
		return n;
	}
```

###### 重载 =号

​	拷贝构造函数 得自己写不要去用默认的

1、 注意区分 哪种是调用拷贝构造  、哪种才是 调用重载等号

如果是定义跟赋值分开写 那么就是重载  ， 否则就是拷贝构造   注意重载和拷贝构造函数都要自己写

两个函数的内容都差不多 只是 重载得先判断删除

```c
注意 如果是在类内重载则需要进行  delete掉 变量的操作  因为可能p3原本的变量就已经有值了所以先删除掉。
    Person& operator=(const Person& p)
	{
		cout << "operator=(const Person& p)"<<endl;
	
		if (this == &p)   //这句是避免自己 =自己  就是 判断下地址是不是一样的一样就不要处理
			return *this;
		this->age = p.age;

		if (this->name) {
			delete this->name;
		}
		if (this->work) {
			delete this->work;
		}
    
    
    
const Person p1("zhangsan", 10);

	cout<<"Person p2 = p1" <<endl;
	Person p2 = p1;   //就是去执行拷贝构造 
	Person p3;
	cout<<"p3=p1"<<endl;
	p3 = p1;            //调用重载等号
	cout<<"end"<<endl;  

如果 const Person p1 是带const   则拷贝构造函数 Person(const Person &per)  的参数也得加const
```

###### 怎么调用函数

```c
Sofabed s;    //  Sofabed  是类名  s 就是实例化对象
	s.watchTV();   //   . 后面的就是函数  通常是类的成员函数   因为是类对象 . 的写法只可能是类成员函数
	s.sleep();
```



###### 继承

public  外界可以直接访问

private 外界不可见， 子类无法直接访问   所有都只能通过类成员函数间接访问

protected   与 private  效果一样，只是子类可以直接访问

这里的外界是在类外的普通函数 以及 main函数 

继承 是可以 拥有protected 以及 public的成员     。只有private是无法被继承

注意是 以 using 为开头

```c
在类后面  ： public写父类的类名  //这种行为叫继承  如果没有写 或被别的类写 那么就没有继承的说法只是普通的类
class Son : public Father     
    /*1、只能访问到 公有的变量或者函数 
      2、想要访问私有变量 可以通过Father的函数去调用私有变量
      3、可以使用protected成员   实际上protected 本来就是专门给 子类使用的
    */
    
1、如果子类把父类 在protected的 变量设置成了  public  那么 mian函数里是可以直接调用的
	class Father {
protected:
	int room_key;
}
-----------------------------------------
	class Son : public Father {
public:
	using Father::room_key;
}
-----------------------------------------
int main(int argc, char **argv)
{
	Son s;
	s.room_key = 1;	  //这样是可以的
	return 0;
}

2、如果 using Father::room_key;  写在 private  那么  main 是不能使用的会报错
    
1、子类可以把父类 的 公有成员函数  定义成 private的  那么外界就不能使用 子类.对象 访问了
   
    
1、如果子类是 以 :protected Father 去继承父类  那么 父类所有public和protected的成员 都变成了子类的 protected 。
    
目的是 让不同的子类做单独的内容不会去影响到非相关的东西
    
如果子类以 : private Father 去继承父类  那么 孙子类即使以: public  继承子类的时候，还是无法使用父类的public   
    
    记住   如果 子类是 以 protected 继承了 父类的 public的成员   那么 孙子类以public继承子类时，外界也是无法 通过孙子类.对象的方式去使用。
    
 1、如果孙子类01或子类001 写了一个跟 父类1同名的函数 那么 外界 通过  01.对象的方式去使用调用的就是孙子类自己新写的函数。
    
```

###### 情况复杂 的继承

```c
class Person {
private:
	char *name;
	int age;

public:
	int address;

    void printInfo(void)
	{
		cout<<"name = "<<name<<", age = "<<age<<endl;
	}
};


class Student : public Person {
private:
	int grade;
	void setGrade(int grade) {this->grade = grade;}
	int getGrade(void) {return grade;}
public:
	void printInfo(void)
	{
		cout<<"Student ";
		Person::printInfo();  //这里调用父类的 成员函数 这个函数是可以访问到父类的私有
	}
};

-----------这时候出现了一个 普通函数--------------
    void test_func(Person &p)  //参数是以父类引用的形式传参
{
	p.printInfo();
}
------------------------------------------
int main(int argc, char **argv)
{
	Person p("lisi", 16);  这样是通过父类自己的构造函数去给私有变量设置值

	Student s;
	s.setName("zhangsan");  这个是调用父类 public的成员函数 所以打印的参数值是这个
	s.setAge(16);           这个是调用父类 public的成员函数

	test_func(p);     //这个肯定是父类的
	test_func(s); /*这个是子类的对象 也就是 Person &p 引用的是 s 里面person部分的内容也就是说调用的是父类的函数 不是自己的printInfo 这里很巧妙的  由于传递的形参 是Person 的引用，所以子类继承的父类，从而是去调用父类的成员函数，而不是自己的同名函数。  很绕口但是这是非常重要的逻辑。
	               */
	s.printInfo();  //这个才是自己的函数

	return 0;
}

注意这段代码只截取一部分不完全。参考  10th_inheritance/person_student.cpp  代码文件
 
    
    这段打印出来的内容是
Pserson(char*, int), name = lisi, age= 16
name = lisi, age= 16 
name = zhangsan, age= 16  
Student name = zhangsan, age= 16 
```

###### 多重继承

目的是 sofabed这个类 既需要 Sofa的内容 也需要用到Bed的内容所以需要继承多个类

```c
同时继承多个父类
class Sofa {    //1、类
public:
	void watchTV(void) { cout<<"watch TV"<<endl; }
};

class Bed {    //2、类
public:
	void sleep(void) { cout<<"sleep"<<endl; }
};

class Sofabed : public Sofa, public Bed {    //继承了 两个类的 写法
};


1、 如果父类 都要同名函数那么子类调用父类的时候的写法

s.Sofa::setWeight(100);   //这样就说明是调用Sofa这个类的函数  but 太繁琐了  ，but 不写有种说法叫二义性。系统不知道到底调用谁的同名函数。唯一的办法是 同名函数用单独的类封装起来，两个父类都去继承下这个类。

由此 产生新的叫法：虚拟继承。  
class Furniture {
private:
	int weight;
public:
	void setWeight(int weight) { this->weight = weight; }
	int getWeight(void) const { return weight; }
};
class Sofa : virtual public Furniture {  // 加上 virtual 就叫虚拟继承
}

class Bed : virtual public Furniture {
};
虚拟继承的效果 是因为 Sofa 、Bed都有同名参数 weight 所以直接共用 那么Sofa 、Bed 不同名的参数 也被子类Sofabed继承了。所以Sofabed 拥有：weight、a、d、自己的参数。   这么4个类的参数。但是这样相当于套娃容易看蒙尽量不要这样用。

```

###### 构造顺序

参考代码文件  12th_constructor_2

如果 类没有被调用 也会构造 只是调用无参构造

```c
有虚拟继承后 构造顺序 1、先虚拟基类  2、后一般基类    再自身类  1、先对象成员   2、后自己
 如  class LeftRightSofabed : public Sofabed, public LeftRightCom 
       自身						父类	           父类            图中的7、8就是对象成员
    
    注意 虚拟基类 ，构造函数只执行一次
    
  如果虚拟基类不是写在靠上面 写在位置比较靠后。 那么执行顺序会变化 按被调用的顺序，虚拟优先构造。 参考文件 Sofabed3.cpp
   
```

![](C:\Users\liurhui\Documents\韦东山c++\虚拟继承的构造顺序截图.png)

###### 多态  可以说多态实际上就是 使用了virtual 关键字 也叫虚函数运行后产生的现象叫多态

现象：使用相同的方法，根据不同对象属于什么类 ，就能够调用不同类自己同名函数

多态受很多限制使用

1、多态只有在 传值时是引用& 才是多态，否则不是多态 

2、静态成员函数、内联函数 、构造函数、重载函数参数不同   都不能设置为多态

3、析构函数一般都声明为虚函数  只有类成员函数才能使用虚函数

```c
当定义了多个类 每个类都有相同的 同名函数 并且都继承了同一个父类。父类里面也有一个同名函数。
    
void test_eating(Human& h)  //形参是 父类的引用
{
	h.eating();
}
int main(int argc, char **argv)
{
	Human h;
	Englishman e;
	Chinese c;
	test_eating(h);  这样的话默认都是调用 父类的同名函数    这样叫做静态编译 非虚函数  也就是父类的同名函数没有加 virtual关键字  在编译时就确定好意思是 ：如果有继承且同名函数那么就是默认调用父类的同名函数而不是自己的同名函数。
	test_eating(e);
	test_eating(c);
	return 0;
}

如果想自己调用自己的同名函数 得把父类的同名函数 写成虚函数 。 
 class Human {
private:
	int a;
public:
	virtual void eating(void) { cout<<"use hand to eat"<<endl; }
};
 这种行为 被叫做 动态编译  父类同名函数有家virtual  再运行时候才去确定
    1、对象里有指针 指向虚函数表
     2、通过指针，找到表，调用虚函数
     只要有写 virtual就会自动生成虚函数表 ，通过表调用代码
     
在编译中， 大小也会变 +12字节
既然写了 加了 virtual那么在析构的时候必须加virtual否则一样是调用父类的析构
     注意 当有继承时候。  析构正常顺序是 1、先调用自己的析构  2、再调用基类也就是父类的析构
---------------------------------------------------------------------------------
     当 同名函数  的返回类型是类指针 时可以产生多态现象  实现自己调自己的同名函数
class Human {
private:
	int a;
public:
	virtual Human* test(void) {cout<<"Human's test"<<endl; return this; }
};

class Englishman : public Human {
public:
	virtual Englishman* test(void) {cout<<"Englishman's test"<<endl; return this; }
};


class Chinese : public Human {
public:
	virtual Chinese* test(void) {cout<<"Chinese's test"<<endl; return this; }
};

void test_return(Human& h)
{
	h.test();
}

int main(int argc, char **argv)
{
	Human h;
	Englishman e;
	Chinese c;

	test_return(h);
	test_return(e);
	test_return(c);


	return 0;
}
```

###### 类型转换  实际上是采用模板函数来处理

注意： 隐式类型转换：由于系统不知道我们的目的 所以常出现一些警告。

比如 int*  char*  可能 我们存放的是数字 和字符串  那么print 以0x%x 输出的时候 就会出现警告

解决的方法就是输出的时候 强制转换（using int）

2、在64位系统中 指针是8字节的  int是4字节所以 把 int* 类型强转为 int 会报警告但没什么事情

解除警报在编译的时候  加   -fpermissive  //这个是根据报错时系统告诉我们的

要么用交叉编译   arm-linux-g++ -o xxx xxx.cpp  这样编译 因为是32位

```c
int *p = reinterpret_cast<int *>(str); // char*强制转为 int* 

	printf("i = %d, str = 0x%x, p = 0x%x\n", i, reinterpret_cast<unsigned int>(str), reinterpret_cast<unsigned int>(p));

	const char *str = "100ask.taobao.com";
	char *str2 = const_cast<char *>(str);   //去除const
```

###### 动态类型转换

1、尽量写指针不要用引用。

2、上行转换 ：派生类转基类（子转父）   下行转换：基类转派生类 （父转子）

3、上行转换 系统会检测错误   。下行转换得自己做判断因为继承的关系存在，但不一定符合逻辑

```c
还是 通过普通函数 传父类的引用形参  所出现的问题
   
class Human { 
}

class Englishman : public Human {
};

class Chinese : public Human {
};

void test_eating(Human& h)   1、两个子类都继承了父类Human 而 普通函数 是以父类类型作为引用传值
{
	Englishman *pe;    //目的是定义自己类的 指针变量 看下是否能够转换过来
	Chinese    *pc;
	
	h.eating();  //这里调用 的eating 得看父类同名函数有没写 virtual 
	/* 想分辨这个"人"是英国人还是中国人? */
	if (pe = dynamic_cast<Englishman *>(&h))   //如果可以动态转换为 自己类的变量那么就简化了很多
        cout<<"This human is Englishman"<<endl;
	if (pc = dynamic_cast<Chinese *>(&h))
		cout<<"This human is Chinese"<<endl;	
	
}
int main(int argc, char **argv)
{
	Human h;
	Englishman e;  //定义了自己类的对象
	Chinese c;
    
	test_eating(h);   //传递的 类型都是父类 没有虚函数 应该是调用父类的
	test_eating(e);
	test_eating(c);

	return 0;
}


实现 出现 单输入多输出效果   一个广西人  既是中国人也是广西人 怎么写
方式一指针形式    
class Chinese : public Human {
public:
	void eating(void) { cout<<"use chopsticks to eat"<<endl; }
	virtual ~Chinese() { cout<<"~Chinese()"<<endl; }
	virtual Chinese* test(void) {cout<<"Chinese's test"<<endl; return this; }
};

class Guangximan : public Chinese {  //1、必须继承不然得不到 Chinese类的类型指针
public:
	void eating(void) { cout<<"use chopsticks to eat, I come from guangxi"<<endl; }
};
void test_eating(Human& h)
{
	Guangximan *pg;
 	Chinese    *pc;   
	if (pc = dynamic_cast<Chinese *>(&h))  //传进来 的对象g由于继承的原因 是可以转成Chinese*类型的
		cout<<"This human is Chinese"<<endl;	//打印成功
	if (pg = dynamic_cast<Guangximan *>(&h))
		cout<<"This human is Guangximan"<<endl;	  //打印成功
}
int main(int argc, char **argv)
{
	Guangximan g;
	test_eating(g);
	return 0;
}

方式二引用形式
 注意  强制转换成没有继承的类 是无法使用引用的
 比如：  Englishman& pe = dynamic_cast<Englishman&>(h);    //其中Guangximan没有写 ：pubilc Englishman 类 这样写编译直接报错  如果运行会奔溃

```

###### 抽象类

当虚函数 再定义的时候初始化为0 那么就变成了抽象类

目的是 父类只是声明不调用  。主要是子类调用  所以再子类写同名函数

1、注意父类如果写了纯虚函数 子类里要是没有实例化。那么编译还是过不了。

2、只有子类实例化了才能正常编译  。

```c
class Human {
private:
	int a;
public:
	virtual void driving(void) = 0;  //纯虚函数 完全不会去用到则写纯虚函数 节省代码空间 且不能实例化
    virtual void driving(void){}  //空函数  就是再后面代码还会用到目前不用 写空函数  叫多态
};

class Englishman : public Human {
public:	
	void driving(void) {cout<<"drive english car"<<endl; }
};

class Chinese : public Human {
public:
	//void driving(void) {cout<<"drive chinese car"<<endl; }
};

class Guangximan : public Chinese {
	void driving(void) {cout<<"drive guangxi car"<<endl; }
};

int main(int argc, char **argv)
{
	//Human h;   //抽象类不能实例化对象
	Englishman e;
    //Chinese c;   //也不能够实例化对象
	Guangximan g;   

	return 0;
}
```

###### 抽象类能做什么

```c
假如每个文件都需要使用到  两个函数 如果每个文件都去写这同名函数那么太麻烦了
    写一个基类 用于当父类，让别的类继承他。
    public:
	void setName(char *name);
	char *getName(void);
	
};

```

做动态库

```c
Human: main.o Chinese.o Englishman.o Human.o
	g++ -o $@ $^

%.o : %.cpp
	g++ -c -o $@ $<

clean:
	rm -f *.o Human	
原本是把所有的 文件都一起编译
----------------------------------------------------------
现在把文件规划下 分成 应用和提供    应用是使用类     提供是制作类
	mian是通过 各种类文件来实现的  所以 把其余的类都做成动态库调用
        
        
Human: main.o libHuman.so
	g++ -o $@ $< -L./ -lHuman

%.o : %.cpp
	g++ -fPIC -c -o $@ $<

libHuman.so : Englishman.o Chinese.o Human.o
	g++ -shared -o $@ $^

clean:
	rm -f *.o Human	
        
-------------------------------
        $@就是  libHuman.so     生成的文件
        $^就是   Englishman.o Chinese.o Human.o    所依赖的文件
        -shared  生成动态库.so文件
1、编译还是用 make
2、运行需要加路径    LD_LIBRARY_PATH=./  ./Human       运行的时候指定下路径否则不知道去哪找库
3、好处是如果只对 依赖文件.cpp修改 那么 make libHuman.so  就可以了 不会对 main文件重新编译 
      
```

###### 模板

16th_template

主要是因为只是参数类型和返回参数类型不一样 而函数的内容完全一样。避免重复的代码使用模板类型T来代替

1、不支持隐式类型转换   比如定义的两个参数分别是int  和double   模板 T  做加法 那么直接报错

2、 定义时是int 类型做参数     调用行参类型是 constT &int   是可以的 反之报错

```c
  当类型是 int  则系统自动把T变成int类型 这样可以省去非常多的重复函数
template<typename T>
T& mymax(T& a, T& b)
{
	cout<<__PRETTY_FUNCTION__<<endl;
	return (a < b)? b : a;
}

int main(int argc, char **argv)
{
	int ia = 1, ib = 2;
	float fa = 1, fb = 2;
	double da = 1, db = 2;
	
	mymax(ia, ib);   //当是 int 类型时候    T自动转换成 int 
	mymax(fa, fb);   //当是 float 类型时候    T自动转换成 float
	mymax(da, db);   //当是 double 类型时候    T自动转换成 double

	return 0;
}
```

```c
template<typename T>
const T& mymax(const T& a, const T& b)   //这里 char[3] 注意这里的 [3]是包含了结束符/0
	cout<<__PRETTY_FUNCTION__<<endl;
	return (a < b)? b : a;
}

template<typename T>
const T* mymax2(const T* a, const T* b)   // char
{
	cout<<__PRETTY_FUNCTION__<<endl;
	return (a < b)? b : a;
}

int main(int argc, char **argv)
{
	char a[]="ab";
	char b[]="cd";
	
	mymax(a, b);  /* T=char[3] */
	mymax2(a, b);

	char a2[]="abc";  //引用的时候由于 数组长度不一致会报错  //而指针却可以编译过 也就是类型一样就可以
	char b2[]="cd";

	//mymax(a2, b2);  /* mymax(char[4], char[3]), 无法推导出T: mymax(char& [4], char& [3]), 因为两个参数类型不一样 */
	mymax2(a2, b2);   /* mymax2(char[4], char[3]), 推导: mymax2(const char *, const char *); */  指针只看类型不看大小
	return 0;
}
```

###### 函数模板重载 不同情况下是调用哪个

16th_template

```c
优先选择匹配的 1、普通函数 再2、选择模板函数  最后3、选择const的的模板函数
    如果同时有两个一样的普通函数会产生二义性  （is ambiguous）
  其中 2和3 是看 原本的变量是否有const  如果不用转换那么就优先用哪个  

template<typename T>    //	1
const T& mymax(const T& a, const T& b)
{
	cout<<"1: "<<__PRETTY_FUNCTION__<<endl;
	return (a < b)? b : a;
}

template<typename T>	//  2
const T& mymax(T& a, T& b)
{
	cout<<"2: "<<__PRETTY_FUNCTION__<<endl;
	return (a < b)? b : a;
}


const int& mymax(int& a, int& b)	//   3
{
	cout<<"3: "<<__PRETTY_FUNCTION__<<endl;
	return (a < b)? b : a;
}
    
    
int main(int argc, char **argv)
{
	int ia = 1;
	int ib = 2;

	int *p1=&ia;  //表示 指针所指向的值  p1表示 是1  指向ia地址
	int *p2=&ib;
	cout<<mymax(p1, p2)<<endl;    //这个调用的是  2   注意这样输出的是 变量本身的大小  0x......
	return 0;					//如果我们是想比较变量值的大小那么应该用取值 *
}

------------------------------------------------------------------
 在前面 加一个模板函数    那么cout<<mymax(p1, p2)<<endl; 会优先调用此模板 
template<typename T>
const T mymax(T * a, T* b)   //4
{
	cout<<"4: "<<__PRETTY_FUNCTION__<<endl;
	return (*a < *b)? *b : *a;
}

为什么优先 ：  首先不用const  这个模板 跟2 都是并列优先。 由于都是模板那么只好选择 更符合更具体的。
	是这样的
    	const T& mymax(T& a, T& b)  允许接受2种
    			T=int   (int&,int&);
    			T=int*  (int *&,int *&);
		const T mymax(T * a, T* b) 
            	T=int   (int*,int*);   //更加准确了具体了
如果 是这样 const T mymax(const T * a,const T* b)   //4
那么优先就变了 是优先//2
    
---------------------------------------------------------------------------------------- 
 如果把 模板2 去掉那么优先 1   而不是//4
   const T& mymax(const T& a, const T& b)   //1
   const T mymax(const T * a,const T* b)   //4
 首先这两个  都带 const   
    1   const int *&   //这个比较复杂 看下面展开的介绍
    4	const int *   //通过下面的读法得知 const int * p  P指向只读的int
  这两种读法都得从右往左      
    const int *p   跟 int const*p   的读法一样 P是一个指向整型常量的指针 
    int *const p    P是一个常量指针，指向整型
    const int* const p  跟 int const *const p   P都是常量指针指向整型常量 
    
    
展开来说
     const T& mymax(const T& a, const T& b)   //1
    众所周知 int a=1; const int&b=a;  通过b无法修改a 
       如果 T=int *; 则 const (int*)&; //const修饰的是 int*
		int*q=&a;    const(int* p)=q;   无法通过P去 修改q  但是p所指内容可修改 虽然这么说在某种程度上说是有问题的。但是只要助于学习就这么理解
  const T& a  a是常量引用，a无法被修改 但是a所指内容可修改   就是因为只读 又可修改所以 才优先于 4的只读 
-------------------------------------------------------------------------------            
            
   比较字符串  这个没什么可学的就是记录一下 
int main(int argc, char **argv)
{            
	char *str1="hello";  
	char *str2="Hellod";
	cout<<mymax(str1, str2)<<endl; //指向字符串的内容 逐个字符比较           
	return 0;
}

char* mymax(char* a, char* b)
{
	cout<<"3: "<<__PRETTY_FUNCTION__<<endl;
	return strcmp(a, b) < 0? b : a;
}
```

###### 类模板

17th_class_template

```c
template<typename T>  //定义类
class AAA {
private:
	T t;
public:
	void test_func(const T &t);
	void print(void);
};

template<typename T>     //定义 类函数  
void AAA<T>::test_func(const T &t)
{
	this->t = t;
}

template<typename T>   //定义类函数 
void AAA<T>::print(void)
{
	cout<<t<<endl;
}

int main(int argc, char **argv)
{
	AAA<int> a;   //定义是 int类型
	a.test_func(1);
	a.print();

	AAA<double> b;   //定义成是double
	b.test_func(1.23);
	b.print();
	return 0;
}
```

###### 类模板重载

```c
只要注意在定义的时候语法有些不一样 ，其他的都是一样的
template<>    //1、
class AAA<int> {   //2、  直接写类型
public:
	void test_func_int(const int & t)
	{
		cout<<t<<endl;
	}
	void print_int(void);
};

void AAA<int>::print_int(void)
{
	cout<<"for test"<<endl;
}   
```

###### 异常

​	避免多个函数嵌套调用时，某一层出错导致需要层层返回。这样代码很乱   

基础异常还是比较简单的 。复杂的待补

```c
比如  A 调用B B需要调用C    那么在A里面使用 try   用catch 捕捉异常信号  在C函数里返回 throw 1
void C()  //C 返回 throw 异常信号
{
	throw 1;
}

void B()   //B里调用C
{
	C();
}
    
void A()   //A里调用B
{
	try {
		B();
	} catch (int i)
	{
		cout<<"catch exception "<<i<<endl;
	}
}  
-------------------------------------------------------------------------------------
    高级一点的写法 通过 输入的值 来作为参数去传递拿去做判断
void C(int i)
{
	int a = 1;
	double b= 1.2;
	float c = 1.3;

	if (i == 0)
	{
		cout<<"In C, it is OK"<<endl;
	}
	else if (i == 1)
		throw a;
	else if (i == 2)
		throw b;
	else 
		throw c;
}

void B(int i)
{
	cout<<"call C ..."<<endl;
	C(i);
	cout<<"After call C"<<endl;
}

void A(int i)
{
	try {
		B(i);
	} catch (int j)
	{
		cout<<"catch int exception "<<j<<endl;
	} catch (double d)
	{
		cout<<"catch double exception "<<d<<endl;
	} catch (...){    //如果异常太多了 用来表示 剩余类型的值（异常）都采用这句
		cout<<"catch other exception "<<endl;
	}
}

int main(int argc, char **argv)
{
	int i;
	if (argc != 2)
	{
		cout<<"Usage: "<<endl;
		cout<<argv[0]<<" <0|1|2|3>"<<endl;
		return -1;
	}
	i = strtoul(argv[1], NULL, 0);

	A(i);
	
	return 0;
}
--------------------------------------------------------------------------------
    更高级的做法 如果带类 且还有派生类 那么怎么让调用派生类自己
class MyException {  
public:
	void what(void) { cout<<"This is MyException"<<endl; }
};

class MySubException : public MyException{
public:
	void what(void) { cout<<"This is MySubException"<<endl; }
};


void C(int i)
{
	int a = 1;
	double b= 1.2;
	float c = 1.3;

	if (i == 0)
	{
		cout<<"In C, it is OK"<<endl;
	}
	else if (i == 1)
		throw a;
	else if (i == 2)
		throw b;
	else if (i == 3)
		throw c;
	else if (i == 4)
		throw MyException();   
	else if (i == 5)
		throw MySubException();  
}

void B(int i)
{
	cout<<"call C ..."<<endl;
	C(i);
	cout<<"After call C"<<endl;
}

void A(int i)
{
	try {
		B(i);
	} catch (int j)
	{
		cout<<"catch int exception "<<j<<endl;
	} catch (double d)
	{
		cout<<"catch double exception "<<d<<endl;
	} catch (MySubException &e)  //所以 子类catch应当写在父类前面  或者父类 加 virtual 不写 catch (MyException &e) 这样只去捕捉 子类 但是会区分 父类对象还是子类对象
	{
		e.what();
	} catch (MyException &e)  // 如果基类（父类）写在 子类（派生类）前面，那么捕捉的时候 会隐式的把子类转换成基类对象
	{
		e.what();
	} catch (...){
		cout<<"catch other exception "<<endl;
	}
}


int main(int argc, char **argv)
{
	int i;
	if (argc != 2)
	{
		cout<<"Usage: "<<endl;
		cout<<argv[0]<<" <0|1|2|3>"<<endl;
		return -1;
	}

	i = strtoul(argv[1], NULL, 0);

	A(i);
	
	return 0;
}   
---------------------------------------------------------------------
 还有一种常用的写法  
    void C(int i) throw(int, double)   //这种就是只检测 int  和double 类型的异常其余异常即使写了相对应的处理函数 也不会去执行。 是向系统提供的默认程序去处理 。  默认程序我们也可以去修改的
    这个函数是 set_unexpected (my_unexpected_func); 其中 参数 my_unexpected_func 是可以自己写通常是错误提示
    还有一个是系统终止函数 	set_terminate(my_terminate_func);  也可以去修改 
set_unexpected  和 set_terminate  两个函数都是 系统自动调用的意外异常函数 。系统都有默认的执行代码内容。但是我们可以去手动调用这两函数去修改内容， 那么系统就不会执行默认代码。采用我们写的代码内容
    
   所谓的意外异常就是  不在我们所捕获类型里的 异常。由系统去调用默认函数处理。比如  throw后面限制的捕获类型
```

###### 智能指针

目的是为了能够释放 空间所以需要一些 语法来自动释放

```c
专门写一个类来 间接的存储开辟空间的内容
    class sp {
private:
	Person *p;

public:
	sp() : p(0) {}
	
	sp(Person *other)
	{
		cout<<"sp(const Person *other)"<<endl;
		p = other;
	}

	~sp()
	{
		cout<<"~sp()"<<endl;
		if (p)
			delete p;
	}

	Person *operator->()  如果不写重载  s-> 是 属于 sp类自己的 无法属于
	{
		return p;
	}
	
};
    
void test_func(void)
{
	sp s = new Person();   //sp是而外写的类  当new出的空间给 sp来存储 解决 如果忘记写delete p; 不会释放造成内存泄漏的问题
	s->printInfo();   

	//Person *p = new Person();
	//p->printInfo();
	//delete p;	
}
原因是 s是局部变量  实际上  sp 自己写了 delete p  
    
    
视频 26分 30秒开始 
   
sp other = new Person();   
//1、 new Person();  调用了 Person() : count(0) 
//2、sp other = new Person();  调用了 sp(Person *other)

sp s = other;   
//3、这句使得调用了    sp(const sp &other) 函数
void test_func(sp &other)  调用完毕后
//4、 释放  ~sp()
因为还没==0 所以这里5 执行一次 ~sp后没去执行~preson
又因为main 里 for (i = 0; i < 2; i++)  执行第二轮重复 3、4、 
    
    
--------------------------------------------------------------------------------------- 	Person *operator->()
	{
		return p;
	}

对应的是 
void test_func(sp &other)
{
	sp s = other;
	s->printInfo();
}
int main(int argc, char **argv)
{	
	int i;
	sp other = new Person();
	for (i = 0; i < 2; i++)
	{
		test_func(other);
	}
	return 0;
}

-----------------------------------------------------------------------------
	Person& operator*()
	{
		return *p;
	}
对应的是
 void test_func(sp &other)
{
	sp s = other;
	s->printInfo();
}   
   int main(int argc, char **argv)
{	
	int i;
	sp other = new Person();
	(*other).printInfo();   //引用就得用*去访问
	for (i = 0; i < 2; i++)
	{
		test_func(other);
	}
	return 0;
}
```



要明白 先父类构造函数 才子类  所以把count 写在父类构造函数 间接的进行初始化 私有成员

##### 构造的顺序

未完 待 轻量级 指针   sp

```c
sp<Person> father = new Person();
	/* 1. 对于 new Person()
	 * 1.1 Person对象里的father先被构造
	 * 1.2 Person对象里的son被构造
	 * 1.3 Person对象本身
	 * 2. Person对象的指针传给"sp<Person> father"
	 *    导致: sp(T* other) 被调用
	 *    它增加了这个Person对象的引用计数(现在此值等于1)
	 */
1、new Person()
    1.1sp<Person> father;
	1.2sp<Person> son;
2、sp<Person> father = new Person();
```

###### Android强弱指针的实现  wp

```c
mStrong  类似计数的count
nWeak	 抽象为一个对象

    void incStrong()    
    void decStrong()    
    void incWeak()    
    void decWeak()    
 
在头文件里不想看到私有成员 只好做优化写法
    拆分成两部分  1、固定接口类  2、变化的实现
    就是 写成动态库 
   refbase.h 里面只能使用指针 否则会影响其他文件的大小
其中 21th_strongpointer_weakpointer\04th\include\utils 的RefBase.h 并没有写重载函数 -> 函数那么不能去使用
   	//s->printInfo(); /* 出错, wp没有重载"->", "*" */
	//(*s).printInfo(); /* 出错, wp没有重载"->", "*" */
 解决办法是： 升级为强指针采用 promote函数
    	sp<Person> f = father.promote();
		sp<Person> s = son.promote();

int flags   
    OBJECT_LIFETIME_STRONG  对象生命周期由mstrong决定   强指针
    OBJECT_LIFETWE_WEAK  由mweak决定
    增加强指针之前会进行弱指针的计数  所以  mstrong< =mweak 
    
     enum {
        OBJECT_LIFETIME_STRONG  = 0x0000,
        OBJECT_LIFETIME_WEAK    = 0x0001,
        OBJECT_LIFETIME_MASK    = 0x0001
    };
```

###### 单例模式

一个进程/线程只执行一个对象

```c

```

###### 桥接模式

比单例模式好理解些 就是通用定义私有成员 指针来实例化调用

```c

```

