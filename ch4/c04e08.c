// Suppose that there will never be more than one character of pushback. Modify
// getch and ungetch accordingly.
#include <stdio.h>
#include <stdlib.h>

#define UNGETCH_BUF_SIZE 100
#define UNGETCH_EMPTY_ID (char)0xF5  // Unused UTF-8 byte

static char ungetch_buf = UNGETCH_EMPTY_ID;

static char GetCh(void);
static void UngetCh(char c);

int main(void) {
  UngetCh('a');
  UngetCh('b');

  char c = GetCh();

  printf("%c\n", c);

  printf("%c\n", GetCh());

  printf("Done!\n");

  return EXIT_SUCCESS;
}

// get a (possibly pushed back) character
static char GetCh(void) {
  if (ungetch_buf != UNGETCH_EMPTY_ID) {
    char return_value = ungetch_buf;
    ungetch_buf = UNGETCH_EMPTY_ID;
    return return_value;
  } else {
    return (char)getchar();
  }
}

// push character back on input
static void UngetCh(char c) { ungetch_buf = c; }
