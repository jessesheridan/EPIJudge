#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<vector<int>> GeneratePascalTriangle(int num_rows) {
  vector<vector<int>> result;
  if (num_rows < 1) {
    return {};
  }
  result.emplace_back(vector<int>(1,1));
  for (int i = 1; i < num_rows; ++i) {
    result.emplace_back(vector<int>());
    for (int left = -1, right = 0; right <= result[i-1].size(); left++, right++) {
      int left_value = 0, right_value = 0;
      if (left >= 0) {
        left_value = result[i-1][left];// [0][1]
      }
      if (right < result[i-1].size()) {
        right_value = result[i-1][right];// result[0][0]
      }
      result[i].emplace_back(left_value+right_value);// 0+1,0+1
    } 
  }
  return result;
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_rows"};
  return GenericTestMain(args, "pascal_triangle.cc", "pascal_triangle.tsv",
                         &GeneratePascalTriangle, DefaultComparator{},
                         param_names);
}
