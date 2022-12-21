#### 9、WIFI(配套示例WIFI_XX_MODE) 
**了解：**
```plaintext
AP 与 STATION：
	AP，即基站，必须分配一个小于 32 字节的 WiFi 名 SSID，
	STATION，移动站。
	如家中，路由器就是 AP，手机就是 STATION。
	
wifi 用tcp协议也就是IP
	DHCP：动态主机配置协议,目的自动配置设备IP地址，子网掩码，默认路由器的IP 地址、域名服务器的 IP 地址

接口分为：查询、设置。
模式分为：AP 、STATION 。
```

##### 基础熟记
	AP
	1、设置 WiFi 的工作模式
	2、设置 WiFi SoftAP 模式，并保存到 flash
	3、查询 WiFi Station 模式或者 AP 模式的 IP 地址，确认模式是否配置成功
	4、获取 AP 模式下接入此 WiFi 的设备数量
	STA
	1、设置 WiFi 的工作模式
	2、设置 WiFi Station 模式并保存到 flash
	3、查询 ESP8266 Wi-Fi Station 接口连接 AP 的状态。
	4、查询 WiFi Station 模式或者 AP 模式的 IP 地址，确认模式是否配置成功
	自定义DHCP
	1、开启 DHCP
	2、关闭 DHCP
	3、设置 AP 模式或 STA 模式 IP 地址、子网掩码、网关 
```c
struct softap_config {
	uint8 ssid[32]; //WiFi 名
	uint8 password[64]; //密码
	uint8 ssid_len; //WiFi 名长度
	uint8 channel; //通道号 1 ~ 13
	AUTH_MODE authmode;//加密方，softAP模式不支持AUTH_WEP加密方式。
	uint8 ssid_hidden; //是否隐藏 WiFi，默认为 0 不隐藏网络
	uint8 max_connection; //最大连接设备数，最大设备数为 4
	uint16 beacon_interval;//信标间隔时间，支持 100-60000ms（信标间隔时间即 SSID 广播包发送的间距），默认为 100ms
};

//设置 WiFi 的工作模式
wifi_set_opmode(0x02);//设置 WiFi 工作模式为 AP 模式

//设置 WiFi SoftAP 模式，并保存到 flash
struct softap_config AP_Config_Struct;
os_strcpy(AP_Config_Struct.ssid,ESP8266_SSID);
os_strcpy(AP_Config_Struct.password,ESP8266_PASS);
AP_Config_Struct.ssid_len=sizeof("YTWZDPJJSZC");
AP_Config_Struct.authmode=AUTH_WPA2_PSK;
AP_Config_Struct.beacon_interval=100;
AP_Config_Struct.channel=1;
AP_Config_Struct.max_connection=4;
AP_Config_Struct.ssid_hidden=0;
wifi_softap_set_config(&AP_Config_Struct);

//查询 WiFi Station 模式或者 AP 模式的 IP 地址，确认模式是否配置成功
wifi_get_ip_info(SOFTAP_IF,&AP_IP_Info);

//获取 AP 模式下接入此 WiFi 的设备数量
uint8 wifi_ap_num = wifi_softap_get_station_num();
```

```c
//你要连接的wifi 的参数
struct station_config {
 uint8 ssid[32]; // WiFi 的名称
 uint8 password[64]; //WiFi 的密码
 uint8 bssid_set; //当一个局域网中有多个同名 WiFi 时使用
				  // bssid_set 为 1 时连接 WiFi 还将校验 MAC 地址
 uint8 bssid[6]; // WiFi 的 MAC 地址
 wifi_fast_scan_threshold_t threshold; //结构体，包含了 WiFi 的加密方
//式和信号强度两个变量
};

//返回值：所查询AP状态
enum{
	STATION_IDLE = 0, //空闲
	STATION_CONNECTING, //正在连接
	STATION_WRONG_PASSWORD, //密码错误
	STATION_NO_AP_FOUND, //没有发现 AP
	STATION_CONNECT_FAIL, //连接失败
	STATION_GOT_IP //获取到 IP
};



//设置 WiFi 的工作模式
wifi_set_opmode(0x01);

//设置 WiFi Station 模式并保存到 flash
os_strcpy(STA_Config_Struct.ssid,ESP8266_SSID);
os_strcpy(STA_Config_Struct.password,ESP8266_PASS);
wifi_station_set_config(&STA_Config_Struct);

//查询 ESP8266 Wi-Fi Station 接口连接 AP 的状态。
uint8 wifi_sta_status = wifi_station_get_connect_status();

//查询 WiFi Station 模式或者 AP 模式的 IP 地址，确认模式是否配置成功
wifi_get_ip_info(SOFTAP_IF,&AP_IP_Info);
```

```c
//开启 DHCP  返回值  true成功 ， false失败
wifi_station_dhcpc_start();

//关闭 DHCP  返回值  true成功 ， false失败
wifi_station_dhcpc_stop();

//设置 AP 模式或 STA 模式 IP 地址、子网掩码、网关
struct ip_info info; //定义一个 IP 信息结构体   ip_info由库函数封装好的
wifi_station_dhcpc_stop();//关闭 dhcp
IP4_ADDR(&info.ip,192,168,43,200); //设置 IP 地址
IP4_ADDR(&info.gw,192,168,43,1);//设置网关
IP4_ADDR(&info.netmask,255,255,255,0); //设置子网掩码
wifi_set_ip_info(STATION_IF,&info);
```

