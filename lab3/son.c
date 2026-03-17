/*
 * A B C
 * 4 5 5
 */
#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
int main() {
  clock_t ut, st, cut, cst;
  struct tms time1;
  struct tms time2;
  times(&time1);
  pid_t pid = getpid();
  pid_t ppid = getppid();
  times(&time2);
  ut = time2.tms_utime - time1.tms_utime;
  st = time2.tms_stime - time1.tms_stime;
  printf("pid: %d ppid: %d time: ut: %ld st: %ld son\n", pid, ppid, ut, st);
  return 0;
}
