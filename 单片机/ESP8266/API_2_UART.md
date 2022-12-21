#### 2、UART(配套示例UART)
**参考文档：（p63）**
	esp8266-technical_reference_cn.pdf
##### 基础熟记
![[ESP8266的串口时序.PNG]]
**发送**： 低位前高位后 `bit0 ~ bit7`  顺序
**共10bit**  1起始 8bit 1停止，`11520个/秒 *10 = 115200bps`
**校验位**
```plaintext
奇校验：10101001 则 凑1变成奇数个101010011 
偶校验：10101001 则 凑1变成偶数个101010010
0校验 ：直接拼接0
1校验 ：直接拼接1
无校验则不加
```
**有校验位的数据包**：起始位，有效数据，校验位，停止位。
**屏蔽上电打印：** 没什么好办法只能改引脚，把上电默认的引脚改为别的引脚，串口工具只会去读默认引脚。
```c
// 举例
system_uart_swap(){
//U0TXD，U0RXD  改为对应U0RTS（MTDO/GPIO15），UOCTS(MTCK/GPIO13)
//烧录还走U0TXD 和 U0RXD
//GPIO15  对应RXD
//GPIO13  对应 TXD
}
```
**上电打印乱码原因**
```plaintext
	esp8266-F 有两个分别是UART0 和 UART1，烧录默认用UART0。
	UART0 默认开启，UART1默认关闭。 
	ESP8266芯片本身支持26MHz 和40MHz 的晶振，若使用40MHz晶振，则默认波特率为115200，若使用26MHz晶振，则UART0上电后的波特率 = 26*115200/40 = 74880。
	安信可的ESP8266系列模组均使用26MHz，由于一般的串口工具不会支持这个波特率，所以上电时会有打印乱码。得用带有74880的串口助手（安信可有提供）。
```
**UART0、UART1区别**
```plaintext
UART0: 既有发送引脚(TXD)也有接收引脚(RXD)
    U0TXD: pin26(U0TXD)
    U0RXD: pin25(U0RXD)
    U0CTS: pin12(MTCK)
    U0RTS: pin13(MTDO)
UART1:而 UART1 只有发送引脚(TXD)引脚为 GPIO2
    U1TXD: pin14(GPIO2)
```
##### 常用的API(通常main.c是这么去写)
	1、头文件 (目录\driver_lib\driver\)
	2、初始化
	3、发送字符串函数
	4、系统打印函数来打印串口写法
```c
//头文件  
uart.c
uart.h 
uart_register.h

//初始化
void uart_init(115200,115200);  //UART0波特率，UART1波特率

 //发送字符串函数
uart0_sendStr("\r\n Hello Word! \r\n"); 串口0的发送字符串函数
uart1_sendStr_no_wait("\r\n Hello Word! 1 \r\n"); //串口1的发送字符串函数
//系统打印函数来打印串口写法
UART_SetPrintPort(UART1);  //参数UART号， UART0 或者 UART1
```

##### API集合(驱动uart.c用到的)
	1、设置串口数据长度
	2、设置停止位长度
	3、设置反相
	4、设置校验位使能和校验方式
	5、设置波特率
	6、设置流量控制也就是串口接收中断阈值 (还得配置中断寄存器所以api和宏比较多)
