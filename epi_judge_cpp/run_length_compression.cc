#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;
using std::to_string; using std::stoi;

string Decoding(const string& s) {
  string result;
  int i = 0;
  while (i < s.size()) {
    const size_t char_idx = s.find_first_not_of("0123456789", i);
    const string num_str = s.substr(i, char_idx-i);
    const int length = stoi(num_str);
    result.append(length, s[char_idx]);
    i = char_idx+1;
  }
  return result;
}

string Encoding(const string& s) {
  string result;
  int i = 0;
  while (i < s.size()) {
    size_t next_idx = s.find_first_not_of(s[i], i);
    if (next_idx == string::npos) {
      next_idx = s.size();
    }
    result += to_string(next_idx-i) + s[i];
    i = next_idx;
  }

  return result;
}

void RleTester(const string &encoded, const string &decoded) {
  if (Decoding(encoded) != decoded) {
    throw TestFailure("Decoding failed");
  }
  if (Encoding(decoded) != encoded) {
    throw TestFailure("Encoding failed");
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"encoded", "decoded"};
  return GenericTestMain(args, "run_length_compression.cc",
                         "run_length_compression.tsv", &RleTester,
                         DefaultComparator{}, param_names);
}
