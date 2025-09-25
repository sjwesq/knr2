// Write a function invert (x,p,n) that returns x with the n bits that begin at
// position p inverted (i.e. 1 changed into 0 and vice versa), leaving the
// others unchanged.
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void TestPrint(char label[], uint32_t x);
static uint32_t Invert32(uint32_t x, int p, int n);
static void PrintBits32(uint32_t x);
static void Test(uint32_t x, int p, int n);

int main(void) {
  Test(0xFFFFFFFF, 8, 16);
  Test(0x00000000, 16, 16);
  Test(0x11111111, 8, 4);
  Test(0x42424242, 8, 16);
  Test(0x22222222, 0, 32);
  Test(0x44444444, 0, 0);

  return EXIT_SUCCESS;
}
static uint32_t Invert32(uint32_t x, int p, int n) {
  int width = 32;

  if (p < 0 || p >= 32 || n <= 0) {
    return x;
  } else if (n >= 32) {
    return ~x;
  }

  int shift = width - p - n;
  uint32_t result = x;
  uint32_t mask = (((UINT32_C(1) << n) - UINT32_C(1)) << shift);

  result ^= mask;

  return result;
}

static void PrintBits32(uint32_t x) {
  int width = 32;
  uint32_t bit_current = UINT32_C(1) << (width - 1);
  for (int i = width; i > 0; --i) {
    printf("%d", (x & bit_current) ? 1 : 0);
    bit_current >>= 1;
  }
}

static void TestPrint(char label[], uint32_t x) {
  printf("%s: ", label);
  PrintBits32(x);
  printf("\n");
}

static void Test(uint32_t x, int p, int n) {
  TestPrint("orig", x);
  printf("Inverting %d bits starting at index %d...\n", n, p);
  TestPrint("chng", Invert32(x, p, n));
  printf("\n");
}
