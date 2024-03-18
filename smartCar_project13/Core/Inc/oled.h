#ifndef __OLED_H__
#define __OLED_H__

void Oled_Init(void);
void Oled_Screen_Clear(void);
void Oled_Show_Char(char row,char col,char oledChar);
void Oled_Show_Str(char row,char col,char *str);

#endif
