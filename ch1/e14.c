/* Write a program to print a histogram of the frequencies of different
 * characters in its input */
#include <stdio.h>
#include <stdlib.h>

static void PrintBars(const int amount) {
  for (int i = 0; i < amount; ++i) {
    printf("|");
  }
}

/* Takes an array of labels and another of correlated values and creates a
 * histogram. The lengths of each array are presumed to be the same. */
static void PrintHistogramCharacters(const char label_arr[],
                                     const int value_arr[], const int arr_len) {
  for (int i = 0; i < arr_len; ++i) {
    /* Skip empty entries */
    if (value_arr[i] <= 0) continue;
    if (i < arr_len - 1) {
      printf("%c:", label_arr[i]);
    } else {
      printf("OTHER:");
    }
    PrintBars(value_arr[i]);
    printf("\n");
  }
}

int main(void) {
  enum {
    kCharFirst = ' ',
    kCharLast = '~',
    kArrSize = (kCharLast - kCharFirst + 2)
  };
  int char_input;
  int char_tally[kArrSize] = {0};
  char char_labels[kArrSize];

  for (char i = kCharFirst; i <= kCharLast; ++i) {
    char_labels[i - kCharFirst] = i;
  }

  while ((char_input = getchar()) != EOF) {
    if (char_input >= kCharFirst && char_input <= kCharLast) {
      ++char_tally[char_input - kCharFirst];
    } else {
      /* Overflow */
      ++char_tally[kArrSize - 1];
    }
  }

  PrintHistogramCharacters(char_labels, char_tally, kArrSize);

  return EXIT_SUCCESS;
}
