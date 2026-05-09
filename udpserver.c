#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    int s_sd;
    socklen_t serv_len;
    char sour[200], dest[200];

    struct sockaddr_in serv, cli;

    serv_len = sizeof(cli);

    s_sd = socket(AF_INET, SOCK_DGRAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_port = htons(8002);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(s_sd, (struct sockaddr *)&serv, sizeof(serv));

    printf("\nThe SERVER is WAITING...\n");

    while (1)
    {
        recvfrom(s_sd, sour, sizeof(sour), 0,
                 (struct sockaddr *)&cli, &serv_len);

        printf("\nMessage from client: %s\n", sour);

        printf("Enter message for client: ");
        scanf(" %[^\n]", dest);

        sendto(s_sd, dest, strlen(dest) + 1, 0,
               (struct sockaddr *)&cli, serv_len);
    }

    close(s_sd);
    return 0;
}
