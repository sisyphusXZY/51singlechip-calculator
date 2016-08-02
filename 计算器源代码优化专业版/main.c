/*
*************************************************************************************************************
* 日期；2016.1.9                              
* 文件名：main.c
* 描  述：入口主函数
* 版本号：1.1.0
* 备  注：通用性不足，编码过多，有待优化，算法复杂
*************************************************************************************************************
*/

#define _MAIN_C
#include <reg52.h>
#include <string.h>
#include "calculdefine.h"
#include "calculcode.h"
#include "calculator.h"

void main()
{
/*串口	
	TMOD=0x20;	
	SCON=0x50;//设定串口工作方式0101 0000
	PCON=0x00;		
	TL1=0xfd;
	TH1=0xfd;
	TR1=1;
串*/
	off_shumaguan();
	LCD_Init();
  	Write_Com(0x80); 
    while(1)
	{
		matrixkeyscan();
	}

}