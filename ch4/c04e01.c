// Write the function strrindex(s, t), which returns the position of the
// rightmost occurence of t in s, or -1 if there is none.
#include <stdio.h>
#include <stdlib.h>

#define STR_LEN 1000

int strrindex(char s[], char t);

int main(void) {
  char testchars[] = "rstlne";
  char teststr[][STR_LEN] = {"water balloon",        "once upon a time",
                             "Super Mario Brothers", "evil incorporated",
                             "Final Fantasy Six",    "LITTLE GREEN"};
  int teststr_len = sizeof(teststr) / sizeof(teststr[0]);

  for (int i = 0; i < teststr_len; ++i) {
    for (int j = 0; testchars[j] != '\0'; ++j) {
      printf("rightmost '%c' in \"%s\": index %d\n", testchars[j], teststr[i],
             strrindex(teststr[i], testchars[j]));
    }
  }

  return EXIT_SUCCESS;
}

int strrindex(char s[], char t) {
  int index = -1;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == t) {
      index = i;
    }
  }

  return index;
}
