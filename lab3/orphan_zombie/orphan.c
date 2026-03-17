#include <unistd.h>

int main() {
  if (fork() == 0) {
    sleep(10);
  } else {
    sleep(3);
  }
  return 0;
}
