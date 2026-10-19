#include <regx52.h>
#include "LCD.h"
 
sbit OneWire_DQ = P1^7;    //数据总线
 
void Delay1000ms()		//@12.000MHz
{
	unsigned char i, j, k;
	i = 8;
	j = 154;
	k = 122;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
 
void Delay600us(void)//600us延时函数
{
    unsigned char a,b;
    for(b=119;b>0;b--)
        for(a=1;a>0;a--);
}
 
//初始化，返回1表示成功
unsigned char OneWire_Init(void) {
    // unsigned int i = 0;
    // unsigned char AckBit;
    // OneWire_DQ = 1;
    // OneWire_DQ = 0;
    // i = 260; while (--i); //延时500us
    // OneWire_DQ = 1;
    // i = 32; while (--i);  //延时70us
    // AckBit = OneWire_DQ;
    // i = 247; while (--i); //延时500us - 走完这个时序
 
	OneWire_DQ=0;//主动拉低480-960us（此处选择600us）
	Delay600us();
	OneWire_DQ=1;//释放总线,传感器15-60us后拉低总线
	while(OneWire_DQ);//等待传感器拉低；
	while(!OneWire_DQ);//度过传感器被拉低的时间（60-240us）后主动拉高
	OneWire_DQ=1;//主动拉高
    return 1;
}
 
 
//主机向从机发送一位数据
void OneWire_SendBit(unsigned char Bit) {
 
    unsigned char i = 0;
    OneWire_DQ = 0;//拉低电平
    i = 3; while (--i);   //延时6us - 告诉从机主机要发送数据
 
    // OneWire_DQ = Bit;           --------------------------------------   更改逻辑
    if (Bit != 0) {
        OneWire_DQ = 1;
    } else {
        OneWire_DQ = 0;
    }
 
    // LCD_ShowNum(2, 5, OneWire_DQ, 2);
    // Delay1000ms();
 
    i = 30; while (--i);  //延时60us - 等待从机读取数据
    i = 3; while (--i);   //延时6us - 告诉从机主机要发送数据
    OneWire_DQ = 1;       //将数据线恢复
    i = 2; while (--i);   //延时4us
}
 
//主机接收从机发送的一位数据
unsigned char OneWire_ReceiveBit(void) {
    unsigned char i = 0;
    unsigned char ACK = 0;
    OneWire_DQ = 0;
    i = 1; while (--i);   //延时2us
    OneWire_DQ = 1;       //释放总线，等待
    i = 3; while (--i);   //延时6us
 
    // ACK = OneWire_DQ;     //获取从机发送发的数据
    if (OneWire_DQ == 1) {
        ACK = 1;
    } else {
        ACK = 0;
    }
 
    i = 30; while (--i);  //延时60us，凑齐时间切片
    i = 2; while (--i);   //延时4us
 
    return ACK;
}
 
 
//主机向从机发送一个字节的数据
void OneWire_SendByte(unsigned char Byte) {
    unsigned char i = 0;
    for (i = 0; i < 8; i++) {
        OneWire_SendBit(Byte & (0x01 << i));
    }
}
 
//主机接收一个字节的数据
unsigned char OneWire_ReceiveByte(void) {
    unsigned char ACK  = 0;
    unsigned char i = 0;
    for (i = 0; i < 8; i++) {
        if (OneWire_ReceiveBit()) {ACK |= (0x01 << i); }
    }
    return ACK;
}
 