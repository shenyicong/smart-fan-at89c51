#include <regx52.h>
 
#define uint8 unsigned char
 
#define out P0
sbit LCD_CS1     = P2 ^ 0;
sbit LCD_CS2     = P2 ^ 1;
sbit RS          = P2 ^ 2;
sbit RW          = P2 ^ 3;
sbit E           = P2 ^ 4;
 
void lcd12864_delay(unsigned int t)		//@12.000MHz
{
	unsigned char i, j;
    while (t--) {
    	i = 2;
	    j = 239;
        do
        {
            while (--j);
        } while (--i);
    }
}
 
void lcd12864_Busy(void) // 12864 ??
{
    out = 0X00; // ???????? 0x00
    RS = 0; // ? RS ????????
    RW = 1; // ? RW ????????
    E = 1; // ? EN ????????,????
    while (out & 0x80); // ????? 1 ?,?????????,?????
    E = 0;  // ? EN ????????
}
 
 
 
void lcd12864_WriteCommed(unsigned char commed) // 12864 ???
{
    unsigned char i = 0;
    lcd12864_Busy(); // 12864 ??,??????????????
    RS = 0; // ? RS ????????,?????
    RW = 0; // ? RW ????????,?????
    out = commed; // ???????????
    E = 1; // ? EN ????????,????
    i = 2; while(i--);    //????
    E = 0; // ? EN ????????,?????????
}
 
 
void lcd12864_WriteData(unsigned char dat)    // 12864 ???
{
    unsigned char i = 0;
    lcd12864_Busy(); // 12864 ??
    RS = 1; // ? RS ????????,?????
    RW = 0; // ? RW ????????,?????
    out = dat; // ?????????
    E = 1; // ? EN ????????,????
    i = 2; while(i--);
    E = 0;  // ? EN ????????,?????????
}
 
 
void Set_page(unsigned int page) {   //???????
    page = 0xB8 | page;   //??????0xB8
    lcd12864_WriteCommed(page);
}
 
void Set_line(unsigned int startline) {  //????????
    startline = 0xC0 | startline;
    lcd12864_WriteCommed(startline);
}
 
void Set_column(unsigned int column) {   //??????
    column &= 0x3F;   //??????64
    column |= 0x40;   //??????0x40
    lcd12864_WriteCommed(column);
}
 
void SetOnOff(unsigned onoff) {     //?????? 0x3E?,0x3F??
    onoff = 0x3F | onoff;   //onoff?0?????,?1?????
    lcd12864_WriteCommed(onoff);
}
 
void SelectScreen(unsigned int screen) {
    switch(screen) {
        case 0:LCD_CS1 = 0; LCD_CS2 = 0; break;
        case 1:LCD_CS1 = 0; LCD_CS2 = 1; break;
        case 2:LCD_CS1 = 1; LCD_CS2 = 0; break;
        default: break;
    }
}
 
void ClearScreen(unsigned int screen) {     //??
    unsigned int i, j;
    SelectScreen(screen);
    for (i = 0; i < 8; i++) {
        Set_page(i);
        Set_column(0);
        for (j = 0; j < 64; j++) {
            lcd12864_WriteData(0x00);  //??0,???????1
        }
    }
}
 
void LCD12864_Init(void) {    //?????
    lcd12864_Busy();
    SelectScreen(0);
    SetOnOff(0);
    SelectScreen(0);
    SetOnOff(1);
    SelectScreen(0);
    ClearScreen(0);
    Set_line(0);
}
 
//????16*16???
void show_ch(uint8 screen,uint8 page,uint8 column,uint8 *p)
{
	uint8 i;
	SelectScreen(screen);
	Set_page(page);
	Set_column(column);
	
	for(i=0;i<16;i++)	//??16*16???
	{
		lcd12864_WriteData(p[i]);
	}
	
	Set_page(page+1);
	Set_column(column);
	for(i=0;i<16;i++)	//??16*16???,"????"
	{
		lcd12864_WriteData(p[i+16]);
	}
}
 
//显示8*16的数字函数
void show_num(uint8 screen, uint8 page, uint8 column, uint8 *p)
{
    uint8 i;
    SelectScreen(screen);
    Set_page(page);
    Set_column(column);
 
    for (i = 0; i < 8; i++) 
    {
        lcd12864_WriteData(p[i]);
    }
 
    Set_page(page + 1);
    Set_column(column);
 
    for (i = 0; i < 8; i++) 
    {
        lcd12864_WriteData(p[i + 8]);
    }
}
 
//????64*64???
void show_im(uint8 screen,uint8 page,uint8 column,uint8 *p)
{
	uint8 i;
	SelectScreen(screen);
	Set_page(page);
	Set_column(column);
 
	for(i=0;i<32;i++)	//??16*16???
	{
		lcd12864_WriteData(p[i]);
	}
	
	Set_page(page+1);
	Set_column(column);
	for(i=0;i<32;i++)	//??16*16???,"????"
	{
		lcd12864_WriteData(p[i+32]);
	}
	
	Set_page(page+2);
	Set_column(column);
	for(i=0;i<32;i++)	//??16*16???,"????"
	{
		lcd12864_WriteData(p[i+64]);
	}
	
	Set_page(page+3);
	Set_column(column);
	for(i=0;i<32;i++)	//??16*16???,"????"
	{
		lcd12864_WriteData(p[i+96]);
	}
}