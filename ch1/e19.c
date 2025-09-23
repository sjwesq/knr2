// Write a function `reverse` that reverses the character string s. Use it to
// write a program that reverses its input a line at a time.
#include <stdio.h>
#include <stdlib.h>

#include "text.h"

#define MAX_LINE_LENGTH 1000

static void reverse(char str[], int len);

int main(void) {
  char line_current[MAX_LINE_LENGTH];

  while ((textGetLine(line_current, MAX_LINE_LENGTH)) > 0) {
    reverse(line_current, MAX_LINE_LENGTH);
    printf("%s", line_current);
  }

  return EXIT_SUCCESS;
}

static void reverse(char str[], int len) {
  char str_copy[MAX_LINE_LENGTH];
  int index_end = 0;

  /* Find end of string */
  for (int i = 0; i < len; ++i) {
    str_copy[i] = str[i];
    if (str[i] == '\n' || str[i] == '\0') {
      index_end = i;
      break;
    }
  }

  if (index_end > 1) {
    for (int i = 0; i < index_end; ++i) {
      str[i] = str_copy[index_end - i - 1];
    }
  }
}
