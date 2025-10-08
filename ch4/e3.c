// Given the basic framework, it's straightforward to extend the calculator. Add
// the modulus (%) operator and provisions for negative numbers.
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100  // maximum depth of val stack
#define BUFSIZE 100
#define EPSILON 1e4 * DBL_EPSILON  // accurate enough to stop divide-by-zero

static int sp = 0;          // next free stack position
static double val[MAXVAL];  // value stack

static char buf[BUFSIZE];  // buffer for ungetch
static int bufp = 0;       // next free position in buf

static char getop(char s[]);
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
        if (fabs(op2) > EPSILON) {
          push(pop() / op2);
        } else {
          printf("error: zero divisor\n");
        }
        break;
      }
      case '%': {
        op2 = pop();
        if (fabs(op2) > EPSILON) {
          push((int)pop() % (int)op2);
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
static char getop(char s[]) {
  int i = 0;
  char c;
  do {
    c = getch();
  } while (c == ' ' || c == '\t');
  s[0] = c;

  if (c == '-') {
    if (isdigit(c = getch())) {
      s[++i] = c;
    } else {
      ungetch(c);
      return '-';
    }
  }
  if (isdigit(c) || c == '.') {
    do {
      s[++i] = c = getch();
    } while (isdigit(c) || c == '.');
    s[i] = '\0';

    if (c != EOF) {
      ungetch(c);
    }

    return NUMBER;
  } else {
    // not a number
    s[1] = '\0';
    return c;
  }
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
