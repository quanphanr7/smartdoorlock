#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include <string.h>
void USART2_Config(void);
void USART1_Config(void);
void Delay(__IO uint32_t nCount);
void USART1_gui_chuoi( char *s);
void USART2_gui_chuoi( char *s);
void USART1_IRQHandler(void);
