#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080
#define IP "127.0.0.1"
#define BUF_SIZE 1024

int main() {

    int connection_status, sock;
    ssize_t buf_len;
    char buffer [BUF_SIZE], command [BUF_SIZE];
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, (struct sockaddr_in *)&serv_addr.sin_addr);

    connection_status = connect(sock, (struct sockaddr_in *)&serv_addr, sizeof(serv_addr));

    if (connection_status < 0) {
        printf("Connecction Failed\n");
        return -1;
    }

    printf("Connected\n");

    while (1) {
        printf("kali@server:~/$ ");
        memset(buffer, 0, BUF_SIZE);
        scanf("%s", buffer);

        buf_len = write(sock, buffer, strlen(buffer));

        if (buf_len < 0){
            perror("ERROR while writing to socket");
            exit(1);
        }

        //buf_len = read(sock, buffer, 255);

        if (buf_len < 0){
            perror("ERROR while reading from socket");
            exit(1);
        }
        printf("server replied: %s \n", buffer);

        // escape this loop, if the server sends message "quit"

        if (!bcmp(buffer, "quit", 4))
            break;
    }

    return 0;
}