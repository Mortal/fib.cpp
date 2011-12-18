#include "fib.h"

/* now, let's evaluate fib N times at compile time and store the
 * result in an array. */
/* {{{ */
template<input_t N>
struct fibarrayimpl;

/* if we want to calculate the fibonacci numbers up to 0, it's just the array
 * containing fib(0). */
template<>
struct fibarrayimpl<0> {
  output_t list[0];
  output_t cur;
  inline fibarrayimpl() : cur(fib<0>::val) {}
};

/* otherwise, we calculate the Nth fibonacci number and append the fibonacci
 * numbers N-1, N-2 down to 0. */
template<input_t N>
struct fibarrayimpl {
  output_t list[0];
  fibarrayimpl<N-1> rest; // this resembles a linked list, but is kept
                          // sequentially in memory
  output_t cur;
  inline fibarrayimpl() : cur(fib<N>::val) {}
  inline output_t operator[](input_t n) {return list[n];}
};
/* }}} */

/* generating the array of fibonacci numbers isn't enough. we can also find the
 * fibonacci number by binary search. */
/* {{{ */

// lo inclusive, hi exclusive
template<input_t lo, input_t hi>
struct fibsearcher {
  static const input_t mid = lo+(hi-lo)/2;
  static inline output_t find(input_t n) {
    if (lo == hi-1) // base case
      return fib<lo>::val; // lo is a compile time constant, unlike n,
                           // even though n == lo in this case

    else if (n < mid)
      return fibsearcher<lo,mid>::find(n);

    else
      return fibsearcher<mid,hi>::find(n);
  }
};
/* }}} */


static fibarrayimpl<max> fibarrayholder;

output_t fibarray(input_t n) {
  return fibarrayholder[n];
}

/* initiate the search. we require n <= N. */
output_t fibsearch(input_t n) {
  return fibsearcher<0,max+1>::find(n);
}
// vim:set sw=2 ts=8 sts=2:
