#### 4、软件定时器(配套示例OS_Timer)
**目的：**
	替代延时代码更精准，但是定时器函数在执行过程，可能被其他中断或高优先级的给延迟。所以os_timer 接口其实也不那么精准。一定非要很精准就得用硬件中断定时器替代。
**注意：**
	1、一个定时器的 `os_timer_arm或os_timer_arm_us `不能重复调用。
	2、`os_timer_setfn` 必须在timer未使能的情况下调用。
##### 基础熟记
	1、头文件
	2、关闭软件定时器
	3、注册定时器回调函数
	4、使能毫秒定时器
```c
//头文件
#include  "./include/osapi.h"
os_timer_t os_timer_1; 
//关闭软件定时器
os_timer_disarm(&os_timer_1);  
//注册定时器回调函数
 os_timer_setfn(&os_timer_1,(os_timer_func_t*)OS_Timer_1_Cb,NULL);
//使能毫秒定时器
 os_timer_arm(&os_timer_1,ms,repeat_flag);
```
##### API 函数集合
调用顺序
```plaintext
1、os_timer_disarm
2、os_timer_setfn   //得在disarm 后， arm前
3、os_timer_arm 或 os_timer_arm_us
```
一、os_timer_arm （使能毫秒级定时器）
```c
void os_timer_arm (os_timer_t *ptimer,uint32_t milliseconds,bool repeat_flag){
	/*
		os_timer_t *ptimer：定时器结构体
		uint32_t milliseconds：定时时间，单位：ms
			如未调用 system_timer_reinit，可支持范围 5 ~ 0x68D7A3
			如调用了 system_timer_reinit，可支持范围 100 ~ 0x689D0
		bool repeat_flag: 0:不重复定时器 1:重复定时
	*/
}
```

二、os_timer_disarm（取消定时器定时）
```c
void os_timer_disarm (os_timer_t *ptimer){	
	//os_timer_t *ptimer：定时器结构
}
```
三、os_timer_setfn（设置定时器回调函数。使⽤定时器，必须设置回调函数。）
```c
void os_timer_setfn(os_timer_t *ptimer,os_timer_func_t *pfunction,void *parg){
	// os_timer_t *ptimer：定时器结构
	// os_timer_func_t *pfunction：定时器回调函数
	// void *parg：回调函数的参数
}
```

一、system_timer_reinit（重新初始化定时器，当需要使⽤微秒级定时器时调⽤）
```c
/*
	同时定义 USE_US_TIMER
	system_timer_reinit 在程序最开始调⽤，user_init 的第⼀句。
*/
void system_timer_reinit (void){

}
```
二、os_timer_arm_us （使能微秒级定时器）
```c
/* 
请定义 USE_US_TIMER，并在 user_init 起始第⼀句，先调⽤ system_timer_reinit。
最⾼精度为 500 μs。
*/
void os_timer_arm_us (os_timer_t *ptimer,uint32_t microseconds,bool repeat_flag){
	//os_timer_t *ptimer:定时器结构体
	//uint32_t microseconds：定时时间，单位 us，最小 0x64,最大 0xFFFFFFF
	//bool repeat_flag：是否重复定时，0：不重复定时，1：重复定时
}
```

##### 示例(原本GPIO中断低电平触发示例改为软件定时触发)
软件定时器初始化示例os_timer.c
```c 
#include "./driver/os_timer.h"

os_timer_t os_timer_1;  //实例化一个对象 os_timer_t 在SDK库头文件提供
//软件定时器1回调函数   
void ICACHE_FLASH_ATTR OS_Timer_1_Cb(void){
	//业务逻辑
	  ....
} 
  
//软件定时器配置初始化
void ICACHE_FLASH_ATTR OS_Timer_Init(uint32_t ms,bool repeat_flag){
    os_timer_disarm(&os_timer_1); //关闭软件定时器
    os_timer_setfn(&os_timer_1,(os_timer_func_t*)OS_Timer_1_Cb,NULL); //注册软件定时回调函数
    os_timer_arm(&os_timer_1,ms,repeat_flag); //打开软件定时器并设置定时时间以及是否重复
}
```
调用示例user_main.c
```c 
user_init(void){
	....
   OS_Timer_Init(500,1);  //软件定时器初始化
}
```

