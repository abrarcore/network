#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int sockfd;

    char a[50], b[50];

    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5777);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    connect(sockfd, (struct sockaddr *)&servaddr,  sizeof(servaddr));

    printf("Enter the data to be sent:\n");

    while (fgets(a, MAXa, stdin) != NULL)
    {
        write(sockfd, a, strlen(a));
        printf("a sent\n");
       int n= read(sockfd, b, MAXa);
	    b[n]='\0';
        printf("Reverse of the given sentence is: %s\n",b);
        printf("\n");
    }

    close(sockfd);

    return 0;
}
