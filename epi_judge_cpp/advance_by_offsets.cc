#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::max;
bool CanReachEnd(const vector<int>& max_advance_steps) {
  int last_index = max_advance_steps.size() - 1;
  int max_index = 0;
  for (int i = 0; i <= max_index && max_index < last_index; ++i) {
    max_index = max(max_index, max_advance_steps[i] + i);
  }
  return max_index >= last_index;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"max_advance_steps"};
  return GenericTestMain(args, "advance_by_offsets.cc",
                         "advance_by_offsets.tsv", &CanReachEnd,
                         DefaultComparator{}, param_names);
}
