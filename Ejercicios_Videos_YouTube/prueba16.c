#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *elements;
  int size;
  int cap;
} dyn_array;

int main() {
  dyn_array arr;
  int i;

  /* initialize array */
  arr.size = 0;
  arr.elements = calloc(1, sizeof(*arr.elements));
  arr.cap = 1; /* room for 1 element */

  /* expand by 5 more elements */
  arr.elements = realloc(arr.elements, (5 + arr.cap) * sizeof(*arr.elements));
  if (arr.elements != NULL)
    arr.cap += 5; /* increase capacity */

  /* add an element and increase size */
  if (arr.size < arr.cap) {
    arr.elements[arr.size] = 50; /* add element to array */
    arr.size++;
  } else
    printf("Need to expand array.");

  /* display array elements */
  for (i = 0; i < arr.cap; i++)
    printf("Element %d: %d\n", i, arr.elements[i]);

  return 0;
}