#include <cstdint>
#include <iostream>
#include "test_framework/generic_test.h"

uint64_t Add(uint64_t a, uint64_t b) {
  while (b) {
    uint64_t carry = (a&b) << 1; 
    a = a^b;
    b = carry;
  }
  return a;
}

// left shift a based on b's bit position for each bit set in b and then accumulate the result in a sum, return the sum
uint64_t Multiply(uint64_t a, uint64_t b) {
  uint64_t r = 0;
  while (b) {
    if (b&1) {
      r = Add(r, a);
    }
    b >>= 1;
    a <<= 1;
  }
  return r;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "primitive_multiply.cc",
                         "primitive_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}