#include <stdio.h>
#include <stdlib.h>

int main() {
  int *ptr;
  ptr = malloc(10 * sizeof(*ptr)); // Un bloque de 10 enteros
  if (ptr != NULL) {
    *(ptr + 2) = 50; // Asigno 50 al tercer elemento
  }
  printf("3rd elem equals to %d\n", *(ptr + 2));
  free(ptr);
  return 0;
}