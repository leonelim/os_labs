#include <math.h>
#include <stdio.h>

const int million = 1000 * 1000;

int main() {
  setvbuf(stdout, NULL, _IOFBF, BUFSIZ);
  double result = 0;
  for (int i = 0; i < 10 * million; i++) {
    result += i * 3 + sin(i) - sqrt(1.f / 15);
    printf("%lf\n", result);
  }
  return 0;
}
