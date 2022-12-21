 
---
创建日期:
  -  2022/11/14
---
### 忘记了就来这里看下
	gpio配置刚接触会迷糊。分为GPIO引脚宏、寄存器宏、中断宏、寄存器api、引脚配置api、中断api、和常用的配置值的宏。 宏一般是以所有gpio整体为思路，配合位移的写法就是配置某一个gpio。
#### 1、GPIO(配套示例GPIO_Input)
**注意：**
	ESP8266-12F 自身的那个小蓝色LED的阴极是接在 GPIO2， 阳极是接VCC 。它受内核管控，即使操作了也会被内核给覆盖亮灭。
##### 基础熟记
	1、两个库 //没有库去官方的SDK内去拷贝来。
	2、设置管脚是普通IO口，还是第二功能IO口。
	3、管脚模式，管脚电平。
```c
//两个库
#include "eagle_soc.h" 
#include  "gpio.h" 

//设置管脚是普通IO口，还是第二功能IO口
/*说明
	参数一表示 引脚， 参数二表示作为普通IO口/第二功能IO口
	参数一：
		1、如GPIO5  对应是MTDO_U。 如GPIO12  对应是MTDI_U
		2、最后加前缀 PERIPHS_IO_MUX_MTDO_U ，PERIPHS_IO_MUX_MTDI_U
	参数二：(有两种表达方式)
		1、计算，查表普通GPIO5的普通IO口是Function4，则 4-1 = 3 。-1是因为从Function1开始算 由单片机都是从0 开始计数所以-1。
		2、加前缀（官方提供的更方便的写法），GPIO5的普通IO口是  FUNC_GPIO5   (宏定义在eagle_soc.h) 
		
	//GPIO5管脚设置为普通IO口功能，查表是Function4，那么值需要-1就是3。
PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U,3);
	//GPIO5管脚设置为I2SO_BCK功能，查表是Function2,那么值需要-1就是1。
PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U,1);
	//GPIO12脚设置为普通IO口
PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12)

	
*/
PIN_FUNC_SELECT(PIN_NAME,FUNC)  //引脚名字，管脚的功能  

//管脚模式，管脚电平
/*
	GPIO_OUTPUT_SET  有时候会有bug会收不到数据
	固定写法 GPIO_ID_PIN(n)  n就是gpio引脚  
*/
GPIO_OUTPUT_SET(GPIO_ID_PIN(2),0) //  设置GPIO2为输出模式，输出低电平
```
如何查表 如GPIO15是MTDO_U ，看表找到MTDO_U的那一行 ，Function 就是引脚类型
	![[ESP8266的GPIO对应的名称.PNG]]
	![[ESP8266的GPIO对应的名称查表.PNG]]
	
