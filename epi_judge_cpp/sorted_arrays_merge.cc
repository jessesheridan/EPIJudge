#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
#include <queue>
#include <vector>
using std::priority_queue; using std::greater; using std::vector; using std::function;
vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  struct sequence_data {
    size_t seq_idx;
    size_t value_idx;
    int value;
  };
  priority_queue<sequence_data, vector<sequence_data>, function<bool(sequence_data, sequence_data)>> min_heap([](const sequence_data a, const sequence_data b) {
    return a.value >= b.value;
  });
  vector<int> result;
  for (size_t i = 0; i < sorted_arrays.size(); ++i) {
    min_heap.emplace(sequence_data{i, 0, sorted_arrays[i][0]});
  }
  while (!min_heap.empty()) {
    auto min = min_heap.top();
    min_heap.pop();
    result.emplace_back(min.value);
    if (min.value_idx + 1 < sorted_arrays[min.seq_idx].size())    
    {
      min_heap.emplace(sequence_data{min.seq_idx, min.value_idx + 1, sorted_arrays[min.seq_idx][min.value_idx + 1]});
    }
  }

  return result;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
