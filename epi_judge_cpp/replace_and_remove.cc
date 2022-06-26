#include <iterator>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;
// count number of a's in the array counting only up to size items, this tells us how far right to shift everything and how big our extra array needs to be
// create extra array
// copy countedAs number of the right hand side into our array
// shift everything else over to the right number a's times
// have index at 0 (left) and right at 0+shift
// put into left the correct letters
// continue where left off and copy contents of buffer correctly into original array
// remove extra b's hanging on the right side of the array
// 0,[] -> 0 []
// 1,[c] -> 1,[c]
// 1,[b] -> 0,[]
// 1,[a] -> 2,[dd]
// 4,abca ->5,[ddcdd]
// 2, ab ->

int ReplaceAndRemove(int size, char s[]) {
  int a_count = 0, write_idx = 0;
  for (int i = 0; i < size; ++i) {
    if (s[i] != 'b') {
      s[write_idx++] = s[i];
    }
    if (s[i] == 'a') {
      ++a_count;
    }
  }
  int cur_idx = write_idx - 1;
  write_idx += a_count - 1;
  const int final_size = write_idx + 1;
  for (;cur_idx >= 0; --cur_idx) {
    if (s[cur_idx] == 'a') {
      s[write_idx--] = 'd';
      s[write_idx--] = 'd';
    }
    else {
      s[write_idx--] = s[cur_idx];
    }
  }

  return final_size;
}


vector<string> ReplaceAndRemoveWrapper(TimedExecutor& executor, int size,
                                       const vector<string>& s) {
  std::vector<char> s_copy(s.size(), '\0');
  for (int i = 0; i < s.size(); ++i) {
    if (!s[i].empty()) {
      s_copy[i] = s[i][0];
    }
  }

  int res_size =
      executor.Run([&] { return ReplaceAndRemove(size, s_copy.data()); });

  vector<string> result;
  for (int i = 0; i < res_size; ++i) {
    result.emplace_back(string(1, s_copy[i]));
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "size", "s"};
  return GenericTestMain(args, "replace_and_remove.cc",
                         "replace_and_remove.tsv", &ReplaceAndRemoveWrapper,
                         DefaultComparator{}, param_names);
}
