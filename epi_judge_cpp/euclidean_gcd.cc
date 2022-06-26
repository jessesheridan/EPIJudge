#include "test_framework/generic_test.h"
// 0, 0
long long Gcd(long long x, long long y) {
  long long max = std::max(x,y);
  long long min = std::min(x,y);
  while (min) {
    long long r = max % min;
    max = min;
    min = r;
  }
  return max;
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "euclidean_gcd.cc", "gcd.tsv", &Gcd,
                         DefaultComparator{}, param_names);
}
