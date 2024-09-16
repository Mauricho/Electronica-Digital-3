#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main() {
  // Con error      // Sin error
  float k = -5;     // 5;
  float num = 1000; // 10;
  float result;

  errno = 0; // Clear errno before the call
  result = sqrt(k);
  if (errno == 0)
    printf("%f\n", result);
  else if (errno == EDOM) {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    printf("%d\n", errno);
  }
  
  errno = 0; // Clear errno before the call
  result = exp(num);
  if (errno == 0)
    printf("%f\n", result);
  else if (errno == ERANGE){
    fprintf(stderr, "Error: %s\n", strerror(errno));
    printf("%d\n", errno);
  }
  return 0;
}