#### 5、硬件定时器(配套示例HW_Timer)
**注意：**
	1、使⽤ NMI 中断源，且为⾃动填装的定时器，调⽤ 毫秒定时函数 时参数 val 必
须⼤于 100。
	2、使⽤ NMI 中断源，那么该定时器将为最⾼优先级，可打断其他 ISR。
	3、使⽤ FRC1 中断源，那么该定时器⽆法打断其他 ISR。
	4、无法和PWM一起用，用的是同一组定时器
	5、回调函数不要加ICACHE_FLASH_ATTR 宏。
	6、如果用了wifi 睡眠模式 cpu 无法响应 NMI中断。
##### 基础熟记
	1、拷贝SDK-2.2.1\driver_lib\driver\的hw_timer.c文件非自己编写
	2、初始化硬件定时器
	3、注册定时器中断服务函数
	4、使能硬件中断定时器
```c
//初始化硬件定时器
hw_timer_init(NMI_SOURCE，1); //参数一可以写NMI_SOURCE 也可以简写1
//注册定时器中断服务函数
hw_timer_set_func(HW_Timer_Intrrupt);  //先定义好中断服务函数HW_Timer_Intrrupt
//使能硬件中断定时器 定时 500ms
hw_timer_arm(500000);
```
##### API 函数集合
一、hw_timer_init （初始化硬件 ISR 定时器）
```c
void hw_timer_init (FRC1_TIMER_SOURCE_TYPE source_type,u8 req){
	/*
	参数一：中断源 0： FRC1_SOURCE是FRC1 中断源  、1：NMI_SOURCE是NMI 中断源
	参数二：是否重装载  0不自动重装载、 1自动重装载
	*/
}
```

二、hw_timer_arm（使能硬件中断定时器）
```c
void hw_timer_arm (uint32 val)
/*
	参数是 定时时间
	情况一 NMI 自动重装载 ,取值范围100 - 0x199999μs(100us - 1,677,721us)
	情况二 FRC1 自动重装载 ,取值范围50-0x199999μs(50us-1,677,721us)
	情况三  非自动重装载模式，取值范围：10 - 0x199999μs
	
*/
```
三、hw_timer_set_func（设置定时器回调函数。使⽤定时器，必须设置回调函数。）
```c
void hw_timer_set_func (void (* user_hw_timer_cb_set)(void) ){
	//void (* user_hw_timer_cb_set)(void)：定时器回调函数（中断服务函数）
}
```

##### 示例()
软件定时器初始化示例hw_timer_driver.c
```c 
#include "./driver/hw_timer_driver.h" 
/*
 * 硬件定时器中断服务函数
 */
void HW_Timer_Intrrupt(void)
{
   //业务逻辑
   ....
}

/*
 * 函数名：硬件定时器初始化配置函数
 * 参数：us:定时时间    100us < us < 1677721us
 */
void ICACHE_FLASH_ATTR HW_Timer_Init(uint32_t us)
{
    if(us<100||us>1677721)
    {
        os_printf("us<100||us>1677721\r\n");
        return;
    }
    hw_timer_init(1,1);     //硬件定时器初始化 使用NMI中断源 重复定时
    hw_timer_set_func(HW_Timer_Intrrupt);   //注册硬件定时器中断服务函数
    hw_timer_arm(us);       //使能中断定时器并设置定时时间
    os_printf("HW_Timer OK!\r\n");
}
```
调用示例user_main.c
```c 
user_init(void){
	....
   HW_Timer_Init(500000); //硬件定时器初始化 定时周期500ms
}
```
