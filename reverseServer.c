#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


int main(int argc, char *argv[])
{
    int i, j;
    ssize_t n;

    char a[50], b[50];

    int sockfd, clifd, clilen;

    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5777);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(sockfd, 7);

    for (;;)
    {
        clilen = sizeof(cliaddr);

        clifd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        printf("Connected to client\n");

        while (1)
        {
            if ((n = read(clifd, a, MAXa)) == 0)
                break;

            a[n] = '\0';

            j = 0;

            for (i = n - 1; i >= 0; i--)
            {
                b[j++] = a[i];
            }

            b[j] = '\0';

            write(clifd, b, n);
        }
    }

    return 0;
}
