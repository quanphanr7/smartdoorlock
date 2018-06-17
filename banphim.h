#include "stm32f10x.h"                  // Device header
#include <string.h>
#define 	PORT_ROW_1			GPIOB
#define		ROW_1						GPIO_Pin_2
#define 	PORT_ROW_2			GPIOB
#define		ROW_2						GPIO_Pin_0
#define 	PORT_ROW_3			GPIOC
#define		ROW_3						GPIO_Pin_4
#define 	PORT_ROW_4			GPIOA
#define		ROW_4						GPIO_Pin_6
#define 	PORT_COL_1			GPIOA
#define		COL_1						GPIO_Pin_4
#define 	PORT_COL_2			GPIOA
#define		COL_2						GPIO_Pin_2
#define 	PORT_COL_3			GPIOC
#define		COL_3						GPIO_Pin_2
#define 	PORT_COL_4			GPIOC
#define		COL_4						GPIO_Pin_0
#define 	PORT_RELAY			GPIOB
#define		PIN_RELAY				GPIO_Pin_1
#define 	RCC_PORT_RELAY 						RCC_APB2Periph_GPIOC
#define 	RCC_PORT_ROW 							RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOB| RCC_APB2Periph_GPIOC
#define 	RCC_PORT_COL 							RCC_APB2Periph_GPIOA|  RCC_APB2Periph_GPIOC

void Delay_ms(__IO uint32_t nCount);
unsigned char get_key_4x4(void);
int check_OK(void);
int check_unlock(void);
int check_button(void);
void check_banphim(void);
void scan_row(int );
void key_pad_Config(void);
void EXTILine0_Config(void);
static char matkhau[10]="123654";
