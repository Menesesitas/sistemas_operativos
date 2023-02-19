#include <stdio.h>
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

	return 0;
}

