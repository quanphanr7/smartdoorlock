#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
#include <string.h>
extern int dem_ngat,dem_uart;
char buf_UART1[20];
int buffer=0;
void EXTI0_IRQHandler(void)
{
 if(EXTI_GetITStatus(EXTI_Line0) != RESET)
 {
  dem_ngat=1;
  EXTI_ClearITPendingBit(EXTI_Line0);
 }
}

int Leng=0,batdau=0;
void USART1_IRQHandler()
	{
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
		{
			unsigned char data = USART_ReceiveData(USART1);
				if(data =='@') 
				{ 
				batdau ++;
				buffer =1;
				}
				if(batdau >1) 
					{
							strncpy(buf_UART1,0,20);
							Leng=0;
							batdau=1;
					}
				if(batdau==1)
				{
					if(data !='@'&&data !='&')
					{
					buf_UART1[Leng] = data;
					Leng++;
					}
					if(data =='&')
						{
							batdau=0;
							Leng =0;
							if(strstr(buf_UART1,"START")) 
							{
								dem_uart=1 ;
								buffer =0;
							}
							if(buffer==1)
							{
								if(dem_uart==2) dem_uart =3;
								buffer =0;
							}
						}
				}
		}	 

}
//void NMI_Handler(void)
//{}
///**
//  * @brief  This function handles Hard Fault exception.
//  * @param  None
//  * @retval None
//  */
//void HardFault_Handler(void)
//{
//  while (1)
//  {}
//}
// 
///**
//  * @brief  This function handles Memory Manage exception.
//  * @param  None
//  * @retval None
//  */
//void MemManage_Handler(void)
//{
//  while (1)
//  {}
//}
// 
///**
//  * @brief  This function handles Bus Fault exception.
//  * @param  None
//  * @retval None
//  */
//void BusFault_Handler(void)
//{
//  while (1)
//  {}
//}
// 
///**
//  * @brief  This function handles Usage Fault exception.
//  * @param  None
//  * @retval None
//  */
//void UsageFault_Handler(void)
//{
//  while (1)
//  {}
//}
///**
//  * @brief  This function handles SVCall exception.
//  * @param  None
//  * @retval None
//  */
//void SVC_Handler(void)
//{}
///**
//  * @brief  This function handles Debug Monitor exception.
//  * @param  None
//  * @retval None
//  */
//void DebugMon_Handler(void)
//{}
///**
//  * @brief  This function handles PendSVC exception.
//  * @param  None
//  * @retval None
//  */
//void PendSV_Handler(void)
//{}
///**
//  * @brief  This function handles SysTick Handler.
//  * @param  None
//  * @retval None
//  */
