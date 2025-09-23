#include "stack.h"

#define FAILCHAR -1
#define FAILINT -1

void StackCharInit(StackCharStack* s) {
  s->top = -1;
  for (int i = 0; i < UTILS_STACK_MAX_SIZE; ++i) {
    s->data[i] = 0;
  }
}

char StackCharPop(StackCharStack* s) {
  if (s->top > -1) {
    return s->data[s->top--];
  } else {
    return FAILCHAR;
  }
}

bool StackCharPush(StackCharStack* s, char c) {
  if (s->top < UTILS_STACK_MAX_SIZE - 1) {
    s->data[++s->top] = c;
    return true;  // success
  } else {
    return false;
  }
}

char StackCharPeek(StackCharStack* s) {
  if (s->top > -1) {
    return s->data[s->top];
  }
  return FAILCHAR;
}

bool StackCharIsEmpty(StackCharStack* s) {
  if (s->top < 0) {
    return true;
  } else {
    return false;
  }
}

void StackIntInit(StackIntStack* s) {
  s->top = -1;
  for (int i = 0; i < UTILS_STACK_MAX_SIZE; ++i) {
    s->data[i] = 0;
  }
}

int StackIntPop(StackIntStack* s) {
  if (s->top > -1) {
    return s->data[s->top--];
  } else {
    return FAILINT;
  }
}

bool StackIntPush(StackIntStack* s, int c) {
  if (s->top < UTILS_STACK_MAX_SIZE - 1) {
    s->data[++s->top] = c;
    return true;  // success
  } else {
    return false;
  }
}

int StackIntPeek(StackIntStack* s) {
  if (s->top > -1) {
    return s->data[s->top];
  }
  return FAILINT;
}

bool StackIntIsEmpty(StackIntStack* s) {
  if (s->top < 0) {
    return true;
  } else {
    return false;
  }
}
