// Write a version of itoa that accepts three arguments instead of two. The
// third argument is a minimum field width; the converted number must be padded
// with blanks on the left if necessary to make it wide enough.
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "text.h"

#define MAX_STR_SIZE 1000

static void itoaAlign(int n, char s[], int padding);

int main(void) {
  char s[MAX_STR_SIZE] = {'\0'};
  int testnums[] = {1254, 20, 123415, 1234, 1251251112, 1, 0};
  int testnums_len = sizeof(testnums) / sizeof(testnums[0]);
  for (int i = 0; i < testnums_len; ++i) {
    itoaAlign(testnums[i], s, 10);
    printf("num: %d\n  str: %s\n", testnums[i], s);
  }

  return EXIT_SUCCESS;
}

static void itoaAlign(int n, char s[], int padding) {
  int i = 0;
  int sign = 0;

  if ((sign = n) < 0) {
    if (n > INT_MIN) {
      n = -n;
    } else {
      n = -(n + 1);
      s[i++] = (char)(n % 10 + '0' + 1);
      n /= 10;
      --padding;
    }
  }

  do {
    s[i++] = (char)(n % 10 + '0');
  } while ((n /= 10) > 0);
  if (sign < 0) {
    s[i++] = '-';
    --padding;
  }
  while (i < padding) {
    s[i++] = ' ';
  }
  s[i] = '\0';

  reverse(s);
}
