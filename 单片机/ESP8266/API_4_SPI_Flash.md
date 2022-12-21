#### 6、SPI Flash (配套示例Flash)
**理解：**
	 bin就是存FLASH,4Mbyte经过换算扇区编号范围0x000 – 0x3FF，可以存储代码和存储数据，掉电复位不丢失。
**注意：**
	1、读写Flash 必须从0x70 000地址后面。
	2、4k对齐。
	3、写前先擦除。擦除函数参数是扇区编号不是地址。
	4、读写函数参数是字节地址不是扇区编号。
##### 基础熟记
	1、拷贝./include/spi_flash.h
	2、获取 FLASH 的 ID 号
	3、擦除 Flash 扇区
	4、往 FLASH 写入数据
	5、从 FLASH 读取数据
```c
//获取 FLASH 的 ID 号
os_printf("\r\nspi_flash_get_id=%d\r\n\r\n",spi_flash_get_id());
//擦除 Flash 扇区
spi_flash_erase_sector((uint16_t) 0x77); //存储数据的扇区编号

//往 FLASH 写入数据 
//Read_Data 为数组名
spi_flash_write(0x77 * 4096,(uint32_t *)Write_Data,sizeof(Write_Data));

//从 FLASH 读取数据
//Read_Data 为数组名
spi_flash_read(0x77 * 4096,(uint32_t *)Read_Data,sizeof(Write_Data));


```
##### API 函数集合
一、spi_flash_get_id （查询 SPI Flash 的 ID）
```c
uint32  spi_flash_get_id = uint32 spi_flash_get_id (void);
```
二、spi_flflash_erase_sector（写flash之前必须先擦除扇区）
```c
// 4k 对齐就是 每个扇区4k  4096 传入的参数必须是倍数
SpiFlashOpResult spi_flash_erase_sector (uint16 sec){
	/*返回值
	typedef enum{ 
		SPI_FLASH_RESULT_OK,//写 FLASH 成功
		SPI_FLASH_RESULT_ERR,//写 FLASH 错误
		SPI_FLASH_RESULT_TIMEOUT//写 FLASH 超时
	}SpiFlashOpResult;
	*/
}
```
三、spi_flash_write（写⼊数据到 Flash）
```c
SpiFlashOpResult spi_flash_write (uint32 des_addr,uint32 *src_addr,uint32 size)


/*
	参数 
		uint32 des_addr：写⼊ Flash ⽬的地址
		uint32 *src_addr：写⼊数据的指针
		uint32 size：数据⻓度，单位 byte，必须 4 字节对⻬进⾏读写
	返回值
	typedef enum{ 
		SPI_FLASH_RESULT_OK,//写 FLASH 成功
		SPI_FLASH_RESULT_ERR,//写 FLASH 错误
		SPI_FLASH_RESULT_TIMEOUT//写 FLASH 超时
	}SpiFlashOpResult;
*/
```
四、spi_flash_read（从 Flash 读取数据） 
```c
SpiFlashOpResult spi_flash_read (uint32 des_addr,uint32 *src_addr,uint32 size)

/*
	参数 
		uint32 des_addr：Flash 的哪个地址取
		uint32 *src_addr：存放读取到的数据存放的地址
		uint32 size：数据⻓度，单位 byte，必须 4 字节对⻬进⾏读写
	返回值
	typedef enum{ 
		SPI_FLASH_RESULT_OK,//写 FLASH 成功
		SPI_FLASH_RESULT_ERR,//写 FLASH 错误
		SPI_FLASH_RESULT_TIMEOUT//写 FLASH 超时
	}SpiFlashOpResult;
*/
```
五、system_param_save_with_protect（使⽤带读写保护机制的⽅式，写⼊数据到 Flash）
```c
bool system_param_save_with_protect (uint16 start_sec,void *param,uint16 len)
/*
	参数 
		uint16 start_sec：读写保护机制使⽤的 3 个 sector 的起始 sector 0 值。
例如，IOT_Demo 中可使⽤ 0x3D000 开始的 3 个 sector（3×4 KB）建⽴读写保护机制，则
参数 start_sec 传 0x3D。
		void *param：写⼊数据的指针
		uint16 len：数据⻓度，不能超过 1 个 sector ⼤⼩，即 4×1024
	返回值
		true：成功
		false：失败
*/

```
六、system_param_load（使⽤带读写保护机制的⽅式，读出数据到 Flash）
```c
bool system_param_load (uint16 start_sec,uint16 offset,void *param,uint16 len)
/*
	参数 
		uint16 offset：需读取数据，在 sector 中的偏移地址
	返回值
		true：成功
		false：失败
*/
```
七、spi_flflash_set_read_func（注册⽤户⾃定义的 SPI Flash 读取接⼝函数）
```c
//仅⽀持在 SPI overlap 模式下使⽤

```
八、spi_flflash_erase_protect_enable（使能 flash 擦写保护）
```c

```
九、spi_flflash_erase_protect_disable（关闭 flash 擦写保护功能）
```c

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
