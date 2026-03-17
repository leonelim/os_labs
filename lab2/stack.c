#include <stdio.h>

typedef struct {
  int array[1000];
} arr;

void recursion(arr array, int n) {
  printf("recursion: %d\n", n);
  recursion(array, n + 1);
}

int main() {
  arr r = {1, 2, 3};
  recursion(r, 0);
  return 0;
}
