/* Write a program to print a histogram of the frequencies of different
 * characters in its input */
#include <stdio.h>
#include <stdlib.h>

#define CHAR_FIRST_INDEX ' '
#define CHAR_LAST_INDEX '~'
#define HISTOGRAM_ARR_SIZE CHAR_LAST_INDEX - CHAR_FIRST_INDEX + 2

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
  int char_input;
  int char_tally[HISTOGRAM_ARR_SIZE] = {0};
  char char_labels[HISTOGRAM_ARR_SIZE];

  for (char i = CHAR_FIRST_INDEX; i <= CHAR_LAST_INDEX; ++i) {
    char_labels[i - CHAR_FIRST_INDEX] = i;
  }

  while ((char_input = getchar()) != EOF) {
    if (char_input >= CHAR_FIRST_INDEX && char_input <= CHAR_LAST_INDEX) {
      ++char_tally[char_input - CHAR_FIRST_INDEX];
    } else {
      /* Overflow */
      ++char_tally[HISTOGRAM_ARR_SIZE - 1];
    }
  }

  PrintHistogramCharacters(char_labels, char_tally, HISTOGRAM_ARR_SIZE);

  return EXIT_SUCCESS;
}
