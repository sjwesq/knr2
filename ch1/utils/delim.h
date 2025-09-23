#include <stdbool.h>
#ifndef KNR2_CHAPTER1_UTILS_DELIM_H_
#define KNR2_CHAPTER1_UTILS_DELIM_H_

bool IsDelimOpen(char c);
bool IsDelimClose(char c);
bool IsDelim(char c);
char MatchDelim(char delim);
bool DelimAllowedWithin(char external, char internal);
#endif
