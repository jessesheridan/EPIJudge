#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// 1,_ 2 => 1,2
// 1,2,4,6,8,_,_,_,_,_ 1,2,3,5
void MergeTwoSortedArrays(vector<int>& a, int m, const vector<int>& b, int n) {
  int correct_place = m + n - 1;
  int left = m - 1;
  int right = n - 1;
  while (correct_place >= 0) {
    if (left < 0 || (right >= 0 && b[right] > a[left])) {
      a[correct_place] = b[right];
      correct_place--, right--;
    } else {
      a[correct_place] = a[left];
      correct_place--, left--;
    }
  }
}

vector<int> MergeTwoSortedArraysWrapper(vector<int> A, int m,
                                        const vector<int>& B, int n) {
  MergeTwoSortedArrays(A, m, B, n);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "m", "B", "n"};
  return GenericTestMain(
      args, "two_sorted_arrays_merge.cc", "two_sorted_arrays_merge.tsv",
      &MergeTwoSortedArraysWrapper, DefaultComparator{}, param_names);
}
