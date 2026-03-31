// 4 5 5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct {
  long type;
  char buffer[256];
} message;

void write_message_else_print_err(int msgid, message *msg);

const int A = 4;
const int B = 5;
const int C = 5;

int main() {
  key_t key = ftok("msg_id", 1);
  if (key == -1) {
    perror("");
    return 1;
  }

  int msgid = msgget(key, 0666 | IPC_CREAT);
  if (msgid == -1) {
    perror("");
    return 1;
  }

  // SERVER 1 - 5 messages of type 3
  if (fork() == 0) {
    message msg = {3, "hello3"};
    for (int i = 0; i < B; ++i) {
      write_message_else_print_err(msgid, &msg);
    }
    exit(0);
  }
  wait(NULL);

  // SERVER 2 - 5 messages of type 1 and 2 (3 and 2 messages respectively)
  if (fork() == 0) {
    message msg1 = {1, "hello1"};
    for (int i = 0; i < 3; ++i) {
      write_message_else_print_err(msgid, &msg1);
    }
    message msg2 = {2, "hello2"};
    for (int i = 0; i < 2; ++i) {
      write_message_else_print_err(msgid, &msg2);
    }
    exit(0);
  }
  wait(NULL);

  // SERVER 3 - 3 messages of type 4
  if (fork() == 0) {
    message msg = {4, "hello4"};
    for (int i = 0; i < 3; ++i) {
      write_message_else_print_err(msgid, &msg);
    }
    exit(0);
  }
  wait(NULL);

  // SERVER 4 - 1 message of type 5
  if (fork() == 0) {
    message msg = {5, "hello5"};
    write_message_else_print_err(msgid, &msg);
    exit(0);
  }
  wait(NULL);
  return 0;
}

void write_message_else_print_err(int msgid, message *msg) {
  int res = msgsnd(msgid, msg, strlen(msg->buffer) + 1, 0);
  if (res == -1) {
    perror("");
  }
}
