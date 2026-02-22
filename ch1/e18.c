/* Write a program to remove trailing spaces and tabs from each line of input,
 * and to delete entirely blank lines. */
#include <stdio.h>
#include <stdlib.h>

#include "text.h"

#define MAX_LINE_LEN 1000

static void RemoveBlank(char str[], const int len);

int main(void) {
  char line_current[MAX_LINE_LEN];

  while ((textGetLine(line_current, MAX_LINE_LEN)) > 0) {
    RemoveBlank(line_current, MAX_LINE_LEN);
    printf("%s", line_current);
  }

  return EXIT_SUCCESS;
}

/* Only handles one line at a time */
static void RemoveBlank(char str[], const int len) {
  int index_nonblank = -1;
  int index_current = 0;

  while (index_current < len - 2 && str[index_current] != '\0') {
    if (str[index_current] != ' ' && str[index_current] != '\t' &&
        str[index_current] != '\n') {
      index_nonblank = index_current;
    }
    ++index_current;
  }
  if (index_nonblank != -1) {
    str[index_nonblank + 1] = '\n';
    str[index_nonblank + 2] = '\0';
  } else {
    str[0] = '\0';
  }
}
