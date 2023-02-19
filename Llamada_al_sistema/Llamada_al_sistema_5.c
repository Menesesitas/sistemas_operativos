#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void check_error(int fd, int n, int m) 
{
	if (fd < 0) 
	{
		perror("Error en fd");
	} else if (n < 0 || m < 0) 
	{
		printf("Error: n o m son valores negativos\n");
	} else 
	{
		switch(errno) 
		{
		case EAGAIN:
			perror("Error EAGAIN: Archivo bloqueado");
			break;
		case EACCES:
			perror("Error EACCES: Problemas con acceder al archivo");
			break;
		case EBADF:
			perror("Error EBADF: Mal descriptor de archivo");
			break;
		default:
			perror("Error desconocido");
		}
	}
}

int main() 
{
	int fd, n, m;
	char buffer[30];
	float arr[5];
	int j = 0;
	
	fd = open("datos2.txt", O_RDONLY);
	
	while((m = read(fd, buffer, sizeof(buffer))) > 0)
	{
		char * ptr = buffer;
		while (*ptr != '\0')
		{
			arr[j] = strtof(ptr, &ptr);
			j++;
			if (j >= 5) break;
		}
		if (j >= 5) break;
	}
	
	check_error(fd, n, m);
	close(fd);
	
	printf("Arreglo de flotantes: \n");
	for (int k = 0; k < j; k++) {
		printf("%.2f\n", arr[k]);
	}
	printf("\n");
	
	return 0;
}

