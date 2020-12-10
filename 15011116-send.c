#include <signal.h>
#include <stdio.h>

int main()
{
    pid_t pid; // for save receiver's pid
    union sigval sv; // send my student id

    sv.sival_int = 15011116; // sigval data my student id

    printf("Receiver PID: ");
    scanf("%d", &pid);
    sigqueue(pid, SIGTSTP, sv); // SIGTSTP add sigqueue to receiver
}
