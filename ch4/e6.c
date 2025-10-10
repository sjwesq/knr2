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

#define TOKEN_MAX_LEN 100
#define VAL_STACK_SIZE 100
#define UNGETCH_BUF_SIZE 100
#define EPSILON 1e4 * DBL_EPSILON  // accurate enough to stop divide-by-zero

enum TokenType {
  kTokenIsNumber,
  kTokenIsSymbol,
  kTokenIsVariable,
  kTokenIsNewline,
  kTokenIsEOF,
  kTokenIsInvalid,
};

// Globals

static int sp = 0;                  // next free stack position
static double val[VAL_STACK_SIZE];  // value stack

static char ungetch_buf[UNGETCH_BUF_SIZE];  // buffer for ungetch
static int ungetch_buf_pos = 0;             // next free position in buf

static double variable_map[27];
static char last_var = '\0';

// Functions

static void StartCalculator(void);

static enum TokenType GetNextToken(char str[]);
static void PushVal(double f);
static double PopVal(void);

static char GetCh(void);
static void UngetCh(char c);
static void MovePastWhitespace(void);
static void ReadToken(char buf[], int startpos);

static void ProcessSymbol(char str[]);
static void ProcessVariable(char str[]);

static int MapCharToVar(char c);
static double GetVar(char c);
static void SetVar(char c, double f);

int main(void) {
  StartCalculator();

  return EXIT_SUCCESS;
}

static void StartCalculator(void) {
  char token[TOKEN_MAX_LEN];

  while (true) {
    switch (GetNextToken(token)) {
      case kTokenIsNumber: {
        PushVal(atof(token));
        break;
      }
      case kTokenIsVariable: {
        ProcessVariable(token);
        break;
      }
      case kTokenIsSymbol: {
        ProcessSymbol(token);
        break;
      }
      case kTokenIsInvalid: {
        printf("error: invalid token\n");
        break;
      }
      case kTokenIsNewline: {
        variable_map[0] = PopVal();
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
static enum TokenType GetNextToken(char str[]) {
  MovePastWhitespace();

  char c_start = GetCh();
  str[0] = c_start;
  int str_start_pos = 0;

  if (c_start == '-' || c_start == '+') {
    c_start = GetCh();
    if (!isalnum(c_start)) {
      UngetCh(c_start);
      str[1] = '\0';
      return kTokenIsSymbol;
    } else {
      str[++str_start_pos] = c_start;
    }
  }

  ReadToken(str, str_start_pos);

  if (isdigit(c_start)) {
    return kTokenIsNumber;
  } else if (isupper(c_start) || c_start == '@') {
    return kTokenIsVariable;
  } else if (isgraph(c_start)) {
    return kTokenIsSymbol;
  } else if (c_start == EOF) {
    return kTokenIsEOF;
  } else if (c_start == '\n') {
    return kTokenIsNewline;
  } else {
    return kTokenIsInvalid;
  }
}

// push f onto value stack
static void PushVal(double f) {
  if (sp < VAL_STACK_SIZE) {
    val[sp++] = f;
  } else {
    printf("error: stack full, can't push %g\n", f);
  }
}

// pop and return top value from stack
static double PopVal(void) {
  if (sp > 0) {
    return val[--sp];
  } else {
    printf("error: stack empty\n");
    return 0.0;
  }
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

static void MovePastWhitespace(void) {
  char c = GetCh();
  while (c == ' ' || c == '\t') {
    c = GetCh();
  }
  UngetCh(c);
}

static void ReadToken(char buf[], int startpos) {
  int i = startpos;
  if (buf[i] == EOF || buf[i] == '\n') {
    return;
  }
  while (!isspace(buf[++i] = GetCh()) && i < TOKEN_MAX_LEN - 2);
  UngetCh(buf[i]);
  buf[i] = '\0';
}

// Pushes a (single capital letter) variable's value to the stack, and marks it
// as `last_var`. This is useful for assignment. Signed variables are also
// allowed.
static void ProcessVariable(char str[]) {
  char variable = str[0];
  int sign = 1;

  if (str[0] == '-' || str[0] == '+') {
    variable = str[1];
    if (str[0] == '-') {
      sign = -1;
    }
  }

  PushVal(GetVar(variable) * sign);

  if (str[0] != '@') {
    last_var = str[0];
  }
}

// This function is a bit hideous but I think a more sophisticated solution is a
// bit overkill for this exercise...
static void ProcessSymbol(char str[]) {
  int sign = 1;
  double op2;
  char* s_start_ptr = str;

  // Set sign, move string start to after sign
  if (strlen(str) > 1) {
    if (str[0] == '-') {
      sign = -1;
      str = &str[1];
    } else if (str[0] == '+') {
      str = &str[1];
    }
  }

  // Variable assignment
  if (strcmp(str, "=") == 0) {
    if (last_var != '\0') {
      double prev_value = GetVar(last_var);
      double new_value = PopVal();
      if (prev_value == new_value) {
        new_value = PopVal();
      }
      SetVar(last_var, new_value);
      PushVal(new_value);
      last_var = '\0';
    } else {
      printf("error: variable missing\n");
    }
  }
  // Standard operations
  else if (strcmp(str, "+") == 0) {
    PushVal(PopVal() + PopVal());
  } else if (strcmp(str, "*") == 0) {
    PushVal(PopVal() * PopVal());
  } else if (strcmp(str, "-") == 0) {
    op2 = PopVal();
    PushVal(PopVal() - op2);
  } else if (strcmp(str, "/") == 0) {
    op2 = PopVal();
    if (fabs(op2) > EPSILON) {
      PushVal(PopVal() / op2);
    } else {
      printf("error: zero ulus\n");
    }
  } else if (strcmp(str, "%") == 0) {
    op2 = PopVal();
    if (fabs(op2) > EPSILON) {
      PushVal((int)PopVal() % (int)op2);
    } else {
      printf("error: zero divisor\n");
    }
  } else if (strcmp(str, "pow") == 0) {
    op2 = PopVal();
    PushVal(pow(PopVal(), op2));
  }
  // Other Operations
  else if (strcmp(str, "sin") == 0) {
    PushVal(sin(PopVal()));
  } else if (strcmp(str, "cos") == 0) {
    PushVal(cos(PopVal()));
  } else if (strcmp(str, "tan") == 0) {
    PushVal(tan(PopVal()));
  } else if (strcmp(str, "asin") == 0) {
    PushVal(asin(PopVal()));
  } else if (strcmp(str, "acos") == 0) {
    PushVal(acos(PopVal()));
  } else if (strcmp(str, "atan") == 0) {
    PushVal(atan(PopVal()));
  } else if (strcmp(str, "log") == 0) {
    PushVal(log(PopVal()));
  }
  // Constants
  else if (strcmp(str, "pi") == 0) {
    PushVal(acos(-1) * sign);
  } else if (strcmp(str, "e") == 0) {
    PushVal(exp(1.0) * sign);
  }

  // Return string to original state
  str = s_start_ptr;
}

static int MapCharToVar(char c) { return (c == '@') ? 0 : (c - 'A' + 1); }

static double GetVar(char c) { return variable_map[MapCharToVar(c)]; }

static void SetVar(char c, double f) { variable_map[MapCharToVar(c)] = f; }
