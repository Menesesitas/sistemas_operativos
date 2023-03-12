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
    pid_t pid_D, pid_L;
    int status;

    pid_D = fork();
    
    if (pid_D == 0) 
    { //Hijo 1
        sleep(1); 
        printf("Terminé mi ejecución. Mi PID es %d y el de mi padre es %d\n", getpid(), getppid());
        return 0;
    } else {
        pid_L = fork();
        
        if (pid_L == 0) 
        { //Hijo 2
            sleep(3); 
            printf("Terminé mi ejecución. Mi PID es %d y el de mi padre es %d\n", getpid(), getppid());
            return 0;
        } 
        else 
        { //Padre
            wait(&status); 
            printf("Uno de mis hijos ha terminado su ejecución con estado: %d\n", WEXITSTATUS(status));
            wait(&status);  
            printf("Uno de mis hijos ha terminado su ejecución con estado: %d\n", WEXITSTATUS(status));
            return 0;
        }
    }
}

