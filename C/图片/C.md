**视频地址  网易云课堂  发布者 ：阿发你好    课时58**/ 
#####    数据类型

整数  char int  shrot  long   longlong 

浮点数 double  float  long    double

逻辑 bool 

指针          

 ```C
#include<stddef.h> //计算偏移量 头文件 
struct Person 
{
    int a;
    char b ;
    char buf[64];
    int d;
} 
void test 02()
{
    struct Person p ={ 10,'a',"hello world!",100};
}             //目的取出 d  通过 首地址+偏移量 方式   
printf("d =%d\n",*(int*)((char*)&p+offsetof(struct Person,d)));    
//   （强制转换成int*型4个字节的读取d）（强制转化换成char*一个字节一个字节去读取）&p是首地址           +封装好的库函数的计算偏移量（参数一类型，参数二要求的偏移量的变量）;
 ```

自定义类型 

##### 类型不同

%d %ld  %if     int  long  double  

范围  char<short<int<float < double
```plaintext

```
**Bit 位或比特     byte 字节   1字节=8位   两个字节=1个汉字 =16位=一个字**

sizeof 一个 字节8比特     例如int 是 8比特*4字节=32位

32位 和64位   long是 4字节   8字节

char 255   %d    输出为 -1

#### 整数范围

char 1字节 -128-127     short 2字节 -32768-32767   -2^ (32-1) ——  2^(32-1)-1

![[整数范围.png]]
![[整数越界.png]]

![[int类型最大数.png]]

![[检测int最大数代码.png]]


%d  %u  %ld  %lu         int      unsigned      long long      unsigned   long long  

scanf 如果 是%d %d  第二个%d后面的空格 则 输入时要检测 到空格或则任意字符 才执行 但 不会被读取 （回车不行）
![[允许字符.png]]
尺寸转换

英尺 =12英寸  =0.3048米 

-1  %u   =2^(32)  -1

0开头的是 8进制      0x开头的是  十六进制     %o   %x  分别是输出    8进制      十六进制

#### 浮点类型
![[浮点类型.png]]


包含 0       inf  无穷大  nan 无效的数字     

%e  输出 **科学计数法**   
![[科学计数法.png]]


%.3f   输出3位有效数    进行四舍五入    



#### 字符类型
 1   %c  1    %d   49             char  1     %d 1         char 1  %d  49  

 char  类型不能直接scanf读取%d的类型 需要 先给int再赋值给char

char   scanf %d             %d  输出整数值的是字面值     %c是字符输出所对应的ASCII码

 char   sacnf%c   1       %d    49     %c   1   

char接收到的是 字符 输出 %c就是字符     接收 整数值  输出%c就是对应的ASCII的字符  

 ***a+'a'-A'   把一个大写字母变成小写字母***

 ***a+'A'-'a'   把一个小写字母变成大写字母***

**用scanf输入的  %d  %c   则输出   整数后面的空格读走     没有空格则结束**

​						  **%d%c   则输出 不把空格读走  把空格留给%c**

#### 逃逸字符
![[逃逸字符.png]]

&hd     short

!>&&>||

man   函数      //查找函数属于哪一个头文件 在unix 系统下   windos 百度查

使用变量 来确定数组的长度时不能同时对数组初始化


%p是输出地址     以十六进制且 是以0x开头

强制转换类型 长度 在32位和64位是不一样的

先定义的 放在高地址   后定义的放在低地址 

&a == a  ==a[0]  都表示地址是同一个 

int * p       如果 p 是int *类型  &p是int **类型

在函数的参数列表中  int  a[ ]  等效于  int  *a    其实是指针    可以直接修改数组中的值
![[作为函数的数组参数都是指针.png]]
![[函数指针参数.png]]


 **p是指向min的地址   *p是min的值   p[0]把p指向的地方 当作数组 但是 min是变量 但这时候得把min看作只有一个数的数组 int min[1]  而这里的值就是 min的值 也是 2**
 ![[指针p和p数组的意思.png]]


**int a[] == int *const  a   //创建的时候就是不能被改变不能  int b[ ]= a;  a是数组**
![[数组变量.png]]
```c 
int * const q =&i ;//q是const    所指的地址是不能被修改
*q=26;  //是将i地址的值修改 是可以的  
q++;   //试图将地址+1 这样的不允许的 

const int*p =&i;
*p=26; //报错 原因是*p是cosnt     p指针是地址  地址可以变  不能变值
i=26;  //  可以
p=&j;  //也可以 

int i;
const int* p1 =&i; //  cosnt  控制了*  不能解值 就是不能改值
int cosnt* p2=&i; 
int* cosnt p3=&i;   //cosnt  只控制了 p3指针  是地址   就是不能改地址 

数组的指针减法  %d输出的话是 = 十六进制地址相减后/4
    *p++  是先取出p所指的那个数据来，再p移到下一个位置去 //常用于遍历数组
```
![[转换const.png]]


