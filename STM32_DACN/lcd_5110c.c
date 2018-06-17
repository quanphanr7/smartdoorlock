#include "lcd_5110c.h"



void LCD_Init()
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_LCD, ENABLE);
 
	 /* Configure PIN RST IN LCD*/
	 GPIO_InitStructure.GPIO_Pin = LCD_PIN_RST;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(LCD_PORT_RST, &GPIO_InitStructure);
	 /* Configure PIN CE IN LCD*/
	 GPIO_InitStructure.GPIO_Pin = LCD_PIN_CE;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(LCD_PORT_CE, &GPIO_InitStructure);
	 /* Configure PIN DC IN LCD*/
	 GPIO_InitStructure.GPIO_Pin = LCD_PIN_DC;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(LCD_PORT_DC, &GPIO_InitStructure);
	 /* Configure PIN DIN IN LCD*/
	 GPIO_InitStructure.GPIO_Pin = LCD_PIN_DIN;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(LCD_PORT_DIN, &GPIO_InitStructure);
	 /* Configure PIN RST IN LCD*/
	 GPIO_InitStructure.GPIO_Pin = LCD_PIN_CLK;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(LCD_PORT_CLK, &GPIO_InitStructure);
		/* Configure PIN LED IN LCD*/
	 GPIO_InitStructure.GPIO_Pin = LCD_PIN_LED;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(LCD_PORT_LED, &GPIO_InitStructure);
	 GPIO_SetBits(LCD_PORT_LED,LCD_PIN_LED);
	 
	 
	Khoi_tao_lcd();
}

// Ham ghi du lieu	

void Ghi_du_lieu(unsigned char du_lieu, unsigned char Chon_du_lieu) 
{    
	unsigned char i;   
	 GPIO_ResetBits(LCD_PORT_CE,LCD_PIN_CE); 			//CE=0; 
	if (Chon_du_lieu == 0) 
		GPIO_ResetBits(LCD_PORT_DC,LCD_PIN_DC); 		//DC=0;           
	else 
		GPIO_SetBits(LCD_PORT_DC,LCD_PIN_DC); 			//DC=1;  
	for(i=0;i<8;i++) 
	{         
		if(du_lieu&0x80) 
			GPIO_SetBits(LCD_PORT_DIN,LCD_PIN_DIN); 	//DIN=1;       
    else  
			GPIO_ResetBits(LCD_PORT_DIN,LCD_PIN_DIN); 		//DIN=0;       
      GPIO_ResetBits(LCD_PORT_CLK,LCD_PIN_CLK); 		//CLK=0;       
      du_lieu = du_lieu << 1;       
      GPIO_SetBits(LCD_PORT_CLK,LCD_PIN_CLK); 			//CLK=1;    
  }     
  GPIO_SetBits(LCD_PORT_CE,LCD_PIN_CE); 			//CE=1; 
}

// Ham dinh vi vi tri 	
void Toa_do(unsigned char x, unsigned char y) 
{ 
	Ghi_du_lieu(0x80|x, 0);    
	Ghi_du_lieu(0x40|y, 0); 
}

// Xoa LCD 	
void Xoa_trang()     
		{  
			unsigned char t;  
			unsigned char k;  
			Toa_do(0,0);  
      for(t=0;t<6;t++)  
{    
for(k=0;k<84;k++) Ghi_du_lieu(0x00,1);        	
		} 
		}
		
		//In ky tu 
void In_ky_tu(unsigned char x,unsigned char y,char data) 
			{
	unsigned char v;
	if((data >= 0x20) && (data <= 0x7a)){
		data=data-32;
			Toa_do(x,y);
		for(v=0;v<5;v++)
			Ghi_du_lieu(font5[data][v],1);
	}
}
void Xoa_ky_tu(unsigned char x,unsigned char y)
	{
		Toa_do(x,y);
		for(int k=x;k<x+6;k++) Ghi_du_lieu(0x00,1);
	}

// In chuoi ky tu 
void LCD_In_chuoi(unsigned char x,unsigned char y,char *s) 
{    
	while(*s)     
		{       
			In_ky_tu(x,y,*s);      
			s++;      
			x += 6; // Vi chu co do rong la 5 nên ta dih 6 de tao dan cah chu    
			} 
			}

//Khoi tao LCD
void Khoi_tao_lcd(void) 
{ 
// Ham khoi tao dua tren datasheet de chinh sua cho hop ly	
	GPIO_ResetBits(LCD_PORT_RST,LCD_PIN_RST); 		//RST=0; 
	GPIO_SetBits(LCD_PORT_RST,LCD_PIN_RST); 			//RST=1;      
	Ghi_du_lieu(0x21, 0);     // Mo che do o rong
	Ghi_du_lieu(0x80+45, 0);  // Set do tuong phan
	Ghi_du_lieu(0x04+0, 0);   // Set thong so nhiet
	Ghi_du_lieu(0x10+4, 0);   // Set thong so BIAS
	Ghi_du_lieu(0x20, 0);     // Dong che do o rong
	Ghi_du_lieu(0x0C, 0);     // Hien thi binh thuong ,0x0D Am ban
}