##### API 函数集合
一、wifi_get_opmode（查询 Wi-Fi 当前⼯作模式）
```c
uint8 wifi_get_opmode (void){
	/*
	返回
		0x01：Station 模式
		0x02：SoftAP 模式
		0x03：Station+SoftAP 模式
	*/
}
```
二、wifi_get_opmode_default（查询保存在 Flash 中的 Wi-Fi ⼯作模式设置）
```c
uint8 wifi_get_opmode_default (void){
	/*
		返回
			0x01：Station 模式
			0x02：SoftAP 模式
			0x03：Station+SoftAP 模式
	*/
}
```
三、wifi_set_opmode(设置 Wi-Fi ⼯作模式（Station，SoftAP 或者 Station+SoftAP），并保存到 Flash。默认为 SoftAP 模式)
```c
/*
	ESP8266_NONOS_SDK_V0.9.2 以及之前版本，设置之后需要调⽤ system_restart() 重启
⽣效；
	ESP8266_NONOS_SDK_V0.9.2 之后的版本，不需要重启，即时⽣效。
	本设置如果与原设置不同，会更新保存到 Flash 系统参数区。
*/
bool wifi_set_opmode (uint8 opmode){
/*
	参数 
		0x01：Station 模式
		0x02：SoftAP 模式
		0x03：Station+SoftAP 模式
	返回
		true：成功
		false：失败
*/
}
```
###### Wi-Fi Station
一、wifi_station_get_config(查询当前配置参数)
```c
bool wifi_station_get_config (struct station_config *config){
	/*
	参数 
		 接⼝参数指针
	返回
		true：成功
		false：失败
	*/
}
```
二、wifi_station_get_config_default(查询保存在 Flash 中的配置参数)
```c
bool wifi_station_get_config_default(struct station_config *config){
	/*
	参数 
		 接⼝参数指针
	返回
		true：成功
		false：失败
	*/
}
```
三、wifi_station_set_config(设置配置参数，并保存到 Flash)
wifi_softap_set_confifig(设置配置，并保存到 Flash)
此函数其实是在内核中完成的，不会一调用就直接配置
```c
/*
	在 ESP8266 Station 使能的情况下，调⽤本接⼝。
	如果在 user_init 中调⽤，则 ESP8266 Station 接⼝会在系统初始化完成后，⾃动连接 AP（路由），⽆需再调⽤ wifi_station_connect
	否则，需要调⽤ wifi_station_connect 连接 AP（路由）。
	会更新保存到 Flash 系统参数区。
*/
bool wifi_station_set_config(struct	station_config	*config){
	/*
	参数 
		配置参数指针
	返回
		true：成功
		false：失败
	*/
}
//示例
void ICACHE_FLASH_ATTR user_set_station_config(void){
   char ssid[32] = SSID;
   char password[64] = PASSWORD;
   struct station_config stationConf;
   
   stationConf.bssid_set = 0; //need not check MAC address of AP
   
   os_memcpy(&stationConf.ssid, ssid, 32);
   os_memcpy(&stationConf.password, password, 64);
   wifi_station_set_config(&stationConf);
}

void user_init(void){
   wifi_set_opmode(STATIONAP_MODE); //Set softAP + station mode
   user_set_station_config();
}


/*
	在 ESP8266 Station 使能的情况下，调⽤本接⼝。
	本设置如果与原设置不同，将更新保存到 Flash 系统参数区。
	因为 ESP8266 只有⼀个信道，因此 SoftAP+Station 共存模式时，ESP8266 SoftAP 接⼝会⾃动调节信道与 ESP8266 Station ⼀致，详细说明请参考附录。
*/
bool wifi_softap_set_config (struct softap_config *config){
	/*
	参数 
		配置参数
	返回
		true：成功
		false：失败
	*/
}
```
四、wifi_station_set_config_current（设置配置参数，不保存到 Flash）
wifi_softap_set_confifig_current
```c
/*
	请在使能的情况下，调⽤本接⼝。
	如果 user_init 中调⽤，则 ESP8266 Station 接⼝会在系统初始化完成后，⾃动连接 AP（路由），⽆需再调⽤ wifi_station_connect
	否则，需要调⽤ wifi_station_connect 连接 AP（路由）。
	会更新保存到 Flash 系统参数区。
*/
bool wifi_station_set_config_current(struct	station_config	*config){
	/*
	参数 
		配置参数指针
	返回
		true：成功
		false：失败
	*/
}

bool wifi_softap_set_config_current (struct softap_config *config)
```
五、wifi_station_connect（连接 AP）
```c
/*
	请勿在 user_init 中调⽤本接⼝，请在 ESP8266 Station 使能并初始化完成后调⽤；
	如果已连接某个 AP，请先调⽤ wifi_station_disconnect	断开上⼀次连接。
*/
bool wifi_station_connect (void){
	/*
		返回
			true：成功
			false：失败
	*/
}
```
六、wifi_station_get_connect_status(查询连接 AP 的状态)
```c
/*
	若为特殊应⽤场景：调⽤ wifi_station_set_reconnect_policy 关闭重连功能，且未调⽤wifi_set_event_handler_cb 注册 Wi-Fi 事件回调，则本接⼝失效，⽆法准确获得连接状态。
*/
uint8 wifi_station_get_connect_status(void){
	/*
		返回
		enum{
			STATION_IDLE = 0,
			STATION_CONNECTING,
			STATION_WRONG_PASSWORD,
			STATION_NO_AP_FOUND,
			STATION_CONNECT_FAIL,
			STATION_GOT_IP
		};
	*/
}
```
七、wifi_station_get_ap_info（获取保存的 AP 信息，最多记录 5 个。）
```c
uint8 wifi_station_get_ap_info(struct station_config config[]){
	/*
		参数 
			AP 的信息，数组⼤⼩必须为 5
		返回
			记录 AP 的数⽬
	*/
}


struct station_config config[5];
int i = wifi_station_get_ap_info(config);
```
八、wifi_station_dhcpc_stop（关闭 ESP8266 Station DHCP client）
```c
/*
	DHCP 默认开启。
	DHCP 与静态 IP 功能 wifi_set_ip_info 互相影响：
	DHCP 开启，则静态 IP 失效；设置静态 IP，则 DHCP 关闭。
*/
bool wifi_station_dhcpc_stop(void){
	/*
		返回
			true：成功
			false：失败
	*/
}
```
九、wifi_station_set_reconnect_policy（连接 AP 失败或断开后是否重连。默认重连。）
```c
/*
	建议在 user_init 中调⽤本接⼝
*/
bool wifi_station_set_reconnect_policy(bool	set){
	/*
		参数
			true：断开则重连
			false：断开不重连
		返回
			true：成功
			false：失败
	*/
}
```
十、wifi_softap_get_station_num（获取 ESP8266 SoftAP 下连接的 Station 个数）
```c
uint8 wifi_softap_get_station_num(void){
	/*
		 
		返回
			SoftAP 下连接的 Station 个数
	*/
}
```
一、wifi_get_ip_info（查询 Wi-Fi Station 接⼝或者 SoftAP 接⼝的 IP 地址）
```c
/*
	在 user_init 中，由于初始化尚未完成，⽆法通过本接⼝查询到有效 IP 地址。
	因为wifi配置是在内核中完成的，并不是一调用配置函数就完成此配置
*/
bool wifi_get_ip_info(uint8 if_index, struct ip_info *info){
	/*
		参数
			uint8 if_index：获取 Station 或者 SoftAP 接⼝的信息
				#define	STATION_IF	0x00
				#define	SOFTAP_IF 0x01
			struct	ip_info	*info：获取到的 IP 信息
		返回
			true：成功
			false：失败
	*/
}
```
二、wifi_set_ip_info（设置 Wi-Fi Station 接⼝或者 SoftAP 接⼝的 IP 地址）
```c
/*
	本接⼝设置静态 IP，请先关闭对应 DHCP 功能 wifi_station_dhcpc_stop 或者
wifi_softap_dhcps_stop
	设置静态 IP，则关闭 DHCP；DHCP 开启，则静态 IP 失效。
*/
bool wifi_set_ip_info(uint8 if_index, struct ip_info *info){
	/*
		参数
			uint8 if_index：获取 Station 或者 SoftAP 接⼝的信息
				#define	STATION_IF	0x00
				#define	SOFTAP_IF 0x01
			struct	ip_info	*info：获取到的 IP 信息
		返回
			true：成功
			false：失败
	*/
}
```

