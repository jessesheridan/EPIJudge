#include <string>

#include "test_framework/generic_test.h"
using std::string;

#include <vector>
#include <cstdint>
using std::vector; using std::string;
vector<int> CreatePatternLUT(const string& s);
// 4,000,000,000 will be 5 characters, so doubling it to 64-bit and we get 10
// GACGCCA, CGC
//          (((3*53)+7)*53)+3
int CharToInt(const char ch) {
  if (ch >= 'a') {
    return ch - 'a' + 26 + 1;
  }
  return ch - 'A' + 1;
}

int RabinKarp(const string& t, const string& s) {
  // Create hash of pattern (s) assuming only a-zA-Z alphabet
  uint64_t pattern_hash = 0;
  for (int i = 0; i < s.size(); ++i) {
    pattern_hash = pattern_hash * 56 + CharToInt(s[i]);
  }
  uint64_t oldest_power = 1;
  for (int i = 1; i < s.size(); ++i) {
    oldest_power = oldest_power * 56;
  }
  uint64_t rolling_hash = 0;
  // create rolling hash of text (t) and compare to pattern hash (s hash)
  for (int i = 0; i < s.size() && i < t.size(); ++i) {
    rolling_hash = rolling_hash * 56 + CharToInt(t[i]);
  }
  if (rolling_hash == pattern_hash) {
    return 0;
  }
  for (int i = 0, j = s.size(); j < t.size(); ++i, ++j) {
    rolling_hash = ((rolling_hash - CharToInt(t[i]) * oldest_power) * 56) + CharToInt(t[j]);
    if (rolling_hash == pattern_hash) {
      return i+1;
    }
  }
  return -1;
}


int KMP(const string& t, const string& s) {
  vector<int> lut = CreatePatternLUT(s);
  int str_idx = 0, text_idx = 0;
  for (int text_start = 0; text_start < t.size(); ++text_start) {
    while (str_idx < s.size() && text_idx < t.size() && t[text_idx] == s[str_idx]) {
      text_idx++; str_idx++;
    }
    if (str_idx == s.size()) {
      return text_start;
    } else if (str_idx > 0 && text_idx < t.size()) {
      int orig_str_idx = str_idx;
      str_idx = lut[str_idx-1];
      while (str_idx > 0 && s[str_idx] != t[text_idx]) {
        str_idx = lut[str_idx - 1];
      }
      if (orig_str_idx > str_idx) {
        text_start += orig_str_idx - str_idx - 1;
      }
    } else if (text_idx < t.size()) {
      text_idx = text_start+1;
    }
  }
  return -1;
}

vector<int> CreatePatternLUT(const string& s) {
  int left = 0, right = 1, count = 0;
  vector<int> lut(s.size(), 0);
  while (right < s.size()) {
    if (s[left] != s[right]) {
      count = 0;
      left = 0;
    }
    if (s[left] == s[right]) {
      lut[right] = ++count;
      ++left;
    }
    ++right;
  }
  return lut;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"t", "s"};
  return GenericTestMain(args, "substring_match.cc", "substring_match.tsv",
                         &RabinKarp, DefaultComparator{}, param_names);
}
