#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 8080
int main()
{
    int clnsock_fd;
    char message[1024], buffer[1024];
    struct sockaddr_in svraddress;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    clnsock_fd = socket(AF_INET, SOCK_STREAM, 0);
    svraddress.sin_family = AF_INET;
    svraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    svraddress.sin_port = htons(PORT);
    connect(clnsock_fd, (struct sockaddr *)&svraddress, addrlen);
    while (1)
    {
        // client --> server
        memset(message, 0, sizeof(message));
        printf("Enter data for server: ");
        gets(message);
        send(clnsock_fd, message, strlen(message), 0);
        if (strcmp(message, "exit") == 0)
            break;
        // client <-- server
        memset(buffer, 0, sizeof(buffer));
        read(clnsock_fd, buffer, 1024);
        printf("Received data from server: %s\n", buffer);
        if (strcmp(buffer, "exit") == 0)
            break;
    }
}