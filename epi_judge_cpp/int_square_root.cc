#include "test_framework/generic_test.h"


int SquareRoot(int k) {
  int left = 0, right = k;
  while (left <= right) {
    int middle = left + (right - left) / 2;
    if (pow(middle, 2) > k) {
      right = middle - 1;
    } else {
      left = middle + 1;
    }
  }
  return left - 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
