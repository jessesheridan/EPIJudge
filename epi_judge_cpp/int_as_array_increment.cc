#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// [1,2,9] --> [1,3,0]
// [] --> return the same
// [9] --> [1,0]
vector<int> PlusOne(vector<int> A) {
  int i = A.size() - 1; // 0
  while (i >= 0) // 0
  {
    if (A[i] < 9) { // 9
      A[i] += 1; //
      break;
    }
    A[i] = 0; // [0]
    i--;// 1
  }
  if (i < 0) {
    A.emplace_back(0);
    A[0] = 1;
  }
  return A; // [1,3,0]
}





int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
