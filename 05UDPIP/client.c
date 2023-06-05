#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define PORT 8080
void main()
{
    int cln_sockfd;
    char message[1024], buffer[1024];
    struct sockaddr_in svraddr;
    socklen_t svraddrlen = sizeof(struct sockaddr_in);
    cln_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    svraddr.sin_family = AF_INET;
    svraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    svraddr.sin_port = htons(PORT);
    while (1)
    {
        // client --> server
        memset(message, 0, sizeof(message));
        printf("Enter data for server :");
        gets(message);
        sendto(cln_sockfd, message, sizeof(message), 0,
               (struct sockaddr *)&svraddr, svraddrlen);
        if (strcmp(message, "exit") == 0)
            break;
        // client <-- server
        memset(buffer, 0, sizeof(buffer));
        recvfrom(cln_sockfd, buffer, sizeof(buffer), 0,
                 (struct sockaddr *)&svraddr, &svraddrlen);
        printf("Received data from server :%s\n", buffer);
        if (strcmp(buffer, "exit") == 0)
            break;
    }
}