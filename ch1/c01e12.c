/* Write a program that prints its input one word per line. */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int c, c_last;

  c_last = 0;
  while ((c = getchar()) != EOF) {
    if (c != ' ' || c_last != ' ') {
      if (c == ' ')
        putchar('\n');
      else if (c != '\n')
        putchar(c);
    }
    c_last = c;
  }
  putchar('\n');

  return EXIT_SUCCESS;
}
