### ADC 

![](ADC接线.png)

测试电压 VREF+ 最高测3.3V ，最低测量电压VREF-   ，接GND也就成0V 。
VREF+ 接VDDA一起 串一个磁珠（600R 100MHZ ）接到3.3V 。 

**超出 0- 3.3V测量**
	通过外部电路矫正到测量电压  
	![[ADC可以测量 负10v到正10v.png]]
**怎么取电阻值通过基尔霍夫定律**KCL
	R1 和R2 都是输入，R3输出 。中间点看作是Vout ，R2 R1 输入为Vint。输入-输出 /电阻
	这里我们知道Vint 是负10V ，R2 R1 R3是阻值，算出 Vout  ？   
	下面的 Vout =（Vint +10）/6  是简化了上面的公式
![求阻值](求阻值.png)
	假设R2 R3 电阻不知道  
	列 两个方程   根据（Vint - Vout）/R2+(3V3 - Vout)/R1 =Vout /R3     
	Vint  10V 时    Vout 为 0V   、3.3V来算出R2和R3 
	当3个电阻都扩大10被则 这里的误差会越小。
**共3组ADC18个通道  ，外部16个**
	通常 前两组通道是一样的。第三组通道通道口会由IO引脚个数的匮乏。减少了部分的通道。改变了通达的IO口 

![ADC通道IO图](ADC通道IO图.png)
	看IO去查芯片手册

#### 外部通道到内部转换为 规则和注入
1. 规则通道  最多16条通道 ，平时用的都是规则。
2. 注入通道  最多4条通道 ，只有在规则通道的基础上，做插队的行为进行升级。

**规则通道转换顺序**
	使用寄存器 SQR1、SQR2、SQR3     其中 SQR1  的最低4位设置使用个数  其余位设置优先级。
![ADC通道优先级设置及使用通道个数](ADC通道优先级设置及使用通道个数.png)
**注入序列转换顺序**
	使用寄存器JSQR 这个转换的顺序 不根据优先级， 是依据  JL如果 有4个要转换从JSQ1开始， 有2个要转换从JSQ3开始 。

![ADC注入通道转换顺序](ADC注入通道转换顺序.png)

####  触发源
![ADC控制寄存器](ADC控制寄存器.png)

1. 相当于信号告诉什么时候启动触发
2. 分为 **软件触发**
   ADON  /   SWSTART   /   JSESTART
   ADON  =1 启动模拟转数字    SWSTART  规则通道开启转换    JSESTART   注入通道开启转换
3. 分为 **外部事件触发**  来自内部定时器或者外部 IO
   ADC_CR2:EXTSEL[2:0]和 JEXTSEL[2:0]
   两个 控制位是开关
![[外部事件触发 内部定时器.png]]

#### 转换时间
   采样时间+12.5个周期
**ADC_CLK**： 最大14MHZ   
**寄存器RCC_CFGR 设置 ADCPRE[1:0] 由PCLK2提供** ，可分频 2/4/6/8  。把 **PCLK=72M**，分频后变成ADC_CLK

数字时钟：RCC_APB2ENR,用于访问寄存器
采样时间：ADC 使用若干个ADC_CLK周期完成对输入的模拟量进行采样

| ADC_SMPR2              |     ADC_SMPR1     |
| :--------------------- | :---------------: |
| SMPx[2:0]位            |    SMPx[2:0]位    |
| 控制通道 0-9           |  控制通道 10-17   |
| 000-111 对应不同的周期 | 常用000为 1.5周期 |

1.5+12.5 =14Mhz    但是我们通常12Mhz这样要去计算 分频
```
PCLK2=72M    ADC_CLK =72/6 =12M   
Tconv =1.5+12.5=14周期   =14/12us =1.17us    如果是 14M变成 1us  采样率就是 1Mhz
```

#### 数据存储器
1. 规则组数据存在 **ADC_DR**寄存器
   1.单独使用一组ADC称为独立模式 由于12位分辨率 所以能存放  且放低地址1-16位
   2.数据低地址的高地址还是低地址对齐 ： ALIGN  。
   1.如果是两组ADC 则 ADC2放在高16位  ADC1 放在低16位。
   1.如果多次使用且每次用一组那么采用DMA 存储法  避免存储在低位里面这样数据不会被覆盖。
   ![ADC存储](ADC存储.png)

