/* Write a program to print all input lines that are longer than 80
 * characters. */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <text.h>

#define MAX_LINE_LEN 1000

int main(void) {
  int line_length = 0;
  char line_current[MAX_LINE_LEN] = {0};

  while ((line_length = textGetLine(line_current, MAX_LINE_LEN)) > 0) {
    if (line_length > 80) {
      printf("%s\n", line_current);
    }
  }

  return EXIT_SUCCESS;
}
