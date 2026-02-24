// Extend atof to handle scientific notation of the form
//   123.45e-6
// where a floating-point number may be followed by e or E and optionally a
// signed exponent.
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "text.h"

#define STR_LEN 1000

// double atofOld(char s[]);
double atofNew(char s[]);

int main(void) {
  char teststrs[][STR_LEN] = {"1.234e5", "123.45e-6", "1.0e3", "-1.545e10"};
  int teststrs_len = sizeof(teststrs) / sizeof(teststrs[0]);

  for (int i = 0; i < teststrs_len; ++i) {
    printf("str: %s, double: %f\n", teststrs[i], atofNew(teststrs[i]));
  }

  return EXIT_SUCCESS;
}

// double atofOld(char s[]) {
//   double val, power;
//   int i, sign;
//
//   for (i = 0; isspace(s[i]); ++i);  // skip whitespace
//
//   sign = (s[i] == '-') ? -1 : 1;
//   if (s[i] == '+' || s[i] == '-') {
//     ++i;
//   }
//   for (val = 0.0; isdigit(s[i]); ++i) {
//     val = 10.0 * val + (s[i] - '0');
//   }
//   if (s[i] == '.') {
//     ++i;
//   }
//   for (power = 1.0; isdigit(s[i]); ++i) {
//     val = 10.0 * val + (s[i] - '0');
//     power *= 10.0;
//   }
//
//   return sign * val / power;
// }

double atofNew(char s[]) {
  int sign = 1;
  double val = 0.0;
  double power = 1.0;
  double sci_modifier = 10.0;
  double sci_exponent = 0.0;

  int i = 0;
  while (isspace(s[i]) || s[i] == '+') {
    // skip whitespace & unary plus
    ++i;
  }

  if (s[i] == '-') {
    sign = -1;
    ++i;
  }

  while (isdigit(s[i])) {
    val = 10.0 * val + (s[i] - '0');
    ++i;
  }

  if (s[i] == '.') ++i;

  while (isdigit(s[i])) {
    val = 10.0 * val + (s[i] - '0');
    power /= 10.0;

    ++i;
  }

  if (s[i] == 'e') {
    ++i;
  }
  if (s[i] == '-') {
    sci_modifier = 0.1;
    ++i;
  }

  while (isdigit(s[i])) {
    sci_exponent *= 10.0;
    sci_exponent += s[i] - '0';
    ++i;
  }

  for (int j = 0; j < sci_exponent; ++j) {
    power *= sci_modifier;
  }

  return sign * val * power;
}
