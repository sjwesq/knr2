/* Write a program to count blanks, tabs, and newlines. */
#include <stdio.h>
#include <stdlib.h>

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
  printf("blanks:%d tabs:%d newlines:%d\n", blanks, tabs, newlines);

  return EXIT_SUCCESS;
}
