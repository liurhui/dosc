注释错乱 UTF-8 改为GBK  或者相反。
#### keil5自动补全代码设置
1、Edit ->Configuration->Text Completion -> 勾选 Symbols after 
2、重启keil

#### keil安装编译器    问题集

![[MDK5打开MDK4报错1.png]]
![[MDK5打开MDK4报错2.png]]
![[MDK5打开MDK4报错3.png]]


#### keil编译 段错误 
Segmentation fault   （core dumped）  通常是 指针 去修改了不可改变的静态区常量
