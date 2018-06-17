#include "usart.h"

void USART2_Config()
{
			GPIO_InitTypeDef		GPIO_InitStructure ;
			USART_InitTypeDef		USART_InitStructure;
			NVIC_InitTypeDef  	NVIC_InitStructure;
		/*Cap clock cho USART và port su dung*/
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		
			/* Cau Tx mode AF_PP, Rx mode FLOATING  */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		/*Cau hinh USART*/
			USART_InitStructure.USART_BaudRate = 115200;
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;
			USART_InitStructure.USART_StopBits = USART_StopBits_1;
			USART_InitStructure.USART_Parity = USART_Parity_No;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(USART2, &USART_InitStructure);
			
			NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
			USART_ClearFlag(USART2,USART_IT_RXNE);
			USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
			USART_Cmd(USART2,ENABLE);
}
void USART1_Config()
{
			GPIO_InitTypeDef		GPIO_InitStructure ;
			USART_InitTypeDef		USART_InitStructure;
			NVIC_InitTypeDef  	NVIC_InitStructure;
		/*Cap clock cho USART và port su dung*/
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		
			/* Cau Tx mode AF_PP, Rx mode FLOATING  */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		/*Cau hinh USART*/
			USART_InitStructure.USART_BaudRate = 115200;
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;
			USART_InitStructure.USART_StopBits = USART_StopBits_1;
			USART_InitStructure.USART_Parity = USART_Parity_No;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(USART1, &USART_InitStructure);
			
			NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
			USART_ClearFlag(USART1,USART_IT_RXNE);
			USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
//			USART_ClearFlag(USART1,USART_IT_TC);
//			USART_ITConfig(USART1,USART_IT_TC,ENABLE);
			
			USART_Cmd(USART1,ENABLE);
}
void Delay(__IO uint32_t nCount)
{
 while(nCount--)
 {
 }
}
void USART1_gui_chuoi( char *s)
{
	
	while(*s)
	{
		USART_SendData(USART1,*s);
		Delay(1000);
		s++;
	}
}
void USART2_gui_chuoi( char *s)
{
	
	while(*s)
	{
		USART_SendData(USART2,*s);
		Delay(1000);
		s++;
	}
}

