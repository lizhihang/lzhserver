#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFFSIZE 1024

int main(int argc, char **argv)
{
    int socket_fd, n;
    char recv[BUFFSIZE];

    struct sockaddr_in6 server_addr;
    //struct sockaddr_in server_addr;

    if (argc != 2)
    {
        printf("useage : a.out <server addr>\n");
        return 0;
    }

    //if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    if ((socket_fd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
    {
        printf("socket error\n");
        return 0;
    }

    memset(&server_addr, 0, sizeof(server_addr));

    //server_addr.sin_family = AF_INET;
    //server_addr.sin_port = htons(13);
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(13);

    //if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0)
    if (inet_pton(AF_INET6, argv[1], &server_addr.sin6_addr) <= 0)
    {
        printf("inet_pton error\n");
        return 0;
    }

    if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("connect error\n");
        return 0;
    }


    while ((n = read(socket_fd, recv, BUFFSIZE)) > 0)
    {
        recv[n] = 0;
        if (fputs(recv, stdout) == EOF)
        {
            printf("fputs error\n");
            return 0;
        }
    }

    if (n < 0)
    {
        printf("read error\n");
        return 0;
    }

    return 0;
}
