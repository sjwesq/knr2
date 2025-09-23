#include <stdio.h>

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
  return 0;
}
