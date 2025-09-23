// Write a program `detab` that replaces tabs in the input with the proper
// number of blanks to space to the next tab stop. Assume a fixed set of tab
// stops, say every n columns. Should n be a variable or a symbolic parameter?
#include <stdio.h>
#include <stdlib.h>

#include "text.h"

#define MAX_LINE_LENGTH 1000
#define TAB_STOP 8

static void DeTab(char str[], int len);

int main(void) {
  char line_current[MAX_LINE_LENGTH];

  while ((textGetLine(line_current, MAX_LINE_LENGTH)) > 0) {
    DeTab(line_current, MAX_LINE_LENGTH);
    printf("%s", line_current);
  }

  return EXIT_SUCCESS;
}

static void DeTab(char str[], int len) {
  int tab_dist = TAB_STOP;
  char str_cpy[MAX_LINE_LENGTH];
  int alignment = 0;

  for (int i = 0; i < len; ++i) {
    str_cpy[i] = str[i];
  }

  for (int i = 0; i < len; ++i) {
    if (str_cpy[i] == '\t') {
      while (tab_dist > 0) {
        str[alignment + i] = ' ';
        ++alignment;
        --tab_dist;
        // An attempt at memory safety:
        --len;
      }
      // The above automatically moves alignment to the next character, however,
      // we need to return to the last character inserted for alignment:
      --alignment;
    } else {
      str[alignment + i] = str_cpy[i];
    }

    if (tab_dist > 0) {
      --tab_dist;
    } else {
      tab_dist = TAB_STOP;
    }
  }
}
