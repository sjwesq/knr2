// In a two's complement number representation, our version of itoa does not
// handle the largest negative number, that is, the value of n equal to -(2 to
// the power (wordsize - 1)). Explain why not. Modify it to print that value
// correctly regardless of the machine on which it runs.
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "text.h"

#define MAX_LINE_LENGTH 1000

// static void itoaOld(int n, char s[]);
static void itoaNew(int n, char s[]);

int main(void) {
  char s[MAX_LINE_LENGTH] = {'\0'};

  // Broken:
  // itoaOld(INT_MIN, s);
  // printf("num: %d, str %s\n", INT_MIN, s);

  itoaNew(INT_MIN, s);
  printf("num: %d, str %s\n", INT_MIN, s);

  int testnum = 1254;
  itoaNew(testnum, s);
  printf("num: %d, str %s\n", testnum, s);

  return EXIT_SUCCESS;
}

// static void itoaOld(int n, char s[]) {
//   int i, sign;
//
//   if ((sign = n) < 0)  // record sign
//     n = -n;            // make n positive
//   i = 0;
//   do {
//     s[i++] = n % 10 + '0';
//   } while ((n /= 10) > 0);
//   if (sign < 0) s[i++] = '-';
//   s[i] = '\0';
//   textReverse(s);
// }

// reversing the sign of INT_MIN is out of range. The integer maximum is
// -(INT_MIN + 1)
static void itoaNew(int n, char s[]) {
  int i = 0;
  int sign = 0;

  if ((sign = n) < 0) {
    if (n > INT_MIN) {
      n = -n;
    } else {
      n = -(n + 1);
      s[i++] = (char)(n % 10 + '0' + 1);
      n /= 10;
    }
  }

  do {
    s[i++] = (char)(n % 10 + '0');
  } while ((n /= 10) > 0);
  if (sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';

  textReverse(s);
}
