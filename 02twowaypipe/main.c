#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main()
{
    /*
    fd[0] = read only
    fd[1] = write only
    */
    int fd1[2], fd2[2], pid = 0;
    char message[1024], buffer[1024];
    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        perror("Pipe creation failed\n");
        exit(0);
    }
    pid = fork();
    if (pid > 0)
    {
        // parent part
        close(fd1[0]); // parent can't read from fd1
        close(fd2[1]); // parent can't write to fd2
        while (1)
        {
            // parent WRITE TO pipe
            memset(message, 0, sizeof(message));
            printf("Enter message for child: ");
            gets(message);
            write(fd1[1], message, sizeof(message));
            if (strcmp(message, "exit") == 0)
                break;
            // parent READ FROM pipe
            memset(buffer, 0, sizeof(buffer));
            read(fd2[0], buffer, sizeof(buffer));
            printf("Recived message from child: %s\n", buffer);
            if (strcmp(buffer, "exit") == 0)
                break;
        }
    }
    else
    {
        // child part
        close(fd1[1]); // child can't write to fd1
        close(fd2[0]); // child can't read from fd2
        while (1)
        {
            // child READ FROM pipe
            memset(buffer, 0, sizeof(buffer));
            read(fd1[0], buffer, sizeof(buffer));
            printf("Recived message from parent: %s\n", buffer);
            if (strcmp(buffer, "exit") == 0)
                break;
            // child WRITE TO pipe
            memset(message, 0, sizeof(message));
            printf("Enter message for parent: ");
            gets(message);
            write(fd2[1], message, sizeof(message));
            if (strcmp(message, "exit") == 0)
                break;
        }
    }
}
