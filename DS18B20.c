#include <regx52.h>
#include "OneWire.h"
 
#define DS18B20_SKIP_ROM        0xCC  //跳过rom指令
#define DS18B20_CONVERT_T       0x44  //启动温度转换的指令
#define DS18B20_READ_SCRATCHPAD 0xBE  //读取温度传感器内部暂存器（Scratchpad）数据
 
void Delay1ms(unsigned int t)//t毫秒延时函数
{
    unsigned char a,b;
	unsigned int i;
	for(i=0;i<t;i++)
    	for(b=199;b>0;b--)
        	for(a=1;a>0;a--);
}
 
//用于启动DS18B20温度传感器的温度转换
void DS18B20_ConvertT(void) {
    unsigned char i = 0;
    OneWire_Init(); // 初始化
    Delay1ms(1);                              //延时1ms
    OneWire_SendByte(DS18B20_SKIP_ROM);
    OneWire_SendByte(DS18B20_CONVERT_T);                        //延时1ms
	Delay1ms(1000);//延时1s等待转化
}
 
 
//读取DS18B20内部暂存器里面的数据
float DS18B20_ReadT(void) {
    unsigned char LSB = 0, MSB = 0; //L表示低位，M表示高位
    int temp = 0;
    float T = 0;
    OneWire_Init(); // 初始化
    Delay1ms(1);
    OneWire_SendByte(DS18B20_SKIP_ROM);
    OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
    LSB = OneWire_ReceiveByte();   //读取16位的低位
    MSB = OneWire_ReceiveByte();   //读取16位的高位
    temp = (MSB << 8) | LSB;
    T = temp / 16.0;
    return T;
}
 
 
 