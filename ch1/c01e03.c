/* Modify the temperature conversion program to print a heading above the
 * table. */
#include <stdio.h>
#include <stdlib.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

int main(void) {
  double fahr;
  double celsius;

  printf("degF  degC\n");
  fahr = LOWER;
  while (fahr <= UPPER) {
    celsius = (5.0 / 9.0) * (fahr - 32.0);
    printf("%3.0f %6.1f\n", fahr, celsius);
    fahr += STEP;
  }

  return EXIT_SUCCESS;
}
