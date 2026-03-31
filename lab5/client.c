#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct {
  long type;
  char buffer[256];
} message;

void read_and_print_message_else_print_err(int msgid, long type);

const int A = 4;
const int B = 5;
const int C = 5;

int main() {
  key_t key = ftok("msg_id", 1);
  if (key == -1) {
    perror("");
    return 1;
  }
  int msgid = msgget(key, 0666);
  if (msgid == -1) {
    perror("");
    return 1;
  }

  // all (5) messages of type 3
  if (fork() == 0) {
    for (int i = 0; i < B; ++i) {
      read_and_print_message_else_print_err(msgid, 3);
    }
    exit(0);
  }
  wait(NULL);

  // 3 messages of type 1 and 2 messages of type 2
  if (fork() == 0) {
    for (int i = 0; i < 3; ++i) {
      read_and_print_message_else_print_err(msgid, 1);
    }
    for (int i = 0; i < 2; ++i) {
      read_and_print_message_else_print_err(msgid, 2);
    }
    exit(0);
  }
  wait(NULL);

  // 3 messages of any type
  if (fork() == 0) {
    message msg;
    for (int i = 0; i < 3; ++i) {
      read_and_print_message_else_print_err(msgid, 0);
    }
    exit(0);
  }
  wait(NULL);

  // last messages left in the queue (1 message)
  if (fork() == 0) {
    read_and_print_message_else_print_err(msgid, 0);
    exit(0);
  }
  wait(NULL);

  int del_res = msgctl(msgid, IPC_RMID, NULL);
  if (del_res == -1) {
    perror("");
  }
  return 0;
}

void read_and_print_message_else_print_err(int msgid, long type) {
  message msg;
  ssize_t bytes = msgrcv(msgid, &msg, sizeof(msg.buffer), type, 0);
  if (bytes == -1) {
    perror("");
  } else {
    puts(msg.buffer);
  }
}
