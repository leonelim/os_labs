#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  int fd = open("12", O_RDONLY);
  char buf[4];
  read(fd, buf, 4);
  close(fd);
  puts(buf);
  return 0;
}