##### 示例
测试wifi.c
```c 
#include "./driver/wifi.h"

//WIFI AP模式初始化配置
void ICACHE_FLASH_ATTR WIFI_AP_Mode_Init(void){
    struct  softap_config AP_Config_Struct;
    wifi_set_opmode(0x02);      //配置WiFi为AP模式
    os_strcpy(AP_Config_Struct.ssid,WIFI_SSID);         //WiFi名称
    os_strcpy(AP_Config_Struct.password,WIFI_PASS);     //WiFi密码
    AP_Config_Struct.ssid_len=sizeof(WIFI_SSID);        //WiFi名称长度
    AP_Config_Struct.authmode=AUTH_WPA2_PSK;            //加密方式
    AP_Config_Struct.beacon_interval=100;               //信标间隔时间
    AP_Config_Struct.channel=1;                         //通道号
    AP_Config_Struct.max_connection=4;                  //允许最大连接设备数量
    AP_Config_Struct.ssid_hidden=0;                     //不隐藏WiFi
    wifi_softap_set_config(&AP_Config_Struct);
}

  

//WIFI STA模式初始化配置
void ICACHE_FLASH_ATTR WIFI_STA_Mode_Init(void){
    struct  station_config STA_Config_Struct;
    struct ip_info sta_ip_info;
    wifi_set_opmode(0x01);      //配置WiFi为STA模式
#if 0
    wifi_station_dhcpc_stop();  //关闭DHCP
    IP4_ADDR(&sta_ip_info.ip,192,168,43,189);       //设置 IP 地址
    IP4_ADDR(&sta_ip_info.gw,192,168,43,1);         //设置网关
    IP4_ADDR(&sta_ip_info.netmask,255,255,255,0);   //设置子网掩码
    wifi_set_ip_info(STATION_IF,&sta_ip_info);
#endif
    os_strcpy(STA_Config_Struct.ssid,WIFI_SSID);            //WiFi名称
    os_strcpy(STA_Config_Struct.password,WIFI_PASS);        //WiFi密码
    wifi_station_set_config(&STA_Config_Struct);
}

```
调用示例user_main.c
```c 
user_init(void){
	....
   WIFI_AP_Mode_Init();	//配置为AP模式
}
```

#### 10、WIFI(配套示例WIFI_AP/STA_UDP_XXX) 
**了解：**
```plaintext
UDP 
	发送方通过IP地址和端口号，发送给接收方。
	接收方从数据包里得到发送方的IP地址和端口号。
实验一：
	电脑作为客服端，ESP8266 作为服务端，客服端主动向服务器发送数据，服务器被动接收到数据，同时在服务器接收到客服端发来的数据之后向对应的客服端回应；

实验二：
	ESP8266 作为客服端，电脑作为服务端，客服端主动向服务器发送数据，服务器被动接收到数据，同时在服务器接收到客服端发来的数据之后向对应的客服端回应。


```

##### 基础熟记
	ESP8266 作为AP服务器
	1、包含头文件espconn.h
	2、创建 UDP 通讯
	3、通过无线网络发送数据
	4、查询某个 TCP 连接或者 UDP 传输的远端信息，此函数一般在接收成功的回调函数中调用。
	ESP8266 作为AP客户端
	1、包含头文件espconn.h
	2、创建 UDP 通讯
	3、通过无线网络接收数据
	4、查询某个 TCP 连接或者 UDP 传输的远端信息，此函数一般在接收成功的回调函数中调用。
	ESP8266 作为STA服务器
	1、跟ap相同步骤
	ESP8266 作为STA客户端
	1、跟ap相同步骤
```c
struct espconn {
 enum espconn_type type; //连接类型，可以是 UDP 和 TCP
 enum espconn_state state; //连接状态
 union {
 esp_tcp *tcp;
 esp_udp *udp;
 } proto; //一个共用体，包含了一个 tcp 连接参数结构体和 udp
//连接参数结构体
 espconn_recv_callback recv_callback; //接收成功的回调函数
 espconn_sent_callback sent_callback; //发送成功的回调函数
 uint8 link_cnt; //连接数量
 void *reverse; //指针变量，可用来存储相关需要的数据
};
//返回值：0：成功，其他：失败，返回对应的错误码
//ESPCONN_ ARG:未找到参数 espconn 对应的 UDP 连接
//ESPCONN_MEM:空间不足
//ESPCONN_ ISCONN:连接已经建立
//注意：定义的网络结构体必须是全局变量。


//创建 UDP 通讯
struct espconn ESPConnect_Struct; //定义网络连接结构体，全局变量
esp_udp udp_Struct;
ESPConnect_Struct.type=ESPCONN_UDP;
ESPConnect_Struct.proto.udp=(esp_udp*)os_malloc(sizeof(esp_udp));
ESPConnect_Struct.proto.udp->local_port=9999;
ESPConnect_Struct.sent_callback=ESP8266_UDP_Sen d_Cb;
ESPConnect_Struct.recv_callback=ESP8266_UDP_Receive_Cb;
espconn_create(&ESPConnect_Struct);

//通过无线网络发送数据(结构体，数据，数据的长度)
espconn_send(&ESPConnect_Struct,"Hello, I'm esp8266!",os_strlen("Hello,I'm esp8266!"));

//查询某个 TCP 连接或者 UDP 传输的远端信息，此函数一般在接收成功的回调函数中调用。（结构体、IP、连接方式 0 正常server 1 SSL server）
sint8 espconn_get_connection_info(struct espconn *espconn, remot_info **pcon_info,uint8 typeflags)
```

