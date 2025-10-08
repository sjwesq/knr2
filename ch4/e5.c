// Add access to library functions like sin, exp, and pow. See <math.h> in
// Appendix B, Section 4.
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP 100
#define WORD -1
#define LETTER -1
#define MAXVAL 100  // maximum depth of val stack
#define BUFSIZE 100
#define EPSILON 1e4 * DBL_EPSILON  // accurate enough to stop divide-by-zero

enum {
  kIsNumber = (char)0xF5,  // start of unused UTF-8 space
  kIsWord,
};

static int sp = 0;          // next free stack position
static double val[MAXVAL];  // value stack

static char buf[BUFSIZE];  // buffer for ungetch
static int bufp = 0;       // next free position in buf

static char getop(char s[]);
static void push(double f);
static double pop(void);

static char getch(void);
static void ungetch(char c);

static double StackPeek(void);
static void StackDuplicate(void);
static void StackSwapTopTwo(void);
static void StackPrint(void);

static void HandleWordOp(char s[]);

int main(void) {
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
      case kIsNumber: {
        push(atof(s));
        break;
      }
      case kIsWord: {
        HandleWordOp(s);
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

  if (isalpha(c)) {
    if (isalpha(c = getch())) {
      s[++i] = c;
      while (isalpha(s[++i] = c = getch()));
      s[i] = '\0';

      if (c != EOF) {
        ungetch(c);
      }

      return kIsWord;
    } else {
      ungetch(c);
      return s[0];
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

    return kIsNumber;
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

static double StackPeek(void) {
  if (sp > 0) {
    printf("%g", val[sp - 1]);
    return val[sp];
  } else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

static void StackDuplicate(void) {
  if (sp > 0) {
    val[sp] = val[sp - 1];
    ++sp;
  } else {
    printf("error: stack empty\n");
  }
}

static void StackSwapTopTwo(void) {
  if (sp > 1) {
    double tmp = val[sp - 2];
    val[sp - 2] = val[sp - 1];
    val[sp - 1] = tmp;
  } else {
    printf("error: not enough values to swap");
  }
}

static void StackPrint(void) {
  for (int i = 0; i < sp; ++i) {
    printf("%g, ", val[i]);
  }
  printf("\n");
}

static void HandleWordOp(char s[]) {
  if (strcmp(s, "sin") == 0) {
    push(sin(pop()));
  }
  if (strcmp(s, "cos") == 0) {
    push(cos(pop()));
  }
  if (strcmp(s, "tan") == 0) {
    push(tan(pop()));
  }
  if (strcmp(s, "asin") == 0) {
    push(asin(pop()));
  }
  if (strcmp(s, "acos") == 0) {
    push(acos(pop()));
  }
  if (strcmp(s, "atan") == 0) {
    push(atan(pop()));
  }
  if (strcmp(s, "log") == 0) {
    push(log(pop()));
  }
  if (strcmp(s, "exp") == 0) {
    push(exp(pop()));
  }
  // -pi is not supported. I'm considering it out of scope for this exercise.
  // I'll handle that in the refactor later.
  if (strcmp(s, "pi") == 0) {
    push(acos(-1));
  }
  if (strcmp(s, "pow") == 0) {
    double exp = pop();
    push(pow(pop(), exp));
  }
}
