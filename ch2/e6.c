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
static int GetBit32(uint32_t x, uint32_t pos);
static void TestPrint32(char label[], uint32_t x);
static void TestSetBits32(uint32_t val1, uint32_t val2, int index, int len);

int main(void) {
  TestSetBits32(0x00000000, 0x11111111, 0, 16);
  TestSetBits32(0xFFFFFFFF, 0x11111111, 16, 16);
  TestSetBits32(0xFFFFFFFF, 0x22222222, 8, 8);

  return EXIT_SUCCESS;
}

static uint32_t SetBits32(uint32_t val1, uint32_t val2, int index, int len) {
  int width = 32;
  uint32_t result = val1;

  for (int i = 0; i < len; ++i) {
    int index_right = width - 1 - index - i;
    uint32_t mask = ~(UINT32_C(1) << index_right);
    uint32_t bitvalue = (val2 & ~mask) ? 1 : 0;
    result &= mask;  // clear current bit
    result |= (bitvalue << index_right);
  }

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
    printf("%d", GetBit32(x, bit_current));
    bit_current >>= 1;
  }
}

static int GetBit32(uint32_t x, uint32_t pos) { return (x & pos) ? 1 : 0; }

static void TestSetBits32(uint32_t val1, uint32_t val2, int index, int len) {
  TestPrint32("x", val1);
  TestPrint32("y", val2);
  printf("Starting at index %d, chainging %d bits of x to y...\n", index, len);
  TestPrint32("result", SetBits32(val1, val2, index, len));
  printf("\n");
}
