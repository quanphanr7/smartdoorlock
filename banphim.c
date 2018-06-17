#include "banphim.h"
#include "lcd_5110c.h"
 GPIO_InitTypeDef		GPIO_InitStructure ;
 NVIC_InitTypeDef  NVIC_InitStructure;
 EXTI_InitTypeDef  EXTI_InitStructure;
int dem_sai=0;

 
unsigned char KEY_4X4[4][4]={'1','2','3','A',
                              '4','5','6','B',
                              '7','8','9','C',
                              '*','0','#','D'
														};

void key_pad_Config()
{
	 RCC_APB2PeriphClockCmd(RCC_PORT_ROW, ENABLE);
 
	 /* Configure PIN ROW 1 In KEYPAD*/
	 GPIO_InitStructure.GPIO_Pin = ROW_1;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(PORT_ROW_1, &GPIO_InitStructure);
	/* Configure PIN ROW 2 In KEYPAD*/
	 GPIO_InitStructure.GPIO_Pin = ROW_2;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(PORT_ROW_2, &GPIO_InitStructure);
	/* Configure PIN ROW 3 In KEYPAD*/
	 GPIO_InitStructure.GPIO_Pin = ROW_3;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(PORT_ROW_3, &GPIO_InitStructure);
	/* Configure PIN ROW 4 In KEYPAD*/
	 GPIO_InitStructure.GPIO_Pin = ROW_4;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(PORT_ROW_4, &GPIO_InitStructure);
	 /* Configure PIN COL 1 In KEYPAD*/
	 GPIO_InitStructure.GPIO_Pin = COL_1;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	 GPIO_Init(PORT_COL_1, &GPIO_InitStructure);
	 /* Configure PIN COL 2 In KEYPAD*/
	 GPIO_InitStructure.GPIO_Pin = COL_2;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	 GPIO_Init(PORT_COL_2, &GPIO_InitStructure);
	 /* Configure PIN COL 3 In KEYPAD*/
	 GPIO_InitStructure.GPIO_Pin = COL_3;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	 GPIO_Init(PORT_COL_3, &GPIO_InitStructure);
	 /* Configure PIN COL 4 In KEYPAD*/
	 GPIO_InitStructure.GPIO_Pin = COL_4;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	 GPIO_Init(PORT_COL_4, &GPIO_InitStructure);
	 
	 	 /* Configure PIN RELAY*/
	 GPIO_InitStructure.GPIO_Pin = PIN_RELAY;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(PORT_RELAY, &GPIO_InitStructure);
	 GPIO_SetBits(PORT_RELAY,PIN_RELAY);
}	
void EXTILine0_Config(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
  
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);
  
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
      
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void check_banphim()
	{
		NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
		NVIC_Init(&NVIC_InitStructure);
		Xoa_trang();
		LCD_In_chuoi(0,0,"XIN MOI BAN");
		LCD_In_chuoi(0,1,"-----------");
		LCD_In_chuoi(0,2,"NHAP MAT KHAU");
		
		int i=0,j=0;
		char password[10];
		strncpy(password,0,10);
		unsigned char key;
		key = get_key_4x4();
		while(!check_OK())
			{
				key=get_key_4x4();
				if(key !=0 &&key !='A' && key !='B' &&key !='*' &&key !='#'&&key !='C' &&key !='D')
					{
						password[i]=key;
						In_ky_tu(j,3,password[i]);
						Delay_ms(100);
						In_ky_tu(j,3,'*');
						i++;
						j=j+6;
						if(j==66) goto exit;

					}
				if(key =='C')
					{
						i--,j=j-6;
						Xoa_ky_tu(j,3);
						password[i] = 0x00;
					}	
				while(key) key = get_key_4x4();	
				Delay_ms(5);
			}
			if(check_OK())
			{
				exit:
				i=j=0;
				Xoa_trang();
				LCD_In_chuoi(0,0,"SMART DOORLOCK");
				LCD_In_chuoi(0,1,"--------------");
				LCD_In_chuoi(0,2,password);
				if (strstr(password,matkhau))
					{
						LCD_In_chuoi(0,4,"MAT KHAU DUNG");
						GPIO_ResetBits(PORT_RELAY,PIN_RELAY);
						Delay_ms(3000);
						GPIO_SetBits(PORT_RELAY,PIN_RELAY);
						Xoa_trang();
						LCD_In_chuoi(0,0,"SMART DOORLOCK");
						LCD_In_chuoi(0,1," -----------");
						LCD_In_chuoi(0,2,"XIN MOI BAN");
						LCD_In_chuoi(0,3," -----------");
						LCD_In_chuoi(0,4,"NHAP MAT KHAU");
					}
					else
						{
							LCD_In_chuoi(0,3,"MAT KHAU SAI");
							LCD_In_chuoi(0,4,"--------------");
							LCD_In_chuoi(0,5,"XIN NHAP LAI");
							dem_sai++;
							if(dem_sai==5)
								{
									Xoa_trang();
									LCD_In_chuoi(0,0,"NHAP SAI 5 LAN");
									LCD_In_chuoi(0,1,"--------------");
									LCD_In_chuoi(0,2,"KHOA TRONG 10S");
									for(int k=6;k<66;k=k+6)
									{
										In_ky_tu(k,3,'=');
										Delay_ms(1000);
									}
									Xoa_trang();
									LCD_In_chuoi(0,0,"SMART DOORLOCK");
									LCD_In_chuoi(0,1," -----------");
									LCD_In_chuoi(0,2,"XIN MOI BAN");
									LCD_In_chuoi(0,3," -----------");
									LCD_In_chuoi(0,4,"NHAP MAT KHAU");
								}
						}
			}
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);	
	}
