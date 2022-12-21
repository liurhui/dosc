#### 12、IIC 协议(配套示例OLED_I2C) 
##### 基础熟记
	IIC 由四根线组成：
		1、VCC、SDA、SCL、GND
		2、SDA 是数据总线，SCL 是时钟总线
		3、SDA、SCL 分别加一个上拉电阻到VCC
		4、同时连接设备数量由电容累计最大400pF,通常不超过8个设备。（除了开发板和大项目，小项目通常用1-2个设备屏幕和存储器）。
	时序：
		1、起始信号：SCL=1,SDA=1->0;
		2、结束信号：SCL=1,SDA=0->1;
		3、数据（还是由SCL和SDA组合形成有时序要求）。
			3.1、一个时钟周期1bit，SCL=1;SDA数据有效。SCL=0;SDA数据无效，数据包是8bit。
		4、地址与方向是7bit或10bit。通常用7bit，加1bit的方向表示读（1）写（0）。1是由主发给从，0表示由从发给主。于是可以看作读和写。
	5、响应（ack包），接收设备收到数据给发送方一个，ack表示继续接收，nack 表示不接收了。ack:SCL=1,SDA=0;   nack:SCL=0,SDA=1;
	
	说明:
		1、i2c_master.c 只封装i2c协议时序，通过对寄存器设置电平，和保持电平时常。
##### i2c时序示例(i2c_master.c)
	组合: 起始信号+地址与方向+响应+数据包+响应+...+结束信号 
```c 
LOCAL uint8 m_nLastSDA;
LOCAL uint8 m_nLastSCL;

//因为GPIO 所以直接同时set 两个IO口 SDA为pin0  SCL为pin4
LOCAL void ICACHE_FLASH_ATTR i2c_master_setDC(uint8 SDA, uint8 SCL){
    SDA	&= 0x01;
    SCL	&= 0x01;
    m_nLastSDA = SDA;
    m_nLastSCL = SCL;
    if ((0 == SDA) && (0 == SCL)) {
        I2C_MASTER_SDA_LOW_SCL_LOW();
    } else if ((0 == SDA) && (1 == SCL)) {
        I2C_MASTER_SDA_LOW_SCL_HIGH();
    } else if ((1 == SDA) && (0 == SCL)) {
        I2C_MASTER_SDA_HIGH_SCL_LOW();
    } else {
        I2C_MASTER_SDA_HIGH_SCL_HIGH();
    }
}

//起始信号
void ICACHE_FLASH_ATTR i2c_master_start(void){
    i2c_master_setDC(1, m_nLastSCL);
    i2c_master_wait(5);
    i2c_master_setDC(1, 1);
    i2c_master_wait(5);	// sda 1, scl 1
    i2c_master_setDC(0, 1);
    i2c_master_wait(5);	// sda 0, scl 1
}

//结束信号
void ICACHE_FLASH_ATTR i2c_master_stop(void){
    i2c_master_wait(5);
    i2c_master_setDC(0, m_nLastSCL);
    i2c_master_wait(5);	// sda 0
    i2c_master_setDC(0, 1);
    i2c_master_wait(5);	// sda 0, scl 1
    i2c_master_setDC(1, 1);
    i2c_master_wait(5);	// sda 1, scl 1
}

//写字节
void ICACHE_FLASH_ATTR i2c_master_writeByte(uint8 wrdata){
    uint8 dat;
    sint8 i;
    i2c_master_wait(5);
    i2c_master_setDC(m_nLastSDA, 0);
    i2c_master_wait(5);
    for (i = 7; i >= 0; i--) {
        dat = wrdata >> i;
        i2c_master_setDC(dat, 0);
        i2c_master_wait(5);
        i2c_master_setDC(dat, 1);
        i2c_master_wait(5);
        if (i == 0) {
            i2c_master_wait(3);   ////
        }
        i2c_master_setDC(dat, 0);
        i2c_master_wait(5);
    }
}

// 接收ack
uint8 ICACHE_FLASH_ATTR i2c_master_getAck(void){
    uint8 retVal;
    i2c_master_setDC(m_nLastSDA, 0);
    i2c_master_wait(5);
    i2c_master_setDC(1, 0);
    i2c_master_wait(5);
    i2c_master_setDC(1, 1);
    i2c_master_wait(5);

    retVal = i2c_master_getDC();
    i2c_master_wait(5);
    i2c_master_setDC(1, 0);
    i2c_master_wait(5);

    return retVal;
}

//设置ack
void ICACHE_FLASH_ATTR i2c_master_setAck(uint8 level){
    i2c_master_setDC(m_nLastSDA, 0);
    i2c_master_wait(5);
    i2c_master_setDC(level, 0);
    i2c_master_wait(5);	// sda level, scl 0
    i2c_master_setDC(level, 1);
    i2c_master_wait(8);	// sda level, scl 1
    i2c_master_setDC(level, 0);
    i2c_master_wait(5);	// sda level, scl 0
    i2c_master_setDC(1, 0);
    i2c_master_wait(5);
}

//校验ack还是nack
bool ICACHE_FLASH_ATTR i2c_master_checkAck(void){
    if(i2c_master_getAck()){
        return FALSE;
    }else{
        return TRUE;
    }
}

//读方向
void ICACHE_FLASH_ATTR i2c_master_send_ack(void){
    i2c_master_setAck(0x0);
}

//写方向
void ICACHE_FLASH_ATTR i2c_master_send_nack(void){
    i2c_master_setAck(0x1);
}
```
调用示例(oled.c)
```c
//利用i2c 协议来传输一个byte
uint8_t ICACHE_FLASH_ATTR I2C_WriteByte(uint8_t addr,uint8_t data)
{
	i2c_master_start();

	i2c_master_writeByte(OLED_ADDR);//发送IIC设备地址
	if(i2c_master_checkAck()==FALSE)//检查应答信号
	{
		i2c_master_stop();
		return 1;
	}

	i2c_master_writeByte(addr);		//发送寄存器地址
	if(i2c_master_checkAck()==FALSE)//检查应答信号
	{
		i2c_master_stop();
		return 1;
	}

	i2c_master_writeByte(data);		//发送数据
	if(i2c_master_checkAck()==FALSE)//检查应答信号
	{
		i2c_master_stop();
		return 1;
	}

	i2c_master_stop();		//发送结束信号
	return 0;
}
```
配置 GPIO 口为IIC 管脚
```c
// 
void ICACHE_FLASH_ATTR i2c_master_init(void){
    uint8 i;

    i2c_master_setDC(1, 0);
    i2c_master_wait(5);

    // when SCL = 0, toggle SDA to clear up
    i2c_master_setDC(0, 0) ;
    i2c_master_wait(5);
    i2c_master_setDC(1, 0) ;
    i2c_master_wait(5);

    // set data_cnt to max value
    for (i = 0; i < 28; i++) {
        i2c_master_setDC(1, 0);
        i2c_master_wait(5);	// sda 1, scl 0
        i2c_master_setDC(1, 1);
        i2c_master_wait(5);	// sda 1, scl 1
    }

    // reset all
    i2c_master_stop();
    return;
}

//初始化GPIO   用到大量的宏和api
void ICACHE_FLASH_ATTR i2c_master_gpio_init(void){
    ETS_GPIO_INTR_DISABLE() ;//关闭 GPIO 中断
//	ETS_INTR_LOCK();

    PIN_FUNC_SELECT(I2C_MASTER_SDA_MUX, I2C_MASTER_SDA_FUNC);
    PIN_FUNC_SELECT(I2C_MASTER_SCL_MUX, I2C_MASTER_SCL_FUNC);
// 每个gpio 占4bit 所以扩展为4bit得出在整个gpio的位置。
// SDA pin0在gpio总地址位  ,  读 pin0在gpio总地址位，使能 pin0
    GPIO_REG_WRITE(GPIO_PIN_ADDR(GPIO_ID_PIN(I2C_MASTER_SDA_GPIO)), GPIO_REG_READ(GPIO_PIN_ADDR(GPIO_ID_PIN(I2C_MASTER_SDA_GPIO))) | GPIO_PIN_PAD_DRIVER_SET(GPIO_PAD_DRIVER_ENABLE)); //open drain;
    GPIO_REG_WRITE(GPIO_ENABLE_ADDRESS, GPIO_REG_READ(GPIO_ENABLE_ADDRESS) | (1 << I2C_MASTER_SDA_GPIO));
// SCL pin4在gpio总地址位 ,  读 pin4在gpio总地址位，使能 pin4    
    GPIO_REG_WRITE(GPIO_PIN_ADDR(GPIO_ID_PIN(I2C_MASTER_SCL_GPIO)), GPIO_REG_READ(GPIO_PIN_ADDR(GPIO_ID_PIN(I2C_MASTER_SCL_GPIO))) | GPIO_PIN_PAD_DRIVER_SET(GPIO_PAD_DRIVER_ENABLE)); //open drain;
    GPIO_REG_WRITE(GPIO_ENABLE_ADDRESS, GPIO_REG_READ(GPIO_ENABLE_ADDRESS) | (1 << I2C_MASTER_SCL_GPIO));

    I2C_MASTER_SDA_HIGH_SCL_HIGH();

    ETS_GPIO_INTR_ENABLE() ;//使能 GPIO 中断
//	ETS_INTR_UNLOCK();

    i2c_master_init();
}
```

