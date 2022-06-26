#include "test_framework/generic_test.h"

int Fibonacci(int n) {
  if (n <= 1) {
    return n;
  }

  int f_minus_1 = 1, f_minus_2 = 0;
  for (int i = 2; i <= n; ++i) {
    int f = f_minus_1 + f_minus_2;
    f_minus_2 = f_minus_1;
    f_minus_1 = f;
  }
  return f_minus_1;
}




int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "fibonacci.cc", "fibonacci.tsv", &Fibonacci,
                         DefaultComparator{}, param_names);
}
