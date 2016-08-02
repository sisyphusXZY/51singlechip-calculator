/*
*************************************************************************************************************
* 日期；2016.1.8                              
* 文件名：define.h
* 描  述：数据类型定义，引脚定义
* 版本号：1.1.0
* 备  注：适用于惠静89C51。通用性不足，编码过多，有待优化。
*************************************************************************************************************
*/

#ifndef  _CALCUL_DEFINE_H
#define  _CALCUL_DEFINE_H

#include <reg52.h>
#include <intrins.h>


//**************************************************
//数据类型定义

#define uchar unsigned char
#define uint unsigned int

//**************************************************
//端口定义

sbit RS = P1^0;
sbit RW	= P1^1;
sbit EN	= P2^5;
sbit du	= P2^6;
sbit we	= P2^7;
sbit SDA = P2^0;	//定义串行数据总线SDA
sbit SCL = P2^1;	//定义串行时钟总线SCL

//**************************************************
//参数配置定义

#define RW_CLR RW=0 
#define RW_SET RW=1 
#define RS_CLR RS=0 
#define RS_SET RS=1
#define EN_CLR EN=0
#define EN_SET EN=1

#define	OP_READ	0xa1		// 器件地址以及读取操作,0xa1即为1010 0001B
#define	OP_WRITE 0xa0		// 器件地址以及写入操作,0xa1即为1010 0000B

#define DataPort P0

#endif