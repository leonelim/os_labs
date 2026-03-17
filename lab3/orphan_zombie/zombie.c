#include <stdlib.h>
#include <unistd.h>

int main() {
  if (fork() == 0) {
    exit(0);
  } else {
    sleep(5);
  }
  return 0;
}
