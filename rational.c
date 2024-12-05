#include "rational.h"

rational_t rational(long n, long d) {
  rational_t result;
  result.num = n;
  result.denom = d;
  return result;
}
