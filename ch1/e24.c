// Write a program to check a C program for rudimentary syntax errors like
// unmatched parentheses, brackets and braces. Don't forget about quotes, both
// single and double, escape sequences, and comments. (This program is hard if
// you do it in full generality.)
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "delim.h"
#include "stack.h"
#include "text.h"
#include "valid.h"

#define MAX_LINE_LENGTH 1024
#define PREV_STRING_STATE is_char_string ? kInCharString : kInString

bool g_in_c_comment = false;

enum ErrorCodes {
  kWrongEscape,
  kBadHexidecimal,
  kBadUnicode,
  kBadString,
  kBadMatch,
  kNotAllowed,
};

static const char* ErrToStr(enum ErrorCodes e);
static void FindErrors(char str[], int len, StackCharStack* stack_delim_ptr,
                       StackIntStack* stack_err_ptr);

int main(void) {
  char line_current[MAX_LINE_LENGTH];
  int line_number = 1;
  StackCharStack delim_stack;
  StackCharInit(&delim_stack);
  StackIntStack err_stack;
  StackIntInit(&err_stack);

  while ((textGetLine(line_current, MAX_LINE_LENGTH)) > 0) {
    FindErrors(line_current, MAX_LINE_LENGTH, &delim_stack, &err_stack);
    while (!StackIntIsEmpty(&err_stack)) {
      enum ErrorCodes error_now = (enum ErrorCodes)StackIntPop(&err_stack);
      printf("[ERROR] line %d:%s\n", line_number, ErrToStr(error_now));
    }
    ++line_number;
  }
  while (!StackCharIsEmpty(&delim_stack)) {
    printf("[ERROR] EOF:%s\n", ErrToStr(kBadMatch));
    StackCharPop(&delim_stack);
  }

  return EXIT_SUCCESS;
}

static const char* ErrToStr(enum ErrorCodes e) {
  switch (e) {
    case kWrongEscape: {
      return "Bad escape character";
    }
    case kBadHexidecimal: {
      return "Invalid hexadecimal";
    }
    case kBadUnicode: {
      return "Incorrect UTF-8 sequence";
    }
    case kBadString: {
      return "Malformed string";
    }
    case kBadMatch: {
      return "Unmatched delimiters";
    }
    case kNotAllowed: {
      return "Incorrect delimiter precedence";
    }
    default: {
      return "idk lol";
    }
  }
}

static void FindErrors(char str[], int len, StackCharStack* stack_delim_ptr,
                       StackIntStack* stack_err_ptr) {
  enum EscapeState {
    kInCode,
    kInCComment,
    kInCPPComment,
    kInString,
    kInCharString,
    kEscStart,
    kEscOctal,
    kEscHexadecimal,
    kEscUnicode,
  };
  enum EscapeState state = g_in_c_comment ? kInCComment : kInCode;
  int esc_pos = 0;
  char unicode_type;
  bool is_char_string;

  char c_now = 0, c_prev = 0;
  for (int i = 0; i < len && IsValidChar(str[i]); ++i) {
    c_now = str[i];
    switch (state) {
      case kInCode: {
        // String States
        if (c_now == '\"') {
          is_char_string = false;
          state = kInString;
        } else if (c_now == '\'') {
          is_char_string = true;
          state = kInCharString;
        }
        // Comment States
        else if (c_now == '*' && c_prev == '/') {
          g_in_c_comment = true;
          state = kInCComment;
        } else if (c_now == '/' && c_prev == '/') {
          state = kInCPPComment;
        }
        // Delimiter Management
        // TODO: This probably needs to be extracted but I'm tired and it works
        else if (IsDelim(c_now)) {
          char delim_prev = StackCharPeek(stack_delim_ptr);
          if (IsDelimOpen(c_now)) {
            if (!DelimAllowedWithin(delim_prev, c_now)) {
              StackIntPush(stack_err_ptr, kNotAllowed);
            } else {
              StackCharPush(stack_delim_ptr, c_now);
            }
          } else if (IsDelimClose(c_now)) {
            if (delim_prev == MatchDelim(c_now)) {
              StackCharPop(stack_delim_ptr);
            } else {
              StackIntPush(stack_err_ptr, kBadMatch);
            }
          }
        }
        break;
      }
      case kInCComment: {
        if (c_now == '/' && c_prev == '*') {
          g_in_c_comment = false;
          state = kInCode;
        }
        break;
      }
      case kInCPPComment: {
        if (c_now == '\n') {
          state = kInCode;
        }
        break;
      }
      case kInString: {
        if (c_now == '\\') {
          state = kEscStart;
        } else if (c_now == '\"') {
          state = kInCode;
        }
        break;
      }
      case kInCharString: {
        if (c_now == '\\') {
          state = kEscStart;
        } else if (c_now == '\'') {
          state = kInCode;
        }
        break;
      }
      case kEscStart: {
        esc_pos = 0;
        if (IsValidSingleEscChar(c_now)) {
          state = PREV_STRING_STATE;
        } else if (IsValidOctal(c_now)) {
          state = kEscOctal;
        } else if (c_now == 'x') {
          state = kEscHexadecimal;
        } else if (c_now == 'u' || c_now == 'U') {
          unicode_type = c_now;
          state = kEscUnicode;
        } else {
          StackIntPush(stack_err_ptr, kWrongEscape);
          state = PREV_STRING_STATE;
        }
        break;
      }
      case kEscOctal: {
        // Recall zero-indexed and first char already processed
        if (!IsValidOctal(c_now) || esc_pos < 2) {
          --i;
          state = PREV_STRING_STATE;
        }
        ++esc_pos;
        break;
      }
      case kEscHexadecimal: {
        if (!IsValidHexadecimal(c_now)) {
          if (esc_pos == 0) {
            StackIntPush(stack_err_ptr, kBadHexidecimal);
          }
          --i;
          state = PREV_STRING_STATE;
        }
        ++esc_pos;
        break;
      }
      case kEscUnicode: {
        if (!IsValidHexadecimal(c_now)) {
          // esc_pos is zero-indexed
          if ((unicode_type == 'u' && esc_pos != 4) ||
              (unicode_type == 'U' && esc_pos != 8)) {
            StackIntPush(stack_err_ptr, kBadUnicode);
          }
          --i;
          state = PREV_STRING_STATE;
        } else if ((unicode_type == 'u' && esc_pos >= 4) ||
                   (unicode_type == 'U' && esc_pos >= 8)) {
          state = PREV_STRING_STATE;
        }
        ++esc_pos;
        break;
      }
    }
    c_prev = c_now;
  }

  // End of line checks
  if (state == kInString || state == kInCharString) {
    StackIntPush(stack_err_ptr, kBadString);
  }
  while (StackCharPeek(stack_delim_ptr) == '(' ||
         StackCharPeek(stack_delim_ptr) == '[') {
    StackIntPush(stack_err_ptr, kBadMatch);
    StackCharPop(stack_delim_ptr);
  }
}
