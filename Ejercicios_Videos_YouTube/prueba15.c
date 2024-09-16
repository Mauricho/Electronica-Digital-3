#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char str20[20];
  char *str = NULL;

  strcpy(str20, "12345");
  printf("str20 size: %ld\n", sizeof(str20));   // Espacio que ocupa
  printf("str20 length: %ld\n", strlen(str20)); // Largo de la cadena

  /*
    Creamos el espacio para guardar la cadena, y le sumamos uno para el
    caracter NULL.
  */
  str = malloc(strlen(str20) + 1); /* make room for \0 */
  strcpy(str, str20);
  printf("%s\n", str);

  return 0;
}