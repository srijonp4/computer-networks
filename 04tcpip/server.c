#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 8080
int main() {
int svrsock_fd, new_conn;
int opt = 1;
char message[1024], buffer[1024];
struct sockaddr_in address;
socklen_t addrlen = sizeof(struct sockaddr_in);
svrsock_fd = socket(AF_INET, SOCK_STREAM, 0);
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);
setsockopt(svrsock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
bind(svrsock_fd, (struct sockaddr*)&address, addrlen);
listen(svrsock_fd, 3);
new_conn = accept(svrsock_fd, (struct sockaddr*)&address, &addrlen);
printf("Waiting for client...\n");
while (1) {
// server <-- client
memset(buffer, 0, sizeof(buffer));
read(new_conn, buffer, 1024);
printf("Received data from client: %s\n", buffer);
if (strcmp(buffer, "exit") == 0) break;
// server --> client
memset(message, 0, sizeof(message));
printf("Enter data for client: ");
gets(message);
send(new_conn, message, strlen(message), 0);
if (strcmp(message, "exit") == 0) break;
}
}