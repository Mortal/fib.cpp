#include <iostream>
#include <csignal>
#include <cstdlib>

#include "fib.h"

/* by default, we cannot output 128 bit integers. implement the output
 * operator. */
/* {{{ */
#ifdef FIB128
static std::ostream & operator<<(std::ostream & in, unsigned __int128 v) {
  if (v <= 0xFFFFFFFFFFFFFFFF) {
    return in << (unsigned long long) v;
  }
  char c[100];
  char *x = c+99;
  *x = 0;
  while (v) {
    *--x = '0'+(v%10);
    v /= 10;
  }
  return in << x;
}
#endif
/* }}} */

/* Speed testing. */
/* {{{ */
static volatile size_t calcs = 0;

static void sighandler(int) {
  std::cout << calcs << std::endl;
  exit(0);
}

typedef output_t fib_fn(input_t);

template<unsigned int n0>
struct hibit {
private:
  static const unsigned int n1 = n0 | (n0 >> 1);
  static const unsigned int n2 = n1 | (n1 >> 2);
  static const unsigned int n3 = n2 | (n2 >> 4);
  static const unsigned int n4 = n3 | (n3 >> 8);
  static const unsigned int n5 = n4 | (n4 >> 16);
public:
  static const unsigned int n = n5 - (n5 >> 1);
};

template<fib_fn t>
static void speed() {
  signal(SIGINT, sighandler);
  signal(SIGTERM, sighandler);
  size_t c = calcs;
  output_t i = 2;
  for (;;) {
    i = t(2+i);
    i &= hibit<max-2>::n - 1;
    calcs = ++c;
  }
}
/* }}} */

int main(int argc, char ** argv) {
  if (argc > 1 && std::string(argv[1]) == "speedarray") {
    speed<fibarray>();
  } else if (argc > 1 && std::string(argv[1]) == "speedsearch") {
    speed<fibbinarysearch>();
  } else if (argc > 1 && std::string(argv[1]) == "speedlinear") {
    speed<fiblinearsearch>();
  }
  input_t i;
  while (std::cin >> i) {
    if (i > max) {
      std::cout << "Input out of range (0 to " << max << ")" << std::endl;
      continue;
    }

    output_t fibn = fibarray(i);
    std::cout << fibn << std::endl;

    if (fibn != fibbinarysearch(i)) {
      std::cerr << "fibarray disagrees with fibbinary" << std::endl;
      *((char*)42)='*'; // segfault
    }
    if (fibn != fiblinearsearch(i)) {
      std::cerr << "fibarray disagrees with fiblinear" << std::endl;
      *((char*)42)='*'; // segfault
    }
  }
}
// vim:set sw=2 ts=8 sts=2:
