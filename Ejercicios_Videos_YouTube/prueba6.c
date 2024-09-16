#include <stdio.h>

union val {
  int int_num;
  float fl_num;
  char str[20];
};

int main() {
  union val test;
  union val u2;

  test.int_num = 42;

  u2 = test;

  printf("%d\n", u2.int_num);
  printf("%s\n", u2.str);

  return 0;
}