字符串连接 用   \       作用域第二行顶格算起

不同字符串当值相同时候  使用的地址是同一块空间 

用指针 来存放字符串    存放的地址是放在代码段 空间小且只可读  

用数组  来存放字符串   存放的地址的接下来的空间里
![[指针还是数组.png]]


 %s  输出一串不带空格的字符串    到空格就结束  把空格看成分割符    但是%s无法知道要读入的长度  

7s%   检测不多于7个字符且连续的字符  不带空格 

###### char*是定义了一个字符串类型的变量string   但是要初始化

![[char指针错误.png]]

![[空字符串.png]]

#### char   a[] [10]   数组   每一个单元有10个字符  且\0包含在内 不能超过10个
![[char数组.png]]
putchar  //你输入什么回车它跟着显示什么

int putchar(int c);   //返回写了几个字符int类型，EOF(-1)表示写失败     

getchar     //  

int  getchar(void);    //返回类型是int 是为了返回EOF(-1)

windows——> Ctrl-Z              Unix——> Ctrl-D   //结束退出输入模式
![[%n.png]]


### 字符串的知识点   string.h

strlen  是不计算\0     sizeof 计算\0

strcmp  比较两个字符串 输出不同的字符相减的差
![[strcmp.png]]
strcpy    拷贝       如果存在 参数二 拷贝后存在占据覆盖参数二的内存空间则报错//c99  resrict 为不重叠参数

![[strcpy.png]]

```c
char* ret =dst;      //指针形式的strcpy            

while(*src !=‘\0'*){        //等效成 while(*src){   *dst++=*src++;  }

*dst=*stc;					//  再进化成   while(*dst++=*src++) ;

dst++;

src++;

}
*dst='\0';
return ret;           
```

strcat  链接     注意存放的空间     为了空间安全  使用C99带n的安全版本的函数
![[str安全版本.png]]
strncmp  的 参数size_t n  是要比较 前多少个字符相同
![[strstr字符串查找字符串.png]]
![[strchr的使用.png]]


strcasestr 忽略大小写对比

#### 枚举    是int类型   比宏 macro 好

enum          最后一个可以看成之前三个枚举量的统计 用于自动计数的枚举套路  语句
![[自动计数的枚举.png]]


这样遍历所有的枚举量或者需要建立一个用枚举量做下标的数组的时候就很方便了

i%  输出结构的成员值

类型定义typedef  

%02hhX     // hh 标示以一个字节char类型打印值。类似于h标示以一个short类型打印值一样。 

  hh和X组合表示 以一个char类型打印一个整数，将四个字节的整数截断成一个字节打印出来 



联合  union    //用于获得内部的字节



0x04D2       输出  D2  04   00   00



 #define 多行宏定义时 不在同一行 使用   \ 来链接 

```
#define _DEBUG_
_LINE_    源代码文件的所在行行号
_FILE_      源代码的文件名
_DATE_    编译的时候的日期时间
_TIME_
_STDC_
```

宏函数   

gcc     文件.c         --save-temps         //

tail    文件.c    // 显示源代码

带参数的宏 每个地方都要带括号  因为是按照优先级 来运行
![[带参数的宏定义分号.png]]
inline函数 可以 了解下

extern 是多文件情况下     变量的声明 

![[定义和声明.png]]



#ifndef      //用于系统检测避免 宏定义重复调用

#endif

​     #pragma once    //是vsstdio  自动加的

printf   输出格式语法      %【flags】【width】【.prec】【hIL】type
![[printf输出格式.png]]


%+-     一样左对齐再 值前面加个+号     
![[printf宽度.png]]


%9.2   输出包括整数部分、小数点和小数部分 共9位有效数   且小数为两位 不足 补空格

（”%*d“ ，替换的写在这，123 ）    这个星号是可以替换还成某个数字或者某个变量 
![[hlL.png]]


hh 输出一个字节整数    12345    的十六进制 0x3039       39  输出十进制 为57     

 ![[type.png]]

![[%n.png]]
![[scanf.png]]


*d%d   跳过输入的第一个字符
![[sacnf1.png]]


```c
Array array_create(int init_size); //创建
void array_free(Array  *a);         //回收
int array_size(const Array  *a);    //可用
int* a rray_at(Array  *a,int index);  //获得
void array_inflate(Array  *a,int more_size); //扩展数组 
```

