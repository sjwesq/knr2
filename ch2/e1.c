// Write a program to determine the ranges of char, short, int and long
// variables, both signed and unsigned, by printing appropriate values from
// standard headers and by direct computation. Harder if you compute them:
// determine the ranges of the various floating-point types.
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // char
  printf("[CHAR] MIN:%d, MAX:%d\n", CHAR_MIN, CHAR_MAX);
  printf("[SCHAR] MIN:%d, MAX:%d\n", SCHAR_MIN, SCHAR_MAX);
  printf("[UCHAR] MIN:0, MAX:%d\n", UCHAR_MAX);

  // short
  printf("[SHRT] MIN:%d, MAX:%d\n", SHRT_MIN, SHRT_MAX);
  printf("[USHRT] MIN:0, MAX:%d\n", USHRT_MAX);

  // int
  printf("[INT] MIN:%d, MAX:%d\n", INT_MIN, INT_MAX);
  printf("[UINT] MIN:0, MAX:%u\n", UINT_MAX);

  // long
  printf("[LONG] MIN:%ld, MAX:%ld\n", LONG_MIN, LONG_MAX);
  printf("[ULONG] MIN:0, MAX:%lu\n", ULONG_MAX);

  // floating types
  printf("[FLOAT]  MIN:%e MAX:%e\n", (double)FLT_MIN, (double)FLT_MAX);
  printf("[DOUBLE] MIN:%e MAX:%e\n", DBL_MIN, DBL_MAX);

  // good enough

  return EXIT_SUCCESS;
}
