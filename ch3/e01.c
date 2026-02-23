// // binsearch: find x in v[0] <= v[1] <= ... v[n-1]
// int binsearch(int x, int v[], int n) {
//   int low, high, mid;
//
//   low = 0;
//   high = n - 1;
//   while (low <= high) {
//     mid = (low + high) / 2;
//     if (x < v[mid])
//       high = mid - 1;
//     else if (x > v[mid])
//       low = mid + 1;
//     else // found match
//       return mid;
//   }
//   return -1; // no match
// }
//
// Our binary search makes two tests inside the loop, when one would suffice (at
// the price of more tests outside.) Write a version with only one test inside
// the loop and measure the difference in runtime.
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>
#define TEST_ARR_SIZE 10000

static int BinSearchOld(int x, int v[], int n);
static int BinSearchNew(int x, int v[], int n);
static double GetSeconds(clock_t begin, clock_t end);
static void TimeBinSearch(int arr[], int arr_size,
                          int (*bfunc)(int, int[], int));

int main(void) {
  int nums[TEST_ARR_SIZE];
  for (int i = 0; i < TEST_ARR_SIZE; ++i) {
    nums[i] = i;
  }

  printf("BinSearchOld ");
  TimeBinSearch(nums, TEST_ARR_SIZE, BinSearchOld);
  printf("BinSearchNew ");
  TimeBinSearch(nums, TEST_ARR_SIZE, BinSearchNew);

  return EXIT_SUCCESS;
}

// binsearch: find x in v[0] <= v[1] <= ... v[n-1]
static int BinSearchOld(int x, int v[], int n) {
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else
      return mid;
  }
  return -1;  // no match
}

static int BinSearchNew(int x, int arr[], int end) {
  int low = 0;
  int high = end - 1;
  int mid = (low + high) / 2;

  while (low <= high && x != arr[mid]) {
    if (x < arr[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
    mid = (low + high) / 2;
  }
  return (x == arr[mid]) ? mid : -1;  // no match
}

static double GetSeconds(clock_t begin, clock_t end) {
  return (double)(end - begin) / CLOCKS_PER_SEC;
}

// I did this for fun but basically the time difference is so insignificant that
// it's essentially not measurable
static void TimeBinSearch(int arr[], int arr_size,
                          int (*search_fn)(int, int[], int)) {
  const int kNumTrials = 256;
  double avg_time = 0.0;

  for (int i = 0; i < kNumTrials; ++i) {
    clock_t begin = clock();
    for (int j = 0; j < arr_size; ++j) {
      search_fn(j, arr, arr_size);
    }
    clock_t end = clock();
    avg_time += GetSeconds(begin, end);
  }

  printf("avg: (%d elements x %d trials): %.8fs\n", arr_size, kNumTrials,
         (avg_time / kNumTrials));
}
