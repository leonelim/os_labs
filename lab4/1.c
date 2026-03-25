#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  for (int i = 0; i < 8; ++i) {
    char name1[100];
    char name2[100];
    sprintf(name1, "1%d", i + 2);
    mkfifo(name1, 0666);
    sprintf(name2, "2%d", i + 2);
    mkfifo(name2, 0666);
  }

  if (fork() == 0) {
    char buff[10];
    FILE *file = fopen("text.txt", "r");
    for (int i = 0; i < 8; ++i) {
      fgets(buff, 8, file);
      buff[6] = 0;
      char name1[100];
      sprintf(name1, "1%d", i + 2);
      int fd = open(name1, O_WRONLY);
      write(fd, buff, 7);
      close(fd);
    }
    exit(0);
  }

  for (int i = 0; i < 8; ++i) {
    if (fork() == 0) {
      char name1[100];
      char name2[100];
      sprintf(name1, "1%d", i + 2);
      sprintf(name2, "2%d", i + 2);

      int fd2 = open(name2, O_WRONLY);
      int fd1 = open(name1, O_RDONLY);

      char proc[100];
      sprintf(proc, "%d", i + 2);
      char buff[100];
      read(fd1, buff, 7);
      strcat(buff, proc);
      write(fd2, buff, 8);
      close(fd1);
      close(fd2);
      exit(0);
    }
  }

  if (fork() == 0) {
    FILE *file = fopen("result.txt", "w");
    for (int i = 0; i < 8; ++i) {
      char name[100];
      char buff[100];
      sprintf(name, "2%d", i + 2);
      int fd = open(name, O_RDONLY);
      read(fd, buff, 8);
      fprintf(file, "%s\n", buff);
      close(fd);
    }
    exit(0);
  }

  wait(NULL);
  for (int i = 0; i < 8; ++i)
    wait(NULL);

  for (int i = 0; i < 8; ++i) {
    char name1[100];
    char name2[100];

    sprintf(name1, "1%d", i + 2);
    sprintf(name2, "2%d", i + 2);

    unlink(name1);
    unlink(name2);
  }

  return 0;
}
