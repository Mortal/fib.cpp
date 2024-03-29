/* Templated compile-time calculator (TCTC)
 * Mathias Rav, December 18, 2011
 */
template <typename output_t, template <input_t N> class calc, input_t N>
struct partialarray;

template <typename output_t, template <input_t N> class calc>
struct partialarray<output_t, calc, 0> {
  output_t cur;
  inline partialarray() : cur(calc<0>::val) {}
};

template <typename output_t, template <input_t N> class calc, input_t N>
struct partialarray {
  partialarray<output_t, calc, N-1> rest;
  output_t cur;
  inline partialarray() : cur(calc<N>::val) {}
};

template <typename input_t, typename output_t, input_t max, template <input_t N> class calc>
struct tctc {
  template <input_t lo, input_t hi>
  struct binarysearcher {
    static const input_t mid = lo+(hi-lo)/2;
    static inline output_t find(input_t n) {
      if (lo == hi-1) // base case
	return calc<lo>::val; // lo is a compile time constant, unlike n,
	                      // even though n == lo in this case

      else if (n < mid)
	return binarysearcher<lo,mid>::find(n);

      else
	return binarysearcher<mid,hi>::find(n);
    }
  };
  static output_t binarysearch(input_t n) {
    return binarysearcher<0, max+1>::find(n);
  }

  template <input_t lo, input_t hi, bool terminate = false>
  struct linearsearcher {
    static inline output_t find(input_t n, output_t def) {
      switch (n) {
	case lo+0: return calc<lo+0>::val;
	case lo+1: return calc<lo+1>::val;
	case lo+2: return calc<lo+2>::val;
	case lo+3: return calc<lo+3>::val;
	case lo+4: return calc<lo+4>::val;
	case lo+5: return calc<lo+5>::val;
	case lo+6: return calc<lo+6>::val;
	case lo+7: return calc<lo+7>::val;
	default:
	  return linearsearcher<lo+8, hi, lo+8 >= hi>::find(n, def);
      }
    }
  };

  template <input_t lo, input_t hi>
  struct linearsearcher<lo, hi, true> {
    static inline output_t find(input_t, output_t def) {
      return def;
    }
  };

  static output_t linearsearch(input_t n, output_t def = 0) {
    return linearsearcher<0, max>::find(n, def);
  }

  struct array {
    output_t list[0];
    partialarray<output_t, calc, max> array;
    inline output_t operator[](input_t n) {
      return list[n];
    }
  };
};
// vim:set sw=2 ts=8 sts=2:
