### 介绍关系
	半糖 eda账户是 HalSweet，都是来源 duck 的首版 进行完善。甘草是抄袭后进行自己独立改良卖板子，sammax是只有4.2用三个人的进行了组装，出了个万年历的ui界面。
	注意：sammax 日历的bin 是需要验证码的。 
	激活提供芯片ID，每人免费提供一个验证码，防js倒卖。 所以固件内启用验证码机制，没有验证码部分功能及节目会有影响。
	目前来说 半糖是活跃在更个之间基本解决发烧友的一些小白问题。duck 力不从心主要是为了爱好友不为了牟利有兴趣就更新没兴趣就不更新了。 甘草是牟利的性质不一样。 最早时候是直接做成品卖赚钱。后面被duck发现有人用这牟利。还跟自己改源码。导致不开源源码只开源pcb和原理图。提供bin烧录。直接改了原本的服务器源码导致只能通过人工在数据库加ID让访问服务器。

#### duck
群占时不加人了，因为duck感觉目前能做的东西都做出来了。咸鱼也有卖，其他爱好群里半糖也都在活跃。
#### gl1996  
是有群 215204131  但是没做4.2 
https://oshwhub.com/gl1996/2.9cun-mo-shui-ping-tian-qi-zhan
解读：用半糖的pcb 、 甘草酸不酸的开源程序 ，进行深度修改版主要不用验证码。
半糖的服务器是需要，验证码。

#### 甘草酸不酸   
是阅读器 和 2.9

#### sammax  跟咸鱼的corogoo是认识的 应该是爱好友跟卖成品的心态。
https://gitee.com/corogoo/epaper-42-ink-screen-weather-station-plus

墨水屏采用佳显三色4.2英寸墨水屏 
https://oshwhub.com/sammax/esp8266-4.2cun-san-se-mo-shui-pi
pcb采用半糖版最新4.2pcb  感谢   半糖版pcb 开源链接
https://oshwhub.com/HalfSweet/ThreeColorEPaper
配网界面参考甘草酸不酸开源工程
https://oshwhub.com/jie326513988/tian-qi-mo-shui-ping

墨水屏驱动部分来自duck https://oshwhub.com/duck/4-2-cun-mo-shui-ping-ri-li

### 早期的内测3按键2.9时候测试板子的记录， 现在新版电路跟旧版不一致，仅早期旧版子。
```c
#define CS 15
#define EPD_CS_0	digitalWrite(CS,LOW)
#define EPD_CS_1	digitalWrite(CS,HIGH)
#define isEPD_CS  digitalRead(CS)

#define RST 2
#define EPD_RST_0	digitalWrite(RST,LOW)
#define EPD_RST_1	digitalWrite(RST,HIGH)
#define isEPD_RST digitalRead(RST)

#define DC 0
#define EPD_DC_0  digitalWrite (DC,LOW)
#define EPD_DC_1  digitalWrite (DC,HIGH)

//1、把EPD_drive_gpio.h 文件里的  DC 5   改成 DC 0


//2、注释掉 主文件里的  loop函数的    //部分
void loop() {
 
// if(digitalRead(0)==LOW)
// {
//   WiFiManager wifiManager;
//  wifiManager.resetSettings();
// }

    EPD.deepsleep();
    byte seconds=timeClient.getSeconds_byte();
    if(seconds>50) timeupdateinterval=seconds+60;
    else timeupdateinterval=60-seconds;
    timeClient.localEpoc+=timeupdateinterval;

    write_time_to_rtc_mem();//save time before sleeping
    #ifdef debug
     Serial.printf("Finish at %dms\n",millis());
    #endif
    ESP.deepSleep(timeupdateinterval * 1 * 1000000,WAKE_RF_DISABLED); 

}

//3、  pinMode(D3,INPUT);  这个也删掉  也是在 主文件
```

```c
连接数热点后
    192.168.4.1  打开这个网址
    
选择wifi   
写下面的城市代码    
CN101230101	fuzhou	福州
CN101230103	minhou	闽侯


    
```

#### 2022/11/1  补充 已更新 和步骤 （目的：早期烧录的板子 回顾记录 现在仅是bin烧录了，早期是源码烧录）
https://oshwhub.com/duck/esp8266-weather-station-epaper#P6     PCB和原理图
要开电下载
1、下载源已经更新为https 。
http://arduino.esp8266.com/stable/package_esp8266com_index.json
变更为
https://arduino.esp8266.com/stable/package_esp8266com_index.json

2、下载时候太慢就挂vpn 最好是全局的安装包的那种，速度秒下。  一个是开发板管理器，一个是管理库 注意看清楚。
工具-开发板-开发板管理器。添加esp, 版本2.3.0 
工具-管理库。添加wifimanager，版本0.12.0   

3、选 开发板 为 nodemcu1.0 
配置 波特率，cpu频率，flash大小。 选下端口号。 然后先传字库给板子比较慢。
要到 100%才算结束。

4、就传字库 比较慢要大概30s以上吧。 然后再下载程序 比较快大概7-8s。  根据编程环境搭及程序上传1.6.word 里面有截图参考。
5、 靠电源 那边 拨是上电。
6、按住reset 有效会连闪烁两次esp灯

7、填写wifi  按 第一个去填
8、wifi 乱码 把 utf-8的文本 编辑好， 用vscode 打开 改为 gbk 编码 就是对应的文本