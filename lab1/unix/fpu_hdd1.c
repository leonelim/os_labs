#include <math.h>
#include <stdio.h>

const int million = 1000 * 1000;

int main() {
  double result = 0;
  FILE *f = fopen("result1.txt", "w");
  if (f == NULL) {
    puts("error writing to file");
    return 1;
  }
  for (int i = 0; i < 20 * million; i++) {
    result += i * 3 + sin(i) - sqrt(1.f / 15);
    fprintf(f, "%lf\n", result);
  }
  fclose(f);
  return 0;
}
