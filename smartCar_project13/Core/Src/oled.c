#include "oled.h"
#include "i2c.h"
#include "oledfont.h"

void Oled_Write_Cmd(uint8_t dataCmd)
{
	
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT,
										&dataCmd, 1, 0xff);
}

void Oled_Write_Data(uint8_t dataData)
{
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x40, I2C_MEMADD_SIZE_8BIT,
										&dataData, 1, 0xff);
}

void Oled_Init(void){
	Oled_Write_Cmd(0xAE);//--display off
	Oled_Write_Cmd(0x00);//---set low column address
	Oled_Write_Cmd(0x10);//---set high column address
	Oled_Write_Cmd(0x40);//--set start line address  
	Oled_Write_Cmd(0xB0);//--set page address
	Oled_Write_Cmd(0x81); // contract control
	Oled_Write_Cmd(0xFF);//--128   
	Oled_Write_Cmd(0xA1);//set segment remap 
	Oled_Write_Cmd(0xA6);//--normal / reverse
	Oled_Write_Cmd(0xA8);//--set multiplex ratio(1 to 64)
	Oled_Write_Cmd(0x3F);//--1/32 duty
	Oled_Write_Cmd(0xC8);//Com scan direction
	Oled_Write_Cmd(0xD3);//-set display offset
	Oled_Write_Cmd(0x00);//
	
	Oled_Write_Cmd(0xD5);//set osc division
	Oled_Write_Cmd(0x80);//
	
	Oled_Write_Cmd(0xD8);//set area color mode off
	Oled_Write_Cmd(0x05);//
	
	Oled_Write_Cmd(0xD9);//Set Pre-Charge Period
	Oled_Write_Cmd(0xF1);//
	
	Oled_Write_Cmd(0xDA);//set com pin configuartion
	Oled_Write_Cmd(0x12);//
	
	Oled_Write_Cmd(0xDB);//set Vcomh
	Oled_Write_Cmd(0x30);//
	
	Oled_Write_Cmd(0x8D);//set charge pump enable
	Oled_Write_Cmd(0x14);//
	
	Oled_Write_Cmd(0xAF);//--turn on oled panel		
}

void Oled_Screen_Clear(void){
	char i,n;
	Oled_Write_Cmd (0x20);                    //set memory addressing mode
	Oled_Write_Cmd (0x02);                    //page addressing mode

	for(i=0;i<8;i++){
		Oled_Write_Cmd(0xb0+i);               //éè??ò3μ??·￡¨0~7￡?
		Oled_Write_Cmd(0x00);                 //éè????ê??????aáDμíμ??·
		Oled_Write_Cmd(0x10);                 //éè????ê??????aáD??μ??·   
		for(n=0;n<128;n++)Oled_Write_Data(0x00); 			
	}	
}

void Oled_Show_Char(char row,char col,char oledChar){ //row*2-2
	unsigned int  i;
	Oled_Write_Cmd(0xb0+(row*2-2));                           //page 0
	Oled_Write_Cmd(0x00+(col&0x0f));                          //low
	Oled_Write_Cmd(0x10+(col>>4));                            //high	
	for(i=((oledChar-32)*16);i<((oledChar-32)*16+8);i++){
		Oled_Write_Data(F8X16[i]);                            //写数据oledTable1
	}

	Oled_Write_Cmd(0xb0+(row*2-1));                           //page 1
	Oled_Write_Cmd(0x00+(col&0x0f));                          //low
	Oled_Write_Cmd(0x10+(col>>4));                            //high
	for(i=((oledChar-32)*16+8);i<((oledChar-32)*16+8+8);i++){
		Oled_Write_Data(F8X16[i]);                            //写数据oledTable1
	}		
}


/******************************************************************************/
// 函数名称：Oled_Show_Char 
// 输入参数：oledChar 
// 输出参数：无 
// 函数功能：OLED显示单个字符
/******************************************************************************/
void Oled_Show_Str(char row,char col,char *str){
	while(*str!=0){
		Oled_Show_Char(row,col,*str);
		str++;
		col += 8;	
	}		
}
