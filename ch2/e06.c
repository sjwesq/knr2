// Write a function `setbits(x,p,n,y)` that returns x with the n bits that begin
// at position p set to the rightmost n bits of y, leaving the other bits
// unchanged.
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// val 1 is x, val 2 is y, index is p, len is n
static uint32_t SetBits32(uint32_t val1, uint32_t val2, int index, int len);
static void PrintBits32(uint32_t x);
static void TestPrint32(char label[], uint32_t x);
static void TestSetBits32(uint32_t val1, uint32_t val2, int index, int len);

int main(void) {
  TestSetBits32(0x00000000, 0xFFFFFFFF, 1, 31);
  TestSetBits32(0xFFFFFFFF, 0x00000000, 31, 1);
  TestSetBits32(0xFFFFFFFF, 0x22222222, 8, 8);
  TestSetBits32(0xFFFFFFFF, 0x22222222, 0, 0);
  TestSetBits32(0xFFFFFFFF, 0x22222222, 0, 32);

  return EXIT_SUCCESS;
}

// index is 0-indexed, and goes from left-to-right
static uint32_t SetBits32(uint32_t val1, uint32_t val2, int index, int len) {
  // error checking first
  int width = 32;

  if (index < 0 || index >= width || len <= 0) {
    return val1;
  } else if (len >= width) {
    return val2;
  }

  uint32_t result = val1;
  int shift = width - len - index;
  uint32_t mask = ~(((UINT32_C(1) << len) - 1) << shift);
  uint32_t values = ~mask & val2;

  result &= mask;  // clear the relevant bits
  result |= values;

  return result;
}

static void TestPrint32(char label[], uint32_t x) {
  printf("%s:", label);
  PrintBits32(x);
  printf("\n");
}

static void PrintBits32(uint32_t x) {
  int width = 32;
  uint32_t bit_current = UINT32_C(1) << (width - 1);
  for (int i = width; i > 0; --i) {
    printf("%d", (x & bit_current) ? 1 : 0);
    bit_current >>= 1;
  }
}

static void TestSetBits32(uint32_t val1, uint32_t val2, int index, int len) {
  TestPrint32("x", val1);
  TestPrint32("y", val2);
  printf("Starting at index %d, changing %d bits of x to y...\n", index, len);
  TestPrint32("result", SetBits32(val1, val2, index, len));
  printf("\n");
}
