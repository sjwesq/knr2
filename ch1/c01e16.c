/* Revise the main routine of the longest-line program so it will correctly
 * print the length of arbitrary long input lines, and as much as possible of
 * the text. */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"

#define LINE_MAX_LEN 1000

/* Print the longest input line */
int main(void) {
  int line_len = 0;
  int line_longest_len = 0;
  char line_current[LINE_MAX_LEN] = {0};
  char line_longest[LINE_MAX_LEN] = {0};

  while ((line_len = textGetLine(line_current, LINE_MAX_LEN)) > 0) {
    if (line_len > line_longest_len) {
      line_longest_len = line_len;
      strncpy(line_longest, line_current, LINE_MAX_LEN);
    }
  }
  if (line_longest_len > 0) { /* There was a line */
    printf("%s\n(length: %d)\n", line_longest, line_longest_len);
  }

  return EXIT_SUCCESS;
}
