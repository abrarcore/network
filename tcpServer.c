#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    int serv_sockfd, cli_sockfd;
    int serv_len, cli_len;

    struct sockaddr_in serv_address, cli_addr;

    char a[100], b[100];

    serv_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(9001);
    serv_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    serv_len = sizeof(serv_address);

    bind(serv_sockfd,
         (struct sockaddr *)&serv_address,
         serv_len);

    listen(serv_sockfd, 5);

    printf("Server waiting...\n");

    cli_len = sizeof(cli_addr);

    cli_sockfd = accept(serv_sockfd,
                        (struct sockaddr *)&cli_addr,
                        &cli_len);

    printf("Client connected.\n");

    while(1)
    {
        read(cli_sockfd, a, sizeof(a));

        printf("Client: %s\n", a);


        printf("Server: ");
        gets(b);

        write(cli_sockfd, b, sizeof(b));
    }

    close(cli_sockfd);
    close(serv_sockfd);

    return 0;
}
