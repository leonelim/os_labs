#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <fileapi.h>
#include <io.h>

const int million = 1000 * 1000;

int main() {
  setvbuf(stdout, NULL, _IOFBF, BUFSIZ);
  double result = 0;
  FILE *f = fopen("result.txt", "w");
  if (f == NULL) {
    puts("error writing to file");
    return 1;
  }
  HANDLE hFile = (HANDLE)_get_osfhandle(fileno(f));
  for (int i = 0; i < 20000; i++) {
    result += i * 3 + sin(i) - sqrt(1.f / 15);
    printf("%lf\n", result);
    fprintf(f, "%lf\n", result);
    fflush(f);
    FlushFileBuffers(hFile);
  }
  fclose(f);
  return 0;
}
