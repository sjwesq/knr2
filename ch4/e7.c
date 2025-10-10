// Write a routine ungets(s) that will push back an entire string onto the
// input. Should ungets know about buf and bufp, or should it just use ungetch?
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNGETCH_BUF_SIZE 100

static char ungetch_buf[UNGETCH_BUF_SIZE];  // buffer for ungetch
static int ungetch_buf_pos = 0;             // next free position in buf

static char GetCh(void);
static void UngetCh(char c);
static void UngetStr(char str[]);

int main(void) {
  char test_str[] = "Test String";
  char buf_str[100] = {'\0'};

  UngetStr(test_str);
  int i;
  for (i = 0; i < (int)strlen(test_str); ++i) {
    buf_str[i] = GetCh();
  }
  buf_str[++i] = '\0';

  printf("%s\n", buf_str);

  return EXIT_SUCCESS;
}

// get a (possibly pushed back) character
static char GetCh(void) {
  return (ungetch_buf_pos > 0) ? ungetch_buf[--ungetch_buf_pos]
                               : (char)getchar();
}

// push character back on input
static void UngetCh(char c) {
  if (ungetch_buf_pos >= UNGETCH_BUF_SIZE) {
    printf("ungetch: too many characters\n");
  } else {
    ungetch_buf[ungetch_buf_pos++] = c;
  }
}

static void UngetStr(char str[]) {
  for (int i = (int)strlen(str); i >= 0; --i) {
    UngetCh(str[i]);
  }
}
