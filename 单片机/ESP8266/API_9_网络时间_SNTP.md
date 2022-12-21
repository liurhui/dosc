#### 13、SNTP 获取网络时间(配套示例SNTP) 
**了解：**
```plaintext
SNTP是一种协议，客户端/服务器的工作方式，通常多台SNTP服务器以防服务器故障。
	1、单播（点对点）模式，定期去服务器拿时间，达到同步。
	2、广播（一点对多点）模式 ，服务器周期性地发送消息给指定的 IP 广播地址或者 IP 多播地址。客户端通过监听地址来获取。
	3、常规的SNTP服务器网站
		us.pool.ntp.org
		ntp.sjtu.edu.cn

串口显示
no found, reconnect after 1s reconnect STATION_CONNECTING
表示wifi连接失败 账户或密码不对
```
##### 基础熟记
	1、SNTP 接口位于 /ESP8266_NONOS_SDK/include/sntp.h
	2、设置 SNTP 服务器域名，一共最多支持 3 个 SNTP 服务器
	3、通过 IP 地址设置 SNTP 服务器，最多支持 3 个 SNTP 服务器
	4、SNTP 初始化，设置完服务器之后需要调用此函数进行初始化配置
	5、查询当前距离基准时间 (1970.01.01 00:00:00 GMT+8)的时间戳单位：秒
		5.1、以伦敦为基准时间 + 中国东八区的误差时间 
		5.2、时间戳在线转换 https://tool.lu/timestamp/
	6、根据时间戳计算实际时间（GMT+8）
	7、设置时区信息
```c 
#include  sntp.h

//设置 SNTP 服务器域名，一共最多支持 3 个 SNTP 服务器
sntp_setservername(0,"us.pool.ntp.org");//设置 0 号服务器域名
sntp_setservername(1,"ntp.sjtu.edu.cn"); //设置 1 号服务器域名 备用

//通过 IP 地址设置 SNTP 服务器，最多支持 3 个 SNTP 服务器
ipaddr_aton("210.72.145.44", addr);
sntp_setserver(0, addr); //设置 0 号服务器 IP 地址

//SNTP 初始化，设置完服务器之后需要调用此函数进行初始化配置
void sntp_init(void)

//查询当前距离基准时间 (1970.01.01 00:00:00 GMT+8)的时间戳单位：秒
uint32 sntp_get_current_timestamp(void)

//根据时间戳计算实际时间（GMT+8）
 string beijingshijian = char* sntp_get_real_time(long t)

//设置时区信息
bool sntp_set_timezone (sint8 timezone) 


// 注意调用顺序 举个例子
sntp_stop();  //先拿时间
if( true==sntp_set_timezone(-5) ){  //再去校对
	sntp_init();  //最后去初始化
}
```
##### 示例
主函数->wifi去连接自己的网络实现通信->去连接sntp服务器->定时获取->解析
```c
//sntp.c
#include "./driver/user_sntp.h"
#include "sntp.h"
#include "./driver/os_timer.h"


void ICACHE_FLASH_ATTR ESP8266_SNTP_Init(void)
{
	ip_addr_t* server_addr;

	//设置SNTP服务器
	sntp_setservername(0,"us.pool.ntp.org");	//设置0号服务器
	sntp_setservername(1,"ntp.sjtu.edu.cn");	//设置1号服务器
	ipaddr_aton("210.72.145.44", server_addr); //210.72.145.44 也是一个服务器
	sntp_setserver(3, server_addr);				//设置2号服务器

	sntp_init();		//sntp初始化   SDK库函数对内核的一些操作

	OS_Timer_SNTP_Init(1000,1);	//调用sntp定时器获取网络时间
}

```
得配置wifi为STA模式 去连接我们的路由器wifi上网
```c
//WIFI STA模式初始化配置
void ICACHE_FLASH_ATTR WIFI_STA_Mode_Init(void)
{
	struct	station_config STA_Config_Struct;
	struct ip_info sta_ip_info;

	wifi_set_opmode(0x01);		//配置WiFi为STA模式

	os_strcpy(STA_Config_Struct.ssid,WIFI_SSID);			//WiFi名称
	os_strcpy(STA_Config_Struct.password,WIFI_PASS);		//WiFi密码

	wifi_station_set_config(&STA_Config_Struct); //相当于把配置信息写进去wifi模块寄存器内
}
```
主函数
```c
/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void ICACHE_FLASH_ATTR
user_init(void)
{ 
	WIFI_STA_Mode_Init();	//配置为STA模式
	//不马上去执行
	OS_Timer_Init(1000,1);	//软件定时器初始化  1s执行一次
} 
```
定时器
```c
//软件定时器配置初始化
void ICACHE_FLASH_ATTR OS_Timer_Init(uint32_t ms,bool repeat_flag)
{
	os_timer_disarm(&os_timer_1);					//关闭软件定时器
	os_timer_setfn(&os_timer_1,(os_timer_func_t*)OS_Timer_1_Cb,NULL);	//注册软件定时回调函数  目的：只有是STATION_GOT_IP 获取到IP地址，把地址读出来进行打印。然后去进行连接SNTP服务器。
	os_timer_arm(&os_timer_1,ms,repeat_flag);		//打开软件定时器并设置定时时间以及是否重复
} 
```

