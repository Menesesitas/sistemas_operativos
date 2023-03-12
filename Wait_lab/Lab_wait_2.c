#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() 
{
    pid_t pidB, pidC, pidE;
    int statusB, statusC, statusE;
    
    pidB = fork();
    
    if (pidB == 0) 
    { //Hijo B
        sleep(3); // Duerme 3 segundos
        printf("Proceso B terminado. Retorna 1\n");
        _exit(1);
    } 
    
    pidC = fork();
    
    if (pidC == 0) 
    { //Hijo C
        sleep(1); // Duerme 1 segundo
        printf("Proceso C terminado. Retorna 2\n");
        _exit(2);
    } 
    
    pidE = fork();
            
    if (pidE == 0) 
    { //Hijo E
        printf("Proceso E terminado. Retorna 3\n");
        _exit(3);
    } 
    
    //Padre A
    waitpid(pidB, &statusB, 0); // Espera a B
    printf("Valor de retorno de B: %d\n", WEXITSTATUS(statusB));
    
    waitpid(pidC, &statusC, 0); // Espera a C
    printf("Valor de retorno de C: %d\n", WEXITSTATUS(statusC));
    
    waitpid(pidE, &statusE, 0); // Espera a E
    printf("Valor de retorno de E: %d\n", WEXITSTATUS(statusE));
                
    return 0;
}