##### GPIO接口
gpio_output_set (设置 GPIO 属性)
```c
//设置 GPIO 属性
void gpio_output_set(uint32	set_mask, uint32 clear_mask, uint32 enable_mask, uint32 disable_mask){
	/*
	uint32	set_mask：设置输出为⾼的位，1：输出⾼，0：不改变状态
	uint32	clear_mask：设置输出为低的位，1：输出低，0：不改变状态
	uint32	enable_mask：设置使能输出的位
	uint32	disable_mask：设置使能输⼊的位
	*/
}
//设置 GPIO12 输出⾼电平
gpio_output_set(BIT12,0,BIT12,0)
//设置 GPIO12 输出低电平
gpio_output_set(0,BIT12,BIT12,0)
//设置 GPIO12 输出⾼电平，GPIO13 输出低电平
gpio_output_set(BIT12,BIT13,BIT12|BIT13,0)
//设置 GPIO12 为输⼊
gpio_output_set(0,0,0,BIT12)

/*举例  即 设置 4种组合 00  01 10 11  
 1<<0|1<<4,0,1<<0|1<<4,0 =  00010001 ,0 ,00010001 ,0   pin0 pin4 输出高电平
*/
// pin0 pin4 输出高电平
#define I2C_MASTER_SDA_HIGH_SCL_HIGH()  \
    gpio_output_set(1<<I2C_MASTER_SDA_GPIO | 1<<I2C_MASTER_SCL_GPIO, 0, 1<<I2C_MASTER_SDA_GPIO | 1<<I2C_MASTER_SCL_GPIO, 0)

// pin0 输出高电平  ，pin4 输出低电平
#define I2C_MASTER_SDA_HIGH_SCL_LOW()  \
    gpio_output_set(1<<I2C_MASTER_SDA_GPIO, 1<<I2C_MASTER_SCL_GPIO, 1<<I2C_MASTER_SDA_GPIO | 1<<I2C_MASTER_SCL_GPIO, 0)

// pin0 输出低电平  ，pin4 输出高电平
#define I2C_MASTER_SDA_LOW_SCL_HIGH()  \
    gpio_output_set(1<<I2C_MASTER_SCL_GPIO, 1<<I2C_MASTER_SDA_GPIO, 1<<I2C_MASTER_SDA_GPIO | 1<<I2C_MASTER_SCL_GPIO, 0)

// pin0 pin4 输出低电平
#define I2C_MASTER_SDA_LOW_SCL_LOW()  \
    gpio_output_set(0, 1<<I2C_MASTER_SDA_GPIO | 1<<I2C_MASTER_SCL_GPIO, 1<<I2C_MASTER_SDA_GPIO | 1<<I2C_MASTER_SCL_GPIO, 0)

```
##### GPIO相关寄存器
一、寄存器读写函数
```c
//GPIO口寄存器的读/写 函数，参数根据业务寄存器。  
gpio_status= GPIO_REG_READ(GPIO_STATUS_ADDRESS); //先从外部拿到数据
GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status); //再修改寄存器
```
二、GPIO 输出寄存器 
```c
GPIO_ENABLE_W1TS //输出使能寄存器 
GPIO_ENABLE_W1TC //输出禁用寄存器 
GPIO_ENABLE  //输出使能状态寄存器
GPIO_OUT_W1TC //输出低电平寄存器 
GPIO_OUT_W1TS //输出高电平寄存器 
GPIO_OUT  // 输出状态寄存器  
```
三、GPIO 输入寄存器
```c
GPIO_IN //输入状态寄存器
```
四、GPIO 中断寄存器
```c
GPIO_PIN12 //中断类型寄存器(中断禁用，上升沿触发，下降沿触发，双沿触发，低电平，高电平)
GPIO_STATUS //中断状态寄存器
GPIO_STATUS_W1TC //清中断寄存器

```
五、GPIO16(XPD_DCDC) 不属于通用GPIO模块，属于RTC模块
```c
	 //可以用来在深度睡眠时候唤醒整个芯片，可以配置为输入或者输出模式，但无法触发 IO 中断。使用接口如下：

gpio16_output_conf(void){
	//将 GPIO16 配置为输出模式
}; 

gpio16_output_set(uint8 value){
	//从 GPIO16 输出高电平/低电平，需要先配置为输出模式
}; 

gpio16_input_conf(void){
	//将 GPIO16 的输入电平状态，需要先配置为输入模式
};
gpio16_input_get(void){
	 //读取 GPIO16 的输入电平状态，需要先配置为输入模式。
};
```
**以配置GPIO12 寄存器为示例**
	1、GPIO12 为普通IO口
	2、GPIO12 输出高电平
	3、使能 GPIO12上拉
	4、获取GPIO12管脚的电平状态
```c
/*
本质上是对PERIPHS_IO_MUX_MTDI_U寄存器的第4位和第5位，置1。
*/
PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12); //GPIO12 为普通IO口

/*
本质上是对GPIO_ENABLE_W1TS 的寄存器第12位写1，表示使能gpio12输出功能。
本质上是对GPIO_OUT_W1TS 的寄存器第12位写1，表示将gpio12输出为高电平。
*/
GPIO_OUTPUT_SET(GPIO_ID_PIN(12), 1); //GPIO12 输出高电平

/*
本质上是对PERIPHS_IO_MUX_MTDI_U 的第7位写1，表示使能gpio12的上拉功能
*/
PIN_PULLUP_EN(PERIPHS_IO_MUX_MTDI_U); //使能 GPIO12上拉

PIN_PULLUP_DIS(PERIPHS_IO_MUX_MTDI_U); //关闭 GPIO12的上拉

PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);//GPIO12 为普通IO口
GPIO_DIS_OUTPUT(GPIO_ID_PIN(12));//配置 GPIO12 为输入模式


//本质上是获取 GPIO_IN 寄存器第 12 位的状态 ,前提是需要使能为输入模式，状态才能获取到
//如果level 为1 是高电平， 0 是低电平
Uint8 level = 0;
level = GPIO_INPUT_GET(GPIO_ID_PIN(12));//获取GPIO12管脚的电平状态

```

