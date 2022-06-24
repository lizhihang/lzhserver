#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <errno.h>

#define BUFFSIZE 1024

int main(int argc, char **argv)
{

    int listen_fd, connfd;
    char buff[BUFFSIZE];
    time_t ticks;

    struct sockaddr_in server_addr;

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket error\n");
        return 0;
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(13);

    int on = 1;
    setsockopt( listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );

    if (bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Error binding socket: %d\n", errno);
        return 0;
    }

    if (listen(listen_fd,5) < 0)
    {
        printf("listen error\n");
        return 0;
    }

    for (;;)
    {
        connfd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        close(connfd);
    }




    return 0;
}
