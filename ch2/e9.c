// In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit
// in x. Explain why. Use this observation to write a faster version of
// bitcount.
//
// 11111111
//    &
// 11111110
//    =
// 11111110
//    &
// 11111101
//    =
// 11111100
//    &
// 11111001
//    =
// 11111000
// etc...

#include <stdio.h>
#include <stdlib.h>

static int bitcount(unsigned int x);

int main(void) {
  int value = 1001;

  printf("%d : %d bits\n", value, bitcount((unsigned)value));

  return EXIT_SUCCESS;
}

static int bitcount(unsigned x) {
  int count = 0;
  while (x != 0) {
    x &= (x - 1);
    ++count;
  }
  return count;
}