```c
//软件定时器1回调函数
void ICACHE_FLASH_ATTR OS_Timer_1_Cb(void)
{
	uint8_t sta_status=0;
	struct	ip_info STA_IP_Info;
	uint8_t ESP8266_IP[4]={0};

	sta_status=wifi_station_get_connect_status();

	switch(sta_status)
	{
	case STATION_IDLE:	//空闲
		os_printf("STATION_IDLE\r\n");
		break;
	case STATION_CONNECTING:	//正在连接
		os_printf("STATION_CONNECTING\r\n");
		break;
	case STATION_WRONG_PASSWORD://密码错误
		os_printf("STATION_WRONG_PASSWORD\r\n");
		break;
	case STATION_NO_AP_FOUND:	//没有发现AP
		os_printf("STATION_NO_AP_FOUND\r\n");
		break;
	case STATION_CONNECT_FAIL:	//连接错误
		os_printf("STATION_CONNECT_FAIL\r\n");
		break;
	case STATION_GOT_IP:		//获取到IP地址
		os_printf("STATION_GOT_IP\r\n");
		break;
	}

	if(sta_status==STATION_GOT_IP)		//如果连接成功
	{
		wifi_get_ip_info(STATION_IF,&STA_IP_Info);
		ESP8266_IP[0]=STA_IP_Info.ip.addr;		//将32位IP地址采用点分十进制进行分割
		ESP8266_IP[1]=STA_IP_Info.ip.addr>>8;
		ESP8266_IP[2]=STA_IP_Info.ip.addr>>16;
		ESP8266_IP[3]=STA_IP_Info.ip.addr>>24;
		os_printf("ESP8266 STA Mode Config OK!\r\n");
		os_printf("IP:%d.%d.%d.%d\r\n",ESP8266_IP[0],
										ESP8266_IP[1],
										ESP8266_IP[2],
										ESP8266_IP[3]);
		os_timer_disarm(&os_timer_1);	//关闭软件定时器
		/*1、去连接SNTP服务器 2、定时去获取*/
		ESP8266_SNTP_Init();	//配置SNTP
	}
}
```
sntp定时器
```c
//SNTP软件定时器回调函数
void ICACHE_FLASH_ATTR OS_Timer_SNTP_Cb(void)
{
	uint32_t timestamp=0;			//存放时间戳
	char *current_time_buf=NULL;	//存放当前时间字符串

	timestamp=sntp_get_current_timestamp();		//获取现在的时间戳
	if(timestamp!=0){
		current_time_buf=sntp_get_real_time(timestamp);	//时间戳转化为当前时间
		os_printf("\r\ntimestamp=%d   Current Time:%s\r\n",timestamp,current_time_buf); 
	}
	else	//获取网络时间失败
		os_printf("SNTP get current time failed!\r\n");
}

//SNTP软件定时器初始化
void ICACHE_FLASH_ATTR OS_Timer_SNTP_Init(uint32_t ms,bool repeat_flag)
{
	os_timer_disarm(&os_timer_sntp);					//关闭软件定时器
	os_timer_setfn(&os_timer_sntp,(os_timer_func_t*)OS_Timer_SNTP_Cb,NULL);	//注册软件定时回调函数
	os_timer_arm(&os_timer_sntp,ms,repeat_flag);		//打开软件定时器并设置定时时间以及是否重复
}
```