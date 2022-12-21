#### 7、用户任务(配套示例Task)
**优先级：**
	分为三个优先级：0、1、2。任务优先级为 2>1>0
	最多支持 3 个用户任务，优先级分别为 0、1、2。
**了解：**
	用户代码长时间占用cpu，会触发看门狗复位。所以要喂狗。
	用户任务常常用于为u发被直接调用的函数。比如 ：`TCP/UDP`是不能在esp8266回调里执行。所以得在回调函数里创建一个用户任务，把相关代码放这里面执行。

##### 基础熟记
	1、创建系统任务，最多支持创建 3 个任务，优先级分别为 0，1，2
	2、给系统安排任务 
```c
//创建系统任务
#define TASK1_QUEUE_LEN   3  //定义消息队列深度
#define SIG_RX 0// 定义任务消息参数类型
os_event_t *task1_queue=NULL;//定义消息队列指针
task1_queue=(os_event_t*)os_malloc(sizeof(os_event_t)*TASK1_QUEUE_LEN);
system_os_task(Task1,0,task1_queue,TASK1_QUEUE_LEN);

//给系统安排任务
#define SIG_RX 0 //定义任务消息参数类型
system_os_post(0,SIG_RX,0);

```
##### API 函数集合
一、system_os_task（创建系统任务，最多⽀持创建 3 个任务，优先级分别为 0/1/2）
```c
bool system_os_task(os_task_t task,uint8 prio,os_event_t *queue,uint8 qlen){
	/*
	参数
		os_task_t task：任务函数
		uint8 prio：任务优先级，可为 0/1/2；0 为最低优先级。这表示最多只⽀持建⽴ 3 个任务
		os_event_t *queue：消息队列指针
		uint8 qlen：消息队列深度
	*/
}
```
二、system_os_post（给系统安排任务）
```c
bool system_os_post (uint8 prio,os_signal_t sig,os_param_t par){
/*
	参数
		uint8 prio：任务优先级，与建⽴时的任务优先级对应。
		os_signal_t sig：消息类型 通过优先级判断这个是谁给的任务
		os_param_t par：消息参数
	返回
		true：成功
		false：失败
*/
}
```

##### 示例
测试flash.c
```c 
#include "./driver/flash.h"


uint32_t Write_buf[10]={89,2,3,4,5,6,7,8,9,0};
uint32_t Read_buf[10]={0};

#define Sector		0x90  //扇区
#define Sector_size 4096

//Flash读写测试程序
void ICACHE_FLASH_ATTR Flash_Write_Read_Test(void)
{
	uint8_t i=0;
	os_printf("FLash ID=%d\r\n",spi_flash_get_id());	//获取flash的ID

	spi_flash_erase_sector(Sector);	//擦除对应的扇区
	spi_flash_write(Sector*Sector_size,(uint32_t *)Write_buf,sizeof(Write_buf));	//往FLASH写入数据
	spi_flash_read(Sector*Sector_size,(uint32_t *)Read_buf,sizeof(Read_buf));		//从FLASH中读取数据
	for(i=0;i<10;i++)
		os_printf("Read_buf[i]=%d\r\n",Read_buf[i]);
}

```
调用示例user_main.c
```c 
user_init(void){
	....
   Flash_Write_Read_Test();
}
```
