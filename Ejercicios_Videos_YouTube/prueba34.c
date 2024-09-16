#include <stdio.h>
//#define T 42
#define sqr(x) x*x

int main() {
  //int T = 8;
  //printf("%d", T);
  int x = 16/sqr(4);

  printf("%d\n",x);
  return 0;
}