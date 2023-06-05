#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
void main()
{
    int fd;
    char *myfifo = "fifo";
    char message[1024], buffer[1024];
    mkfifo(myfifo, 0666);
    while (1)
    {

        memset(buffer, 0, sizeof(buffer));
        fd = open(myfifo, O_RDONLY);
        read(fd, buffer, 1024);
        printf("Received data from 1st program: %s\n", buffer);
        close(fd);
        if (strcmp(buffer, "exit") == 0)
            break;
        memset(message, 0, sizeof(message));
        fd = open(myfifo, O_WRONLY);
        printf("Enter data for 1st program: \n");
        gets(message);
        write(fd, message, 1024);
        close(fd);
        if (strcmp(message, "exit") == 0)
            break;
    }
}