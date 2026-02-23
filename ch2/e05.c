// Write the function any(s1,s2) , which returns the first location in the
// string s1 where any character from the string s2 occurs, or -1 if s1 contains
// no characters from s2 . (The standard library function strpbrk does the same
// job but returns a pointer to the location.)
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int any(const char s1[], const signed char s2[]);

int main(void) {
  char s1[] = "The Quick Brown Fox Jumps Over The Lazy Dog";
  char s2[] = "font";
  int found_pos = any(s1, (signed char*)s2);

  printf("s1: %s, s2: %s, 1st pos. = %d:%c\n", s1, s2, found_pos,
         s1[found_pos]);

  return EXIT_SUCCESS;
}

int any(const char s1[], const signed char s2[]) {
  bool char_map[SCHAR_MAX * 2] = {false};

  for (int i = 0; s2[i] != '\0'; ++i) {
    char_map[(int)s2[i] + SCHAR_MAX / 2] = true;
  };

  for (int i = 0; s1[i] != '\0'; ++i) {
    char c_now = s1[i];
    if (char_map[((int)c_now + SCHAR_MAX / 2)]) {
      return i;
    }
  }

  return -1;
}