&a    //取a的地址 十六进制  0012FF7C

(int)   &a   //把a的地址强制转换成十进制的整形    1245052

(int&) a  不经过转换  直接得到a地址的值

### 强制转换

```
代码： 

   int n;
    int m = 5;
    int *p = &m;
    int *a = (int *)(p + 5);
```

 int *a = (int *)(p + 5);
p的值m的地址，5是整形的数据，在这个等式里，相当于偏移量；
p的地址：0x0017f858
m的地址：0x0017f864；参与运算的是m的地址，及p的值
环境是vs2013，一个int类型的4字节，4 * 5 = 20； 就是说偏移20个字节，转换成16进制，就是14； 64 + 14 = 78；就是说(p + 5)的地址是0x0017f878，同时在这个地址里有一个数值，如上：157000872   //  5
定义一个int类型的指针a，a的值是指向数值“157000872”的地址“0x0017f878” 

```c
int *a[] => (int *) a[]
定义a是一个数组，
每一个数组的元素是一个指针，指向一个整数
```



```c
int (*a)[]      (*a)是一个数组，数组的每一个元素都是一个整数，而a是指向这个数组的指针
```

int p=(int)&i;       十六进制强制转换成int    以int类型的十六进制输出

```
void f(int*p);  //在被调用的时候得到某个变量的地址   p是地址就是 i的地址 （可以看作p就是i 共同地址同值）
int i=0;										*p 是值  就是 i的值
f(&i);    //在函数里面可以通过这个指针访问外面的这个i     取i的地址为参数值

输出：   &i=0xbf17d70  
		p=0xbff17d70
```

 

### 链表    

  /资源**视频地址  网易云课堂  发布者 ：阿发你好    课时58**/ 

链表尾 为 NULL

链表头为第一个对象 

一个链表，当有N个对象串起来时，使用第一个对象来指代整个链表

###### 注意代码  参数列表     传入地址     就是 拿地址    Student类型 主要是内存空间大小要匹配 用结构类型

```c
Student* result=find(&ss[0],201503)  //ss[0]是链表头作为首地址传入   ，201503 是被查找的值
   Student 对象 
Stdent* find (Student* head,int id) //取出传入的值 ， 201503
{
    Student*p=head; // 把接受到的地址给 p   等效Student*p =&ss[0];
    while(p)
    {
        if (p->id==id)
            return p;
        p=p->next;
    }
    return NULL;
}
```

有头链表   用一个固定的头节点来指代整个链表，所有对象挂在这个头节点下面，而头节点本身不包含有效数据

无头链表  所有的节点都包含了有效数据

#### 添加对象

```c
void add(Student* obj)   //插入头部
{
    obj->next=m_head.next;//把原先链表头的节点 （原先链表头的节点是A）给obj做下一个节点obj就在他的上面
    m_head.next=obj;   //把obj挂在 头链表的下面
}
//链表中的对象由动态创建 

void add(Student* obj)   //插入尾部
{
	Student*p =&m_head;
	while(p->next)
        /*重点语句  节点交换*/
	p=p->next;   //找到最后一个对象一直循环这一句  直到检测到 next是空 
	p->next=obj;  //把obj挂在最后一个对象后面
	obj->next=NULL; //现在obj作为最后一个对象
}

```


![[有头节点插入节点.png]]


思路

 链表是结构类型的 存放内容都是对象，这些对象多为动态创建  

（动态创建的对象的生命期，自malloc之时生效，到free之后失效）

```c
Student*  obj = (Student*)malloc(sizeof(Student));//创建一个对象
obj->id =12; 
strcpy(obj->name,"X");
add(obj);  //add是插入头 还是尾  用上面的两个去获得
```

 

```c
/*有头链表的遍历*/
  
  void show_all()
  {
  	Student* p =m_head.next;   //将第一个节点给p 一直循环p如果是空也就是到了链尾 
  	while(p)
  	{
  		printf("ID:%d,,name:%s\n",p->id,p->name);
  		p=p->next; 
	  }
   } 
```

按顺序插入节点
![[排序节点.png]]


```C
 /*重点语句  节点交换*/    其中链表是结构类型的 内容是对象 obj和pre都是对象  拿对象的id比较大小
  如果obj大于 pre  则pre原来的指向下一个数的节点必须先挂给obj的节点 
obj->next =pre->next;
pre->nxet=obj;  //  把对象obj给 pre作为下一个节点的对象  
```

