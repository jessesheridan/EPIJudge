#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
#include <vector>
#include <queue>
using std::vector; using std::priority_queue; using std::function;
vector<int> SortKIncreasingDecreasingArray(const vector<int>& array) {
  struct Set {
    int start, end;
    bool increasing;
  };
  vector<Set> sets;
  int start = 0;
  bool increasing = true;
  for (int i = 1; i < array.size(); ++i) {
    if (increasing && array[i-1] > array[i]) {
      Set set{start, i-1, true};
      sets.emplace_back(set);
      start = i;
      increasing = false;
    } else if (!increasing && array[i-1] < array[i]) {
      Set set {i-1, start, false};
      sets.emplace_back(set);
      start = i;
      increasing = true;
    }
  }
  
  priority_queue<Set, vector<Set>, function<bool(Set, Set)>> min_heap([&](const Set& a, const Set& b) {
    return array[a.start] >= array[b.start];
  });

  for (auto set : sets) {
    min_heap.push(set);
  }

  vector<int> result;
  while (!min_heap.empty()) {
    auto min = min_heap.top();
    min_heap.pop();
    if (min.start != min.end) {
      if (min.increasing) {
        min.start++;
      } else {
        min.start--;
      }
      min_heap.push(min);
    }
    result.push_back(array[min.start]);
  }
  return result;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "sort_increasing_decreasing_array.cc",
                         "sort_increasing_decreasing_array.tsv",
                         &SortKIncreasingDecreasingArray, DefaultComparator{},
                         param_names);
}
