#include "fib.h"
#include "tctc.h"

static tctc<input_t, output_t, max, fib> tctcfib;

static tctc<input_t, output_t, max, fib>::array fibarrayholder;

output_t fibarray(input_t n) {
  return fibarrayholder[n];
}

/* initiate the search. we require n <= N. */
output_t fibsearch(input_t n) {
  return tctcfib.binarysearch(n);
}
// vim:set sw=2 ts=8 sts=2:
