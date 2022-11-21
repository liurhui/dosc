##### 区别

如果需要用相同的方式处理信号多次出现，且信号容易多次出现，则建议使用sigaction函数；

若可以保证信号长时间内只出现并只需要处理一次，或者周期性循环处理同一个信号，则可以使用signal函数。

尽量使用sigaction  ，因为signal可能跨平台不一样内容。





如果 去利用SIGCHLD信号回收子进程处理信号

**分情况去处理**

1. 子进程 不睡眠会出现一个僵死 信号来的太快了捕获只处理一次。 
2. 父进程的注册必须在 子进程死亡之前 否则无法回收

```c
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
void catch_sig(int num) {  
   // pid_t wpid=waitpid(-1,NULL,WNOHANG);
    pid_t wpid；
        while((wpid=waitpid(-1,NULL,WNOHANG)>0){
            printf("wait child %d ok\n",wpid);
        }
/*    if(wpid>0)
    {
        printf("wait child %d ok\n",wpid);
    }
 */   
}
int main()
{
    int i=0;
    pid_t pid;
    /*
 	sigset_t myset,oldset; 
    sigemptyset(&myset);//先清空
    sigaddset(&myset,SIGCHLD);  //
    sigprocmask(SIG_BLOCK,&myset,&oldset);
    */
    for(i=0;i<10;i++){
        pid=fork();
        if(pid==0){
            break;
    }
}
    if(i==10){
      /*parent*/  
      /*  父进程的注册必须在 子进程死亡之前 否则无法回收 所以这里不能加sleep
      	或者创建子进程之前屏蔽SIGCHLD信号 就是手动加一个信号集 去阻塞一下，然后利用 oldset 保留现场
      //sleep(3);	
      */
	  struct sigaction act;
  	  act.as_flags=0;  
   	  act.sa_handler=catch_sig;   
       
      sigaction(SIGCHLD,&act,NULL); 
     /*解除阻塞
   		 sigprocmask(SIG_BLOCK,&oldset,NULL);  
     */   
		while(1){    	 
     		sleep(1); 
        }
	else if(i<10){
      /*child*/  
          printf("I am %d child,pid =%d\n",i,getpid());
          sleep(i);// 不睡眠会出现一个僵死 信号来的太快了捕获只处理一次。 如果不写那么捕获信号做改进
    }
    return0;
}             
```





​	