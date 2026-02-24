// Rewrite the funciton lower, which converts uppercase letters to lowercase,
// with a conditional expression instead of if-else.
#include <stdio.h>
#include <stdlib.h>

static void lower(char str[]);

int main(void) {
  char c[] = "I aM sO cOoL";
  printf("1st: %s\n", c);
  lower(c);
  printf("2nd: %s\n", c);
  return EXIT_SUCCESS;
}

static void lower(char str[]) {
  for (int i = 0; str[i] != '\0'; ++i) {
    str[i] = (str[i] >= 'A' && str[i] <= 'Z') ? str[i] + ('a' - 'A') : str[i];
  }
}
