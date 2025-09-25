// /* squeeze: delete all c from s */
// void squeeze(char s[], int c) {
//   int i, j;
//
//   for (i = j = 0; s[i] != '\0'; i++)
//     if (si[i] != c)
//       s[j++] = s[i];
//     s[j] = '\0';
// }
// Write an alternate version of squeeze(s1,s2) that deletes each character in
// the string s1 that matches any character in the string s2 .
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void SqueezeStr(char s1[], const signed char s2[]);

int main(void) {
  char base[] = "buffalo buffalo buffalo buffalo buffalo buffalo buffalo";
  char filter[] = "fou";

  printf("before: %s\n", base);

  SqueezeStr(base, (signed char*)filter);

  printf("after:  %s\n", base);

  return EXIT_SUCCESS;
}

static void SqueezeStr(char s1[], const signed char s2[]) {
  unsigned int str_pos = 0;
  bool ignore_map[256] = {false};

  for (int i = 0; s2[i] != '\0'; ++i) {
    ignore_map[(int)s2[i] + 127] = true;
  }

  for (int i = 0; s1[i] != '\0'; ++i) {
    char c_now = s1[i];
    if (!ignore_map[(int)c_now + 127]) {
      s1[str_pos++] = c_now;
    }
  }

  s1[str_pos] = '\0';
}
