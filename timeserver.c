#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>

int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;

    char msg1[100], msg2[100];

    time_t t;

    struct sockaddr_in server_address, client_address;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = 4006;
    server_address.sin_addr.s_addr =
        inet_addr("127.0.0.1");

    server_len = sizeof(server_address);

    bind(server_sockfd,
         (struct sockaddr *)&server_address,
         server_len);

    listen(server_sockfd, 5);

    client_len = sizeof(client_address);

    client_sockfd = accept(server_sockfd,
                          (struct sockaddr *)&client_address,
                          &client_len);

    read(client_sockfd, msg2, sizeof(msg2));

    printf("Message from client: ");
    puts(msg2);

    t = time(NULL);

    sprintf(msg1, "%s", ctime(&t));

    write(client_sockfd, msg1, sizeof(msg1));

    close(client_sockfd);

    return 0;
}