void scan_row(int i)
{
	GPIO_SetBits(PORT_ROW_1,ROW_1);
	GPIO_SetBits(PORT_ROW_2,ROW_2);
	GPIO_SetBits(PORT_ROW_3,ROW_3);
	GPIO_SetBits(PORT_ROW_4,ROW_4);
  switch(i)
	{
		case 1: { GPIO_ResetBits(PORT_ROW_1,ROW_1);break;}
		case 2: { GPIO_ResetBits(PORT_ROW_2,ROW_2);break;}
		case 3: { GPIO_ResetBits(PORT_ROW_3,ROW_3);break;}
		case 4: { GPIO_ResetBits(PORT_ROW_4,ROW_4);break;}
	}
}
int check_button()
	{
		 GPIO_ResetBits(PORT_ROW_1,ROW_1);
		 GPIO_ResetBits(PORT_ROW_2,ROW_2);
		 GPIO_ResetBits(PORT_ROW_3,ROW_3);
		 GPIO_ResetBits(PORT_ROW_4,ROW_4);
		if( GPIO_ReadInputDataBit(PORT_COL_1,COL_1)==0 || GPIO_ReadInputDataBit(PORT_COL_2,COL_2)==0 
			|| GPIO_ReadInputDataBit(PORT_COL_3,COL_3)==0 || GPIO_ReadInputDataBit(PORT_COL_4,COL_4)==0) 
			return 1;
		else return 0;
	}
int check_unlock()
	{
		scan_row(1);
		if(GPIO_ReadInputDataBit(PORT_COL_4,COL_4)==0) return 1;
		else return 0;
	}
int check_OK()
	{
		scan_row(4);
		if(GPIO_ReadInputDataBit(PORT_COL_4,COL_4)==0) return 1;
		else return 0;
	}
unsigned char get_key_4x4()
{         
         for(int i=1;i<5;i++)
         {            
            scan_row(i);
            if(GPIO_ReadInputDataBit(PORT_COL_1,COL_1)==0 ) return KEY_4X4[i-1][0];
            if(GPIO_ReadInputDataBit(PORT_COL_2,COL_2)==0 ) return KEY_4X4[i-1][1];
            if(GPIO_ReadInputDataBit(PORT_COL_3,COL_3)==0 ) return KEY_4X4[i-1][2];
            if(GPIO_ReadInputDataBit(PORT_COL_4,COL_4)==0 ) return KEY_4X4[i-1][3];
         }      
   return 0;
}

void Delay_ms(__IO uint32_t nCount)
{
	nCount=7200*nCount;
 while(nCount--)
 {
 }
}
