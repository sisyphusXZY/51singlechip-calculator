/*
*************************************************************************************************************
* ���ڣ�2016.1.9                              
* �ļ�����calculator.c
* ��  �������̼�lcd�ĵ��ú���
* �汾�ţ�1.1.0
* ��  ע��ͨ���Բ��㣬������࣬�д��Ż����㷨����
*************************************************************************************************************
*/

#define  _CALCULATOR_C
#include "calculdefine.h"
#include "calculator.h"




void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms����ʱԼxms����
		for(j=110;j>0;j--);
}


void off_shumaguan()
{	
	du=1;
	P0=0x00; // �ر������
	du=0;
}
 /*------------------------------------------------
              ��ʼ������
------------------------------------------------*/
void LCD_Init() 
{	
	Write_Com(0x01);	  /*����*/
	Write_Com(0x38);    /*��ʾģʽ����*/ 
	Write_Com(0x0F);    /*��ʾ����ƶ�����*/ 
	Write_Com(0x06); 
	  
}
/*------------------------------------------------
              д�������
------------------------------------------------*/
void Write_Com(uchar com) 
{  
	 RS_CLR; 
	 RW_CLR; 
	 EN_SET; 
	 delayms(5);
	 DataPort=com;
	 delayms(5);
	 EN_CLR;
}
/*------------------------------------------------
              д�����ݺ���
------------------------------------------------*/
 void LCD_Write_Data(uchar Data) 
 { 
 //while(LCD_Check_Busy()); //æ��ȴ�
 //delayms(5);
 RS_SET; 
 RW_CLR; 
 EN_SET; 
 delayms(5);
 DataPort= Data; 
 //_nop_()
 delayms(5);
 EN_CLR;
 }
