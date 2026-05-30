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
    int sockfd, len, result;
    struct sockaddr_in address;

    char name[100], ser[100];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(9001);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    len = sizeof(address);

    result = connect(sockfd,
                     (struct sockaddr *)&address,
                     len);

    if(result == -1)
    {
        perror("Unable to connect");
        exit(1);
    }

    printf("Connected to server...\n");

    while(1)
    {
        printf("Client: ");
        gets(name);

        write(sockfd, name, sizeof(name));

        if(strcmp(name, "exit") == 0)
            break;

        read(sockfd, ser, sizeof(ser));

        printf("Server: %s\n", ser);

        if(strcmp(ser, "exit") == 0)
            break;
    }

    close(sockfd);

    return 0;
}
