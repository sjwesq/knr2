#include "valid.h"

#include <stdio.h>

bool IsValidChar(char c) {
  switch (c) {
    case '\n':
    case EOF: {
      return false;
    }
    default: {
      return true;
    }
  }
}

bool IsValidDecimal(char c) {
  switch (c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
      return true;
    }
    default: {
      return false;
    }
  }
}

bool IsValidOctal(char c) {
  switch (c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7': {
      return true;
    }
    default: {
      return false;
    }
  }
}

bool IsValidHexadecimal(char c) {
  switch (c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f': {
      return true;
    }
    default: {
      return false;
    }
  }
}

bool IsValidSingleEscChar(char c) {
  switch (c) {
    case 'a':
    case 'b':
    case 'e':
    case 'f':
    case 'n':
    case 'r':
    case 't':
    case 'v':
    case '\\':
    case '\'':
    case '\"':
    case '?': {
      return true;
    }
    default:
      return false;
  }
}
