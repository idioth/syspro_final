#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_READ_NAME "15011116_s"
#define FIFO_WRITE_NAME "15011116_c"

int main()
{
    char buf[100];
    int state;
    int num, fd;
    int re;

    // making a FD, which is the same one the server uses, for FIFO
    state = mkfifo(FIFO_READ_NAME, S_IFIFO | 0666);
    if(state == -1)
    {
        perror("mkfifo error");
    }

    // waiting for a server
    // open the FD, when the server opens the FD
    fd = open(FIFO_READ_NAME, O_RDONLY);

    do
    {
        if((num = read(fd, buf, 100)) == -1)
        {
            perror("read error");
        }
        else
        {
            re = atoi(buf);
            printf("%d + 1 = %d\n", re, re+1);
        }
    } while(num > 0);

    return 0;
}
