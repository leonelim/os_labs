#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const size_t rows = 46340;
const size_t cols = 46340;
int main() {
  int64_t **p = malloc(rows * sizeof(int64_t *));
  if (!p) {
    printf("error");
    return 1;
  }
  for (uint64_t i = 0; i < rows; i++) {
    p[i] = malloc(cols * sizeof(int64_t));
    for (uint64_t j = 0; j < cols; j++) {
      p[i][j] = 1;
    }
  }
  return 0;
}
