#ifndef _LCD12168_H_
#define _LCD12168_H_
 
#define uint8 unsigned char
 
void show_im(uint8 screen,uint8 page,uint8 column,uint8 *p);
void LCD12864_Init(void);
void show_ch(uint8 screen,uint8 page,uint8 column,uint8 *p);
void show_num(uint8 screen, uint8 page, uint8 column, uint8 *p);
void ClearScreen(unsigned int screen);
void SelectScreen(unsigned int screen);
void lcd12864_WriteCommed(unsigned char commed);
 
#endif