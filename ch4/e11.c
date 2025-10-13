// Modify getop so that it doesn't need to use ungetch. Hint: use an internal
// static variable.

// I'm reusing the original calculator.c I typed out. The refactor is a bit too
// separated from the original, so I'm bringing the original back for this
// exercise.
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100  // maximum depth of val stack
#define BUFSIZE 100

static int sp = 0;          // next free stack position
static double val[MAXVAL];  // value stack

static char buf[BUFSIZE];  // buffer for ungetch
static int bufp = 0;       // next free position in buf

static int getop(char s[]);
static void push(double f);
static double pop(void);

static char getch(void);
static void ungetch(char c);

int main(void) {
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
      case NUMBER: {
        push(atof(s));
        break;
      }
      case '+': {
        push(pop() + pop());
        break;
      }
      case '*': {
        push(pop() * pop());
        break;
      }
      case '-': {
        op2 = pop();
        push(pop() - op2);
        break;
      }
      case '/': {
        op2 = pop();
        if (op2 != 0.0) {
          push(pop() / op2);
        } else {
          printf("error: zero divisor\n");
        }
        break;
      }
      case '\n': {
        printf("\t%.8g\n", pop());
        break;
      }
      default: {
        printf("error: unknown command %s\n", s);
        break;
      }
    }
  }

  return EXIT_SUCCESS;
}

// get next operator or numeric operand
static int getop(char s[]) {
  char c;
  static char c_prev = 0;

  if (c_prev == 0) {
    c = getch();
  } else {
    c = c_prev;
  }

  int i;
  while ((s[0] = c) == ' ' || c == '\t') c = getch();

  s[1] = '\0';
  if (!isdigit(c) && c != '.') {
    return c;
  }
  i = 0;
  if (isdigit(c)) {
    while (isdigit(s[++i] = c = getch()));
  }
  if (c == '.') {
    while (isdigit(s[++i] = c = getch()));
  }
  s[i] = '\0';
  if (c != EOF) {
    c_prev = c;
  }

  return NUMBER;
}

// push f onto value stack
static void push(double f) {
  if (sp < MAXVAL) {
    val[sp++] = f;
  } else {
    printf("error: stack full, can't push %g\n", f);
  }
}

// pop and return top value from stack
static double pop(void) {
  if (sp > 0) {
    return val[--sp];
  } else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

// get a (possibly pushed back) character
static char getch(void) { return (bufp > 0) ? buf[--bufp] : (char)getchar(); }

// push character back on input
static void ungetch(char c) {
  if (bufp >= BUFSIZE) {
    printf("ungetch: too many characters\n");
  } else {
    buf[bufp++] = c;
  }
}
