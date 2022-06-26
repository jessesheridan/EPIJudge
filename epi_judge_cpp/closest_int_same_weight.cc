#include "test_framework/generic_test.h"
// flip lsb unset x|(x+1) and flip the closest bit to the unset one
// if 2
// 1011 = 1011&1010=1010 ^ 1011|1100=1111 = 0101 ^ 1011 = 1110
unsigned long long ClosestIntSameBitCount(unsigned long long x) {
  unsigned long long unset = (x&~(x-1)), set = ((x+1)^x)&(x+1);
  if (unset > set) {
    return x ^ (unset | unset >> 1);
  }
  return x ^ (set | set >> 1);
}





int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "closest_int_same_weight.cc",
                         "closest_int_same_weight.tsv", &ClosestIntSameBitCount,
                         DefaultComparator{}, param_names);
}
