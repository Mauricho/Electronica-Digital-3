#include <stdio.h>
#include <stdlib.h>

int main() {
  //   int *ptr;
  //   ptr = malloc(10 * sizeof(*ptr)); /* a block of 10 ints */
  //   if (ptr != NULL) {
  //     *(ptr + 2) = 50; /* assign 50 to third int */
  //   }
  //   ptr = realloc(ptr, 100 * sizeof(*ptr)); /* 100 ints */
  //   *(ptr + 30) = 75;
  //   printf("%d %d\n", *(ptr + 2), *(ptr + 30));

  int *arr = malloc(sizeof(int)); // Creo un espacio de 4 bytes

  *arr = 13;                      // Guardo el 13 en ese espacio          

  arr = realloc(arr, 2 * sizeof(int));  // Expando para que sea de 8 bytes

  *(arr + 1) = *arr;                    // 

  printf("%d", *(arr + 1));

  return 0;
}