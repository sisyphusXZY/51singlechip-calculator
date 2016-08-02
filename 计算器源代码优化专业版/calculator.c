/*
*************************************************************************************************************
* 日期；2016.1.9                              
* 文件名：calculator.c
* 描  述：键盘及lcd的调用函数
* 版本号：1.1.0
* 备  注：通用性不足，编码过多，有待优化，算法复杂
*************************************************************************************************************
*/

#define  _CALCULATOR_C
#include "calculdefine.h"
#include "calculator.h"




void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms即延时约xms毫秒
		for(j=110;j>0;j--);
}


void off_shumaguan()
{	
	du=1;
	P0=0x00; // 关闭数码管
	du=0;
}
 /*------------------------------------------------
              初始化函数
------------------------------------------------*/
void LCD_Init() 
{	
	Write_Com(0x01);	  /*清屏*/
	Write_Com(0x38);    /*显示模式设置*/ 
	Write_Com(0x0F);    /*显示光标移动设置*/ 
	Write_Com(0x06); 
	  
}
/*------------------------------------------------
              写入命令函数
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
              写入数据函数
------------------------------------------------*/
 void LCD_Write_Data(uchar Data) 
 { 
 //while(LCD_Check_Busy()); //忙则等待
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
             键盘
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
			delayms(800);  //提供时间放手，否则会再次输入等号。
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
		   delayms(60);	 //经测试，比较接近3秒
			h++;
         }
		 while((temp==0x77)&&(j <= 31))
         {
           temp=P3;  
		   delayms(60);	 //经测试，比较接近3秒
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
			delayms(800);  //提供时间放手，否则会再次输入等号。	
			key = 16;	   
		 } 
		 if(j>=30)
		 {
			EEPROM_read2();
			for(g = 0;g < 4;g++)
				LCD_Write_Data(read[g]);
			delayms(800);  //提供时间放手，否则会再次输入等号。		  
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
             计算功能
------------------------------------------------*/
void calculator(uchar ch)
{
	*pa = 0;
	if(ch==0x2B)	
		while(1)
  		{
			matrixkeyscan2(0x2B);//不停调用键盘扫描程序
  		}
	if(ch==0x2D)
		while(1)
	 	{
			matrixkeyscan2(0x2D);//不停调用键盘扫描程序
  		}	
	if(ch==0x2A)
		while(1)
 	 	{
			matrixkeyscan2(0x2A);//不停调用键盘扫描程序
	  	}
	if(ch==0x2F)
		while(1)
 	  	{
			matrixkeyscan2(0x2F);//不停调用键盘扫描程序
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
		/*Write_Com(0x80);			  以下4行指令，清液晶屏第一行
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
		while(1)			 //使得输入等号只后能继续运算。
 	  	{
			matrixkeyscan2();//不停调用键盘扫描程序
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
函数功能：开始数据传送
***************************************************/
void start()
// 开始位
{
	SDA = 1;    //SDA初始化为高电平“1”
   SCL = 1;    //开始数据传送时，要求SCL为高电平“1”
	_nop_();    //等待一个机器周期
	_nop_();    //等待一个机器周期
	_nop_();    //等待一个机器周期
	_nop_();    //等待一个机器周期
	SDA = 0;    //SDA的下降沿被认为是开始信号
	_nop_();    //等待一个机器周期
	_nop_();    //等待一个机器周期
	_nop_();    //等待一个机器周期
	_nop_();    //等待一个机器周期
	SCL = 0;    //SCL为低电平时，SDA上数据才允许变化(即允许以后的数据传递）  
}
/***************************************************
函数功能：结束数据传送
***************************************************/
void stop()
// 停止位
{
	SDA = 0;     //SDA初始化为低电平“0”	_n
	SCL = 1;     //结束数据传送时，要求SCL为高电平“1”
	_nop_();     //等待一个机器周期
	_nop_();     //等待一个机器周期
	_nop_();     //等待一个机器周期
	_nop_();     //等待一个机器周期
	SDA = 1;    //SDA的上升沿被认为是结束信号
	_nop_();     //等待一个机器周期
	_nop_();     //等待一个机器周期
	_nop_();     //等待一个机器周期
	_nop_();     //等待一个机器周期
	SDA=0;
	SCL=0;
}
/***************************************************
函数功能：从AT24Cxx读取数据
出口参数：x
***************************************************/
unsigned char ReadData()
// 从AT24Cxx移入数据到MCU
{
	unsigned char h;
	unsigned char x;   //储存从AT24Cxx中读出的数据
	for(h = 0; h < 8; h++)
	{
		SCL = 1;                //SCL置为高电平
		x<<=1;                  //将x中的各二进位向左移一位
		x|=(unsigned char)SDA;  //将SDA上的数据通过按位“或“运算存入x中
		SCL = 0;                        //在SCL的下降沿读出数据
	}
	return(x);                //将读取的数据返回
}
/***************************************************
函数功能：向AT24Cxx的当前地址写入数据
入口参数：y (储存待写入的数据）
***************************************************/
//在调用此数据写入函数前需首先调用开始函数start(),所以SCL=0
bit WriteCurrent(unsigned char y)
{
	unsigned char h;
	bit ack_bit;               //储存应答位
	for(h = 0; h < 8; h++)		// 循环移入8个位
	{
    	SDA = (bit)(y&0x80);   //通过按位“与”运算将最高位数据送到S
		                                  //因为传送时高位在前，低位在后
		_nop_();            //等待一个机器周期   
	   SCL = 1;            //在SCL的上升沿将数据写入AT24Cxx      
   	_nop_();            //等待一个机器周期 
	  _nop_();             //等待一个机器周期       
		
	  	SCL = 0;            //将SCL重新置为低电平，以在SCＬ线形成传送数据所需的８个脉冲
		y <<= 1;           //将y中的各二进位向左移一位
	}
	SDA = 1;			  // 发送设备（主机）应在时钟脉冲的高电平期间(SCL=1)释放SDA线，
	                //以让SDA线转由接收设备(AT24Cxx)控制
	_nop_();        //等待一个机器周期 
	_nop_();        //等待一个机器周期 
	SCL = 1;       //根据上述规定，SCL应为高电平
	_nop_();       //等待一个机器周期 
	_nop_();       //等待一个机器周期 
	_nop_();       //等待一个机器周期 
	_nop_();       //等待一个机器周期 
	ack_bit = SDA; //接受设备（AT24Cxx)向SDA送低电平，表示已经接收到一个字节
	               //若送高电平，表示没有接收到，传送异常
	SCL = 0;       //SCL为低电平时，SDA上数据才允许变化(即允许以后的数据传递）
	return  ack_bit;			// 返回AT24Cxx应答位
}
/***************************************************
函数功能：向AT24Cxx中的指定地址写入数据
入口参数：add (储存指定的地址）；dat(储存待写入的数据）
***************************************************/
void WriteSet(unsigned char add, unsigned char dat)
// 在指定地址addr处写入数据WriteCurrent
{
	start();               //开始数据传递
	WriteCurrent(OP_WRITE);  //选择要操作的AT24Cxx芯片，并告知要对其写入数据
	WriteCurrent(add);       //写入指定地址
	WriteCurrent(dat);       //向当前地址（上面指定的地址）写入数据
	stop();                //停止数据传递
	delayms(4);	       //1个字节的写入周期为1ms, 最好延时1ms以上
}
/***************************************************
函数功能：从AT24Cxx中的当前地址读取数据
出口参数：x (储存读出的数据） 
***************************************************/
unsigned char ReadCurrent()
{
	unsigned char x;
	start();               //开始数据传递
	WriteCurrent(OP_READ);   //选择要操作的AT24Cxx芯片，并告知要读其数据
	x=ReadData();         //将读取的数据存入x
	stop();                //停止数据传递
	return x;              //返回读取的数据
}
/***************************************************
函数功能：从AT24Cxx中的指定地址读取数据
入口参数：set_addr
出口参数：x 
***************************************************/
unsigned char ReadSet(unsigned char set_addr)
// 在指定地址读取
{
	start();                      //开始数据传递
	WriteCurrent(OP_WRITE);       //选择要操作的AT24Cxx芯片，并告知要对其写入数据
	WriteCurrent(set_addr);       //写入指定地址
	return(ReadCurrent());        //从指定地址读出数据并返回
}
/***************************************************
函数功能：主函数
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
	SDA = 1;           // SDA=1,SCL=1,使主从设备处于空闲状态
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
	SDA = 1;           // SDA=1,SCL=1,使主从设备处于空闲状态
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