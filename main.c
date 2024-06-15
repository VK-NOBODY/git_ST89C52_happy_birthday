/**************************************************************************************
���������пƼ����޹�˾��PRECHIN ���У�
����֧�֣�www.prechin.net
PRECHIN
 ����

ʵ�����ƣ�LED����ʵ��(��ʾ����)
����˵����	
ʵ���������س����8*8LED������ʾ����0
ע�����LED�����Ե�J24��ɫ����ñ�̽ӵ�GNDһ��																				  
***************************************************************************************/
#include "reg51.h"
#include <INTRINS.H>

typedef unsigned int u16;	//��ϵͳĬ���������ͽ����ض���
typedef unsigned char u8;

//����74HC595���ƹܽ�
sbit SRCLK=P3^6;	//��λ�Ĵ���ʱ������
sbit RCLK=P3^5;		//�洢�Ĵ���ʱ������
sbit SER=P3^4; 		//������������

sbit k1 = P3^1; //��������

#define LEDDZ_COL_PORT	P0	//�����п��ƶ˿�


u8 gled_row0[8]={0x00,0x7C,0x82,0x82,0x82,0x7C,0x00,0x00};//LED������ʾ����0��������

u8 gled_row1[8]={0x00,0x00,0x00,0x40,0xFF,0x00,0x00,0x00};//LED������ʾ����1��������

u8 gled_row2[8]={0x00,0x41,0x83,0x85,0x89,0x71,0x00,0x00};//LED������ʾ����2��������

u8 gled_row3[8]={0x00,0x42,0x89,0x89,0x89,0x76,0x00,0x00};//LED������ʾ����3��������

u8 gled_row4[8]={0x00,0x70,0x08,0x08,0x08,0x7E,0x00,0x00};//LED������ʾ����4��������

u8 gled_row5[8]={0x00,0x32,0x49,0x49,0x49,0x46,0x00,0x00};//LED������ʾ����5��������

u8 gled_row6[8]={0x00,0x7E,0x89,0x89,0x89,0x46,0x00,0x00};//LED������ʾ����6��������

u8 gled_row7[8]={0x00,0x40,0x40,0x40,0x40,0x7F,0x00,0x00};//LED������ʾ����7��������

u8 gled_row8[8]={0x00,0x76,0x89,0x89,0x89,0x76,0x00,0x00};//LED������ʾ����8��������

u8 gled_row9[8]={0x00,0x72,0x89,0x89,0x89,0x7E,0x00,0x00};//LED������ʾ����9��������

u8 gled_col[8]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//LED����������

u16 time = 0;



					 /***********���տ���**************************************************************************/
void Delay(unsigned char xms)		//@11.0592MHz
{
	unsigned char i, j;
	while(xms--)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}


void MetrixLED_Init()
{
	RCLK=0;
	SRCLK=0;
}

//74HC595���Ҫ��ʾ��һ�� Row:0~7
void _74HC595_WriteRow(unsigned char Row)
{
	unsigned char i = 0;
	Row=0x80>>Row;
	for(i=0;i<8;i++)
	{
		SER=Row&(0x80>>i);
		SRCLK=1;
		SRCLK=0;
	}
	RCLK=1;
	RCLK=0;
}

//Data: 1��0��
void MertixLED_ShowRow(unsigned char Row,Data)
{
	_74HC595_WriteRow(Row);
	P0=~Data;
	Delay(2);
	_74HC595_WriteRow(0xff);
}


unsigned char code Animation[]={
    0x02,0x1C,0x28,0x48,0x7E,0x08,0x2C,0x5A,
 	0x44,0x44,0x4F,0xE5,0x4F,0x44,0x4A,0x51,
    0x00,0x7C,0x44,0x44,0x7C,0x44,0x44,0x7C,  
	0x14,0x24,0x7F,0x84,0x04,0x3F,0x04,0x3F
};

/***********���տ���********************************************************************************************/
  


/*******************************************************************************
* �� �� ��       : delay_10us
* ��������		 : ��ʱ������ten_us=1ʱ����Լ��ʱ10us
* ��    ��       : ten_us
* ��    ��    	 : ��
*******************************************************************************/
void delay_10us(u16 ten_us)
{
	while(ten_us--);	
}

/*******************************************************************************
* �� �� ��         : hc595_write_data(u8 dat)
* ��������		   : ��74HC595д��һ���ֽڵ�����
* ��    ��         : dat������
* ��    ��         : ��
*******************************************************************************/
void hc595_write_data(u8 dat)
{
	u8 i=0;
	
	for(i=0;i<8;i++)//ѭ��8�μ��ɽ�һ���ֽ�д��Ĵ�����
	{
		SER=dat>>7;//���ȴ���һ���ֽ��еĸ�λ
		dat<<=1;//����λ�ƶ�����λ
		SRCLK=0;
		delay_10us(1);
		SRCLK=1;
		delay_10us(1);//��λ�Ĵ���ʱ�������ؽ��˿���������Ĵ�����	
	}
	RCLK=1;
	delay_10us(1);
	RCLK=0;//�洢�Ĵ���ʱ�������ؽ�ǰ��д�뵽�Ĵ������������	
}


