#include <stdio.h>

int main() 
{
	int num_n = 1;
	int potencia_p = 0;
	while(num_n < 30) 
	{
		num_n *= 2;
		potencia_p++;
	}
	printf("La potencia de 2 mayor que 30 es: 2^%d = %d", potencia_p, num_n);
	return 0;
}

