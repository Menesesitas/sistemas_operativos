#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define N 10

int main()
{
	pid_t pid_N, pid_M;
	int status, fd1, fd2, n, m1, m2;
	int impares[] = {7, 1, 5, 17, 11, 19, 3, 21, 13, 9};
	int pares[] = {4, 8, 2, 6, 10, 18, 20, 14, 12, 16};
	int suma = 0;
	int arr_n[N];
	int arr_m[N];
	
	pid_N = fork();
	
	if (pid_N == 0)
	{
		fd1 = creat("N.txt", 777);
		n = write(fd1, pares, sizeof(pares));
	}
	
	if (pid_N > 0)
	{
		pid_M = fork();
		
		if (pid_M == 0)
		{
			fd2 = creat("M.txt", 777);
			n = write(fd2, impares, sizeof(impares));
		}
		if (pid_M > 0)
		{
			return 0;
		}
		
		fd1 = open("M.txt", 0);
		fd2 = open("N.txt", 0);
		m1 = read(fd1, arr_m, sizeof(arr_m));
		m2 = read(fd2, arr_n, sizeof(arr_n));
		
		
		for (int i = 0; i < N; i++)
		{
			suma = arr_n[i] + arr_m[i];
			printf("Suma %d: %d+%d=%d\n", i+1, arr_n[i], arr_m[i], suma);
			suma = 0;
		}
		close(fd1);
		close(fd2);	
	}
	return 0;
}