2. 注入组数据存在**JDRx**寄存器
    这里刚好有4个 分别 JDR0、JDR1、JDR2、JDR3  这样存储就非常方便 不存在覆盖

#### ADC中断
	标志位3个： EOC 规则通道   JEOC 注入通道   AWD 看门狗  
	AWD 都是 由两个 12位寄存器组成起到电压保护的作用 高于多少 低于多少

#### 电压转换
	计算算出模拟量 
```plaintext
1、电压输入范围 0-3.3v
2、分辨率为 12位
3、最小精度为 3.3/2^12
4、设数字量为X，则有模拟量 Y=（3.3/2^12）*X
    Y就是 采集到的电压
```

#### ADC中断方式代码
##### 初始化结构体
**调用固件库**  目的 把初始化的成员写到相应的内存里才能配置成功

```c
1、void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct); 
2、void RCC_ADCCLKConfig(uint32_t RCC_PCLK2); //配置时钟 属于stm32f10x_rcc.h 680行
3、void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
4、void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState); // 开启ADON 
5、void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState); //配置软件触发
6、void ADC_ExternalTrigConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState); //外部触发

/*45 是用于单ADC模式  使用双重时候用6  ADC2需要配置为外部触发 */
7、void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState); //参数一配置哪个ADC，参数二为 ENABLE 或DISABLE 是否采集转换完后要把数据转移别的地方去存储，避免覆盖了之前的数据。
```

**ADC_Init的初始化结构体**
	文件在  stm32f10x_adc.h
```c
/*模式*/    
uint32_t ADC_Mode;
	使用独立模式#define ADC_Mode_Independent       ((uint32_t)0x00000000)  
   // 其余的都是双重模式
配置寄存器ADC_CR1   的DUALMOD[3:0]    0000 独立模式    0001-1001 都是ADC1/2同时使用分为8种模式 
	这8种模式
0101	同步注入模式       
0110	同步规则模式 //示波器 //就是ADC2和ADC1同时工作转换一个规则通道组， 这样主ADC1放低16位，从ADC2放高16位，同时就是转换的数据处于同样的内容。
0111	快速交叉模式 //当ADC2触发后 ADC1 需要等 7个ADCclk  后触发
1000	慢速交叉模式 //只能采集一个通道， 采集要转换完毕才再次采集，这里就是使用ADC1/2交叉 这样提高采集转换的速度 //当ADC2触发后 ADC1 需要等 14个ADCclk  后触发
1001	交替触发模式 //ADC1和ADC2轮流采集注入通道组，当ADC1所有通道采集完毕后，在采集ADC2的通道。循环工作。与交叉不同
```

```c
/*扫描模式*/
FunctionalState ADC_ScanConvMode; 
配置 寄存器ADC_CR1	 的SCAN  
 	一行一行的通道读取 

多通道 ENABLE  单通道DISABLE
```

```c
/*连续转换模式*/
FunctionalState ADC_ContinuousConvMode;
配置ADC_CR2	的CON
	对通道一直采集
```

```c
/*启动规则通道转换的外部触发转换选择*/
uint32_t ADC_ExternalTrigConv; 
配置ADC_CR2	的EXTTRIG和EXTSEL[2:0]
    111是软件触发
    //以下是写好的地址
#define ADC_ExternalTrigConv_T1_CC1    ((uint32_t)0x00000000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrigConv_T1_CC2    ((uint32_t)0x00020000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrigConv_T2_CC2    ((uint32_t)0x00060000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrigConv_T3_TRGO   ((uint32_t)0x00080000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrigConv_T4_CC4    ((uint32_t)0x000A0000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrigConv_Ext_IT11_TIM8_TRGO    ((uint32_t)0x000C0000) /*!< For ADC1 and ADC2 */

#define ADC_ExternalTrigConv_T1_CC3     ((uint32_t)0x00040000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrigConv_None        ((uint32_t)0x000E0000) /*!< For ADC1, ADC2 and ADC3 */  软件触发宏

#define ADC_ExternalTrigConv_T3_CC1      ((uint32_t)0x00000000) /*!< For ADC3 only */
#define ADC_ExternalTrigConv_T2_CC3      ((uint32_t)0x00020000) /*!< For ADC3 only */
#define ADC_ExternalTrigConv_T8_CC1      ((uint32_t)0x00060000) /*!< For ADC3 only */
#define ADC_ExternalTrigConv_T8_TRGO     ((uint32_t)0x00080000) /*!< For ADC3 only */
#define ADC_ExternalTrigConv_T5_CC1      ((uint32_t)0x000A0000) /*!< For ADC3 only */
#define ADC_ExternalTrigConv_T5_CC3      ((uint32_t)0x000C0000) /*!< For ADC3 only */ 
```

