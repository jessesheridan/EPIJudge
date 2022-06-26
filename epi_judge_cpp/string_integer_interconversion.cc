#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;
#include <cmath>

#include <cmath>
#include <cmath>
#include <algorithm>
using std::accumulate;
string IntToString(int x) {
  bool is_negative = false;
  if (x < 0) {
    is_negative = true;
  }

  string s;
  do {
    s += '0' + abs(x % 10);
    x /= 10;
  } while (x);

  s += is_negative ? "-" : "";
  return {s.rbegin(), s.rend()};
}

int StringToInt(const string &str) {
  return (str[0] == '-' ? -1 : 1) * accumulate(str.begin() + (str[0] == '-' || str[0] == '+'), str.end(), 0, [](int running_sum, char c) {
    return running_sum * 10 + c - '0';
});
}



void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
