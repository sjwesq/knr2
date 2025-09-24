#include "text.h"

#include <stdio.h>

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