```c
/*数据对齐*/
uint32_t ADC_DataAlign;
配置ADC_CR2	的ALIGN
 0 右对齐  1左对齐   //通常 右对齐
 右对齐 ADC_DataAlign_Right 
 左对齐 ADC_DataAlign_Left    
```

```c
/*规则通道的转换的个数*/
uint8_t ADC_NbrOfChannel; 
规则配置ADC_SQR1	的L[3:0]
    0000-1111
注入配置ADC_JSQR    的JL[3:0] 
    00-11
```

霸道和指南者 纯净的 ADC接口 做演示

![](ADC纯净接口.png)

PC1使用跳帽接到 滑动变阻器上达到 0-3.3V的电压采集
指南者的PC0接到SPI 这里不够纯净。  剩余的4个通道都是纯净的ADC
##### 独立通道代码实现利用串口创建一个驱动文件夹
创建 驱动文件 .h 和.c 再加到项目里
```c
static void ADCx_GPIO_Config()
{
    //配置 ADC的 为输入GPIO  
}
static void ADCx_Mode_Config(void)
3、void ADC_RegularChannelConfig(ADC_x, ADC_Channel, 1, ADC_SampleTime_55Cycles5);
	1、哪个ADC 2、哪个通道 3、转换顺序 4、采样时间周期
        
    /*使能ADC转换完成中断 配置中断优先级*/    
4、void ADC_ITConfig( ADC_x, ADC_IT_EOC, enable);
	1、哪个ADC  2、规则通道ADC_IT_EOC 3、使能转换ADC
5、void ADC_Cmd(ADC_x, ENABLE); 
	1、哪个ADC 2、使能ADC准备开始转换
6、 ADC_StartCalibration(ADC_x);
		while(ADC_GetCalibrationStauts(ADC_x));  循环检测是否置1	
	1、 校准ADC   ADC_CR2 的 CAL  会是RSTCAL置1 我们检测 RSTCAL
7、void ADC_SoftwareStartConvCmd(ADC_x, ENABLE); 
		1、哪个ADC  2、软件触发

static void ADC_NVIC_Config(void)
{//配置中断优先级
            
}
void ADCx_Init(void)
{
    ADC_NVIC_Config();
    ADCx_GPIO_Config();
	ADCx_Mode_Config();
}
//在 头文件里 声明下 就可以给main 调用
在中断文件里写中断函数
void AD_IRQHandler(void)  //ADC中断
{
    if(ADC_GetIStatus(ADC_x,ADC_IT_EOC) ==SET)  //获取下是否产生了中断
    {
        //读取数据转换  把值赋给一个变量
       ADC_ConvertedValue =ADC_GetConversionValue(ADC_x);
    }
    ADC_ClearITPendingBit(ADC_x,ADC_IT_EOC)  //清除标志位
}

//在main里面主要 是调用输出
    while(1)
    {
        ADC_ConvertedValueLocal=(float) ADC_ConvertedValue/4096*3.3;
         pirntf("\r\n   AD value =0x%04X \r\n",ADC_ConvertedValue);
         pirntf("\r\n   AD value =%f V \r\n",ADC_ConvertedValueLocal);
         pirntf("\r\n\r\n");
    }
```

#### ADC使用DMA方式读取
	不占用CPU 、用于采样速度快还要处理的情况  ADC2没有DMA   使用ADC1/3

