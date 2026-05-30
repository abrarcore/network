#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int sockfd, len, result;

    struct sockaddr_in address;

    char a[100], b[100];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = 4006;
    address.sin_addr.s_addr =
        inet_addr("127.0.0.1");

    len = sizeof(address);

    result = connect(sockfd,
                    (struct sockaddr *)&address,
                    len);

    if (result == -1)
    {
        perror("Oops: client");
        exit(1);
    }

    printf("Enter: ");

    gets(b);

    write(sockfd, b, sizeof(b));

    read(sockfd, a, sizeof(a));

    printf("Time of server is:\n");

    puts(a);

    return 0;
}
