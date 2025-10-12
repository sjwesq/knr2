// An alternate organization uses getline to read an entire input line; this
// makes getch and ungetch unnecessary. Revise the calculator to use this
// approach.

// I simply rewrote GetCh & UngetCh to handle a global string stored by getline.
// All the rest of the logic is intact. This saved me from doing a lot of work.
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"

// Constants

#define TOKEN_MAX_LEN 100
#define VAL_STACK_SIZE 100
#define LINE_MAX_LEN 100
#define EPSILON 1e4 * DBL_EPSILON  // accurate enough to stop divide-by-zero

enum TokenType {
  kTokenIsNumber,
  kTokenIsSymbol,
  kTokenIsVariable,
  kTokenIsNewline,
  kTokenIsInvalid,
};

// Globals

static int sp = 0;                  // next free stack position
static double val[VAL_STACK_SIZE];  // value stack

static char line_input[LINE_MAX_LEN];
static int line_pos = 0;

static double variable_map[27];
static char last_var = '\0';

// Functions

static void StartCalculator(void);

static enum TokenType GetNextToken(char str[]);
static void PushVal(double f);
static double PopVal(void);

static char GetLineCh(void);
static void UngetLineCh(void);
static void MovePastWhitespace(void);
static char* ReadToken(char buf[]);

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
  int line_len = textGetLine(line_input, LINE_MAX_LEN);
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
        line_len = textGetLine(line_input, LINE_MAX_LEN);
        if (line_len == 0) {
          return;
        }
        line_pos = 0;
        break;
      }
    }
  }
}

// get next operator or numeric operand
// `s` serves as a buffer to store the next token
static enum TokenType GetNextToken(char str[]) {
  MovePastWhitespace();

  char* working_str = ReadToken(str);
  char c_first = working_str[0];

  if (isdigit(c_first)) {
    return kTokenIsNumber;
  } else if (isupper(c_first) || c_first == '@') {
    return kTokenIsVariable;
  } else if (isgraph(c_first)) {
    return kTokenIsSymbol;
  } else if (c_first == '\n') {
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
static char GetLineCh(void) {
  if (line_pos < LINE_MAX_LEN && line_pos < (int)strlen(line_input)) {
    return line_input[line_pos++];
  } else {
    return '\n';
  }
}

// push character back on input
static void UngetLineCh(void) {
  if (line_pos > 0) {
    --line_pos;
  }
}

static void MovePastWhitespace(void) {
  char c = GetLineCh();
  while (c == ' ' || c == '\t') {
    c = GetLineCh();
  }
  UngetLineCh();
}

// Reads the next token into buf. A pointer is returned to the start of buf
// (after signs or prefixes are acouunted for.)
static char* ReadToken(char buf[]) {
  char* substr_ptr = buf;

  // Determine if prefixed or not
  buf[0] = GetLineCh();
  if (buf[0] == '-' || buf[0] == '+') {
    char c_tmp = GetLineCh();
    UngetLineCh();
    if (isalnum(c_tmp)) {
      substr_ptr = &buf[1];
    } else {
      buf[1] = '\0';
      return substr_ptr;
    }
  } else if (!isgraph(buf[0])) {
    buf[1] = '\0';
    return substr_ptr;
  }

  int i = 0;
  while (!isspace(buf[++i] = GetLineCh()) && i < TOKEN_MAX_LEN - 3);
  UngetLineCh();
  buf[i] = '\0';

  return substr_ptr;
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
      printf("error: zero divisor\n");
    }
  } else if (strcmp(str, "%") == 0) {
    op2 = PopVal();
    if (fabs(op2) > EPSILON) {
      PushVal((int)PopVal() % (int)op2);
    } else {
      printf("error: zero modulus\n");
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
