argc是命令行总的参数个数
argv[]是argc个参数，其中第0个参数是程序的全名，以后的参数
命令行后面跟的用户输入的参数，比如：
int main(int argc, char* argv[])
{
int i;
for (i = 0; i

这个赋值过程是编译器完成的，我们只需要读出数据就可以了。
int main( int argc , char *argv[] , char *envp[] )
main()函数一般用int或者void形的。我比较喜欢用int型定义main。因为在结束的时候可以返回给操作系统一个值以表示执行情况。

int argc
这个东东用来表示你在命令行下输入命令的时候，一共有多少个参数。比方说你的程序编译后，可执行文件是test.exe
D:\tc2>test
这个时候，argc的值是1
但是
D:\tc2>test.exe myarg1 myarg2
的话，argc的值是3。也就是 命令名 加上两个参数，一共三个参数

char *argv[]
这个东东用来取得你所输入的参数
D:\tc2>test
这个时候，argc的值是1，argv[0]的值是 “test”
D:\tc2>test myarg1 myarg2
这个时候，argc的值是3，argc[0]的值是”test”，argc[1]的值是”myarg1”，argc[2]的值是”myarg2”。
这个东东一般用来为程序提供非常重要的信息，如：数据文件名，等等。
如：copy a.c b.txt
这个时候，a.c和b.txt就是所谓的“非常重要的信息”。不指定这两个文件，你没法进行拷贝。
当你的程序用到argc和argv这两个参数的时候，可以简单地通过判断argc的值，来看看程序的参数是否符合要求

char *envp[]
这个东东相对来说用得比较少。它是用来取得系统的环境变量的。
如：在DOS下，有一个PATH变量。当你在DOS提示符下输入一个命令（当然，这个命令不是dir一类的内部命令）的时候，DOS会首先在当前目录下找这个命令的执行文件。如果找不到，则到PATH定义的路径下去找，找到则执行，找不到返回Bad command or file name
在DOS命令提示符下键入set可查看系统的环境变量
同样，在UNIX或者LINUX下，也有系统环境变量，而且用得比DOS要多。如常用的PATH,PATH,USER,HOME等等。envp保存所有的环境变量。其格式为（UNIX下）PATH=/usr/bin;/local/bin;HOME=/home/shuui即：环境变量名=值DOS下大概也一样。环境变量一般用来为程序提供附加信息。如，你做了一个显示文本的内容的程序。你想控制其一行中显示的字符的个数。你可以自己定义一个环境变量（UNIX下）HOME等等。envp保存所有的环境变量。其格式为（UNIX下）PATH=/usr/bin;/local/bin;HOME=/home/shuui即：环境变量名=值DOS下大概也一样。环境变量一般用来为程序提供附加信息。如，你做了一个显示文本的内容的程序。你想控制其一行中显示的字符的个数。你可以自己定义一个环境变量（UNIX下）NUMBER
10
然后你可以在程序中读入这个环境变量。然后根据其值决定一行输出多少个字符。这样，如果你不修改环境变量的话，你每次执行这个程序，一行中显示的字符数都是不一样的
下面是一个例子程序

#include

命令行参数啊。argc 是参数的个数，argv[]是参数，argv[0]是文件名，argv[1]是第一个参数…
如你得exe文件名是:myprog.exe，那么
myprog 12 22 32
则argv[0]=”myprog”，argv[1]=”12”，argv[2]=”22”…

exit()是程序退出时的返回码。可以用其他程序接收，判断是否正常退出。如exit(-1)认为异常退出。
————————————————
版权声明：本文为CSDN博主「mengyandelove」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/mengyandelove/article/details/82285504