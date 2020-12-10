#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "15011116_s"

int main()
{
    char buf[100];
    int num, fd;
    int state;

    // making a FD for FIFO
    state = mkfifo(FIFO_NAME, S_IFIFO | 0666);
    
    if(state == -1) 
    {
        perror("mkfifo error");
    }

    // waiting for a client
    // open FD, when the client opens the FD
    fd = open(FIFO_NAME, O_WRONLY);

    while(fgets(buf, sizeof(buf), stdin), !feof(stdin))
    {
        if((num = write(fd, buf, strlen(buf))) == -1)
        {
            perror("write error");
        }
    }

    return 0;
}