##### 初始化GPIO示例
```c
#include "eagle_soc.h"
#include  "gpio.h"
//配置管脚
PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);

//禁止管脚输出
GPIO_DIS_OUTPUT(GPIO_ID_PIN(12));

//禁止内部上拉
PIN_PULLUP_DIS(PERIPHS_IO_MUX_GPIO2);
//使能内部上拉
PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO2);

//读取管脚电平状态
GPIO_INPUT_GET(GPIO_ID_PIN(12));
//输出管脚电平状态
GPIO_OUTPUT_SET(GPIO_ID_PIN(12), 0);

//喂狗
system_soft_wait_feed(); 
```
外设初始化示例（封装初始化写法）
```c
driver_lib/driver/Peripherals.c
//LED GPIO初始化
void LED_GPIO_Init (void){
PIN_FUNC_SELECT (PERIPHS_IO_MUX_MTDO_U, FUNC_GPIO15) ; //设置GPIO15管脚的功能GPIO
GPIO_OUTPUT_SET (GPIO_ID_PIN (15), 0);//设置GPIO为输出模式 设置GPIO输出电平为高电平
}

//蜂鸣器GPIO初始化
void FM_GPIO_Init (void){
PIN_FUNC_SELECT (PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12); //设置GPIO15管脚的功能GPIO
GPIO_OUTPUT_SET (GPIO_ID_PIN (12), 0);//设置GPIO为输出模式设置GPIO输出电平为高电平
}

//继电器GPIO初始化
void RELAY_GPIO_Init (void){
PIN_FUNC_SELECT (PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13) ; //设置GPIO15管脚的功能GPIO
GPIO_OUTPUT_SET (GPIO_ID_PIN (13), 0) ;//设置GPIO为输出模式设置GPIO输出电平为高电平
}
```
调用示例（main.c调用）
```c
void ICACHE_FLASH ATTR user_init (void)
{
	LED_GPIO_Init (); //LED GPIO引脚初始化
	FM_GPIO_Init (); //蜂鸣器GPIO初始化
	RELAY_GPIO_Init(); //继电器GPIO初始化
	while (1)
		{
			system_soft_wdt_feed();//喂狗
			LED_ON();
			FM_ON();
			RELAY_ON();
			delay_ms (1000) ;
			system_soft_wdt_feed (); //喂狗
			LED_OFF();
			FM_OFF();
			RELAY_OFF();
			delay_ms (1000);
		}
}
```



#### 3、GPIO中断(配套示例GPIO_EXIT在GPIO配置后配置GPIO中断)
**注意：**
	只有输入中断，没有输出中断。
	在中断服务函数内，不应该去写阻塞的逻辑（如延时）。
**参考文档：（p63）**
	手把手教你学ESP8266 NONOSDK开发指南——樱桃丸子单片机技术支持.pdf	
##### 基础熟记
	1、关闭 GPIO 中断
	2、配置 GPIO 的中断触发方式，该结构体在 gpio.h 中声明
	3、注册中断处理函数
	4、打开 GPIO 中断
	5、读取 GPIO 中断标志位
	6、清除 GPIO 中断标志位
```c
//关闭 GPIO 中断
ETS_GPIO_INTR_DISABLE()

//配置 GPIO 的中断触发方式，该结构体在 gpio.h 中声明
void gpio_pin_intr_state_set( uint32 i, GPIO_INT_TYPE intr_state){
	//uint32 i: GPIO 引脚 ID
	/*
		typedef enum{
			GPIO_PIN_INTR_DISABLE= 0,//禁止中断
			GPIO_PIN_INTR_POSEDGE= 1,//上升沿触发
			GPIO_PIN_INTR_NEGEDGE= 2,//下降沿触发
			GPIO_PIN_INTR_ANYEDGE= 3,//双边沿触发
			GPIO_PIN_INTR_LOLEVEL= 4,//低电平触发
			GPIO_PIN_INTR_HILEVEL= 5//高电平触发
		} GPIO_INT_TYPE;
	*/
}
//例子：配置 GPIO14 引脚为下降沿触发。
gpio_pin_intr_state_set(GPIO_ID_PIN(14)，GPIO_PIN_INTR_NEGEDGE);

//注册中断处理函数
ETS_GPIO_INTR_ATTACH(func, arg){
	//Func:中断服务函数函数名
	//arg:传入的参数
}

//打开 GPIO 中断
ETS_GPIO_INTR_ENABLE()

//读取 GPIO 中断标志位
uint32 gpio_status; //用于存中断标志位，为了清除时候用
gpio_status= GPIO_REG_READ(GPIO_STATUS_ADDRESS);// GPIO_STATUS_ADDRESS是 整个gpio口的状态寄存器

//清除 GPIO 中断标志位
GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status);//清除中断标志位
```

