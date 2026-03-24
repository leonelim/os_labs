#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  for (int i = 0; i < 8; ++i) {
    char name1[3];
    char name2[3];

    sprintf(name1, "1%d", i + 2);
    mkfifo(name1, 0666);
    sprintf(name2, "2%d", i + 2);
    mkfifo(name2, 0666);
  }
  if (fork() == 0) {
    for (int i = 0; i < 8; ++i) {
      char name1[3];
      sprintf(name1, "1%d", i + 2);
      int fd = open(name1, O_WRONLY);
      write(fd, name1, 3);
    }
  }

  for (int i = 0; i < 8; ++i) {
    if (fork() == 0) {
      char name1[3];
      char name2[3];
      sprintf(name1, "1%d", i + 2);
      sprintf(name2, "2%d", i + 2);
      int fd1 = open(name1, O_RDONLY);
      int fd2 = open(name2, O_WRONLY);
      char buff[3];
      read(fd1, buff, 3);
      puts(buff);
      write(fd2, buff, 3);
      exit(0);
    }
  }

  if (fork() == 0) {
    for (int i = 0; i < 8; ++i) {
      char name[3];
      char buff[3];
      sprintf(name, "2%d", i + 2);
      int fd = open(name, O_RDONLY);
      read(fd, buff, 3);
      puts(buff);
    }
  }

  return 0;
}