```c
//数据位
	#define UART_BIT_NUM 0x00000003 //数据位长度占用两个bit
	设置这两个bit可以配置数据长度0:5bit; 1:6bit；2:7bit；3:8bit
	#define UART_BIT_NUM_S    2     //寄存器偏移为2（第2bit开始）
void UART_SetWordLength(uint8 uart_no, UartBitsNum4Char len);

//停止位
	#define UART_STOP_BIT_NUM    0x00000003    //数据位长度占用两个bit
	设置这两个bit可以配置停止位长度 1:1bit；2:1.5bit；3:2bit
	#define UART_STOP_BIT_NUM_S    4    // 寄存器偏移为4(第4bit开始)
void UART_SetStopBits(uint8 uart_no, UartStopBitsNum bit_num);

//反相
    UART 各个信号输入与输出信号，可在内部进行反向配置
    #define UART_DTR_INV    （BIT(24)）
    #define UART_RTS_INV     (BIT(23))
    #define UART_TXD_INV     (BIT(22))
    #define UART_DSR_INV     (BIT(21))
    #define UART_CTS_INV     (BIT(20))
    #define UART_RXD_INV     (BIT(19))
    将对应寄存器置位，可以将对应信号线反向输出/输入。
void UART_SetLineInverse(uint8 uart_no, UART_LineLevelInverse inverse_mask);

//校验位
#define UART_PARITY_EN (BIT(1)) 校验使能：1：enable; 0：diable
#define UART_PARITY    (BIT(0)) 校验类型设置 1：奇校验；0：偶校验
void UART_SetParity(uint8 uart_no, UartParityMode Parity_mode);

//波特率 300 ~ 115200*40
void UART_SetBaudrate(uint8 uart_no,uint32 baud_rate);


//流量控制配置过程：
/* a. 先配置uart0的pin12，pin13脚复用为U0CTS,和U0RTS功能。*/
#define FUNC_U0RTS    4
#define FUNC_U0CTS    4
PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_U0RTS);
PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_U0CTS);
    
/*b. 接收方向的硬件流控可以配置阀值，当 rx fifo 中的长度大于所设的阀值， U0RTS脚就会拉高，阻止对方发送。
    配置接收流控制阀：
    阀值相关的配置一般都在UART_CONF1定义的寄存器中
    */
#define UART_RX_FLOW_EN (BIT(23))  // 第23bit使能接收流控: 0:disable; 1:enable
#define UART_RX_FLOW_THRHD 0x0000007F  // 门限值，占用7bit，范围0~127
#define UART_RX_FLOW_THRHD_S    16   // 寄存器偏移为16 (第16bit开始)

/* c. 发送方向的流控只需配置使能，该寄存器在UART_CONF0中：*/ 
  
#define UART_TX_FLOW_EN    (BIT(15))   // 使能发送流控: 0:disable; 1:enable
void UART_SetFlowCtrl(uint8 uart_no,UART_HwFlowCtrl flow_ctrl,uint8 rx_thresh);
void UART_WaitTxFifoEmpty(uint8 uart_no , uint32 time_out_us); /*do not use if tx flow control enabled*/
void UART_ResetFifo(uint8 uart_no);
void UART_ClearIntrStatus(uint8 uart_no,uint32 clr_mask);
void UART_SetIntrEna(uint8 uart_no,uint32 ena_mask);


//切换打印函数输出端口
/*   
	默认情况下，系统打印函数 os_printf 从 uart0 口输出内容，通过以下接口可以设置从 uart0 或者 uart1 口输出打印。
*/
void UART_SetPrintPort(uint8 uart_no);
bool UART_CheckOutputFinished(uint8 uart_no, uint32 time_out_us);
```
##### 配置串口接收中断（什么时候退出接收状态这部分在uart.c）
```plaintext
	由于所有中断事件在发送到中断控制器之前会一起进行“或运算”操作，所以任意时刻 UART 只能向中断产生一个中断请求。通过查询中断状态函数 UART_INT_ST(uart_no),软件可以在同一个中断服务函数里处理多个中断事件
(多个并列的if语句)。
```
**用到的寄存器**
```plaintext
uart的中断寄存器有：
    UART_INT_RAW 中断原始状态寄存器
    UART_INT_ENA 中断使能寄存器：表示当前使能的uart中断
    UART_INT_ST 中断状态寄存器：表示当前有效的中断状态
    UART_INT_CLR 清除中断寄存器：置对应位来清除中断状态寄存器
 
接口：
    打开中断使能：UART_ENABLE_INTR_MASK(uart_no, ena_mask)；
    关闭中断使能：UART_DISABLE_INTR_MASK(uart_no, disable_mask);
    清除中断状态：UART_CLR_INTR_STATUS_MASK(uart_no, clr_mask);
    获取中断状态：UART_GET_INTR_STATUS(uart_no);
```
**用到的宏定义（串口接收中过程会触发的三种中断，用宏封装）**	
** 区别在于：**
		一个是手动分长度超过了长度则触发，人为设置阀值并且数据不会丢失。
		一个是自动但是超过了（系统）默认的最大长度，溢出中断触发则一般都会存在数据丢失。
		一个是开始接收数据后，长时间内没有接收到则表示结束接收。
