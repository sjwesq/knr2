/* Write a program to copy its input to its output, replacing each string of one
 * or more blanks by a single blank. */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int c, c_last;

  c_last = 0;
  while ((c = getchar()) != EOF) {
    if (c != ' ' || c_last != ' ') putchar(c);
    c_last = c;
  }
  return EXIT_SUCCESS;
}
