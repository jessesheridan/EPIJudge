#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsPalindromic(const string& str) {
  for (int left = 0, right = str.length()-1; left < right; ++left, --right) {
    if (str[left] != str[right]) {
      return false;
    }
  }
  return true;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic.cc",
                         "is_string_palindromic.tsv", &IsPalindromic,
                         DefaultComparator{}, param_names);
}
