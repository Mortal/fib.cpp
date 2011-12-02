/* input should be in the range {0,1,2,...,max} */
typedef unsigned int input_t;

/* output can be very large */
typedef unsigned long long output_t;

output_t fibarray(input_t n);
output_t fibsearch(input_t n);

/* now, let's calculate the Nth fibonacci number, where N is known at compile
 * time. */
/* {{{ */
template<input_t N>
struct fib;

/* fib(0) = 0 */
template<>
struct fib<0> {
  const static output_t val = 0;
};

/* fib(1) = 1 */
template<>
struct fib<1> {
  const static output_t val = 1;
};

/* fib(N) = fib(N-2) + fib(N-1) */
template<input_t N>
struct fib {
  const static output_t val = fib<N-2>::val + fib<N-1>::val;
};
/* }}} */

/* what is the largest fibonacci number that output_t can represent?
 * let's make the compiler find out for us. */
/* {{{ */
template<input_t N, bool isbad>
struct badfib;

template<input_t N>
struct badfib<N, true> {
  const static input_t val = N;
};

template<input_t N, bool isbad>
struct badfib {
  const static bool bad = (fib<N>::val >= fib<N+1>::val);
  const static input_t val = bad ? N : badfib<bad ? N : N+1, bad>::val;
};

/* maximum input */
static const input_t max = badfib<2, false>::val;
// results:
// fib(186) is the greatest fibonacci number less than 2^128
// fib(93) is the greatest fibonacci number less than 2^64
// fib(47) is the greatest fibonacci number less that 2^32
// fib(24) is the greatest fibonacci number less that 2^16
// fib(13) is the greatest fibonacci number less that 2^8

/* }}} */
