// Write a program to remove all comments from a C program.  Don't forget to
// handle quoted strings and character constants properly. C comments don't
// nest.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"

#define MAX_LINE_LENGTH 1024

static bool DeComment(char in[], char out[], int len, bool in_comment) {
  enum CodeState {
    kInCode,
    kInString,
    kInCComment,
    kInCPPComment,
  };
  enum CodeState state = in_comment ? kInCComment : kInCode;
  bool escape_state = false;
  char char_last = 0;

  int in_index, out_index;
  for (in_index = out_index = 0; out_index < len - 1 && in[in_index] != '\0';
       ++in_index) {
    char char_current = in[in_index];
    char char_next = in[in_index + 1];
    bool output = true;

    switch (state) {
      case kInCComment: {
        // Look for comment end, ignore output
        output = false;
        if (char_current == '/' && char_last == '*') {
          state = kInCode;
        }
        break;
      }
      case kInCPPComment: {
        // ignore til end of line
        output = false;
        if (char_current == '\n') {
          out[out_index++] = char_current;
          state = kInCode;
        }
        break;
      }
      case kInString: {
        // Look for string end, ignore escaped '"', increment out
        output = true;
        if (!escape_state) {
          if (char_current == '\"') {
            state = kInCode;
          }
          if (char_current == '\\') {
            escape_state = true;
          }
        } else {
          escape_state = false;
        }
        break;
      }
      case kInCode: {
        // Check if comment or string started, increment out
        output = true;
        if (char_current == '\"') {
          state = kInString;
        } else if (char_current == '/' && char_next == '*') {
          output = false;
          state = kInCComment;
        } else if (char_current == '/' && char_next == '/') {
          output = false;
          state = kInCPPComment;
        }
      }
    }
    if (output) {
      out[out_index++] = char_current;
    }
    char_last = char_current;
  }
  out[out_index] = '\0';

  return state == kInCComment;
}

int main(void) {
  bool in_comment = false;
  char line_current[MAX_LINE_LENGTH];
  char line_buffer[MAX_LINE_LENGTH];

  while ((textGetLine(line_current, MAX_LINE_LENGTH)) > 0) {
    in_comment =
        DeComment(line_current, line_buffer, MAX_LINE_LENGTH, in_comment);
    strncpy(line_current, line_buffer, MAX_LINE_LENGTH);
    printf("%s", line_current);
  }

  return EXIT_SUCCESS;
}
