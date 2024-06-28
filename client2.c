#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h> 

#define MAX_TEXT 512

struct message {
    long type;
    char text[MAX_TEXT];
};

void *receive_messages(void *arg) {
    int msgid = *((int *)arg);
    struct message msg;

    while (1) {
        if (msgrcv(msgid, &msg, sizeof(msg.text), 2, 0) == -1) {
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        }
        printf("Client 1: %s\n", msg.text);
    }
    return NULL;
}

int main() {
    key_t key;
    int msgid;
    struct message msg;
    pthread_t thread_id;

    key = ftok("communicate", 98);
    msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("message get failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server. Type your messages below:\n");

    pthread_create(&thread_id, NULL, receive_messages, &msgid);

    while (1) {
        if (fgets(msg.text, MAX_TEXT, stdin) == NULL) {
            perror("fgets failed");
            exit(EXIT_FAILURE);
        }
        msg.type = 3; 

        if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
            perror("message send failed");
            exit(EXIT_FAILURE);
        }
    }

    pthread_join(thread_id, NULL);
    return 0;
}

