### IPC  进程间通信

#### pipe函数   只能一边读一边写   对讲机功能
```cpp
int pipe(int pipdefd[2]);
:pipefd 读写文件描述符  ，0 读  1写
:返回值 失败 -1    成功0
/*需要去注意关闭读和写*/ 
  1、使用进程fork函数
    子进程
    		write(fd[1],"hello",5);  
    父进程
        	int ret = read(fd[0],buf,sizeof(buf));
总结：父进程的read读函数会阻塞等待 子进程的write写函数。所以子进程sleep多久 父进程等多久。
```

#### 使用dup2重定向
```cpp
使用pipe管道 执行命令   ps -aux|grep bash
    
    pipe创建两个描述符 pipe(fd[2]);
	子进程
        1、dup2重定向
        2、execlp 执行命令 execlp("ps","ps","aux",NULL);
    父进程
        1、dup2重定向
        2、execlp  执行命令 execlp("grep","grep","bash",NULL);
        
  注意：  close(fd[0]); 关闭子进程读端   原因：子进程作为输入写到管道
      	 close(fd[1]); 关闭父进程写端   原因：父进程作为输出读取管道		
        
  1、 grep命令 当 grep  hello   会阻塞等待 只有输入hello  它就输出hello 可以看成它等待你的输入 它就输出  利用dup2重定向输入口到管道的输入端    
```

```cpp
读管道：

写端全部关闭 -- read读到0，相当于读到文件末尾
写端没有全部关闭
有数据 -- read 读到数据
没有数据 -- read 阻塞 fcntl函数可以更改非阻塞

写管道：

读端全部关闭 ---- ？出错，产生一个信号SIGPIPE，程序直接异常终止
读端未全部关闭
管道已满 -- write阻塞        --如果要显示现象，读端一直不读，写端狂写。
管道未满 -- write正常写入
```

#### FIFO函数   没关联的父子进程通信
```cpp
需要创建一个文件，利用文件来实现管道的效果
     1、 创建命令  mkfifo 文件名  例： mkfifo myfifo
  		 或者函数 int mkfifo(const char *pathname,  mode_t mode); 
```

```cpp
//-----------------大致的思路
写文件04_fifo_w.c
1、int fd = open(argv[1],O_WRONLY);   //argv[1] ====  ./04_fifo_w.c   myfifo
2、 while循环取读buf的内容


读文件04_fifo_r.c
1、int fd = open(argv[1],O_RDONLY);   //argv[1] ====  ./04_fifo_r.c   myfifo
2、while循环写入buf的内容
```

#### MMAP函数   不使用read和write函数   利用内存映射区获取    利用文件通信
```c
头文件#include<unistd.h>     文件 05_mmap.c
原型：  创建映射区  
	void *mmap(void *adrr, size_t length, int prot, int flags, int fd, off_t offset); 
返回值：成功：返回创建的映射区首地址   失败：MAP_FAILED宏
参数：	
	addr: 	 建立映射区的首地址，由Linux内核指定。使用时，直接传递NULL
	length： 欲创建映射区的大小
	prot：	映射区权限PROT_READ、PROT_WRITE、PROT_READ|PROT_WRITE
        	 还有两个可执行、不可访问不常用到。
	flags：	标志位参数(常用于设定更新物理区域、设置共享、创建匿名映射区)
		  	MAP_SHARED: 共享的   会将映射区所做的操作反映到物理设备（磁盘）上。
		  	MAP_PRIVATE: 私有的  映射区所做的修改不会反映到物理设备。
	fd： 	用来建立映射区的文件描述符
	offset： 	映射文件的偏移(4k的整数倍)  4096

原型：  释放映射区
  int munmap(void *adrr, size_t length); 
返回值：
参数：	
	addr: 	 传mmap的返回值
	length： mmap创建的长度
```

##### 1、命名映射 利用文件 实现父子进程通信

```c
int *mem = mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);  
//int *mem = mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
但是有个问题是创建出来的mem.txt文件我们用完需要进行删除关闭。unlik 、close那么使用匿名映射就可以解决这个繁琐的过程。在mmap函数里加一个参数 MAP_ANONYMOUS 或者缩写MAP_ANON 

 1、子进程 往*mem 写内容   
 2、父进程 往*mem 写内容   
 3、打印子进程 得知 获取*mem的值  跟 父进程是一致的。实现映射的方式 共同读写同一个文件
```

##### 2、匿名映射 不利用文件 实现父子进程通信     

```cpp
 	 int *mem = mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANON,-1,0);
注意点：有可能有的unix是没有这两个宏，使用 ls /dev/zero文件去映射，或者 /dev/null 文件去映射
    null主要是作为报错或者异常的日志重定向到这个文件，使用方法 也是open

关键词：参数宏    缩写MAP_ANON     或者     MAP_ANONYMOUS       
```

##### 3、测试 两文件 一读一写 

```cpp
文件： 08_mmap_w.c   08_mmap_r.c
总结：与fifo不同 这里是映射内存所以多次运行读文件同时读 的内容是重复的。且内容不会消失。而fifo读完就没了使用的管道的效果  
```



作业 

1、通过命名管道传输数据，进程A和进程B，进程A将一个文件（MP3）发送给进程B

2、实现多进程拷贝文件

​		

1000+34      每个进程206个  1034/5=206   发现这样总的大小小了  206*5=1030        

所以把多余的内容放在最后一个进程要多一点  206+(1034-5 *206)

```c
memcpy(首地址,源地址,拷贝的总大小)
memcpy(pdst+i*cpsize,psrc+i*cpsize,cpsize+mod);   第五个进程   
else
memcpy(pdst+i*cpsize,psrc+i*cpsize,cpsize);        前四个进程
```

