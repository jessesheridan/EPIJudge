#include "test_framework/generic_test.h"
double Power(double x, int y) {
  // double r = 1;
  // while (y) {
  //   if (y < 0) {
  //     r *= 1/x;
  //     y++;
  //   }
  //   else {
  //     r *= x;
  //     y--;
  //   }
  // }

  // return r;

  if (x == 0) {
    return 0;
  }
  if (y == 0) {
    return 1;
  }
  if (y == 1) {
    return x;
  }
  if (y == -1) {
    return 1/x;
  }

  double pow = Power(x, y/2); // 2^2=4
  if (y&1) {
    if (y < 0)
    {
      return 1/x * pow * pow;
    }
    return x * pow * pow; // 2 * 2^2 * 2^2 = 2^5
  }
  return pow * pow; // 2^2 * 2^2 = 2^4


}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}
