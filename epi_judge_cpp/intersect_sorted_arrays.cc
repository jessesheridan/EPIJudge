#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// 1122344456778, 0113569 => 13
vector<int> IntersectTwoSortedArrays(const vector<int>& a, const vector<int>&b) {
  int left = 0, right = 0;
  vector<int> result;
  while (left < a.size() && right < b.size()) {
    if (a[left] == b[right] && (result.empty() || result.back() != a[left])) {
      result.emplace_back(a[left]);
      left++; right++;
    } else if (a[left] < b[right]) {
      left++;
    } else {
      right++;
    }
  }
  
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