```C
文件在 ADC-单通道-DMA读取项目了
    static void ADCx_Mode_Config(void)
    1、DMA_InitTypeDef DMA_InitStructure;//初始化DMA结构体
	2、RCC_AHBPeriphClockCmd(ADC_DMA_CLK, ENABLE);//开启DMA时钟  RCC_AHBPeriph_DMA1
	//复位DMA控制器
	DMA_DeInit(ADC_DMA_CHANNEL);
	//配置 DMA 初始化结构体
	//外设基址：ADC 数据寄存器地址
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uit32_t) ( & (ADCx->DR) );
	//存储器地址，实际上就是一个内部SRAM的变量
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uit32_t)&ADC_ConvertedValue;
	//数据源来自外设
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	//缓冲区大小为1，缓冲区的大小应该等于存储器的大小
	DMA_InitStructure.DMA_BufferSzie = 1;
	
	//外设寄存器只有一个，地址不能递增
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	//存储器地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	//外设数据大小为半字 16位，跟外设数据大小相同
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	//存储器数据大小也为半字，跟外设数据大小相同
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	//循环传输模式
	DMA_InitStructure.DMA_Mode = DMA_Mode_Cirular;
	//DMA 传输通管道优先级为高，当使用一个DMA通道时，优先级设置不影响
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	//禁止存储器到存储器模式，因为是从外设到存储器
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	//初始化DMA
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
	//使能 DMA通道
	DMA_Cmd(ADC_DMA_CHANNEL, ENABLE);
//----------------------------------------------以上是初始化DMA
把时钟 定义为宏 为了好记   
    #define		ADC_DMA_CLK		RCC_AHBPeriph_DMA1
    #define		ADC_DMA_CHANNEL	DMA1_Channel1
其中注意 ADC1 对应的DMA的通道1和DMA1
   		ADC3 对应的DMA的通道5和DMA2
     #define		ADC_DMA_CLK		RCC_AHBPeriph_DMA2
     #define		ADC_DMA_CHANNEL	DMA2_Channel5 
    
    //使能ADC DMA请求  这样DMA才能开启
    ADC_DMACmd(ADC_x, ENABLE);

直接用跳帽测 值是1.7V左右   
```

#### 多通道ADC 采集 DMA读取
	多通道依次采集，把数据放到DR寄存器的低16位，然后用DMA，放到数组a[ ]。这样不会覆盖之前采集的数据，且使用扫描模式采集。
```c
配置下ADC采集通道的 GPIO 以及通道号
 //转换通道个数
#define NOPCHANEL	6

//PC0 这个ADC 霸道开发板是被蜂鸣器给共用了所以默认是 低电平     指南者是高电平
  //当测试的时候 所有的ADC如果是打开状态下 没接外部电路  其值默认 在1.6左右并非0  除PC0特殊  
//这里使用PC0 是因为 这里以别人做好的开发板  如果 是裸板则  IO口从 PA0-PA7 PC0-PC5  PB0-PB1 但是难免大部分的ADC被其他电路使用 所以纯净的ADC 不多    
#define ADC_PIN1		GPIO_Pin_0
#define ADC_CHANNEL1	ADC_Channel_10    

#define ADC_PIN2		GPIO_Pin_1
#define ADC_CHANNEL2	ADC_Channel_11  

#define ADC_PIN3		GPIO_Pin_2
#define ADC_CHANNEL3	ADC_Channel_12  
    
#define ADC_PIN4		GPIO_Pin_3
#define ADC_CHANNEL4	ADC_Channel_13  

#define ADC_PIN5		GPIO_Pin_4
#define ADC_CHANNEL5	ADC_Channel_14 

#define ADC_PIN6		GPIO_Pin_5
#define ADC_CHANNEL6	ADC_Channel_15
 
//ADC1  对应 DMA1通道1，ADC3对应DMA2通道5，ADC2没有DMA功能
#define	ADC_x			ADC1
 
// 这里使用通道获取的值 创建个数组存储  
__IO uint16_t ADC_ConvertedValue[NOFCHANEL]={0,0,0,0,0,0};

float ADC_ConvertedValueLocal[NOFCHANEL];

static void ADCx_Mode_Config(void)
{
    //这里需要修改  DMA存储地址  以及  DMA的大小
    	//存储器地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //DMA_MemoryInc_Disable
    //缓冲区大小为1，缓冲区的大小应该等于存储器的大小
	DMA_InitStructure.DMA_BufferSzie =NOFCHANEL ; //1
    
    //ADC  修改结构体成员变量开启扫描模式
    	ADC_InitStruct.ADC_ScanConvMode = ENABLE;  // DISABLE
   		ADC_InitStruct.ADC_NbrofChannel = NOFCHANEL;  // ENABLE
    
    //配置每个通道口转换的顺序
    ADC_RegularChannelConfig(ADC_x, ADC_Channel, 1, ADC_SampleTime_55Cycles5);
	1、哪个ADC 2、哪个通道 3、转换顺序 4、采样时间周期
    ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL2, 2, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL3, 3, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL4, 4, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL5, 5, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL6, 6, ADC_SampleTime_55Cycles5);
//---------------------------以上完成初始化的配置
 main 函数里循环
while(1)
     {
        ADC_ConvertedValueLocal[0]=(float) ADC_ConvertedValue[0]/4096*3.3;
    	ADC_ConvertedValueLocal[1]=(float) ADC_ConvertedValue[1]/4096*3.3;
    	ADC_ConvertedValueLocal[2]=(float) ADC_ConvertedValue[2]/4096*3.3;
    	ADC_ConvertedValueLocal[3]=(float) ADC_ConvertedValue[3]/4096*3.3;
   	 	ADC_ConvertedValueLocal[4]=(float) ADC_ConvertedValue[4]/4096*3.3;
    	ADC_ConvertedValueLocal[5]=(float) ADC_ConvertedValue[5]/4096*3.3;
          
        pirntf("\r\n   AD value =%f V \r\n",ADC_ConvertedValueLocal[0]);
    	pirntf("\r\n   AD value =%f V \r\n",ADC_ConvertedValueLocal[1]);
   	 	pirntf("\r\n   AD value =%f V \r\n",ADC_ConvertedValueLocal[2]);
    	pirntf("\r\n   AD value =%f V \r\n",ADC_ConvertedValueLocal[3]);
    	pirntf("\r\n   AD value =%f V \r\n",ADC_ConvertedValueLocal[4]);
    	pirntf("\r\n   AD value =%f V \r\n",ADC_ConvertedValueLocal[5]);
        pirntf("\r\n\r\n");   
    	Delay(0xffffee);   //延时显示
     }    
```

