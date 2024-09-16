#include <stdio.h>

//#define VAR(name, num) name##num
#define CONCAT(x,y) x##y

int main() {
  //   int x1 = 125;
  //   int x2 = 250;
  //   int x3 = 500;

  //   printf("%d\n", VAR(x, 1));

  int x = 4, y = 5;
  int CONCAT(x,y) = x+y;
  
  printf("%d\n",xy);
  
  return 0;
}