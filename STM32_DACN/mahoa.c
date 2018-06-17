#include "mahoa.h"
extern long unsigned int Songuyento[1000],dem ,private_key, public_key_N, public_key_E,mahoa,giaima ;


void tao_so_nguyen_to()
{
	for (long unsigned int i =49153 ; i < 65535; i = i + 2)
	{
		if (fermat_testing(i) == 1)
		{
			Songuyento[dem] = i;
			dem = dem + 1;
		}

	}
}
void tao_khoa()
{
	long unsigned int p, q;
	p = Songuyento[TIM_GetCounter(TIM2)%(dem/2) +dem/2];
	q = Songuyento[TIM_GetCounter(TIM2)%(dem/2)];

	public_key_N = p * q;
	public_key_E = 65537;
	private_key = modulo_inverse(public_key_E, (p - 1)*(q - 1));
	//mahoa = mod_pow(123654, public_key_E, public_key_N);
//	giaima = mod_pow(mahoa, private_key, public_key_N);

}
	
long int fermat_testing(long unsigned int N)
{

	long int a = 2 + (long unsigned int)rand() % (N - 3);
	if (UCLN(a, N) != 1)
	{
		return HOPSO;
	}
	else
	{
		if (mod_pow(a, N - 1, N) != 1)
		{
			return HOPSO;
		}
		else
		{
			return miler_rabin(N);
		}
	}
}
long int UCLN(long unsigned int a, long unsigned int b)
{
	long int x;
	while (b != 0)
	{
		x = b;
		b = a % b;
		a = x;
	}
	return a;
}
long unsigned int mod_pow(long long unsigned int a, long unsigned int b, long unsigned int p)
{
	if (b == 1) return a;
	else
	{
		long long unsigned int x = mod_pow(a, b / 2, p);
		if (b % 2 == 0)
			return (x*x) % p;
		else
			return (((x*x) % p)*a) % p;

	}
}

long int miler_rabin(long unsigned int N)
{
	int k, m;
	phantich(N - 1, &k, &m);
	long unsigned  int X, Y;
	long int b = 2 + (long unsigned int)rand() % (N - 3);
	X = mod_pow(b, m, N);
	if (X == 1) return NGUYENTO;
	else
	{
		int i = 1;
		while (i <= k)
		{
			Y = (X * X) % N;
			if (Y == 1)
			{
				if (X == N - 1) return NGUYENTO;
				else
					return HOPSO;
			}
			i++;
		}
		return HOPSO;
	}

}
void phantich(long unsigned int N, int *k, int *m)
{

	int j = 0;
	while (N % 2 == 0)
	{
		N = N / 2;
		j++;
	}
	*k = j;
	*m = N;
}

long unsigned int exp_modulo(long unsigned int p, long unsigned int q)
{
	long unsigned int phi = (p - 1)*(q - 1);
	for (long unsigned int e = 20; e < phi / 2; e++)
	{
		if (UCLN(e, phi) == 1)
		{
			return e;
		}
	}
	return 0;
}
long unsigned int modulo_inverse(long unsigned int a, long unsigned int m)
{

	long unsigned int temp = m, r, q;
	int y, y0 = 0, y1 = 1;
	while (a>0)
	{

		r = m % a;
		if (r == 0) break;
		q = m / a;
		y = y0 - q * y1;
		y0 = y1;
		y1 = y;
		m = a;
		a = r;
	}
	if (a > 1) return 0;
	else
	{
		if (y<0) return (y + temp);
		else return y;

	}

}
void int_to_char(long long unsigned int i, char *b)
{
	char const digit[] = "0123456789";
	int z,x = 0;
	char p[20];
	do {
		p[x] = digit[i % 10];
		x++;
		i = i / 10;
	} while (i);
	z=x;
	for (int  j = 0;j<20; j++)
	{
		x--;
		b[j] = p[x];
	}
	for (int  j = z;j<20; j++)
	{
	b[j]=0x00;
	}
}
void TIM2_Configuration(void)
{
 TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
   
 /* Time base configuration */
 TIM_TimeBaseStructure.TIM_Prescaler = 0;
 TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
 TIM_TimeBaseStructure.TIM_ClockDivision = 0;
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
 TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
 TIM_Cmd(TIM2, ENABLE);
}