```c
struct espconn ESPConnect_Struct; //定义网络连接结构体，全局变量
esp_udp udp_Struct;
ESPConnect_Struct.type=ESPCONN_UDP;
ESPConnect_Struct.proto.udp=(esp_udp*)os_malloc(sizeof(esp_udp));
ESPConnect_Struct.proto.udp->local_port=9999;
ESPConnect_Struct.proto.udp->remote_port=6666;
ESPConnect_Struct.proto.udp->remote_ip[0]=192;
ESPConnect_Struct.proto.udp->remote_ip[1]=168;
ESPConnect_Struct.proto.udp->remote_ip[2]=4;
ESPConnect_Struct.proto.udp->remote_ip[3]=2;
ESPConnect_Struct.sent_callback=ESP8266_UDP_Sen d_Cb;
ESPConnect_Struct.recv_callback=ESP8266_UDP_Receive_Cb;
espconn_create(&ESPConnect_Struct);
```
##### UDP_AP示例
###### WIFI_AP_UDP_Sever
```c 
#include "./driver/wifi.h"
#include "espconn.h"
#include "./driver/Peripherals.h"
#include "mem.h"

//WIFI AP模式初始化配置
void ICACHE_FLASH_ATTR WIFI_AP_Mode_Init(void)
{
	struct	softap_config AP_Config_Struct;

	wifi_set_opmode(0x02);		//配置WiFi为AP模式

	os_strcpy(AP_Config_Struct.ssid,WIFI_SSID);			//WiFi名称
	os_strcpy(AP_Config_Struct.password,WIFI_PASS);		//WiFi密码
	AP_Config_Struct.ssid_len=sizeof(WIFI_SSID);		//WiFi名称长度
	AP_Config_Struct.authmode=AUTH_WPA2_PSK;			//加密方式
	AP_Config_Struct.beacon_interval=100;				//信标间隔时间
	AP_Config_Struct.channel=1;							//通道号
	AP_Config_Struct.max_connection=4;					//允许最大连接设备数量
	AP_Config_Struct.ssid_hidden=0;						//不隐藏WiFi

	wifi_softap_set_config(&AP_Config_Struct);
}

//ESP8266 UDP通讯接收成功回调函数
void ICACHE_FLASH_ATTR ESP8266_UDP_Receive_Cb(void *arg, char *pdata, unsigned short len)
{
	struct	espconn	*pesp_conn=arg;
	remot_info *premot=NULL;	//定义远端信息结构体
	premot=(remot_info*)os_malloc(sizeof(remot_info));	//申请内存
	os_printf("ESP8266 Receive Data=%s\r\n",pdata);
	
	if(espconn_get_connection_info(pesp_conn,&premot,0)==0)	//获取远端设备信息
	{
		pesp_conn->proto.udp->remote_port=premot->remote_port;
		pesp_conn->proto.udp->remote_ip[0]=premot->remote_ip[0];
		pesp_conn->proto.udp->remote_ip[1]=premot->remote_ip[1];
		pesp_conn->proto.udp->remote_ip[2]=premot->remote_ip[2];
		pesp_conn->proto.udp->remote_ip[3]=premot->remote_ip[3];
}
//给远端设备回应//ESP8266 UDP通讯接收成功回调函数
void ICACHE_FLASH_ATTR ESP8266_UDP_Receive_Cb(void *arg, char *pdata, unsigned short len)
{
	struct	espconn	*pesp_conn=arg;
	remot_info *premot=NULL;	//定义远端信息结构体
	premot=(remot_info*)os_malloc(sizeof(remot_info));	//申请内存
	os_printf("ESP8266 Receive Data=%s\r\n",pdata);
	if(espconn_get_connection_info(pesp_conn,&premot,0)==0)	//获取远端设备信息
	{
		pesp_conn->proto.udp->remote_port=premot->remote_port;
		pesp_conn->proto.udp->remote_ip[0]=premot->remote_ip[0];
		pesp_conn->proto.udp->remote_ip[1]=premot->remote_ip[1];
		pesp_conn->proto.udp->remote_ip[2]=premot->remote_ip[2];
		pesp_conn->proto.udp->remote_ip[3]=premot->remote_ip[3];

		//给远端设备回应
		espconn_send(pesp_conn,"ESP8266 Receive Success!\r\n",os_strlen("ESP8266 Receive Success!\r\n"));
	}

	os_free(premot);	//释放内存
}

//ESP8266 UDP通讯发送成功回调函数
void ICACHE_FLASH_ATTR ESP8266_UDP_Send_Cb(void *arg)
{
	os_printf("ESP8266 Send Data OK!\r\n");
}

//定义网络信息结构体	全局变量
struct	espconn ESPConnect_Struct;
//UDP通讯初始化
void ICACHE_FLASH_ATTR WIFI_UDP_Init(void)
{
	ESPConnect_Struct.type=ESPCONN_UDP;
	ESPConnect_Struct.proto.udp=(esp_udp*)os_malloc(sizeof(esp_udp));	//申请内存
	ESPConnect_Struct.proto.udp->local_port=9999;			//设置本地端口
	ESPConnect_Struct.recv_callback=ESP8266_UDP_Receive_Cb;	//注册udp通讯接成功回调函数
	ESPConnect_Struct.sent_callback=ESP8266_UDP_Send_Cb;	//注册udp通讯发送成功回调函数

//	espconn_regist_recvcb(&ESPConnect_Struct,ESP8266_UDP_Receive_Cb);
//	espconn_regist_sentcb(&ESPConnect_Struct,ESP8266_UDP_Send_Cb);
	espconn_create(&ESPConnect_Struct);
}

		espconn_send(pesp_conn,"ESP8266 Receive Success!\r\n",os_strlen("ESP8266 Receive Success!\r\n"));
	}

	os_free(premot);	//释放内存
}

//ESP8266 UDP通讯发送成功回调函数
void ICACHE_FLASH_ATTR ESP8266_UDP_Send_Cb(void *arg)
{
	os_printf("ESP8266 Send Data OK!\r\n");
}

//定义网络信息结构体	全局变量
struct	espconn ESPConnect_Struct;
//UDP_Sever通讯初始化
void ICACHE_FLASH_ATTR WIFI_UDP_Init(void)
{
	ESPConnect_Struct.type=ESPCONN_UDP;
	ESPConnect_Struct.proto.udp=(esp_udp*)os_malloc(sizeof(esp_udp));	//申请内存
	ESPConnect_Struct.proto.udp->local_port=9999;			//设置本地端口
	ESPConnect_Struct.recv_callback=ESP8266_UDP_Receive_Cb;	//注册udp通讯接成功回调函数
	ESPConnect_Struct.sent_callback=ESP8266_UDP_Send_Cb;	//注册udp通讯发送成功回调函数

//	espconn_regist_recvcb(&ESPConnect_Struct,ESP8266_UDP_Receive_Cb);
//	espconn_regist_sentcb(&ESPConnect_Struct,ESP8266_UDP_Send_Cb);
	espconn_create(&ESPConnect_Struct);
}
```
调用示例user_main.c
```c 
user_init(void){
	....
  WIFI_AP_Mode_Init();	//配置为AP模式
}
```
###### WIFI_AP_UDP_Client
```C
//UDP_Client通讯初始化
void ICACHE_FLASH_ATTR WIFI_UDP_Init(void)
{
	ESPConnect_Struct.type=ESPCONN_UDP;
	ESPConnect_Struct.proto.udp=(esp_udp*)os_malloc(sizeof(esp_udp));	//申请内存
	ESPConnect_Struct.proto.udp->local_port=9999;			//设置本地端口
	ESPConnect_Struct.proto.udp->remote_port=6666;
	ESPConnect_Struct.proto.udp->remote_ip[0]=192;
	ESPConnect_Struct.proto.udp->remote_ip[1]=168;
	ESPConnect_Struct.proto.udp->remote_ip[2]=4;
	ESPConnect_Struct.proto.udp->remote_ip[3]=2;
	ESPConnect_Struct.recv_callback=ESP8266_UDP_Receive_Cb;	//注册udp通讯接成功回调函数
	ESPConnect_Struct.sent_callback=ESP8266_UDP_Send_Cb;	//注册udp通讯发送成功回调函数
	espconn_create(&ESPConnect_Struct);
	FM_ON();
	espconn_send(&ESPConnect_Struct,"ESP8266 Online!\r\n",os_strlen("ESP8266 Online!\r\n"));
}
```

