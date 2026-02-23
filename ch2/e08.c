// Write a function rightrot(x, n) that returns the value of the integer x
// rotated to the right by n positions.
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t rightrot(uint32_t x, int n);
static void PrintBits32(uint32_t x);
static void Test(uint32_t x, int n);
static void TestPrint(char label[], uint32_t x);

int main(void) {
  Test(0x88888888, 1);
  Test(0x33333333, 1);
  Test(0x00008888, 1);

  Test(0x000000FF, 1);
  Test(0x000000FF, 2);
  Test(0x000000FF, 4);
  Test(0x000000FF, 8);
  Test(0x000000FF, 16);
  Test(0x000000FF, 32);
  Test(0x000000FF, 64);
  ;
  return EXIT_SUCCESS;
}
static uint32_t rightrot(uint32_t x, int n) {
  int width = 32;
  uint32_t result = x;

  for (int i = 0; i < n; ++i) {
    if (result & UINT32_C(1)) {
      result -= 1;
      result >>= 1;
      result += UINT32_C(1) << (width - 1);
    } else {
      result >>= 1;
    }
  }

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

static void Test(uint32_t x, int n) {
  TestPrint("orig", x);
  printf("Shifting bits %d to the right...\n", n);
  TestPrint("chng", rightrot(x, n));
  printf("\n");
}
