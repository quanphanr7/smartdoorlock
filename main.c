#include "lcd_5110c.h"
#include "banphim.h"
#include "usart.h"
#include "mahoa.h"
int dem_ngat=0,dem_uart=0;
extern char buf_UART1[20];
char key[20],data[20];
long unsigned int Songuyento[1000],dem, private_key, public_key_N, public_key_E,mahoa,giaima;
void tao_so_nguyen_to(void);
 long long unsigned int temp;;
int main()
{
	TIM2_Configuration();
	LCD_Init();
	key_pad_Config();
	EXTILine0_Config();
	USART1_Config();;
	Xoa_trang();
		LCD_In_chuoi(0,0,"SMART DOORLOCK");
		LCD_In_chuoi(0,1," -----------");
		LCD_In_chuoi(0,2,"XIN MOI BAN");
		LCD_In_chuoi(0,3," -----------");
		LCD_In_chuoi(0,4,"NHAP MAT KHAU");
	tao_so_nguyen_to();
	
	while(1)
	{

		check_unlock();
		if(dem_ngat==1)
		{
			check_banphim();
			dem_ngat=0;
		}
			if(dem_uart ==1)
			{
					char key_N[20],key_E[20];
					tao_khoa();
					int_to_char(public_key_N,key_N);
					int_to_char(public_key_E,key_E);
					int_to_char(mahoa,data);
					USART1_gui_chuoi("N");
					USART1_gui_chuoi(key_N);
					USART1_gui_chuoi("E");
					USART1_gui_chuoi(key_E);
					//USART1_gui_chuoi("DATA");
					//USART1_gui_chuoi(data);
				strncpy(buf_UART1,0,20);
				dem_uart=2;
			}
			if( dem_uart ==3)
			{
				Delay_ms(500);
				temp=atoll(buf_UART1);
				giaima = mod_pow(temp, private_key, public_key_N);
				//int_to_char(giaima,key);
				//USART1_gui_chuoi("\nKEY GIAI MA : ");
				//USART1_gui_chuoi(key);
				Xoa_trang();
				LCD_In_chuoi(0,0,"SMART DOORLOCK");
				LCD_In_chuoi(0,1,"--------------");
				LCD_In_chuoi(0,2,key);
				if (giaima==123654)
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
							LCD_In_chuoi(0,4,"  ----------");
							LCD_In_chuoi(0,5,"XIN NHAP LAI");
					}
			strncpy(buf_UART1,0,20);
			dem_uart=0 ;
			}

	}
}