##### UDP_STA示例
###### WIFI_STA_UDP_Sever
```c
//WIFI STA模式初始化配置
void ICACHE_FLASH_ATTR WIFI_STA_Mode_Init(void)
{
	struct	station_config STA_Config_Struct;
	struct ip_info sta_ip_info;
	wifi_set_opmode(0x01);		//配置WiFi为STA模式
	os_strcpy(STA_Config_Struct.ssid,WIFI_SSID);			//WiFi名称
	os_strcpy(STA_Config_Struct.password,WIFI_PASS);		//WiFi密码
	wifi_station_set_config(&STA_Config_Struct);
}

//ESP8266 UDP通讯接收成功回调函数
void ICACHE_FLASH_ATTR ESP8266_UDP_Receive_Cb(void *arg, char *pdata, unsigned short len){
	struct	espconn	*pesp_conn=arg;
	remot_info *premot=NULL;	//定义远端信息结构体
	premot=(remot_info*)os_malloc(sizeof(remot_info));	//申请内存
	os_printf("ESP8266 Receive Data=%s\r\n",pdata);
	if(espconn_get_connection_info(pesp_conn,&premot,0)==0)	//获取远端设备信息
	{
		pesp_conn->proto.udp->remote_port=premot->remote_port;
		pesp_conn->proto.udp->remote_ip[0]=premot->remote_ip[0];
		pesp_conn->proto.udp->remote_ip[1]=premot->remote_ip[1];
		pesp_conn->proto.udp->remote_ip[2]=premot->remote_ip[2];
		pesp_conn->proto.udp->remote_ip[3]=premot->remote_ip[3];
		//给远端设备回应
		espconn_send(pesp_conn,"ESP8266 Receive Success!\r\n",os_strlen("ESP8266 Receive Success!\r\n"));
	}
	os_free(premot);	//释放内存
}

//ESP8266 UDP通讯发送成功回调函数
void ICACHE_FLASH_ATTR ESP8266_UDP_Send_Cb(void *arg)
{
	os_printf("ESP8266 Send Data OK!\r\n");
}

//定义网络信息结构体	全局变量
struct	espconn ESPConnect_Struct;
//UDP通讯初始化
void ICACHE_FLASH_ATTR WIFI_UDP_Init(void)
{
	ESPConnect_Struct.type=ESPCONN_UDP;
	ESPConnect_Struct.proto.udp=(esp_udp*)os_malloc(sizeof(esp_udp));//申请内存
	ESPConnect_Struct.proto.udp->local_port=9999;	//设置本地端口
	ESPConnect_Struct.recv_callback=ESP8266_UDP_Receive_Cb;	//注册udp通讯接成功回调函数
	ESPConnect_Struct.sent_callback=ESP8266_UDP_Send_Cb; //注册udp通讯发送成功回调函数
	espconn_create(&ESPConnect_Struct);
}
```
调用示例user_main.c
```C
void ICACHE_FLASH_ATTR user_init(void){
	 ...
	WIFI_STA_Mode_Init();	//配置为AP模式
}
```
###### WIFI_STA_UDP_Client
```C
//UDP通讯初始化
void ICACHE_FLASH_ATTR WIFI_UDP_Init(void)
{
	ESPConnect_Struct.type=ESPCONN_UDP;
	ESPConnect_Struct.proto.udp=(esp_udp*)os_malloc(sizeof(esp_udp));	//申请内存
	ESPConnect_Struct.proto.udp->local_port=9999;			//设置本地端口
	ESPConnect_Struct.proto.udp->remote_port=6666;
	ESPConnect_Struct.proto.udp->remote_ip[0]=192;
	ESPConnect_Struct.proto.udp->remote_ip[1]=168;
	ESPConnect_Struct.proto.udp->remote_ip[2]=0;
	ESPConnect_Struct.proto.udp->remote_ip[3]=6;
	ESPConnect_Struct.recv_callback=ESP8266_UDP_Receive_Cb;	//注册udp通讯接成功回调函数
	ESPConnect_Struct.sent_callback=ESP8266_UDP_Send_Cb;	//注册udp通讯发送成功回调函数
	espconn_create(&ESPConnect_Struct);
	espconn_send(&ESPConnect_Struct,"ESP8266 Online!\r\n",os_strlen("ESP8266 Online!\r\n"));
}
```

