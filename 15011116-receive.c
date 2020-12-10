#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signo, siginfo_t *si)
{
    // sig_queue realtime signal handler
    if(si->si_code == SI_QUEUE)
    {
        printf("User RTS signal %d\n", si->si_pid);
        printf("Sig Number %d\n", si->si_signo);
        printf("User Data is %d\n", si->si_value.sival_int);
        getchar();
    }

    // no realtime signal
    else
    {
        printf("Get none realtime signal %d\n", signo);
    }
}

int main()
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_restorer = NULL;
    sa.sa_sigaction = handler;

    // reciver's pid
    printf("pid : %d\n", getpid());

    // if SIGTSTP -> handler execution
    if(sigaction(SIGTSTP, &sa, 0) == 1)
    {
        printf("signal error\n");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        sleep(1);
    }

    return 0;
}
