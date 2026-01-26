#include <math.h>

const int million = 1000 * 1000;

int main() {
  double result = 0;
  for (int i = 0; i < 200 * million; i++) {
    result += i * 3 + sin(i) - sqrt(1.f / 15);
  }
  return 0;
}
