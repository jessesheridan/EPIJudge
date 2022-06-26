#include "test_framework/generic_test.h"
unsigned long long ReverseBits(unsigned long long x) {
  uint64_t rev = 0;
  for (auto i = 0; i < sizeof(unsigned long long)*8; ++i) {
    rev <<= 1;
    rev |= x&1;
    x >>= 1;
  }
  return rev;

}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
