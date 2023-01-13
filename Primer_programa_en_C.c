#include <stdio.h>
// este código te dará el resultado del área de un rectángulo
int main() 
{
	float base_b;
	float altura_h;
	float resultado_r;
	
	printf("Ingresa una medida para las base:\n");
	scanf("%f", &base_b);
	printf("Ingresa una medida para las altura:\n");
	scanf("%f", &altura_h);
	
	resultado_r = base_b * altura_h;
	printf("El área del rectángulo es igual a= %f", resultado_r);
	
	return 0; 
}

