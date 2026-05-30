#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    int sd;
    char a[200], b[200];

    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    sd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8002);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1)
    {
        printf("\nEnter message for Server: ");
        scanf(" %[^\n]", a);
        sendto(sd, a, strlen(a) + 1, 0, (struct sockaddr *)&server, len);
        recvfrom(sd, b, sizeof(b), 0, (struct sockaddr *)&server, &len);
        printf("Message from Server: %s\n", b);
    }

    close(sd);
    return 0;
}
