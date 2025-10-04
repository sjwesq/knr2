// Write a function expand(s1,s2) that expands shorthand notations like a-z in
// the string s1 into the equivalent complete list abc...xyz in s2 . Allow for
// letters of either case and digits, and be prepared to handle cases like a-b-c
// and a-z0-9 and -a-z . Arrange that a leading or trailing '-' is taken
// literally.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void Expand(const char str1[], char str2[]);
bool CheckValidRange(char c1, char c2);
static bool IsUppercase(char c);
static bool IsLowercase(char c);
static bool IsNumber(char c);
static void TestExpand(const char str[]);

#define MAX_STR_LENGTH 256

int main(void) {
  TestExpand("a-b-c n-y 5-8");
  TestExpand("B-M");
  TestExpand("1-2-3 7-9");
  TestExpand("A-Z2-4-6a-zB-F");
  TestExpand("1-3a-c 1-5-6 2-2 A-B-C-D-E-F");
  TestExpand("AZAZAZ");
  TestExpand("azadabab");

  return EXIT_SUCCESS;
}

static void Expand(const char str1[], char str2[]) {
  bool range_enabled = false;
  char last_alphanumeric = '\0';
  unsigned out_pos = 0;
  for (int i = 0; str1[i] != '\0'; ++i) {
    char c_now = str1[i];
    if (IsUppercase(c_now) || IsLowercase(c_now) || IsNumber(c_now)) {
      if (CheckValidRange(last_alphanumeric, c_now) && range_enabled) {
        for (int j = 1; j <= c_now - last_alphanumeric; ++j) {
          str2[out_pos++] = last_alphanumeric + (char)j;
        }
      } else {
        str2[out_pos++] = c_now;
      }
      last_alphanumeric = c_now;
    } else if (c_now == '-') {
      range_enabled = true;
    } else {
      last_alphanumeric = '\0';
    }
  }
}

// c1 is expected to be the lesser value
bool CheckValidRange(char c1, char c2) {
  if (c1 < c2) {
    if (IsUppercase(c1) && IsUppercase(c2)) {
      return true;
    } else if (IsLowercase(c1) && IsLowercase(c2)) {
      return true;
    } else if (IsNumber(c1) && IsNumber(c2)) {
      return true;
    }
  }
  return false;
}

static bool IsUppercase(char c) {
  if (c >= 'A' && c <= 'Z') {
    return true;
  }
  return false;
}

static bool IsLowercase(char c) {
  if (c >= 'a' && c <= 'z') {
    return true;
  }
  return false;
}

static bool IsNumber(char c) {
  if (c >= '0' && c <= '9') {
    return true;
  }
  return false;
}

static void TestExpand(const char str[]) {
  char str_buffer[MAX_STR_LENGTH] = {0};

  Expand(str, str_buffer);
  printf("in: %s, out: %s\n", str, str_buffer);
}
