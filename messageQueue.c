#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {

    key_t key ;

    int msgid = msgget(key, 0666 | IPC_CREAT);

    printf("Message Queue ID: %d\n", msgid);

    return 0;
}
