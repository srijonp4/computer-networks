// #include<stdio.h>
// #include<fcntl.h>
// #include<unistd.h>
// #include<sys/types.h>
// #include<string.h>
// void main()
// {

//     int fd;
//     char *myfifo = "fifo";
//     char message[1024];char buffer[1024];
//     mkfifo(myfifo,0666);
//     while(1){
//         memset(message,0,sizeof(message));
//         fd=open(myfifo,O_WRONLY);
//         printf("")
//     }

// }

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

        memset(message, 0, sizeof(message));
        fd = open(myfifo, O_WRONLY);
        printf("Enter data for 2nd program: ");
        gets(message);
        write(fd, message, 1024);
        close(fd);
        if (strcmp(message, "exit") == 0)
            break;
        memset(buffer, 0, sizeof(buffer));
        fd = open(myfifo, O_RDONLY);
        read(fd, buffer, 1024);
        printf("Received data from 2nd program: %s\n", buffer);
        close(fd);
        if (strcmp(buffer, "exit") == 0)
            break;
    }
}