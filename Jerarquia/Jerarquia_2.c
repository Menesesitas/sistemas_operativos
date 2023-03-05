#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t T, W, V, S, L, P;
	
	printf("R: %d, gfe: %d\n", getpid(), getppid());
	T = fork();
	if (T == 0){
		printf("T: %d, gfe: %d\n", getpid(), getppid());
		V = fork();
		if (V == 0){
		printf("V: %d, gfe: %d\n", getpid(), getppid());
		return 0;
		}
		return 0;
	}
		
	W = fork();
	if (W == 0) {
		printf("W: %d, gfe: %d\n", getpid(), getppid());
		S = fork();
		if (S == 0){
			printf("S: %d, gfe: %d\n", getpid(), getppid());
			return 0;
		}
			
		L = fork();
		if (L == 0){
			printf("L: %d, gfe: %d\n", getpid(), getppid());
			P = fork();
			if (P == 0){
			printf("P: %d, gfe: %d\n", getpid(), getppid());
			return 0;
			}
			return 0;
		}
		return 0;
	}
	return 0;
}

