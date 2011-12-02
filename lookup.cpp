#include <iostream>
#include <csignal>
#include <cstdlib>

#include "fib.h"

/* by default, we cannot output 128 bit integers. implement the output
 * operator. */
/* {{{ */
std::ostream & operator<<(std::ostream & in, unsigned __int128 v) {
  if (v <= 0xFFFFFFFFFFFFFFFF) {
    return in << (unsigned long long) v;
  }
  char c[100];
  char *x = c+100;
  *x = 0;
  while (v) {
    *--x = '0'+(v%10);
    v /= 10;
  }
  return in << x;
}
/* }}} */

/* Speed testing. */
/* {{{ */
static volatile size_t calcs = 0;

void sighandler(int sig) {
  std::cout << calcs << std::endl;
  exit(0);
}

typedef output_t fib_fn(input_t);

void speed(fib_fn & t) {
  signal(SIGINT, sighandler);
  signal(SIGTERM, sighandler);
  output_t i = 2;
  for (;;) {
    i = t(2+(i % (max-2)));
    ++calcs;
  }
}
/* }}} */

int main(int argc, char ** argv) {
  if (argc > 1 && std::string(argv[1]) == "speedarray") {
    speed(fibarray);
  } else if (argc > 1 && std::string(argv[1]) == "speedsearch") {
    speed(fibsearch);
  }
  input_t i;
  while (std::cin >> i) {
    if (i > max) {
      std::cout << "Input out of range (0 to " << max << ")" << std::endl;
      continue;
    }

    std::cout << fibarray(i) << std::endl;
    //std::cout << fibsearch(i) << std::endl;

    if (fibarray(i) != fibsearch(i)) *((char*)42)='*'; // segfault
  }
}
// vim:set sw=2 ts=8 sts=2:
