// Add commands for handling variables. (It's easy to provide twenty-six
// variables with single-letter names.) Add a variable for the most recently
// printed value.

// I went kind of crazy working on this one. Well, I can admit I was super
// overcomplicating things. Writing what is effectively an interpreter in the
// way this book did is something I found counter-intuitive. So... A refactor
// happened.
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

// Constants

#define MAXOP 100
#define WORD -1
#define LETTER -1
#define MAXVAL 100  // maximum depth of val stack
#define BUFSIZE 100
#define EPSILON 1e4 * DBL_EPSILON  // accurate enough to stop divide-by-zero

enum TokenType {
  kTokenIsNumber = (char)0xF5,  // start of unused UTF-8 space
  kTokenIsSymbol,
  kTokenIsVariable,
  kTokenIsNewline,
  kTokenIsEOF,
  kTokenIsInvalid,
};

// Globals

static int sp = 0;          // next free stack position
static double val[MAXVAL];  // value stack

static char buf[BUFSIZE];  // buffer for ungetch
static int bufp = 0;       // next free position in buf

static double variable_map[27];
static char last_var = '\0';

// Functions

static void StartCalculator(void);

static enum TokenType getop(char s[]);
static void push(double f);
static double pop(void);

static char getch(void);
static void ungetch(char c);

static void HandleSymbol(char s[]);

static int MapCharToVar(char c);
static double GetVar(char c);
static void SetVar(char c, double f);

int main(void) {
  StartCalculator();

  return EXIT_SUCCESS;
}

static void StartCalculator(void) {
  char token[MAXOP];

  while (true) {
    switch (getop(token)) {
      case kTokenIsNumber: {
        push(atof(token));
        break;
      }
      case kTokenIsVariable: {
        char variable = token[0];
        int sign = 1;
        if (token[0] == '-' || token[0] == '+') {
          variable = token[1];
        }
        if (token[0] == '-') {
          sign = -1;
        }
        push(GetVar(variable) * sign);

        if (token[0] != '@') {
          last_var = token[0];
        }
        break;
      }
      case kTokenIsSymbol: {
        HandleSymbol(token);
        break;
      }
      case kTokenIsInvalid: {
        printf("error: invalid token\n");
        break;
      }
      case kTokenIsNewline: {
        variable_map[0] = pop();
        printf("\t%.8g\n", variable_map[0]);
        break;
      }
      case kTokenIsEOF: {
        return;
      }
    }
  }
}

// get next operator or numeric operand
// `s` serves as a buffer to store the next token
static enum TokenType getop(char s[]) {
  enum TokenType type_now = kTokenIsInvalid;
  int s_pos = 0;
  char c;
  // clears whitespace before token
  while ((c = getch()) == ' ' || c == '\t');
  // c now equals the first character of the token
  s[0] = c;
  s[1] = '\0';  // just in case

  // 1. Check for sign
  // Early exit for special conditions
  if (c == '-' || c == '+') {
    if (!isalnum(c = getch())) {
      ungetch(c);
      return kTokenIsSymbol;
    } else {
      s[++s_pos] = c;
    }
  }
  // 2. Check for number, could be malformed, atof will handle it
  if (isdigit(c)) {
    while (!isspace(s[++s_pos] = c = getch()) && s_pos < MAXOP - 1);
    type_now = kTokenIsNumber;
  }
  // 3. Check for variable, ignore rest of token
  // Variables are any capital letter or '@'
  else if (isupper(c) || c == '@') {
    while (!isspace(s[++s_pos] = c = getch()) && s_pos < MAXOP - 1);
    type_now = kTokenIsVariable;
  }
  // 4. Check if symbol
  else if (isgraph(c)) {
    while (!isspace(s[++s_pos] = c = getch()) && s_pos < MAXOP - 1);
    type_now = kTokenIsSymbol;
    s[s_pos] = '\0';
  } else if (c == EOF) {
    return kTokenIsEOF;
  } else if (c == '\n') {
    return kTokenIsNewline;
  }

  if (type_now != kTokenIsInvalid) {
    ungetch(c);
  }
  s[s_pos] = '\0';
  return type_now;
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

// This function is a bit hideous but I think a more sophisticated solution is a
// bit overkill for this exercise...
static void HandleSymbol(char s[]) {
  int sign = 1;
  double op2;
  char* s_start_ptr = s;

  // Set sign, move string start to after sign
  if (strlen(s) > 1) {
    if (s[0] == '-') {
      sign = -1;
      s = &s[1];
    } else if (s[0] == '+') {
      s = &s[1];
    }
  }

  // Variable handling
  if (strcmp(s, "=") == 0) {
    if (last_var != '\0') {
      double prev_value = GetVar(last_var);
      double new_value = pop();
      if (prev_value == new_value) {
        new_value = pop();
      }
      SetVar(last_var, new_value);
      push(new_value);
      last_var = '\0';
    } else {
      printf("error: variable missing\n");
    }
  }
  // Standard operations
  else if (strcmp(s, "+") == 0) {
    push(pop() + pop());
  } else if (strcmp(s, "*") == 0) {
    push(pop() * pop());
  } else if (strcmp(s, "-") == 0) {
    op2 = pop();
    push(pop() - op2);
  } else if (strcmp(s, "/") == 0) {
    op2 = pop();
    if (fabs(op2) > EPSILON) {
      push(pop() / op2);
    } else {
      printf("error: zero ulus\n");
    }
  } else if (strcmp(s, "%") == 0) {
    op2 = pop();
    if (fabs(op2) > EPSILON) {
      push((int)pop() % (int)op2);
    } else {
      printf("error: zero divisor\n");
    }
  } else if (strcmp(s, "pow") == 0) {
    op2 = pop();
    push(pow(pop(), op2));
  }
  // Other Operations
  else if (strcmp(s, "sin") == 0) {
    push(sin(pop()));
  } else if (strcmp(s, "cos") == 0) {
    push(cos(pop()));
  } else if (strcmp(s, "tan") == 0) {
    push(tan(pop()));
  } else if (strcmp(s, "asin") == 0) {
    push(asin(pop()));
  } else if (strcmp(s, "acos") == 0) {
    push(acos(pop()));
  } else if (strcmp(s, "atan") == 0) {
    push(atan(pop()));
  } else if (strcmp(s, "log") == 0) {
    push(log(pop()));
  }
  // Constants
  else if (strcmp(s, "pi") == 0) {
    push(acos(-1) * sign);
  } else if (strcmp(s, "e") == 0) {
    push(exp(1.0) * sign);
  }

  // Return string to original state
  s = s_start_ptr;
}

static int MapCharToVar(char c) { return (c == '@') ? 0 : (c - 'A' + 1); }

static double GetVar(char c) { return variable_map[MapCharToVar(c)]; }

static void SetVar(char c, double f) { variable_map[MapCharToVar(c)] = f; }