**总结：**
	阈值、使能、清除状态。（即手动设置长度也叫full中断）
	溢出、使能、清除状态。（在没有配置阈值时候就用这个即自动溢出中断）
	超时、使能、清除状态。（也叫tout中断）
**一、full中断 (中断状态位：UART_RXFIFO_FULL_INT_ST)**
```plaintext
	说明：rx(接收)fifo数据比较长要用到，比如,配置阀值为100，并使能full中断，当串口收到100字节后，会触发full中断。
    
    1、配置 full中断阀值(或门限值)：(在UART_CONF1寄存器)
    #define UART_RXFIFO_FULL_THRHD    0x0000007F    // 门限值mask,7bit长,范围0-127
    #define UART_RXFIFO_FULL_THRHD_S  0    // 寄存器偏移为0 (第0bit开始)
    
    2、设置full中断使能：(在UART_INT_ENA寄存器的bit0)
    #define UART_RXFIFO_FULL_INT_ENA  (BIT(0))    // 1:enable; 0:disable
    
    3、清除full中断状态：
		对于full中断比较特殊，需要先将接收fifo中的数据全部读空，然后写清楚中断状态寄存器。否则推出后，中断状态位还是会被置上。
    
```
**二、溢出中断 (中断状态位：UART_RXFIFO_OVF_INT_ST)**
```plaintext
    说明：当接收队列的长度大于队列总长度(128bytes)时，会触发该中断信号。
    
    1、设置溢出中断使能：(在UART_INT_ENA寄存器的bit4)
    #define UART_RXFIFO_OVF_INT_ENA    (BIT(4))  // 1:enable; 0:disable
    
    2、清除中断状态：
	    读取队列值，使队列长度小于128，然后置清除中断状态寄存器即可。
```
**三、tout超时中断 (中断状态位：UART_RXFIFO_TOUT_INT_ST)**
```plaintext
    说明：当uart开始接收数据后，停止传输的时间超过所设定的门限值，就
会触发tout中断。

    1、配置tout中断阀值（或门限值）：(在UART_CONF1寄存器中)
    Tout阀值的单位为8个uart数据比特的时间(近似一个byte)
    #define UART_RX_TOUT_EN    (BIT(31))    // 超时功能使能位：1：enable；0：disable
    #define UART_RX_TOUT_THRHD 0x0000007F   // 超时阀值配置位，共7位，范围0-127
    #define UART_RX_TOUT_THRHD_S 24         // 寄存器偏移为24 (第24bit开始)
    
    2、设置tout中断使能：(在UART_INT_ENA寄存器的bit8)
    #define UART_RXFIFO_TOUT_INT_ENA    (BIT(8))  // 1:enable;0:disable 
    
    3、清除中断状态：
	    与full中断类似，tout中断也需要先将接收fifo中的数据全部读空，然后写清除中断状态寄存器，否则退出后中断状态还是会被置上。
```

**四、full和tout 在uart.c   91行 是怎么配置寄存器的**
	把宏和寄存器 用接口 去设置
```C
//通过 WRITE_PERI_REG 给 uart0  配置UART_CONF1 寄存器 即 接收中断

//配置 full中断阀值100 
//7f & 100 =  0111 1111 &0110 0100 = 0110 0100     << 0   即值移动 0bit

//配置中断阀值
 WRITE_PERI_REG(
		 UART_CONF1(uart_no),
        ((100 & UART_RXFIFO_FULL_THRHD) << UART_RXFIFO_FULL_THRHD_S)|
        (0x02 & UART_RX_TOUT_THRHD) << UART_RX_TOUT_THRHD_S |
        UART_RX_TOUT_EN|
        ((0x10 & UART_TXFIFO_EMPTY_THRHD)<<UART_TXFIFO_EMPTY_THRHD_S));|
       SET_PERI_REG_MASK(UART_INT_ENA(uart_no), UART_RXFIFO_TOUT_INT_ENA |
       UART_FRM_ERR_INT_ENA
  );
 //清除状态
 WRITE_PERI_REG(UART_INT_CLR(uart_no), 0xffff);
 //使能中断
 SET_PERI_REG_MASK(
	 UART_INT_ENA(uart_no), 
	 UART_RXFIFO_FULL_INT_ENA|
	 UART_RXFIFO_OVF_INT_ENA
);

```
