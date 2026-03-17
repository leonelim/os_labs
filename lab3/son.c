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
  cut = time2.tms_cutime - time1.tms_cutime;
  cst = time2.tms_cstime - time1.tms_cstime;
  printf("pid: %d time: ut: %ld st: %ld cu: %ld cs: %ld son\n", pid, ut, st,
         cut, cst);
  return 0;
}
