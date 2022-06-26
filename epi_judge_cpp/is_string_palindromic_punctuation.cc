#include <string>

#include "test_framework/generic_test.h"
using std::string;
// convert to lower case
// remove non alpha numerics, we want to keep 0-9,a-z
// use two indexes (left and right) and compare incrementing and decrementing them // in each iteration until left > right. If the value at the indexes do not match 
// return false. If we make it to the end return true.
// [],0 -> true
// [a],1 -> true
// [aa],2 -> true
// [AA],2 -> true
// [,.],2 -> true
// 
bool IsPalindrome(const string& s) {
  for (int left = 0, right = s.size() - 1; left < right;) {
    if (s[left] == s[right]) {
      ++left; --right;
      continue;
    }
    if (std::tolower(static_cast<unsigned char>(s[left])) == std::tolower(static_cast<unsigned char>(s[right]))) {
      ++left; --right;
      continue;
    }
    if (!std::isalnum(static_cast<unsigned char>(s[left]))) {
      ++left;
      continue;
    }
    if (!std::isalnum(static_cast<unsigned char>(s[right]))) {
      --right;
      continue;
    }
    return false;
  }

  return true;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