/*------------------------------------------------
             ����
------------------------------------------------*/
void matrixkeyscan()
{
	uchar temp,key;
	int h = 0,g;

    P3=0xfe;   //1111 1110
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delayms(10);
	  temp=P3;
	  temp=temp&0xf0;
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xee:	 //11101110
               key=0;
               break;
          case 0xde:	//11011110
               key=1;
               break;
          case 0xbe:
               key=2;
               break;
          case 0x7e:
               key=3;
               break;
         }
         while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
         } 
		LCD_Write_Data(table[key]);
        if(key == 3)
		{
	
			calculator(0x2F);
		}
		else
			jishu(table1[key]);
      }
    }
    P3=0xfd;
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delayms(10);
      temp=P3;
      temp=temp&0xf0;
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xed:
               key=4;
               break;
          case 0xdd:
               key=5;
               break;
          case 0xbd:
               key=6;
               break;
          case 0x7d:
               key=7;
               break;
         }
         while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
         }
		LCD_Write_Data(table[key]);
        if(key == 7)
		{	
	
			calculator(0x2A);
		}
		else
			jishu(table1[key]);
      }
      }
    P3=0xfb;
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delayms(10);
   	  temp=P3;
      temp=temp&0xf0;
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xeb:
               key=8;
               break;
          case 0xdb:
               key=9;
               break;
          case 0xbb:
               key=10;
               break;
          case 0x7b:
               key=11;
               break;
         }
         while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
         }
        LCD_Write_Data(table[key]);
		if(key == 11)
		{
			
			calculator(0x2D);
		}
		else
			jishu(table1[key]);
      }
      }
    P3=0xf7;
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delayms(10);
      temp=P3;
      temp=temp&0xf0;
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xe7:
               key=12;
               break;
          case 0xd7:
               key=13;
               break;
          case 0xb7:
               key=14;
               break;
          case 0x77:
               key=15;
               break;
         }
		 while((temp==0xb7)&&(h <= 31))
         {
           temp=P3;  
		   delayms(60);
			h++;
         }
		 if(temp!=0xb7)						   
		 {
			 	while(temp!=0xf0)
	         {
	           temp=P3;
	           temp=temp&0xf0;
	         }
		 }
		
		 if(h>=30)
		 {
		 	key = 88;
			EEPROM_write();
			for(g = 0;g < 4;g++)
				LCD_Write_Data(save[g]);
			delayms(800);
			Write_Com(0x80);			
			for(g = 0;g < 17;g++)
			LCD_Write_Data(0x20);
			Write_Com(0x80);
			delayms(800);  //�ṩʱ����֣�������ٴ�����Ⱥš�
		 }
		 
		if(key == 15 || key == 13)
		{
			LCD_Write_Data(table[key]);
	        if(key == 15)
			{
			
				calculator(0x2B);
			}
			if(key == 13)
				jishu(0);
	    	}
		if(key == 12)
			guiling();
	  }
    }
}
void matrixkeyscan2(uchar ch)
{
	uchar temp,key;
	int h = 0,g, j = 0;
    P3=0xfe;   //1111 1110
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delayms(10);
	  temp=P3;
	  temp=temp&0xf0;
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xee:	 //11101110
               key=0;
               break;
          case 0xde:	//11011110
               key=1;
               break;
          case 0xbe:
               key=2;
               break;
          case 0x7e:
               key=3;
               break;
         }
         while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
         }
		LCD_Write_Data(table[key]);
        if(key == 3)
		{	
			calculator2(ch);
			calculator(0x2F);
		}
		else
			jishu2(table1[key]);
      }
    }
    P3=0xfd;
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delayms(10);
      temp=P3;
      temp=temp&0xf0;
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xed:
               key=4;
               break;
          case 0xdd:
               key=5;
               break;
          case 0xbd:
               key=6;
               break;
          case 0x7d:
               key=7;
               break;
         }
         while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
         }
	   LCD_Write_Data(table[key]);
       if(key == 7)
		{
			calculator2(ch);
			calculator(0x2A);
		}
		else
			jishu2(table1[key]);
      }
      }
    P3=0xfb;
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delayms(10);
   	  temp=P3;
      temp=temp&0xf0;
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xeb:
               key=8;
               break;
          case 0xdb:
               key=9;
               break;
          case 0xbb:
               key=10;
               break;
          case 0x7b:
               key=11;
               break;
         }
         while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
         }
		 LCD_Write_Data(table[key]);
        if(key == 11)
		{
			calculator2(ch);
			calculator(0x2D);		
		}
		else
			jishu2(table1[key]);
      }
      }
    P3=0xf7;
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delayms(10);
      temp=P3;
      temp=temp&0xf0;
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xe7:
               key=12;
               break;
          case 0xd7:
               key=13;
               break;
          case 0xb7:
               key=14;
               break;
          case 0x77:
               key=15;
               break;
         }
        
		 while((temp==0xb7)&&(h <= 31))
         {
           temp=P3;  
		   delayms(60);	 //�����ԣ��ȽϽӽ�3��
			h++;
         }
		 while((temp==0x77)&&(j <= 31))
         {
           temp=P3;  
		   delayms(60);	 //�����ԣ��ȽϽӽ�3��
			j++;
         }
		 if((temp!=0xb7)&&(temp!=0x77))						   
		 	 	while(temp!=0xf0)
	         {
	           temp=P3;
	           temp=temp&0xf0;
	         }
		
		 if(h>=30)
		 {
			EEPROM_write();
			for(g = 0;g < 4;g++)
				LCD_Write_Data(save[g]);
			delayms(800);  //�ṩʱ����֣�������ٴ�����Ⱥš�	
			key = 16;	   
		 } 
		 if(j>=30)
		 {
			EEPROM_read2();
			for(g = 0;g < 4;g++)
				LCD_Write_Data(read[g]);
			delayms(800);  //�ṩʱ����֣�������ٴ�����Ⱥš�		  
			key = 14;
		 } 
		LCD_Write_Data(table[key]);
		delayms(500);
		if(key == 15)
		{
			calculator2(ch);
			calculator(0x2B);
		}
		if(key == 13)
			jishu2(0);
		if(key == 14)
		{	
			calculator2(ch);
			calculator(0x3D);
		}
		if(key == 12)
			guiling();
      }
    }
}
/*------------------------------------------------
             ���㹦��
------------------------------------------------*/
void calculator(uchar ch)
{
	*pa = 0;
	if(ch==0x2B)	
		while(1)
  		{
			matrixkeyscan2(0x2B);//��ͣ���ü���ɨ�����
  		}
	if(ch==0x2D)
		while(1)
	 	{
			matrixkeyscan2(0x2D);//��ͣ���ü���ɨ�����
  		}	
	if(ch==0x2A)
		while(1)
 	 	{
			matrixkeyscan2(0x2A);//��ͣ���ü���ɨ�����
	  	}
	if(ch==0x2F)
		while(1)
 	  	{
			matrixkeyscan2(0x2F);//��ͣ���ü���ɨ�����
	  	}
	if(ch==0x3D)
	{  
		
	//	float a, b, temp = *psum;
		long uint c, temp = *psum;
		//LCD_Write_Data(table0[1]);
		int i = 0;		
		Write_Com(0x01);
		Write_Com(0x80+0x40); 
		for(c = 0;temp >= 1;)
		{	
			c = temp%10;
			temp = temp/10;	
			i++;
			table2[i] = c;
		
		}
		//	LCD_Write_Data(table0[*pi]);
	  
			for(;i > 0;--i)
				LCD_Write_Data(table0[table2[i]]);
			i = 0;
		/*Write_Com(0x80);			  ����4��ָ���Һ������һ��
		for(b = 0;b < 17;b++)
		LCD_Write_Data(0x20);
		Write_Com(0x80);*/
	/*for(a=1.0,b = 0;a < 1.0;a = (temp/10),++b);
		for(c = 0;b == 0;--b)
		{
			c = (int)(temp1 /= pow(10,b));	
			temp1 = temp1 - c * pow(10,b);
			
		}					 */	
		Write_Com(0x80);
		//SBUF=*psum;
		while(1)			 //ʹ������Ⱥ�ֻ���ܼ������㡣
 	  	{
			matrixkeyscan2();//��ͣ���ü���ɨ�����
	  	}
	}
		
}

