#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    /*
    fd[0] = read only
    fd[1] = write only
    */
    int fd[2], pid = 0;
    char message[1024], buffer[1024];
    if (pipe(fd) == -1)
    {
        perror("Pipe creation failed\n");
        exit(0);
    }
    pid = fork();
    if (pid > 0)
    {
        // parent part
        close(fd[0]); // parent can't read from fd
        while (1)
        {
            // parent WRITE TO pipe
            memset(message, 0, sizeof(message));
            sleep(1);
            printf("Enter message for child: ");
            gets(message);
            write(fd[1], message, 1024);
            if (strcmp(message, "exit") == 0)
                break;
        }
    }
    else
    {
        // child part
        close(fd[1]); // child can't write to fd
        while (1)
        {
            // child READ FROM pipe
            memset(buffer, 0, sizeof(buffer));
            read(fd[0], buffer, 1024);
            printf("Recived message from parent: %s\n", buffer);
            if (strcmp(buffer, "exit") == 0)
                break;
        }
    }
}