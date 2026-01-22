#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pid;
    pid = fork();

    if (pid < 0)
    {
        printf("fork failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
        execlp("whoami", "whoami", NULL);
        exit(0);
    }
    else
    {
        printf("\nProcess ID is: %d\n", getpid());
        wait(NULL);
        exit(0);
    }
}