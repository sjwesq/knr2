/* Write a program to print the corresponding Celsius to Fahrenheit table. */
#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

int main(void) {
  float celsius;
  float fahr;

  celsius = LOWER;
  for (celsius = LOWER; celsius <= UPPER; celsius += STEP) {
    fahr = ((float)(9.0 / 5.0) * celsius) + 32;
    printf("%3.0f%6.1f\n", (double)celsius, (double)fahr);
  }

  return 0;
}
