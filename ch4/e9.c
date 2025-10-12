// Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what
// their properties ought to be if an EOF is pushed back, then implement your
// design.

// I had to look into this one a bit. Apparently, EOF is expected to have a
// separate meaning to just (char)0xFF. If we interpret an input stream as ints
// for example, 0xFF has a separate meaning from EOF (-1). So to solve this
// exercise, you work with ints instead of chars.
#include <stdio.h>
#include <stdlib.h>

#define UNGETCH_BUF_SIZE 100

static int ungetch_buf[UNGETCH_BUF_SIZE];  // buffer for ungetch
static int ungetch_buf_pos = 0;            // next free position in buf

static int GetCh(void);
static void UngetCh(int c);

int main(void) {
  UngetCh(EOF);
  GetCh();

  return EXIT_SUCCESS;
}

// get a (possibly pushed back) character
static int GetCh(void) {
  return (ungetch_buf_pos > 0) ? ungetch_buf[--ungetch_buf_pos] : getchar();
}

// push character back on input
static void UngetCh(int c) {
  if (c == EOF) {
    printf("error: can't push EOF back on input\n");
    return;
  }
  if (ungetch_buf_pos >= UNGETCH_BUF_SIZE) {
    printf("ungetch: too many intacters\n");
  } else {
    ungetch_buf[ungetch_buf_pos++] = c;
  }
}
