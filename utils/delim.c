#include "delim.h"

bool IsDelimOpen(char c) {
  switch (c) {
    case '(':
    case '[':
    case '{': {
      return true;
    }
    default: {
      return false;
    }
  }
}

bool IsDelimClose(char c) {
  switch (c) {
    case '}':
    case ')':
    case ']': {
      return true;
    }
    default: {
      return false;
    }
  }
}

bool IsDelim(char c) {
  if (IsDelimOpen(c) || IsDelimClose(c)) {
    return true;
  } else {
    return false;
  }
}

char MatchDelim(char delim) {
  switch (delim) {
    case '(': {
      return ')';
    }
    case ')': {
      return '(';
    }
    case '[': {
      return ']';
    }
    case ']': {
      return '[';
    }
    case '{': {
      return '}';
    }
    case '}': {
      return '{';
    }
    case '\"': {
      return '\"';
    }
    case '\'': {
      return '\'';
    }
    default: {
      return -1;
    }
  }
}

bool DelimAllowedWithin(char external, char internal) {
  if (external == '[' || external == '(') {
    if (internal == '{') {
      return false;
    }
  }
  return true;
}
