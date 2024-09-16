#include <stdio.h>

union val {
  int int_num;
  float fl_num;
  char str[20];
};

int main() {
  union val num[10];
  int k;

  /*create an array of ints*/
  for (k = 0; k < 10; k++) {
    num[k].int_num = k;
  }

  /*display array values*/
  for (k = 0; k < 10; k++) {
    printf("%d ", num[k].int_num); 
  }

  return 0;
}