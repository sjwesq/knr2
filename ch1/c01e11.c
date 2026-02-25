/* How would you test the word count program? What kinds of input are most
 * likely to uncover bugs if there are any? */

/* Much like testing any program, you would want to create a series of inputs
 * with expected outputs, trying to cover as many different cases as possible
 * including those that are most likely to cause errors. As this program is
 * written, it might be easier overall to do that validation with a simple bash
 * script, but it would be more maintainable if the program itself had a way to
 * process test strings.
 *
 * I may revisit this problem later to try this out, but the answer book makes
 * it clear this exercise is intended as a simple word problem. */
#include <stdio.h>
#include <stdlib.h>

#define IN 1
#define OUT 0

/* count lines, words, and characters in input */
int main(void) {
  int c, nl, nw, nc, state;

  state = OUT;
  nl = nw = nc = 0;
  while ((c = getchar()) != EOF) {
    ++nc;
    if (c == '\n') ++nl;
    if (c == ' ' || c == '\n' || c == '\t')
      state = OUT;
    else if (state == OUT) {
      state = IN;
      ++nw;
    }
  }
  printf("%d %d %d\n", nl, nw, nc);

  return EXIT_SUCCESS;
}
