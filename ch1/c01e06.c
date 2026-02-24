/* Verify that the expression getchar () != EOF is 0 or 1. */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int c;
  while ((c = getchar()) != EOF) printf("%3d - 1\n", c);
  printf("%3d - 0\n", c);

  return EXIT_SUCCESS;
}
