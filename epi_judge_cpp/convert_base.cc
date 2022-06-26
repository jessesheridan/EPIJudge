#include <string>

#include "test_framework/generic_test.h"
using std::string;
string ConvertBase(const string &str, int b1, int b2) {
  if (str.size() < 1 || b1 < 2 || b2 < 2) {
    return {};
  }
  int base10 = accumulate(str.begin() + (str[0] == '-'), str.end() , 0, [b1](int num, char c){
    return num * b1 + (c > '9' ? (c - 'A' + 10) : (c - '0'));
  });

  string result;

  if (base10 == 0) {
    return "0";
  }
  while (base10) {
    int temp = base10 % b2;
    if (temp > 9) {
      result.push_back(temp - 10 + 'A');
    }
    else {
      result.push_back(temp + '0');
    }
    base10 /= b2;
  }

  if (str[0] == '-') {
    result.push_back('-');
  }
  return {result.rbegin(), result.rend()};
}





int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