/*******************************************************************************
* �� �� ��       : main
* ��������		 : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void main()
{	

  
unsigned char i,offset=24,count=0;
	MetrixLED_Init();

    while(1)
	{
		for(i=0;i<8;i++)
		{
			MertixLED_ShowRow(i,Animation[i+offset]);
		}
		count++;
		if(count>5)
		{
			count=0;

			offset--;
			if(offset < 1)  //�����ƶ�
				offset=24;
		/*	offset++;
			if(offset>32)  //�����ƶ�
				offset=0;*/
			
		}
		if(k1 == 0)
	    {
				  u8 i=0;  

	while(1)
	{			
	
	    time = 50;
		while(time) {
		   time--;
		   for(i=0;i<8;i++)//ѭ��8��ɨ��8�С���
		   {
		  	LEDDZ_COL_PORT=gled_col[i];//������ѡ����
			hc595_write_data(gled_row9[i]);//������ѡ����
			delay_10us(100);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
			hc595_write_data(0x00);//��Ӱ	
		   }		
	    }

	    time = 50;
		while(time) {

		time--;
		for(i=0;i<8;i++)//ѭ��8��ɨ��8�С���
		{
			LEDDZ_COL_PORT=gled_col[i];//������ѡ����
			hc595_write_data(gled_row8[i]);//������ѡ����
			delay_10us(100);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
			hc595_write_data(0x00);//��Ӱ	
		}
		}


	    time = 50;
		while(time) {
			time--;
		for(i=0;i<8;i++)//ѭ��8��ɨ��8�С���
		{
		
			LEDDZ_COL_PORT=gled_col[i];//������ѡ����
			hc595_write_data(gled_row7[i]);//������ѡ����
			delay_10us(100);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
			hc595_write_data(0x00);//��Ӱ	
		}
		}

		 time = 50;
		while(time) {
			time--;
		for(i=0;i<8;i++)//ѭ��8��ɨ��8�С���
		{
	
			LEDDZ_COL_PORT=gled_col[i];//������ѡ����
			hc595_write_data(gled_row6[i]);//������ѡ����
			delay_10us(100);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
			hc595_write_data(0x00);//��Ӱ	
		}
		}

		 time = 50;
		while(time) {
			time--;
		for(i=0;i<8;i++)//ѭ��8��ɨ��8�С���
		{
	
			LEDDZ_COL_PORT=gled_col[i];//������ѡ����
			hc595_write_data(gled_row5[i]);//������ѡ����
			delay_10us(100);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
			hc595_write_data(0x00);//��Ӱ	
		}
		}

		 time = 50;
		while(time) {
			time--;
		for(i=0;i<8;i++)//ѭ��8��ɨ��8�С���
		{
	
			LEDDZ_COL_PORT=gled_col[i];//������ѡ����
			hc595_write_data(gled_row4[i]);//������ѡ����
			delay_10us(100);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
			hc595_write_data(0x00);//��Ӱ	
		}
		}

		 time = 50;
		while(time) {
			time--;
		for(i=0;i<8;i++)//ѭ��8��ɨ��8�С���
		{
	
			LEDDZ_COL_PORT=gled_col[i];//������ѡ����
			hc595_write_data(gled_row3[i]);//������ѡ����
			delay_10us(100);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
			hc595_write_data(0x00);//��Ӱ	
		}
		}

		 time = 50;
		while(time) {
			time--;
		for(i=0;i<8;i++)//ѭ��8��ɨ��8�С���
		{
		
			LEDDZ_COL_PORT=gled_col[i];//������ѡ����
			hc595_write_data(gled_row2[i]);//������ѡ����
			delay_10us(100);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
			hc595_write_data(0x00);//��Ӱ	
		}
		}

		 time = 50;
		while(time) {
			time--;
		for(i=0;i<8;i++)//ѭ��8��ɨ��8�С���
		{
		
			LEDDZ_COL_PORT=gled_col[i];//������ѡ����
			hc595_write_data(gled_row1[i]);//������ѡ����
			delay_10us(100);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
			hc595_write_data(0x00);//��Ӱ	
		}
		}

		 time = 50;
		while(time) {
			time--;
		for(i=0;i<8;i++)//ѭ��8��ɨ��8�С���
		{
		
			LEDDZ_COL_PORT=gled_col[i];//������ѡ����
			hc595_write_data(gled_row0[i]);//������ѡ����
			delay_10us(100);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
			hc595_write_data(0x00);//��Ӱ	
		}
		}


						
	}	
	}	
	    }
	}
