#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void random_number();

int main()
{
    pid_t A, B, M;
    int status;
    srand(time(0));
    
     //A
    A = fork();
    if (A == 0)
    {
        printf("Hijo A, con el pid %d\n", getpid());
        random_number();
        return 0;
    }
    
    //B
    B = fork();
    if (B == 0)
    {
        printf("Hijo B, con el pid %d\n", getpid());
        random_number();
        return 0;
    }
    
    //M
    M = fork();
    if (M == 0)
    {
        printf("Hijo M, con el pid %d\n", getpid());
        random_number();
        return 0;
    }
    
    //Padre
    if (A > 0)
    {
        wait(&status);
        printf("Mi hijo terminó con estado de salida: %d.\n\n", WEXITSTATUS(status));
        wait(&status);
        printf("Mi hijo terminó con estado de salida: %d.\n\n", WEXITSTATUS(status));
        wait(&status);
        printf("Mi hijo terminó con estado de salida: %d.\n\n", WEXITSTATUS(status));
    }
    
    return 0;
}

// Escribir un array en un archivo
void random_number()
{
    int a = rand();
    int b = a % 100;
    printf("%d\n", b + 1);
}