这个函数应该调用在 当创建一个动态空间后
![[排序插入链表举例.png]]
```C
int insert(Student* obj)   //  这里首先 是一个有头链表
{					 // 这里是有头节点 从第二个节点开始
Student* cur= m_head.next;//头节点的下一个节点就是第一个的值      	 给cur
Student* pre= &m_head;        //头节点的地址   				   给pre
    while(cur)
    {
        if(obj->id < cur->id)    
            break;
        pre=cur;    //这里是  第一个值已经比传入的值大 所以 第一个值要放到上一个节点里
        cur=cur->next; //下一个节点的值给当前结点
    }
    
    obj->next=pre->next;
    pre->next=obj;
    return 0;
}
```
![[初始化压栈.png]]
```C
	/*查找和删除节点*/ 
	void remove(int id)
	{
		Student*cur=m_head.nxet;
		Student*pre=&m_head;
		while(cur)
		{
			if(id==cur->id)    //如果id是相等的
			{
				pre->next=cur->next;   
				free(cur);
				break;
			}
			pre=cur;
			cur=cur->next;
		 } 
	 } 
```

尽量使用有头链表 的原因      （除非 循环队列 要用无头链表）
![[有头链表和无头链表.png]]

什么是堆  malloc 创建的内存空间块 ； 栈就是类型定义的都在栈

![[什么是堆和栈.png]]
栈     定义    实现先进后出的存储结构 

​		分类    静态栈  动态栈

​		算法     出栈     压栈

队列        先进先出

 
![[初始化压栈.png]]

数据域要变化链    指针域不变化     
![[栈变化.png]]


其中  几个比较重要的思路

初始化且 将Bottom设置为NULL  在调用中只变化Top不  Top可以看作是地址   将pNew结构放在Top的里面 
每次pNew变化就要去定义Top的地址跟随pNew



```c++
void init (PSTACK pS)
{
	pS->pTop = (PNODE)malloc(sizeof(NODE)) ;
	if(NULL== pS->pTop)   //先判断是否分配内存空间成功
	{
		printf("动态内存分配失败！\n");
		exit(-1);
	}  
	else
	{
		pS->pBottom = pS->pTop;    //将对象的 pTop和pBottom空间一样大
		pS->pTop->pNext = NULL;  //将第一个的Bottom初始化为空指针 可以看作是一个头链表为空
	} 
	
}

void  push(STACK pS,int val )
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));//创建一个结构 
	pNew->data = val;    //开始赋值给data
	pNew->pNext = pS->pTop;  //这里是 Bottom不变化 ,变动pTop，将
	pS->pTop = pNew;
	return;
}
```
![[创建栈.png]]


## 指针

**int*   char*    区别char  int      **

```c
char  a;
int   p;
int*  ai;
char* pi;
//这里以小端存储为例
  高字节放高字节 ，低字节放低字节
//那么 大端存储是什么
大端模式：低位字节存在高地址上，高位字节存在低地址上 
小端模式：高位字节存在高地址上，低位字节存在低地址上
linux,ARM中 默认小端 ， 注意 如果存入的值为十进制先转换为十六进制。 所有的都是以十六进制存储
/*       
		int  x= 367328153 //0x15E4FB99  
		int *y= &x;   //看X的地址 根据x地址 调试看寄存器 值是怎么存放的		

*/
        
a =0x12345678;   //长度为  1；	假设其内存地址为  &p=0xffee0933
p =0xabcdefdh;   //长度为  4；  假设其内存地址为  &p=0xffee0934
pi  ai  //长度32位时为 4， 64位时为 8
// 假设其内存地址为  &ai=0xffee0938     假设其内存地址为  &pi=0xffee093c 
char* pi=&p;   
printf("pi =%p\t",pi);  printf("*pi =0x%x\n", *pi)//则  pi 的地址是 0xffee0934    值0xdh
//当  pi=pi+1;
printf("pi =%p\t",pi);  printf("*pi =0x%x\n", *pi)//则  pi 的地址是 0xffee0935	 值0xef   
//当  pi=pi+1;
printf("pi =%p\t",pi);  printf("*pi =0x%x\n", *pi)//则  pi 的地址是 0xffee0936	 值0xcd
//当  pi=pi+1;
printf("pi =%p\t",pi);  printf("*pi =0x%x\n", *pi)//则  pi 的地址是 0xffee0937	 值0xab
```

**数组就不一样  从低地址往高地址存 **
![[C指针  数组的存储方式.png]]
**高级版深刻理解**
![[C指针  数组的存储方式1.png]]


s%  是直到遇到/0 ，结束输出  。期间会移动指针

c%  是只输出一个字符，即指针跳转后，不会去移动指针的操作。