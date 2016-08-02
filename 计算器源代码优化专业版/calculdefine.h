/*
*************************************************************************************************************
* ���ڣ�2016.1.8                              
* �ļ�����define.h
* ��  �����������Ͷ��壬���Ŷ���
* �汾�ţ�1.1.0
* ��  ע�������ڻݾ�89C51��ͨ���Բ��㣬������࣬�д��Ż���
*************************************************************************************************************
*/

#ifndef  _CALCUL_DEFINE_H
#define  _CALCUL_DEFINE_H

#include <reg52.h>
#include <intrins.h>


//**************************************************
//�������Ͷ���

#define uchar unsigned char
#define uint unsigned int

//**************************************************
//�˿ڶ���

sbit RS = P1^0;
sbit RW	= P1^1;
sbit EN	= P2^5;
sbit du	= P2^6;
sbit we	= P2^7;
sbit SDA = P2^0;	//���崮����������SDA
sbit SCL = P2^1;	//���崮��ʱ������SCL

//**************************************************
//�������ö���

#define RW_CLR RW=0 
#define RW_SET RW=1 
#define RS_CLR RS=0 
#define RS_SET RS=1
#define EN_CLR EN=0
#define EN_SET EN=1

#define	OP_READ	0xa1		// ������ַ�Լ���ȡ����,0xa1��Ϊ1010 0001B
#define	OP_WRITE 0xa0		// ������ַ�Լ�д�����,0xa1��Ϊ1010 0000B

#define DataPort P0

#endif