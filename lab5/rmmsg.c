#include <stddef.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
  int msgid = msgget(ftok("msg_id", 1), 0666);
  msgctl(msgid, IPC_RMID, NULL);
  return 0;
}