##### i2c时序示例(oled.c)
	1、oled.c oled由驱动SSD1306芯片是分为寄存器部分和显示部分。需要借助i2c的有效数据即byte 来传输给oled 地址、寄存器、值，进行初始化oled使能电路。开关每个坐标使其发亮或熄灭。
	2、128*64个点，列128，行64。
	3、ESP8266只能做主设备，不能做从设备。
```C
// 向OLED写入命令
// command：命令代码
void ICACHE_FLASH_ATTR WriteCmd(unsigned char command)//写命令
{
	I2C_WriteByte(0x00, command);
}


//向OLED寄存器地址写一个byte的数据
//addr：寄存器地址 0x00代表data为命令 0x40代表data数据
//data：数据
//返回值 成功：0 失败：1
uint8_t ICACHE_FLASH_ATTR I2C_WriteByte(uint8_t addr,uint8_t data)
{
	i2c_master_start();

	i2c_master_writeByte(OLED_ADDR);//发送IIC设备地址
	if(i2c_master_checkAck()==FALSE)//检查应答信号
	{
		i2c_master_stop();
		return 1;
	}

	i2c_master_writeByte(addr);		//发送寄存器地址
	if(i2c_master_checkAck()==FALSE)//检查应答信号
	{
		i2c_master_stop();
		return 1;
	}

	i2c_master_writeByte(data);		//发送数据
	if(i2c_master_checkAck()==FALSE)//检查应答信号
	{
		i2c_master_stop();
		return 1;
	}

	i2c_master_stop();		//发送结束信号
	return 0;
}
```
