
#include "text.h"

#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int textGetLine(char line_out[], const int limit) {
  int input_value = 0;
  int line_length = 0;
  int index = 0;

  while ((input_value = getchar()) != EOF) {
    if (index < limit - 1) {
      // Check if valid ASCII
      if (input_value <= 127) {
        line_out[index] = (char)input_value;
      } else {
        line_out[index] = 0;
      }
      ++index;
    }
    ++line_length;
    if (input_value == '\n') {
      break;
    }
  }
  line_out[index] = '\0';

  return line_length;
}

void textReverse(char str[]) {
  char str_copy[MAX_LINE_LENGTH];
  int index_end = 0;

  /* Find end of string */
  for (int i = 0; i < MAX_LINE_LENGTH; ++i) {
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
  str[index_end] = '\0';
}
