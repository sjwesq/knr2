// Write a program to "fold" long input lines into two or more shorter lines
// after the last non-blank character that occurs before the n-th column of
// input. Make sure your program does something intelligent with very long
// lines, and if there are no blanks or tabs before the specified column.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"

#define SHIFT_WIDTH 8
#define MAX_LINE_LENGTH 1000

static void FoldLine(char in[], char out[], int len, int textwidth) {
  int line_pos = 0;
  int last_space_pos = 0;

  int in_pos = 0, out_pos = 0;
  for (; out_pos < len - 1 && in[in_pos] != '\0'; ++in_pos, ++out_pos) {
    // break line
    if (line_pos >= textwidth) {
      if (last_space_pos > 0) {
        out[last_space_pos] = '\n';
        line_pos = in_pos - last_space_pos;
        last_space_pos = 0;
      } else {
        out[out_pos++] = '\n';
        line_pos = 0;
      }
    }

    int char_width = 1;
    switch (in[in_pos]) {
      case ' ': {
        last_space_pos = out_pos;
        break;
      }
      case '\n': {
        line_pos = 0;
        char_width = 0;
        break;
      }
      case '\t': {
        char_width = SHIFT_WIDTH - (line_pos % SHIFT_WIDTH);
        break;
      }
    }

    out[out_pos] = in[in_pos];
    line_pos += char_width;
  }
  out[out_pos] = '\0';
}

int main(void) {
  char line_current[MAX_LINE_LENGTH];
  char line_buffer[MAX_LINE_LENGTH];

  while ((textGetLine(line_current, MAX_LINE_LENGTH)) > 0) {
    FoldLine(line_current, line_buffer, MAX_LINE_LENGTH, 80);
    strncpy(line_current, line_buffer, MAX_LINE_LENGTH);
    printf("%s", line_current);
  }

  return EXIT_SUCCESS;
}
