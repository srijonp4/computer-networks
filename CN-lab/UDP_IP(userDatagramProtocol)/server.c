#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 8080

void main(){
    int svr_sockfd;
    char message[1024], buffer[1024];
    struct sockaddr_in svraddr, clnaddr;//system define structure to store network informations.
    socklen_t svraddrlen = sizeof(struct sockaddr_in);
    socklen_t clnaddrlen = sizeof(struct sockaddr_in);
    svr_sockfd = socket(AF_INET, SOCK_DGRAM,0);//AF_INET -> Ipv4 family ,2nd udp,3rd 0 means ip protocol

    svraddr.sin_family = AF_INET;//IPV4
    svraddr.sin_addr.s_addr = INADDR_ANY; // sin_addr.s_addr any kind of INet address
    svraddr.sin_port = htons(PORT);//to store port number host to network short(htons)
    bind(svr_sockfd, (struct sockaddr *)&svraddr, svraddrlen);//binding server variables with svr_sockfd structure,server address length in svraddrlen,
    printf("Wating for CLient Request \n");
    while(1){
        memset(buffer,0,sizeof(buffer));
        recvfrom(svr_sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clnaddr, &clnaddrlen);//udp/IP === connectionless , no dedicated channel to we have to get the client info to send data to the client .
        printf("received data from client : %s \n", buffer);
        if(strcmp(buffer,"exit")==0) break;
        memset(message, 0, sizeof(message));
        printf("enter data for the Client :\t  ");
        gets(message);
        sendto(svr_sockfd, message, sizeof(message), 0, (struct sockaddr *)&clnaddr, clnaddrlen);
        if(strcmp(message,"exit")==0)
            break;
    }
}