void calculator2(uchar ch)
{
	int d = 0,b;
	*pa = 0;
	{
		if(ch == 0x2F)
		{	
			d = (*psum) % (*psum2);
			(*psum) = (*psum) / (*psum2);
				  			
		}
		if(ch == 0x2A)
			{(*psum) = (*psum) * (*psum2);}
		if(ch == 0x2D)
			(*psum) = (*psum) - (*psum2);
		if(ch == 0x2B)
			(*psum) = (*psum) + (*psum2);
	}
	if(*psum < 0 || (d != 0))
	{
		for(b = 0;b < 5;b++)
		LCD_Write_Data(error[b]);
		delayms(500);
		guiling();
	}
	*psum2 =0; 
}

void jishu(int ch)
{		
	if(*pa >= 1)
		(*psum) = 10 * (*psum);	
	(*psum) += ch;
	(*pa)++;

}
void jishu2(int ch)
{
	if(*pa >= 1)
		*psum2 = 10 * (*psum2);
	(*psum2) += ch;
	(*pa)++;

}
void guiling()
{
	*psum = 0;
	*psum2 = 0;
	LCD_Init();
  	Write_Com(0x80); 
    while(1)
	{
		matrixkeyscan();
	}
}



/***************************************************
�������ܣ���ʼ���ݴ���
***************************************************/
void start()
// ��ʼλ
{
	SDA = 1;    //SDA��ʼ��Ϊ�ߵ�ƽ��1��
   SCL = 1;    //��ʼ���ݴ���ʱ��Ҫ��SCLΪ�ߵ�ƽ��1��
	_nop_();    //�ȴ�һ����������
	_nop_();    //�ȴ�һ����������
	_nop_();    //�ȴ�һ����������
	_nop_();    //�ȴ�һ����������
	SDA = 0;    //SDA���½��ر���Ϊ�ǿ�ʼ�ź�
	_nop_();    //�ȴ�һ����������
	_nop_();    //�ȴ�һ����������
	_nop_();    //�ȴ�һ����������
	_nop_();    //�ȴ�һ����������
	SCL = 0;    //SCLΪ�͵�ƽʱ��SDA�����ݲ�����仯(�������Ժ�����ݴ��ݣ�  
}
/***************************************************
�������ܣ��������ݴ���
***************************************************/
void stop()
// ֹͣλ
{
	SDA = 0;     //SDA��ʼ��Ϊ�͵�ƽ��0��	_n
	SCL = 1;     //�������ݴ���ʱ��Ҫ��SCLΪ�ߵ�ƽ��1��
	_nop_();     //�ȴ�һ����������
	_nop_();     //�ȴ�һ����������
	_nop_();     //�ȴ�һ����������
	_nop_();     //�ȴ�һ����������
	SDA = 1;    //SDA�������ر���Ϊ�ǽ����ź�
	_nop_();     //�ȴ�һ����������
	_nop_();     //�ȴ�һ����������
	_nop_();     //�ȴ�һ����������
	_nop_();     //�ȴ�һ����������
	SDA=0;
	SCL=0;
}
/***************************************************
�������ܣ���AT24Cxx��ȡ����
���ڲ�����x
***************************************************/
unsigned char ReadData()
// ��AT24Cxx�������ݵ�MCU
{
	unsigned char h;
	unsigned char x;   //�����AT24Cxx�ж���������
	for(h = 0; h < 8; h++)
	{
		SCL = 1;                //SCL��Ϊ�ߵ�ƽ
		x<<=1;                  //��x�еĸ�����λ������һλ
		x|=(unsigned char)SDA;  //��SDA�ϵ�����ͨ����λ�����������x��
		SCL = 0;                        //��SCL���½��ض�������
	}
	return(x);                //����ȡ�����ݷ���
}
/***************************************************
�������ܣ���AT24Cxx�ĵ�ǰ��ַд������
��ڲ�����y (�����д������ݣ�
***************************************************/
//�ڵ��ô�����д�뺯��ǰ�����ȵ��ÿ�ʼ����start(),����SCL=0
bit WriteCurrent(unsigned char y)
{
	unsigned char h;
	bit ack_bit;               //����Ӧ��λ
	for(h = 0; h < 8; h++)		// ѭ������8��λ
	{
    	SDA = (bit)(y&0x80);   //ͨ����λ���롱���㽫���λ�����͵�S
		                                  //��Ϊ����ʱ��λ��ǰ����λ�ں�
		_nop_();            //�ȴ�һ����������   
	   SCL = 1;            //��SCL�������ؽ�����д��AT24Cxx      
   	_nop_();            //�ȴ�һ���������� 
	  _nop_();             //�ȴ�һ����������       
		
	  	SCL = 0;            //��SCL������Ϊ�͵�ƽ������SC�����γɴ�����������ģ�������
		y <<= 1;           //��y�еĸ�����λ������һλ
	}
	SDA = 1;			  // �����豸��������Ӧ��ʱ������ĸߵ�ƽ�ڼ�(SCL=1)�ͷ�SDA�ߣ�
	                //����SDA��ת�ɽ����豸(AT24Cxx)����
	_nop_();        //�ȴ�һ���������� 
	_nop_();        //�ȴ�һ���������� 
	SCL = 1;       //���������涨��SCLӦΪ�ߵ�ƽ
	_nop_();       //�ȴ�һ���������� 
	_nop_();       //�ȴ�һ���������� 
	_nop_();       //�ȴ�һ���������� 
	_nop_();       //�ȴ�һ���������� 
	ack_bit = SDA; //�����豸��AT24Cxx)��SDA�͵͵�ƽ����ʾ�Ѿ����յ�һ���ֽ�
	               //���͸ߵ�ƽ����ʾû�н��յ��������쳣
	SCL = 0;       //SCLΪ�͵�ƽʱ��SDA�����ݲ�����仯(�������Ժ�����ݴ��ݣ�
	return  ack_bit;			// ����AT24CxxӦ��λ
}
/***************************************************
�������ܣ���AT24Cxx�е�ָ����ַд������
��ڲ�����add (����ָ���ĵ�ַ����dat(�����д������ݣ�
***************************************************/
void WriteSet(unsigned char add, unsigned char dat)
// ��ָ����ַaddr��д������WriteCurrent
{
	start();               //��ʼ���ݴ���
	WriteCurrent(OP_WRITE);  //ѡ��Ҫ������AT24CxxоƬ������֪Ҫ����д������
	WriteCurrent(add);       //д��ָ����ַ
	WriteCurrent(dat);       //��ǰ��ַ������ָ���ĵ�ַ��д������
	stop();                //ֹͣ���ݴ���
	delayms(4);	       //1���ֽڵ�д������Ϊ1ms, �����ʱ1ms����
}
/***************************************************
�������ܣ���AT24Cxx�еĵ�ǰ��ַ��ȡ����
���ڲ�����x (������������ݣ� 
***************************************************/
unsigned char ReadCurrent()
{
	unsigned char x;
	start();               //��ʼ���ݴ���
	WriteCurrent(OP_READ);   //ѡ��Ҫ������AT24CxxоƬ������֪Ҫ��������
	x=ReadData();         //����ȡ�����ݴ���x
	stop();                //ֹͣ���ݴ���
	return x;              //���ض�ȡ������
}
/***************************************************
�������ܣ���AT24Cxx�е�ָ����ַ��ȡ����
��ڲ�����set_addr
���ڲ�����x 
***************************************************/
unsigned char ReadSet(unsigned char set_addr)
// ��ָ����ַ��ȡ
{
	start();                      //��ʼ���ݴ���
	WriteCurrent(OP_WRITE);       //ѡ��Ҫ������AT24CxxоƬ������֪Ҫ����д������
	WriteCurrent(set_addr);       //д��ָ����ַ
	return(ReadCurrent());        //��ָ����ַ�������ݲ�����
}
/***************************************************
�������ܣ�������
***************************************************/
void EEPROM_write()
{
	int c, i=0;
	long uint temp = *psum;
	while(temp >= 1)
	{	
		temp = temp/10;	
		i++;
	}
	*pi = i + 1;
	SDA = 1;           // SDA=1,SCL=1,ʹ�����豸���ڿ���״̬
	SCL = 1;
	 temp = *psum;
	WriteSet(88,*pi);
	for(;i >= 1;i--)
	{	
		c = temp%10;
		temp = temp/10;	
		WriteSet(i,c);
		
	}
	
}

void EEPROM_read2()
{
    int c = 0, h;
		//LCD_Write_Data(table0[1]);
	SDA = 1;           // SDA=1,SCL=1,ʹ�����豸���ڿ���״̬
	SCL = 1;
	*pi = ReadSet(88);
	c = ReadSet(1);	
	for(h = 2;h<=*pi;h++)
	{			
		LCD_Write_Data(table0[c]);
		jishu2(c);
		c = ReadSet(h);
		
	}
}