#### 双重模式 规则同步  DMA 读取
```c
ADC1  
ADC2
    其中 ADC1和ADC2 采集同一个通道 同步就是  ADC1/2 同时采集 同时转换同一个通道 数据放在DR寄存器
  创建一个32位的变量 通过DMA把 DR的数据传给 32位变量 高16位存 ADC2  低16位存 ADC1

//设置双模式的宏
#define		ADCx_1					ADC1
#define		ADC_1_APBxClock_FUN		RCC_AHB2PeriphClockCmd
#define		ADC_1_CLK				RCC_AHB2Periph_ADC1

#define		ADCx_1_GPIO_APBxClock_FUN	RCC_AHB2PeriphClockCmd
#define		ADC_1_GPIO_CLK				RCC_AHB2Periph_GPIOC
#define		ADC_1_PORT					GPIOC
#define		ADC_1_PIN					GPIO_Pin_1
#define		ADC_1_CHANNEL				ADC_Channel_l1

// ADC2
#define		ADCx_2					ADC2
#define		ADC_2_APBxClock_FUN		RCC_AHB2PeriphClockCmd
#define		ADC_2_CLK				RCC_AHB2Periph_ADC2

#define		ADCx_2_GPIO_APBxClock_FUN	RCC_AHB2PeriphClockCmd
#define		ADC_2_GPIO_CLK				RCC_AHB2Periph_GPIOC
#define		ADC_2_PORT					GPIOC
#define		ADC_2_PIN					GPIO_Pin_4
#define		ADC_2_CHANNEL				ADC_Channel_l4

#define	NOFCHANEL		1
//ADC1 对应 DMA1通道1， ADC3对应DMA2通道5， ADC2没有DMA功能
#define ADC_DMA_CHANNEL			DMA1_Channel1
#define ADC_DMA_CLK				RCC_AHBPeriph_DMA1
//------------------------------------------------------

//同时要配置两组GPIO
ADCx_1_GPIO_APBxClock_FUN (ADCx_1_GPIO_CLK,ENABLE);
GPIO_InitStructure.GPIO_Pin =ADCx_1_PIN;
GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AIN;
GPIO_Init(ADCx_1_PORT,&GPIo_InitStructure);

//ADCx_2 GPIO初始化
ADCx_1_GPIO_APBxClock_FUN (ADCx_2_GPIO_CLK,ENABLE);
GPIO_InitStructure.GPIO_Pin =ADCx_2_PIN;
GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AIN;
GPIO_Init(ADCx_2_PORT,&GPIo_InitStructure);
//------------------------------------------------------

//配置模式DMA
	//配置 DMA 初始化结构体
	//外设基址：ADC 数据寄存器地址
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uit32_t) ( & (ADCx_1->DR) );//DCx->DR
	//存储器地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	//外设数据大小为字 32位，跟外设数据大小相同
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; 				//存储器数据大小也为字，跟外设数据大小相同
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;

//要把 数组给设置位uint32位的  还用数组为了多通道避免再去创建变量 
__IO uint32_t ADC_ConvertedValue[NOFCHANEL]={0};
如果 ADC1/2  每次读取多个通道那么 NOFCHANEL要更改为 相应的个数


//配置ADC1初始化结构体
    	ADCx_1_APBxClock_FUN(ADCx_1_CLK, ENABLE)   // ADCx_CLK
    	ADC_InitStruct.ADC_Mode = ADC_Mode_RegSimult;  // ADC_Mode_Independent
        ADC_InitStruct.ADC_ScanConvMode =DISEBLE;  // ENABLE
   		ADC_InitStruct.ADC_NbrofChannel = NOFCHANEL;  // ENABLE
		ADC_Init(ADCx_1,&ADC_InitStruct); //ADC_x
//配置转换通道
		ADC_RegularChannelConfig(ADCx_1, ADCx_1_Channel, 1, ADC_SampleTime_55Cycles5);
		//ADCx_1, ADCx_1_Channel

//配置ADC2初始化结构体  与ADC1 差不多就是把 ADCx_1 改为 ADCx_2

//使能ADC1 DMA 请求
	ADC_DMACmd(ADCx_1,ENABLE);

//校准 ADCx_1
	//开启ADC，并开始转换
ADC_Cmd(ADCX_1,ENABLE);
	//初始化ADC 校准寄存器
ADC_ResetCalibration(ADCx_1);
	//等待校准寄存器初始化完成
while(ADC_GetResetCalibrationStatus(ADCx_1));
	//ADC开始校准
ADC_StartCalibration(ADCx_1)
    //等待校准完成
 while(ADC_GetCalibrationStatus(ADCx_1));

//校准 ADCx_2
	//开启ADC，并开始转换
ADC_Cmd(ADCX_2,ENABLE);
	//初始化ADC 校准寄存器
ADC_ResetCalibration(ADCx_2);
	//等待校准寄存器初始化完成
while(ADC_GetResetCalibrationStatus(ADCx_2));
	//ADC开始校准
ADC_StartCalibration(ADCx_2)
    //等待校准完成
 while(ADC_GetCalibrationStatus(ADCx_2));


//由于是双重模式  ADC1是主  ADC2是从    其中ADC1是通过软件触发    ADC2是从多路复用获取 所以ADC2要配置为外部触发模式
/*重点使能ADCx_2的外部触发转换*/
ADC_ExternalTrigConvCmd(ADCx_2,ENABLE);
//由于没有采用外部触发，所以使用软件触发ADC转换
ADC_SoftwareStartConvCmd(ADCx_1,ENABLE);

//--------------------------------------以上为配置

在mian 里   
   // float ADC_ConvertedValueLocal[NOFCHANEL];
   float ADC_ConvertedValueLocal[NOFCHANEL*2];  //因为两个ADC 取出32位分为16位时候ADC要分开存储用
	while(1)
    {
        //取出ADC1数据寄存器的高16位，这个是ADC2的转换数据
        temp0=(ADC_ConvertedValue[0]&0XFFFF0000)>>16;
        //取出ADC1数据寄存器的低16位，这个是ADC1的转换数据
        temp1=(ADC_ConvertedValue[0]&0XFFFF);
        ADC_ConvertedValueLocal[0]=(float) temp0/4096*3.3;
        ADC_ConvertedValueLocal[1]=(float) temp1/4096*3.3;
        printf("\r\n ADCx_1 value =%f V \r\n", ADC_ConvertedValueLocal[1]);
        printf("\r\n ADCx_2 value =%f V \r\n", ADC_ConvertedValueLocal[0]);
        printf("\r\n\r\n");
        Delay(oxffffee);       
    }
```

