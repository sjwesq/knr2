/* Write a program to print a histogram of the lengths of words in its input. It
 * is easy to draw the histogram with the bars horizontal; a vertical
 * orientation is more challenging.*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 29

static int GetMaxValue(int* iarr, int len) {
  int max = iarr[0];
  for (int i = 1; i < len; i++) {
    if (iarr[i] > max) {
      max = iarr[i];
    }
  }
  return max;
}

static void HistogramPrintHorizontal(int* iarr, int len) {
  for (int i = 0; i < len; i++) {
    if (iarr[i] > 0) {
      if (i < len - 1)
        printf("%2d:|", i + 1);
      else
        printf("OVERFLOW:");
      for (int j = 0; j < iarr[i]; j++) {
        printf("=");
      }
      printf("|%d\n", iarr[i]);
    }
  }
}

static void HistogramPrintVertical(int* iarr, int len) {
  int height = GetMaxValue(iarr, len);
  for (int i = 0; i < height; i++) {
    printf(" ");
    for (int j = 0; j < len; j++) {
      if (iarr[j] > 0) {
        if ((height - i) > iarr[j])
          printf(" ");
        else
          printf("X");
        printf("  ");
      }
    }
    printf("\n");
  }
  for (int i = 0; i < len; i++) {
    if (iarr[i] > 0) printf("%2d ", i + 1);
  }
  printf("\n");
}

int main(void) {
  int c;
  int word_length = 0;
  int length_occurrences[MAX_WORD_LENGTH] = {0};

  printf("\"");
  while ((c = getchar()) != EOF) {
    putchar(c);
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
      ++word_length;
    } else if (c != '\'' && c != '-') {
      if (word_length > 0) {
        if (word_length < MAX_WORD_LENGTH)
          ++length_occurrences[word_length - 1];
        else
          ++length_occurrences[MAX_WORD_LENGTH - 1];
        word_length = 0;
      }
    }
  }
  if (word_length > 0) {
    if (word_length < MAX_WORD_LENGTH)
      ++length_occurrences[word_length - 1];
    else
      ++length_occurrences[MAX_WORD_LENGTH - 1];
  }
  printf("\"\n");

  HistogramPrintVertical(length_occurrences, MAX_WORD_LENGTH);
  printf("--------------------\n");
  HistogramPrintHorizontal(length_occurrences, MAX_WORD_LENGTH);

  return EXIT_SUCCESS;
}
