// Write the function itob(n,s,b) that converts the integer n into a base b
// character representation in the string s. In particular, itob(n,s,16)
// formats n as a hexadecimal integer in s.
#include <stdio.h>
#include <stdlib.h>

#include "text.h"

#define MAX_LINE_LENGTH 1000

static void IntToBase(int n, int base, char str[]);
static char ValToChar(unsigned n);

int main(void) {
  char str[MAX_LINE_LENGTH] = {0};
  int test_nums[] = {255, 16, 5, 10, 100, 1024};
  int test_nums_length = sizeof(test_nums) / sizeof(test_nums[0]);
  int test_bases[] = {2, 8, 16, 36};
  int test_bases_length = sizeof(test_bases) / sizeof(test_bases[0]);

  // for (int i = 0; i < 36; ++i) {
  //   printf("%c, ", ValToChar((unsigned)i));
  // }
  // printf("\n");

  for (int i = 0; i < test_bases_length; ++i) {
    for (int j = 0; j < test_nums_length; ++j) {
      IntToBase(test_nums[j], test_bases[i], str);
      printf("(base %d) in: %d, out: %s\n", test_bases[i], test_nums[j], str);
    }
  }

  return EXIT_SUCCESS;
}

static void IntToBase(int n, int base, char str[]) {
  int i = 0;
  if (base < 0 || base > 36) {
    return;
  }
  do {
    str[i++] = ValToChar((unsigned)(n % base));
  } while ((n /= base) > 0);
  str[i] = '\0';
  reverse(str);
}

// Doesn't worry about base, caps at base 36
static char ValToChar(unsigned n) {
  if (n < 10) {
    return '0' + (char)n;
  } else if (n >= 10 && n < 36) {
    return 'A' + (char)(n - 10);
  } else
    return '\0';
}