#### 11、WIFI(配套示例WIFI_AP/STA_TCP_XXX) 
##### 基础熟记
	ESP8266 作为STA服务器
	1、包含头文件espconn.h
	2、创建TCP server 建立侦听
	3、注册 ESP8266 TCP server 超时时间（原因超时无传输数据会断开）
	4、通过无线网络发送数据
	5、查询某个 TCP 连接或者 UDP 传输的远端信息
	ESP8266 作为STA客户端
	1、包含头文件espconn.h
	2、连接 TCP server（ESP8266 作为 TCP client）。
	3、通过无线网络发送数据
	
	ESP8266 作为AP服务器
	1、去连接 WiFi 热点网络（实际代码跟STA差不大多）
	ESP8266 作为AP客户端
	1、去连接 WiFi 热点网络（实际代码跟STA差不大多）
```c
struct espconn {
 enum espconn_type type; //连接类型，可以是 UDP 和 TCP
 enum espconn_state state; //连接状态
 union {
 esp_tcp *tcp;
 esp_udp *udp;
 } proto; //一个共用体，包含了一个 tcp 连接参数结构体和 udp
//连接参数结构体
 espconn_recv_callback recv_callback; //接收成功的回调函数
 espconn_sent_callback sent_callback; //发送成功的回调函数
 uint8 link_cnt; //连接数量
 void *reverse; //指针变量，可用来存储相关需要的数据
};
//返回值：0：成功，其他：失败，返回对应的错误码
//ESPCONN_ ARG:未找到参数 espconn 对应的 UDP 连接
//ESPCONN_MEM:空间不足
//ESPCONN_ ISCONN:连接已经建立
//注意：定义的网络结构体必须是全局变量。


//创建TCP server 建立侦听
struct espconn ESPConnect_Struct;//定义网络信息结构体，全局变量
ESPConnect_Struct.type=ESPCONN_TCP;
ESPConnect_Struct.proto.tcp=(esp_tcp*)os_malloc(sizeof(esp_tcp)); //申请内存
ESPConnect_Struct.proto.tcp->local_port=6666;
ESPConnect_Struct.proto.tcp->connect_callback=WIFI_TCP_Connect_Success_Cb;
ESPConnect_Struct.proto.tcp->disconnect_callback=WIFI_TCP_Disconnect_Cb;
ESPConnect_Struct.proto.tcp->reconnect_callback=WIFI_TCP_Reconnect_Cb;
ESPConnect_Struct.recv_callback=ESP8266_TCP_Receive_Cb;
ESPConnect_Struct.sent_callback=ESP8266_TCP_Send_Cb;
espconn_accept(&ESPConnect_Struct);

//注册 ESP8266 TCP server 超时时间（结构体、超时时间s， 当前设置对TCP连接有效 0全部，1仅自己）
espconn_regist_time(&ESPConnect_Struct,300,1);

//通过无线网络发送数据（结构体，发送的内容，内容的长度）
espconn_send(&ESPConnect_Struct,"Hello, I'm esp8266!",os_strlen("Hello, 
I'm esp8266!"));

//查询某个 TCP 连接或者 UDP 传输的远端信息，此函数一般在接收成功的回调函数中调用。（结构体、IP、连接方式 0 正常server 1 SSL server）
sint8 espconn_get_connection_info(struct espconn *espconn, remot_info **pcon_info,uint8 typeflags)
```

