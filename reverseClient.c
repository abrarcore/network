#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 20
#define SERV_PORT 5777

int main(int argc, char *argv[])
{
    int sockfd;

    char line[MAXLINE], revline[MAXLINE];

    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    connect(sockfd,
            (struct sockaddr *)&servaddr,
            sizeof(servaddr));

    printf("Enter the data to be sent:\n");

    while (fgets(line, MAXLINE, stdin) != NULL)
    {
        write(sockfd, line, strlen(line));

        printf("Line sent\n");

       int n= read(sockfd, revline, MAXLINE);
	revline[n]='\0';
        printf("Reverse of the given sentence is: %s\n",
               revline);

        printf("\n");
    }

    close(sockfd);

    return 0;
}
