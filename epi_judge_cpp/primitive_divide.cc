#include "test_framework/generic_test.h"
uint32_t Divide(uint32_t a, uint32_t b) {
  uint32_t power = 32;
  uint64_t c = b << power;
  uint64_t multiple = 1 << power;
  uint32_t result = 0;
  while (a >= b) {
    while (c > a) {
      c >>= 1;
      multiple >>= 1;
    }
    a -= c;
    result += multiple;
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "primitive_divide.cc", "primitive_divide.tsv",
                         &Divide, DefaultComparator{}, param_names);
}
