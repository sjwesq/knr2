#ifndef KNR2_CHAPTER1_UTILS_STACK_H_
#define KNR2_CHAPTER1_UTILS_STACK_H_
#include <stdbool.h>

#define UTILS_STACK_MAX_SIZE 512

// Simple implementation of a stack ADT (`char` version.) Initialize with
// `stackCharinit` function.

typedef struct {
  char data[UTILS_STACK_MAX_SIZE];
  int top;
} StackCharStack;

typedef struct {
  int data[UTILS_STACK_MAX_SIZE];
  int top;
} StackIntStack;

// Initializes an empty stack
void StackCharInit(StackCharStack* s);
// Removes and returns char from top of stack
char StackCharPop(StackCharStack* s);
// Adds a new char to top of stack
bool StackCharPush(StackCharStack* s, char c);
// Returns current char at top of stack without modifying it
char StackCharPeek(StackCharStack* s);
bool StackCharIsEmpty(StackCharStack* s);

// Initializes an empty stack
void StackIntInit(StackIntStack* s);
// Removes and returns int from top of stack
int StackIntPop(StackIntStack* s);
// Adds a new int to top of stack
bool StackIntPush(StackIntStack* s, int c);
// Returns current int at top of stack without modifying it
int StackIntPeek(StackIntStack* s);
bool StackIntIsEmpty(StackIntStack* s);

#endif