##### GPIO中断示例(如GPIO5作为key,搭配个中断作为自动触发逻辑)
	这里以key.c 为demo，123是必须要的，34的内容根据实际业务去写，但基本有模板。 
	1、先初始化用作key的GPIO
	2、去初始化配置搭配的key的中断
	3、去定义key触发中断时的中断服务函数
	4、定义（封装起来复用）一些检测key的GPIO的一些逻辑代码
```c
#include "./driver/key.h"
#include "gpio.h"
#include <eagle_soc.h>
#include "./driver/Peripherals.h"

void ICACHE_FLASH_ATTR KEY_GPIO_Init(void){  //按键GPIO初始化
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U,FUNC_GPIO5);//设置GPIO5引脚的功能为GPIO
    GPIO_DIS_OUTPUT(GPIO_ID_PIN(5));  //设置GPIO为输入模式 禁止GPIO输出
    PIN_PULLUP_DIS(PERIPHS_IO_MUX_GPIO5_U); //禁止内部上拉
}
```

```c
//GPIO外部中断初始化
void ICACHE_FLASH_ATTR GPIO_EXIT_Init(void){
    KEY_GPIO_Init();  //配置相关GPIO为GPIO输入模式
    ETS_GPIO_INTR_DISABLE(); //关闭GPIO中断 
    gpio_pin_intr_state_set(GPIO_ID_PIN(5), GPIO_PIN_INTR_NEGEDGE);  //配置GPIO触发引脚5和触发下降沿模式
    ETS_GPIO_INTR_ATTACH((ets_isr_t)GPIO_EXIT_Interrupt, NULL); //注册中断服务函数 GPIO_EXIT_Interrupt 函数名 没有传入参数为NULL
    ETS_GPIO_INTR_ENABLE(); //中断使能
}
```

```c
/*************************************************************************
 * FunctionName : GPIO外部中断中断服务函数
 * Description  : 主要是做按键检测到电平变化则认为是按下或松开按键，按下led亮松开灭。(之前demo是不用外部中断检测电平变化，是直接在main进行检测GPIO口高低电平，在单片机开发中应该用外部中断检测电平变化替代GPIO高低电平变化检测思路，因为存在bug单片机多少都会漏检测到的bug缺陷可能是库函数问题)
*************************************************************************/ 
void GPIO_EXIT_Interrupt(void){
    uint32 gpio_status;  //用于存中断标志位，为了清除时候用
    static uint8_t LED_Flag=0;
    gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);   //读取中断状态寄存器的值  整个GPIO口的状态寄存器拿到了去查pin5
    /*
    因为是设置的pin5脚也就是中断5所以左移5到指定的bit位置
	   如: 12个引脚就有 12bit pin5就是移到5bit位置(单片机通用知识)
    */
	 if((gpio_status&(1<<5))) {    //判断是哪一个GPIO引起的中断
        os_delay_us(4000);      //软件消抖
        if(GPIO_INPUT_GET(GPIO_ID_PIN(5))==0){
            LED_Flag=!LED_Flag; //切换led灯亮灭
            if(LED_Flag==0){
                LED_ON();
            }else{
                LED_OFF();
            } //LED_Flag==0
        } //GPIO_INPUT_GET(GPIO_ID_PIN(5))==0
    } //(gpio_status&(1<<5))
    GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status);  //清除中断
} //GPIO_EXIT_Interrupt
```

```c
//按键扫描成函数
//参数mode：0：不支持连续按键      1：支持连续按键
//返回1：按键被按下 返回0：按键不被按下
uint8_t ICACHE_FLASH_ATTR Key_Scan(uint8_t mode)
{
    static uint8_t key_flag=0;
    if(mode==1)     //支持连续按键
        key_flag=0;
    if((KEY_STATUS==0&&key_flag==0))
    {
        os_delay_us(5000);  //软件消抖
        if(KEY_STATUS==0 && key_flag==0)
        {
            key_flag=1;
            return KEY_ON;
        }
    }
    else if(KEY_STATUS==1)
    {
       key_flag=0;
    }
    return KEY_OFF;
}
```








