// Write a function `htoi(s)` which converts a string of hexadecimal digits
// (including an optional 0x or 0X) into its equivalent integer value. The
// allowable digits are 0 through 9, a through f, and A through F.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int htoi(const char s[]);
static int GetCharHexVal(char c);
static int Exponent(int i, int n);
static void Test(void);

int main(void) {
  Test();

  return EXIT_SUCCESS;
}

static int htoi(const char s[]) {
  int hex_value = 0;
  int length = (int)strlen(s);
  int sign = 1;

  for (int i = 0; i < length; ++i) {
    if (s[i] == '-') {
      sign = -sign;
    }
    if (GetCharHexVal(s[i]) == -1) {
      continue;
    } else {
      hex_value += GetCharHexVal(s[i]) * Exponent(16, length - i - 1);
    }
  }

  return sign * hex_value;
}

static int GetCharHexVal(char c) {
  if (c >= 'A' && c <= 'F') {
    return 10 + c - 'A';
  } else if (c >= 'a' && c <= 'f') {
    return 10 + c - 'a';
  } else if (c >= '0' && c <= '9') {
    return c - '0';
  }

  return -1;
}

static int Exponent(int i, int n) {
  int result;
  if (n > 0) {
    result = i * Exponent(i, n - 1);
  } else {
    result = 1;
  }
  return result;
}

static void Test(void) {
  char test_str[][8] = {"FF",     "0xff",  "0X10", "11",   "b1f",
                        "0aB1",   "-0XFF", "ff",   "0a00", "dagff",
                        "456789", "0",     "-111", "--B",  "255"};
  int test_str_len = sizeof(test_str) / sizeof(test_str[0]);

  for (int i = 0; i < test_str_len; ++i) {
    printf("%s: %d\n", test_str[i], htoi(test_str[i]));
  }
}
