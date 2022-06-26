#include "test_framework/generic_test.h"
#include <cstdint>
#include <vector>
using std::vector;

short Parity(unsigned long long x) {
  auto i = 0;
  while (x) {
    if (x & 1) {
      i++;
    }
    x >>= 1;
  }
  if (i % 2) {
    return true; // odd
  }
  return false; // even
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
