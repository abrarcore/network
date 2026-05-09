#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define MAXLINE 20
#define SERV_PORT 5777

int main(int argc, char *argv[])
{
    int i, j;
    ssize_t n;

    char line[MAXLINE], revline[MAXLINE];

    int listenfd, connfd, clilen;

    struct sockaddr_in servaddr, cliaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd,
         (struct sockaddr *)&servaddr,
         sizeof(servaddr));

    listen(listenfd, 7);

    for (;;)
    {
        clilen = sizeof(cliaddr);

        connfd = accept(listenfd,
                        (struct sockaddr *)&cliaddr,
                        &clilen);

        printf("Connected to client\n");

        while (1)
        {
            if ((n = read(connfd, line, MAXLINE)) == 0)
                break;

            line[n] = '\0';

            j = 0;

            for (i = n - 1; i >= 0; i--)
            {
                revline[j++] = line[i];
            }

            revline[j] = '\0';

            write(connfd, revline, n);
        }
    }

    return 0;
}
