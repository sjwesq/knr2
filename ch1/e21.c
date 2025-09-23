// Write a program `entab` that replaces strings of spaces by the minimum number
// of tabs and blanks to achieve the same spacing. Use the same tab stops as for
// `detab`. When either a tab or a single blank would suffice to reach a tab
// stop, which should be given preference?
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"

#define MAX_LINE_LENGTH 1000
#define TAB_STOP 8

static unsigned int Entab(char str[], char buffer[], unsigned int len) {
  strncpy(buffer, str, len);
  unsigned int str_length = 0;
  unsigned int line_pos = 0;
  unsigned int spaces_til_tabstop = 0;

  unsigned int str_pos = 0;
  unsigned int bufpos = 0;
  for (; bufpos < len - 1 && buffer[bufpos] != '\0'; ++bufpos) {
    if (line_pos % TAB_STOP == 0) {
      if (spaces_til_tabstop > 1) {
        str_pos -= spaces_til_tabstop;

        str[bufpos + str_pos] = '\t';
        ++str_pos;

        str_length -= str_pos;
        spaces_til_tabstop = 0;
      }
    }

    switch (buffer[bufpos]) {
      case ' ': {
        ++line_pos;
        ++spaces_til_tabstop;
        break;
      }
      case '\n': {
        line_pos = 0;
        spaces_til_tabstop = 0;
        break;
      }
      default: {
        ++line_pos;
        spaces_til_tabstop = 0;
        break;
      }
    }

    str[bufpos + str_pos] = buffer[bufpos];
    ++str_length;
  }
  str[bufpos + str_pos] = '\0';
  ++str_length;

  return str_length;
}

int main(void) {
  char line_current[MAX_LINE_LENGTH];
  char line_buffer[MAX_LINE_LENGTH];

  while ((textGetLine(line_current, MAX_LINE_LENGTH)) > 0) {
    Entab(line_current, line_buffer, MAX_LINE_LENGTH);
    printf("%s", line_current);
  }

  return EXIT_SUCCESS;
}
