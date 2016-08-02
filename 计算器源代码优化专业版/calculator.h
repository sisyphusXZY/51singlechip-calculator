/*
*************************************************************************************************************
* 日期；2016.1.9                             
* 文件名：calculator.h
* 描  述：计算器模块的头文件
* 版本号：1.1.0
* 备  注：通用性不足，编码过多，有待优化
*************************************************************************************************************
*/

#ifndef _CALCULATOR_H
#define _CALCULATOR_H


const uchar code table[]={			     
0x31,0x32,0x33,0x2F,		  // 1,2,3,/
0x34,0x35,0x36,0x2A,		  // 4,5,6,*
0x37,0x38,0x39,0x2D,		  // 7,8,9,-
0x43,0x30,0x3D,0x2B,' '		  // AC,0,=,+							  
};
const uchar code table0[]={			     
0x30,0x31,0x32,0x33,		  
0x34,0x35,0x36,	
0x37,0x38,0x39		  						  
};
const uchar code table1[]={			     
1,2,3,0,4,
5,6,0,7,8,
9,0,0,0,0,
0		  						  
};
uchar table2[10];
uchar code error[]=
"error";															   
uchar code save[]=
"save";
uchar code read[]=			     
"read";

long uint sum = 0;
long uint sum2 = 0;
int a = 0, i = 0;
int *const pa = &a;
int *const pi = &i;
long uint *const psum = &sum;
long uint *const psum2 = &sum2;

/*
********************************************************************************
* ----------------------- Globle functions  ------------------------------------
********************************************************************************
*/

void delayms(uint xms);
void Write_Com(uchar com);
void calculator(uchar ch);
void calculator2(uchar ch);
void jishu(int ch);
void jishu2(int ch);
void LCD_Write_Date(uchar Date);
void LCD_Init();
void guiling();
void off_shumaguan();
void EEPROM_write();
void EEPROM_read2(); 
void matrixkeyscan();

#endif
