#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    int sd;
    char ch1[200], ch2[200];

    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    sd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8002);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1)
    {
        printf("\nEnter message for Server: ");
        scanf(" %[^\n]", ch1);

        sendto(sd, ch1, strlen(ch1) + 1, 0,
               (struct sockaddr *)&server, len);

        recvfrom(sd, ch2, sizeof(ch2), 0,
                 (struct sockaddr *)&server, &len);

        printf("Message from Server: %s\n", ch2);
    }

    close(sd);
    return 0;
}
