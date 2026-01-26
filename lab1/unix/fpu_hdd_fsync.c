#include <math.h>
#include <stdio.h>
#include <unistd.h>

const int million = 1000 * 1000;

int main() {
  double result = 0;
  FILE *f = fopen("result.txt", "w");
  if (f == NULL) {
    puts("error writing to file");
    return 1;
  }
  int fd = fileno(f);
  for (int i = 0; i < 10000; i++) {
    result += i * 3 + sin(i) - sqrt(1.f / 15);
    fprintf(f, "%lf\n", result);
    fflush(f);
    if (fsync(fd) == -1) {
      puts("error with fsync");
      return 1;
    }
  }
  fclose(f);
  return 0;
}
