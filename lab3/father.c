/*
 * A B C
 * 4 5 5
 */
#include <stdio.h>
#include <sys/times.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  clock_t ut, st, cut, cst;
  struct tms time1;
  struct tms time2;
  times(&time1);
  pid_t pid = getpid();
  pid_t cpid;
  pid_t ppid = getppid();
  for (int i = 0; i < 5; i++) {
    cpid = fork();
    if (cpid == 0) {
      execl("./son", "son", NULL);
    } else if (cpid == -1) {
      puts("Fork failed!");
    } else {
      pid_t ended_proc = wait(NULL);
      if (ended_proc == -1) {
        puts("Wait failed!");
      }
    }
  }
  times(&time2);
  ut = time2.tms_utime - time1.tms_utime;
  st = time2.tms_stime - time1.tms_stime;
  cut = time2.tms_cutime - time1.tms_cutime;
  cst = time2.tms_cstime - time1.tms_cstime;
  printf("pid: %d ppid: %d time: ut: %ld st: %ld cu: %ld cs: %ld father\n", pid,
         ppid, ut, st, cut, cst);
  return 0;
}
