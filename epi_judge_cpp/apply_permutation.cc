#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::swap;
// [1,0,3,4,2]
void ApplyPermutation(vector<int> perm, vector<int>* A_ptr) {
  vector<int> &array = *A_ptr;
  for(size_t i = 0; i < perm.size(); ++i) { 
    size_t j = 0;
    while (perm[j] != i) {
      j++; 
    }
    while (j < i) { 
      for (size_t k = 0; k < perm.size(); ++k) {
        if (perm[k] == j) {
          j = k;
          break;
        }
      }
    }
    if (j > i) {
      swap(array[j], array[i]);
    }
  }
}




vector<int> ApplyPermutationWrapper(const vector<int>& perm, vector<int> A) {
  ApplyPermutation(perm, &A);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm", "A"};
  return GenericTestMain(args, "apply_permutation.cc", "apply_permutation.tsv",
                         &ApplyPermutationWrapper, DefaultComparator{},
                         param_names);
}
