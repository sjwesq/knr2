// for(i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
//   s[i] = c;
//
// Write a loop equivalent to the for loop above without using && or || .
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int main(void) {
  char s[MAX_LINE_LENGTH];

  for (int i = 0; i < MAX_LINE_LENGTH - 1; ++i) {
    char c = (char)getchar();
    switch (c) {
      case EOF:
      case '\n': {
        goto getline_end;  // cursed assignments require cursed solutions
      }
      default: {
        s[i] = (char)c;
      }
    }
  }
getline_end:

  // For testing
  for (int i = 0; i < MAX_LINE_LENGTH - 1; ++i) {
    if (s[i] == '\0') {
      break;
    }
    printf("%c", s[i]);
  }
  printf("\n");

  return EXIT_SUCCESS;
}
