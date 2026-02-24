/* Experiment to find out what happens when printf's argument string contains
 * \c, where c is some character not listed above (\n, \t, \b, \", and \\.) */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  printf("hello \a\rworld\n");

  return EXIT_SUCCESS;
}
