#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int signo)
{
    // printf signal
    psignal(signo ,"Received Signal:");
}

int main()
{
    // sigaction struct for SIGTSTP, SIGINT
    struct sigaction sa_tstp, sa_int;
    int count = 0;
    
    // Setting sigaction struct for SIGTSTP
    sa_tstp.sa_handler = handler; // handler
    sa_tstp.sa_flags = 0;
    sigemptyset(&sa_tstp.sa_mask); // empty set
    sigaddset(&sa_tstp.sa_mask, SIGQUIT); // add SIGQUIT

    // Setting sigaction struct for SIGINT
    sa_int.sa_handler = handler; // handler
    sa_int.sa_flags = 0;
    sigemptyset(&sa_int.sa_mask); // empty set
    sigaddset(&sa_int.sa_mask, SIGQUIT); // add SIGQUIT

    // setting SIGTSTP's sigaction handler
    if(sigaction(SIGTSTP, &sa_tstp, NULL) == -1)
    {
        perror("Couldn't set SIGTSTP handler");
        return -1;
    }

    // setting SIGINT's sigaction handler
    if(sigaction(SIGINT, &sa_int, NULL) == -1)
    {
        perror("Couldn't set SIGINT handler");
        return -1;
    }


    // Waiting for signal to received...
    while(1)
    {
        printf("Waiting for signal to be received! Count:%d\n", count);
        count++;
        sleep(1);
    }

    return 0;
}
