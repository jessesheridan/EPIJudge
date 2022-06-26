#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// 234 * 10 = 100
// 153 
// 702
// 70
// (9,9), (9)  = 81+810 = 891

vector<int> Multiply(vector<int> num1, vector<int> num2) {
  vector<int> result(num1.size()+num2.size(),0); // 2+1=3
  int sign = num1[0] < 0 ^ num2[0] < 0 ? -1 : 1;
  num1[0] = abs(num1[0]); num2[0] = abs(num2[0]);
  
  for (int outer = num1.size() - 1; outer >= 0; --outer) { // 1, 0
    for (int inner = num2.size() - 1; inner >= 0; --inner) { // 0, 0
      int resultNum = num1[outer] * num2[inner]; // 81, 81
      int index = inner + outer + 1;
      result[index] += resultNum; // [0,0,81], [0,89,1]
      int resultDivided = result[index] / 10; // 8, 8
      result[index - 1] += resultDivided; // [0,8,81], [8,89,1]
      result[index] -= resultDivided * 10; // [0,8,1], [8,9,1]
    } // end for
  } // end
  
  while (result[0] == 0 && result.size() > 1) { // false
    result.erase(result.begin());
  }
  result[0] *= sign;
  return result; // [8,9,1]
}






int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
