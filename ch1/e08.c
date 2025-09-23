#include <stdio.h>

int main(void) {
  int c;
  int blanks, tabs, newlines;

  blanks = tabs = newlines = 0;
  while ((c = getchar()) != EOF) {
    switch (c) {
      case ' ':
        ++blanks;
        break;
      case '\t':
        ++tabs;
        break;
      case '\n':
        ++newlines;
        break;
    }
  }
  printf("%d %d %d\n", blanks, tabs, newlines);

  return 0;
}