```c
//连接 TCP server（ESP8266 作为 TCP client）
struct espconn ESPConnect_Struct;//定义网络信息结构体，全局变量
ESPConnect_Struct.type=ESPCONN_TCP;
ESPConnect_Struct.proto.tcp=(esp_tcp*)os_malloc(sizeof(esp_tcp)); //申请内存
ESPConnect_Struct.proto.tcp->remote_ip[0]=192;
ESPConnect_Struct.proto.tcp->remote_ip[1]=168;
ESPConnect_Struct.proto.tcp->remote_ip[2]=1;
ESPConnect_Struct.proto.tcp->remote_ip[3]=43;
ESPConnect_Struct.proto.tcp->connect_callback=WIFI_TCP_Connect_Success_Cb;
ESPConnect_Struct.proto.tcp->disconnect_callback=WIFI_TCP_Disconnect_Cb;
ESPConnect_Struct.proto.tcp->reconnect_callback=WIFI_TCP_Reconnect_Cb;
ESPConnect_Struct.recv_callback=ESP8266_TCP_Receive_Cb;
ESPConnect_Struct.sent_callback=ESP8266_TCP_Send_Cb;
espconn_connect (&ESPConnect_Struct);truct;//定义网络信息结构体，全局变量

//通过无线网络发送数据
espconn_send(&ESPConnect_Struct,"Hello, I'm esp8266!",os_strlen("Hello, 
I'm esp8266!"));
```
##### TCP_STA示例
###### WIFI_STA_TCP_Sever
```c 
#include "./driver/wifi.h"
#include "espconn.h"
#include "mem.h"
#include "./driver/Peripherals.h"
//WIFI STA模式初始化配置
void ICACHE_FLASH_ATTR WIFI_STA_Mode_Init(void)
{
	struct	station_config STA_Config_Struct;
	struct ip_info sta_ip_info;
	wifi_set_opmode(0x01);		//配置WiFi为STA模式
	os_strcpy(STA_Config_Struct.ssid,WIFI_SSID);			//WiFi名称
	os_strcpy(STA_Config_Struct.password,WIFI_PASS);		//WiFi密码
	wifi_station_set_config(&STA_Config_Struct);
}
//ESP8266 TCP通讯接收成功回调函数
void ICACHE_FLASH_ATTR ESP8266_TCP_Receive_Cb(void *arg, char *pdata, unsigned short len){
	struct	espconn	*pesp_conn=arg;
	os_printf("ESP8266 Receive Data=%s\r\n",pdata);
	//给远端设备回应
	espconn_send(pesp_conn,"ESP8266 Receive Success!\r\n",os_strlen("ESP8266 Receive Success!\r\n"));
}

//TCP连接成功回调函数
void ICACHE_FLASH_ATTR ESP8266_TCP_Connect_Success_Cb(void *arg)
{
	os_printf("ESP8266 TCP Connect Success!\r\n");
}

//TCP正常断开回调函数
void ICACHE_FLASH_ATTR ESP8266_TCP_Disconnect_Cb(void *arg)
{
	os_printf("ESP8266 TCP Disconnect Success!\r\n");
}

//TCP异常断开的回调函数
void ICACHE_FLASH_ATTR ESP8266_TCP_Reconnect_Cb(void *arg, sint8 err)
{
	switch(err)	//输出错误信息
	{
	case ESPCONN_TIMEOUT:
		os_printf("ESPCONN_TIMEOUT!\r\n");break;
	case ESPCONN_ABRT:
		os_printf("ESPCONN_ABRT!\r\n");break;
	case ESPCONN_RST:
		os_printf("ESPCONN_RST!\r\n");break;
	case ESPCONN_CLSD:
		os_printf("ESPCONN_CLSD!\r\n");break;
	case ESPCONN_CONN:
		os_printf("ESPCONN_CONN!\r\n");break;
	case ESPCONN_HANDSHAKE:
		os_printf("ESPCONN_HANDSHAKE!\r\n");break;
	default:
		os_printf("ESPCONN_PROTO_MSG!\r\n");break;
	}

	//需要重新建立TCP连接
	espconn_accept(&ESPConnect_Struct);	//建立TCP侦听
}

//定义网络信息结构体	全局变量
struct	espconn ESPConnect_Struct;

void ICACHE_FLASH_ATTR WIFI_TCP_Init(void)
{
	ESPConnect_Struct.type=ESPCONN_TCP;
	ESPConnect_Struct.proto.tcp=(esp_tcp*)os_malloc(sizeof(esp_tcp));	//申请内存
	ESPConnect_Struct.proto.tcp->local_port=9999;
	ESPConnect_Struct.proto.tcp->connect_callback=ESP8266_TCP_Connect_Success_Cb;	//TCP连接成功回调函数
	ESPConnect_Struct.proto.tcp->disconnect_callback=ESP8266_TCP_Disconnect_Cb;		//TCP正常断开回调函数
	ESPConnect_Struct.proto.tcp->reconnect_callback=ESP8266_TCP_Reconnect_Cb;		//TCP异常断开回调函数

	ESPConnect_Struct.recv_callback=ESP8266_TCP_Receive_Cb;
	ESPConnect_Struct.sent_callback=ESP8266_TCP_Send_Cb;

	espconn_accept(&ESPConnect_Struct);	//建立TCP侦听
	espconn_regist_time(&ESPConnect_Struct,10,0);	//设置超时时间
}


```
调用示例user_main.c
```c 
user_init(void){
	....
	WIFI_STA_Mode_Init();	//配置为STA模式
}
```
###### WIFI_STA_TCP_Client
```C
#include "./driver/os_timer.h"
//ESP8266 TCP通讯发送成功回调函数
void ICACHE_FLASH_ATTR ESP8266_TCP_Send_Cb(void *arg)
{
	os_printf("ESP8266 Send Data OK!\r\n");
}

//TCP连接成功回调函数
void ICACHE_FLASH_ATTR ESP8266_TCP_Connect_Success_Cb(void *arg)
{
	os_timer_disarm(&os_timer_tcp);			//关闭TCP连接定时器
	os_printf("ESP8266 TCP Connect Success!\r\n");
}
//TCP异常断开的回调函数
void ICACHE_FLASH_ATTR ESP8266_TCP_Reconnect_Cb(void *arg, sint8 err)
{
	switch(err)	//输出错误信息
	{
	case ESPCONN_TIMEOUT:
		os_printf("ESPCONN_TIMEOUT!\r\n");break;
	case ESPCONN_ABRT:
		os_printf("ESPCONN_ABRT!\r\n");break;
	case ESPCONN_RST:
		os_printf("ESPCONN_RST!\r\n");break;
	case ESPCONN_CLSD:
		os_printf("ESPCONN_CLSD!\r\n");break;
	case ESPCONN_CONN:
		os_printf("ESPCONN_CONN!\r\n");break;
	case ESPCONN_HANDSHAKE:
		os_printf("ESPCONN_HANDSHAKE!\r\n");break;
	default:
		os_printf("ESPCONN_PROTO_MSG!\r\n");break;
	}

	//需要重新建立TCP连接
	os_timer_arm(&os_timer_tcp,1000,1);		//重新打开TCP连接定时器
}

//定义网络信息结构体	全局变量
struct	espconn ESPConnect_Struct;

void ICACHE_FLASH_ATTR WIFI_TCP_Init(void)
{
	ESPConnect_Struct.type=ESPCONN_TCP;
	ESPConnect_Struct.proto.tcp=(esp_tcp*)os_malloc(sizeof(esp_tcp));	//申请内存
	ESPConnect_Struct.proto.tcp->remote_port=8888;
	ESPConnect_Struct.proto.tcp->remote_ip[0]=192;
	ESPConnect_Struct.proto.tcp->remote_ip[1]=168;
	ESPConnect_Struct.proto.tcp->remote_ip[2]=0;
	ESPConnect_Struct.proto.tcp->remote_ip[3]=6;
	ESPConnect_Struct.proto.tcp->connect_callback=ESP8266_TCP_Connect_Success_Cb;	//TCP连接成功回调函数
	ESPConnect_Struct.proto.tcp->disconnect_callback=ESP8266_TCP_Disconnect_Cb;		//TCP正常断开回调函数
	ESPConnect_Struct.proto.tcp->reconnect_callback=ESP8266_TCP_Reconnect_Cb;		//TCP异常断开回调函数

	ESPConnect_Struct.recv_callback=ESP8266_TCP_Receive_Cb;
	ESPConnect_Struct.sent_callback=ESP8266_TCP_Send_Cb;

	espconn_connect(&ESPConnect_Struct);	//连接TCP Server
}
```

