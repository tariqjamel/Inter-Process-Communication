#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 512

struct message {
    long type;
    char text[MAX_TEXT];
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    key = ftok("communicate", 98);
    msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("message get failed");
        exit(EXIT_FAILURE);
    }

    printf("Server started. Waiting for messages...\n");

    while (1) {
        if (msgrcv(msgid, &msg, sizeof(msg.text), 0, 0) == -1) {
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        }

        if (msg.type == 1) {
            printf("Client 1: %s\n", msg.text);
            msg.type = 2; 
        } else if (msg.type == 3) {
            printf("Client 2: %s\n", msg.text);
            msg.type = 4;
        }

        if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
            perror("msgsnd failed");
            exit(EXIT_FAILURE);
        }
    }

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}

