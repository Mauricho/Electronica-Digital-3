#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE *fptr;

  errno = 0;
  fptr = fopen("c:\\nonexistantfile.txt", "r");
  if (fptr == NULL) {
    perror("Error");
    fprintf(stderr, "%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  fclose(fptr);
  return 0;
}