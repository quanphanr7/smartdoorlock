#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f10x.h"                  // Device header


#define HOPSO 0
#define NGUYENTO 1

long int							UCLN(long unsigned int, long unsigned int);
long int							fermat_testing(long unsigned int);
long unsigned int			mod_pow(long long unsigned int, long unsigned int, long unsigned int);
void									phantich(long unsigned int, int *, int *);
long int							miler_rabin(long unsigned int);
long unsigned int			exp_modulo(long unsigned int, long unsigned int);
long unsigned int			modulo_inverse(long unsigned int, long unsigned int);
void 									tao_khoa(void);
void 									tao_so_nguyen_to(void);
void 									int_to_char(long long unsigned int , char *);
static long unsigned int k, m; // private_key, public_key_N, public_key_E;

void TIM2_Configuration(void);
