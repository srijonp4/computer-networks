#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define PORT 8080
void main()
{
    int svr_sockfd;
    char message[1024], buffer[1024];
    struct sockaddr_in svraddr, clnaddr;
    socklen_t svraddrlen = sizeof(struct sockaddr_in);
    socklen_t clnaddrlen = sizeof(struct sockaddr_in);
    svr_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    svraddr.sin_family = AF_INET;
    svraddr.sin_addr.s_addr = INADDR_ANY;
    svraddr.sin_port = htons(PORT);
    bind(svr_sockfd, (struct sockaddr *)&svraddr, svraddrlen);
    printf("WAITING FOR CLIENT REQUEST\n");
    while (1)
    {
        // server <-- client
        memset(buffer, 0, sizeof(buffer));
        recvfrom(svr_sockfd, buffer, sizeof(buffer), 0,
                 (struct sockaddr *)&clnaddr, &clnaddrlen);
        printf("Received data from client :%s\n", buffer);
        if (strcmp(buffer, "exit") == 0)
            break;
        // server --> client
        memset(message, 0, sizeof(message));
        printf("Enter data for client :");
        gets(message);
        sendto(svr_sockfd, message, sizeof(message), 0,
               (struct sockaddr *)&clnaddr, clnaddrlen);
        if (strcmp(message, "exit") == 0)
            break;
    }
}