##### TCP_AP示例
###### WIFI_AP_TCP_Sever
```c
#include "./driver/wifi.h"
#include "espconn.h"
#include "./driver/Peripherals.h"
#include "mem.h"

//WIFI AP模式初始化配置
void ICACHE_FLASH_ATTR WIFI_AP_Mode_Init(void)
{
	struct	softap_config AP_Config_Struct;

	wifi_set_opmode(0x02);		//配置WiFi为AP模式

	os_strcpy(AP_Config_Struct.ssid,WIFI_SSID);			//WiFi名称
	os_strcpy(AP_Config_Struct.password,WIFI_PASS);		//WiFi密码
	AP_Config_Struct.ssid_len=sizeof(WIFI_SSID);		//WiFi名称长度
	AP_Config_Struct.authmode=AUTH_WPA2_PSK;			//加密方式
	AP_Config_Struct.beacon_interval=100;				//信标间隔时间
	AP_Config_Struct.channel=1;							//通道号
	AP_Config_Struct.max_connection=4;					//允许最大连接设备数量
	AP_Config_Struct.ssid_hidden=0;						//不隐藏WiFi

	wifi_softap_set_config(&AP_Config_Struct);
}
//ESP8266 TCP通讯接收成功回调函数
void ICACHE_FLASH_ATTR ESP8266_TCP_Receive_Cb(void *arg, char *pdata, unsigned short len){
	struct	espconn	*pesp_conn=arg;
	os_printf("ESP8266 Receive Data=%s\r\n",pdata);
	//给远端设备回应
	espconn_send(pesp_conn,"ESP8266 Receive Success!\r\n",os_strlen("ESP8266 Receive Success!\r\n"));
}

//TCP连接成功回调函数
void ICACHE_FLASH_ATTR ESP8266_TCP_Connect_Success_Cb(void *arg)
{
	os_printf("ESP8266 TCP Connect Success!\r\n");
}

//TCP正常断开回调函数
void ICACHE_FLASH_ATTR ESP8266_TCP_Disconnect_Cb(void *arg)
{
	os_printf("ESP8266 TCP Disconnect Success!\r\n");
}

//TCP异常断开的回调函数
void ICACHE_FLASH_ATTR ESP8266_TCP_Reconnect_Cb(void *arg, sint8 err)
{
	switch(err)	//输出错误信息
	{
	case ESPCONN_TIMEOUT:
		os_printf("ESPCONN_TIMEOUT!\r\n");break;
	case ESPCONN_ABRT:
		os_printf("ESPCONN_ABRT!\r\n");break;
	case ESPCONN_RST:
		os_printf("ESPCONN_RST!\r\n");break;
	case ESPCONN_CLSD:
		os_printf("ESPCONN_CLSD!\r\n");break;
	case ESPCONN_CONN:
		os_printf("ESPCONN_CONN!\r\n");break;
	case ESPCONN_HANDSHAKE:
		os_printf("ESPCONN_HANDSHAKE!\r\n");break;
	default:
		os_printf("ESPCONN_PROTO_MSG!\r\n");break;
	}

	//需要重新建立TCP连接
	espconn_accept(&ESPConnect_Struct);	//建立TCP侦听
}


//定义网络信息结构体	全局变量
struct	espconn ESPConnect_Struct;
void ICACHE_FLASH_ATTR WIFI_TCP_Init(void){
	ESPConnect_Struct.type=ESPCONN_TCP;
	ESPConnect_Struct.proto.tcp=(esp_tcp*)os_malloc(sizeof(esp_tcp));	//申请内存
	ESPConnect_Struct.proto.tcp->local_port=9999;
	ESPConnect_Struct.proto.tcp->connect_callback=ESP8266_TCP_Connect_Success_Cb;	//TCP连接成功回调函数
	ESPConnect_Struct.proto.tcp->disconnect_callback=ESP8266_TCP_Disconnect_Cb;		//TCP正常断开回调函数
	ESPConnect_Struct.proto.tcp->reconnect_callback=ESP8266_TCP_Reconnect_Cb;		//TCP异常断开回调函数

	ESPConnect_Struct.recv_callback=ESP8266_TCP_Receive_Cb;
	ESPConnect_Struct.sent_callback=ESP8266_TCP_Send_Cb;

	espconn_accept(&ESPConnect_Struct);	//建立TCP侦听
	espconn_regist_time(&ESPConnect_Struct,10,0);	//设置超时时间
}
```
调用示例user_main.c
```C
void ICACHE_FLASH_ATTR user_init(void){
	 ...
	WIFI_AP_Mode_Init();	//配置为AP模式
}
```
###### WIFI_AP_TCP_Client
```C
#include "./driver/os_timer.h"

//ESP8266 TCP通讯发送成功回调函数
void ICACHE_FLASH_ATTR ESP8266_TCP_Send_Cb(void *arg)
{
	os_printf("ESP8266 Send Data OK!\r\n");
}

//TCP连接成功回调函数
void ICACHE_FLASH_ATTR ESP8266_TCP_Connect_Success_Cb(void *arg)
{
	os_timer_disarm(&os_timer_tcp);			//关闭TCP连接定时器
	os_printf("ESP8266 TCP Connect Success!\r\n");
}

//TCP异常断开的回调函数
void ICACHE_FLASH_ATTR ESP8266_TCP_Reconnect_Cb(void *arg, sint8 err)
{
	switch(err)	//输出错误信息
	{
	case ESPCONN_TIMEOUT:
		os_printf("ESPCONN_TIMEOUT!\r\n");break;
	case ESPCONN_ABRT:
		os_printf("ESPCONN_ABRT!\r\n");break;
	case ESPCONN_RST:
		os_printf("ESPCONN_RST!\r\n");break;
	case ESPCONN_CLSD:
		os_printf("ESPCONN_CLSD!\r\n");break;
	case ESPCONN_CONN:
		os_printf("ESPCONN_CONN!\r\n");break;
	case ESPCONN_HANDSHAKE:
		os_printf("ESPCONN_HANDSHAKE!\r\n");break;
	default:
		os_printf("ESPCONN_PROTO_MSG!\r\n");break;
	}

	//需要重新建立TCP连接
	os_timer_arm(&os_timer_tcp,1000,1);		//重新打开TCP连接定时器
}

//定义网络信息结构体	全局变量
struct	espconn ESPConnect_Struct;

void ICACHE_FLASH_ATTR WIFI_TCP_Init(void)
{
	ESPConnect_Struct.type=ESPCONN_TCP;
	ESPConnect_Struct.proto.tcp=(esp_tcp*)os_malloc(sizeof(esp_tcp));	//申请内存
	ESPConnect_Struct.proto.tcp->remote_port=8888;
	ESPConnect_Struct.proto.tcp->remote_ip[0]=192;
	ESPConnect_Struct.proto.tcp->remote_ip[1]=168;
	ESPConnect_Struct.proto.tcp->remote_ip[2]=4;
	ESPConnect_Struct.proto.tcp->remote_ip[3]=2;
	ESPConnect_Struct.proto.tcp->connect_callback=ESP8266_TCP_Connect_Success_Cb;	//TCP连接成功回调函数
	ESPConnect_Struct.proto.tcp->disconnect_callback=ESP8266_TCP_Disconnect_Cb;		//TCP正常断开回调函数
	ESPConnect_Struct.proto.tcp->reconnect_callback=ESP8266_TCP_Reconnect_Cb;		//TCP异常断开回调函数

	ESPConnect_Struct.recv_callback=ESP8266_TCP_Receive_Cb;
	ESPConnect_Struct.sent_callback=ESP8266_TCP_Send_Cb;

	espconn_connect(&ESPConnect_Struct);	//连接TCP Server
}
```
