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
    pid_t pidA, pidB, pidC, pidD;
    int statusA, statusB, statusC, statusD;

    //D
    pidD = fork();
    if (pidD == 0) 
    {
        printf("Proceso D, PID: %d, PPID: %d\n", getpid(), getppid());
        char *args[] = {"ls", NULL};
        execvp(args[0], args);
        exit(0);
    } 
    else 
    {
        waitpid(pidD, &statusD, 0);
        printf("\n");
    }

    //A
    pidA = fork();
    if (pidA == 0) 
    {
        printf("Proceso A, PID: %d, PPID: %d\n", getpid(), getppid());
        char *args[] = {"rm", "-r", "new_folder", NULL};
        execvp(args[0], args);
        exit(0);
    } else 
    {
        waitpid(pidA, &statusA, 0);
        printf("\n");
    }

    //C
    pidC = fork();
    if (pidC == 0) 
    {
        printf("Proceso C, PID: %d, PPID: %d\n", getpid(), getppid());
        char *args[] = {"ls", NULL};
        execvp(args[0], args);
        exit(0);
    } else 
    {
        waitpid(pidC, &statusC, 0);
        printf("\n");
    }

    //M
    if (pidA > 0 && pidC > 0) 
    {
        printf("Soy M y mi PID es %d\n", getpid());
        pidB = fork();
        if (pidB == 0) 
        { //B
            printf("Proceso B, PID: %d, PPID: %d\n", getpid(), getppid());
            char *args[] = {"mkdir", "new_folder", NULL};
            execvp(args[0], args);
            exit(0);
        } 
        else 
        {
            waitpid(pidB, &statusB, 0);
            char *args[] = {"ls", NULL};
            execvp(args[0], args);
        }
    }
    return 0;
}

