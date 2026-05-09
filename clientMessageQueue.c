#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    struct msgbuf
    {
        long mtype;
        char mtext[100];
    } send, recv;

    int qid, len;

    qid = msgget((key_t)25, IPC_CREAT | 0666);

    if (qid < 0)
    {
        perror("msgget failed");
        exit(1);
    }

    if (msgrcv(qid, &recv, 100, 1, 0) == -1)
    {
        perror("msgrcv failed");
        exit(1);
    }

    printf("Message from TTY-1 is: %s\n", recv.mtext);

    printf("Enter message for TTY-1: ");

    scanf("%[^\n]s", send.mtext);

    send.mtype = 2;

    len = strlen(send.mtext);

    if (msgsnd(qid, &send, len, 0) == -1)
    {
        perror("msgsnd failed");
        exit(1);
    }

    return 0;
}
