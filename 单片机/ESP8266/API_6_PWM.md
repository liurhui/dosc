#### 8、PWM(配套示例PWM) 
**了解：**
	控制彩灯、蜂鸣器和电机等设备。
	通过FRC1 是⼀个 23 bits 的硬件定时器。
	用NMI 中断更精准。
	最多8路PWM信号。
	`>14bit`分辨率，最小分辨率4ms
	⽆需配置寄存器，调⽤函数接⼝即可完成配置。
	通过 80MHZ，用16预分频，变成5MHZ，用FRC1 来产⽣粗调定时，最快可以到45ns。PWM 波信号周期为1000us-10000us，对应频率为 1kHz-100Hz 。
##### 基础熟记
	1、头文件pwm.h
	2、初始化 PWM 配置输出的 GPIO、周期、占空比
	3、PWM 开始输出
	4、设置占空比 (设置后需要调用 pwm_start();才有效)
	5、设置周期 (设置后需要调用 pwm_start();才有效)
	6、获取某路通道反馈实际的占空比
	7、获取反馈实际周期
	8、查询 PWM 的版本信息
```c
#include "pwm.h"
//初始化 PWM 配置输出的 GPIO、周期、占空比
struct pwm_param PWM_Param_Struct={1000,1000,{0}};
pwm_init(PWM_Param_Struct.period,PWM_Param_Struct.duty,1,PWM_IO_Info);

//PWM 开始输出
//每一次更改了 PWM 的设置的时候都需要调用此函数，因为此函数内部进行了相应的计算。
pwm_start();
 
//设置占空比 
/*
duty 不是实际的高电平时间
duty最大取值 =  Period(频率) * 1000 /45

如输出1khz 的pwm波 求出 取值范围和 占空比？ 

duty取值范围是 1000* 1000 /45 =22222.222  范围也就是 0-22222 
占空比： 
(实际duty)/(duty最大值) = duty /(Period *1000/45)=duty*45/Period/1000
*/
pwm_set_duty(100,0); //设置通道 0 的 duty 为 100

//设置周期 
/*
	单位 us。稳定的 PWM 输出周期范围1000us-10000us
*/
pwm_set_period(1000);//设置 PWM 周期为 1000


//获取某路通道反馈实际的占空比
/*经过计算，实际占空比= (duty*45)/ (period*1000)*/
uint8 pwm_get_duty(uint8 channel)
//获取反馈实际周期
uint32 pwm_get_period(void)
//查询 PWM 的版本信息
uint32 pwm_get_period(void)
```
##### API 函数集合
一、pwm_init（初始化 PWM，包括 GPIO 选择，周期和占空⽐。⽬前仅⽀持调⽤⼀次）
```c
void pwm_init(uint32 period,uint8 *duty,uint32 pwm_channel_num,uint32 (*pin_info_list)[3]){
	/*
	参数
		uint32 period：PWM 周期
		uint8 *duty：各路 PWM 的占空⽐
		uint32 pwm_channel_num：PWM 通道数
		uint32 (*pin_info_list)[3]：PWM 各通道的 GPIO 硬件参数。本参数是⼀个 n * 3 的数组指针，数组中定义了 GPIO 的寄存器，对应 PIN 脚的 IO 复⽤值和 GPIO 对应的序号
	*/
}
uint32 io_info[][3] =
{
	{PWM_0_OUT_IO_MUX,PWM_0_OUT_IO_FUNC,PWM_0_OUT_IO_NUM},
	{PWM_1_OUT_IO_MUX,PWM_1_OUT_IO_FUNC,PWM_1_OUT_IO_NUM},
	{PWM_2_OUT_IO_MUX,PWM_2_OUT_IO_FUNC,PWM_2_OUT_IO_NUM}
};
pwm_init(light_param.pwm_period, light_param.pwm_duty, 3, io_info);
```
二、pwm_start（每次更新 PWM 设置后，都需要重新调⽤本接⼝进⾏计算。）
```c
void pwm_start (void)
```
三、pwm_set_duty(设置某路 PWM 信号的 duty 参数)
```c
void pwm_set_duty(uint32 duty, uint8 channel){
/*
	参数
		占空比的值(duty*45)/ (period*1000)
		PWM通道	
*/

}
```
四、pwm_get_duty(获取某路 PWM 信号的 duty 参数)
```c
uint8 pwm_get_duty(uint8 channel){
	//PWM 通道
}
```
五、pwm_set_period(设置 PWM 周期)
```c
void pwm_set_period(uint32 period){
	/*
	参数
		单位：μs。例如，1KHz PWM，参数为 1000 μs。
	*/
}
```
六、pwm_get_period(查询 PWM 周期)
```c
uint32 pwm_get_period(void){
	//μs
}
	
```
七、get_pwm_version （查询 PWM 版本信息）
```c
uint32 get_pwm_version(void){
	
}
```

##### 示例
测试pwm_driver.c
```c 
#include "./driver/pwm_driver.h"
#include "pwm.h"
#include "eagle_soc.h"

//PWM????????
struct pwm_param PWM_Param_Struct={
	1000,1000,{0,0}
};

//PWM??????IO????
uint32_t PWM_IO_Info[2][3]={
	{PERIPHS_IO_MUX_MTDO_U,FUNC_GPIO15,GPIO_ID_PIN(15)},
	{PERIPHS_IO_MUX_GPIO2_U,FUNC_GPIO2,GPIO_ID_PIN(2)}
};

//PWM?????
void ICACHE_FLASH_ATTR PWM_Init(void){
 pwm_init(PWM_Param_Struct.period,PWM_Param_Struct.duty,2,PWM_IO_Info);  //pwm?????
}

```
调用示例user_main.c
```c 
user_init(void){
	....
   PWM_Init();
}
```

