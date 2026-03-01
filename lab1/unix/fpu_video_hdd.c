#include <math.h>
#include <stdio.h>

const int million = 1000 * 1000;

int main() {
  setvbuf(stdout, NULL, _IOFBF, BUFSIZ);
  double result = 0;
  FILE *f = fopen("result.txt", "w");
  if (f == NULL) {
    puts("error writing to file");
    return 1;
  }
  for (int i = 0; i < 2 * million; i++) {
    result += i * 3 + sin(i) - sqrt(1.f / 15);
    fprintf(f, "%lf\n", result);
    printf("%lf\n", result);
  }
  fclose(f);
  return 0;
}
