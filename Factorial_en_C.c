#include <stdio.h>
//Este c�digo dar� el factorial de cualquier n�mero
int f(int n);
int main() 
{
	int n, r;
	printf("Ingrese el n�mero del que quiere el factorial\n");
	scanf("%i", &n);
	r = f(n);
	
	printf("f = %d", r);
	
	return 0;
}
	
int f(int n)
{
	if (n != 0)
		return n * f(n-1);
	else 
	return 1;
}

