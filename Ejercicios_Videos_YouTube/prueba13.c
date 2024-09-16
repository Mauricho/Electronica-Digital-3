#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int num;
  char *info;
} record;

int main() {
  record *recs; // Creo un puntero - guardo una dirección para una estructura
  int num_recs = 2;
  int k;
  char str[] = "This is information";

  /*
  Defino que el tamaño que va a tener ese espacio en memoria al que apunta el
  puntero para la estructura
  */
  recs = calloc(num_recs, sizeof(record));

  if (recs != NULL) { // Si el tamaño fue asignado

    for (k = 0; k < num_recs; k++) {
      (recs + k)->num = k; // Le coloco un valor de k

      // Defino el tamaño que va a tener el puntero de la estructura
      (recs + k)->info = malloc(sizeof(str));

      // Le doy el valor al puntero de la estructura
      strcpy((recs + k)->info, str);
    }
  }

  for (k = 0; k < num_recs; k++) {
    printf("%d\t%s\n", (recs + k)->num, (recs + k)->info);
  }

  return 0;
}
