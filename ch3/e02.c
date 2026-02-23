// Write a function escape(s, t) that converts characters like newline and tab
// into visible escape sequences like '\n' and '\t' as it copies the string from
// t to s. Use a `switch`. Write a function for the other direction as well,
// converting escape sequences into the real characters.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_MAX 80

static void Escape(char s[], char t[]);
static void Unescape(char s[], char t[]);
static char ConvertFromEsc(char c);
static char ConvertToEsc(char c);

int main(void) {
  char str1[STR_MAX] =
      "\tThis test string\v\a is pretty cool.\n\tIt's perfect for testing.\n";
  char str2[STR_MAX];

  printf("Escape test:\n");
  printf("str1: %s\n", str1);
  Escape(str1, str2);
  printf("str2: %s\n", str2);

  for (int i = 0; i < STR_MAX; ++i) {
    str1[i] = 0;
  }
  printf("\nCleared str1.\n");

  printf("\nUnescape test:\n");
  printf("str2: %s\n", str2);
  Unescape(str2, str1);
  printf("str1: %s\n", str1);

  return EXIT_SUCCESS;
}

static void Escape(char s[], char t[]) {
  int t_offset = 0;
  for (int i = 0; s[i] != '\0'; ++i, ++t_offset) {
    if (ConvertFromEsc(s[i]) != -1) {
      t[t_offset++] = '\\';
      t[t_offset] = ConvertFromEsc(s[i]);
    } else {
      t[t_offset] = s[i];
    }
  }
}

static void Unescape(char s[], char t[]) {
  int t_offset = 0;
  for (int i = 0; s[i] != '\0'; ++i, ++t_offset) {
    if (s[i] == '\\' && ConvertToEsc(s[i + 1]) != -1) {
      t[t_offset] = ConvertToEsc(s[i + 1]);
      ++i;
    } else {
      t[t_offset] = s[i];
    }
  }
}

static char ConvertFromEsc(char c) {
  switch (c) {
    case '\a': {
      return 'a';
    }
    case '\b': {
      return 'b';
    }
    case '\f': {
      return 'f';
    }
    case '\n': {
      return 'n';
    }
    case '\r': {
      return 'r';
    }
    case '\t': {
      return 't';
    }
    case '\v': {
      return 'v';
    }
    default: {
      return -1;
    }
  }
}

static char ConvertToEsc(char c) {
  switch (c) {
    case 'a': {
      return '\a';
    }
    case 'b': {
      return '\b';
    }
    case 'f': {
      return '\f';
    }
    case 'n': {
      return '\n';
    }
    case 'r': {
      return '\r';
    }
    case 't': {
      return '\t';
    }
    case 'v': {
      return '\v';
    }
    default: {
      return -1;
    }
  }
}
