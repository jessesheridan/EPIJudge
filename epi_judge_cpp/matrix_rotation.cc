#include <vector>
#include <algorithm>

#include "test_framework/generic_test.h"
using std::vector;
using std::swap;
// 7,4,1,5
// 8,5,2,6
// 9,6,3,7
// 9,1,2,3
// loop n/2 times: (rings)
//   store start and end
//   loop n-1 times: (each element in a row)
//     set destination to end with column set to end + i
//     loop 3 times: (swap & rotate destination)
//       swap start with destination
//       rotate destination
// dest= 0,3 3,3 3,0
//       1,3 3,2 2,0
//       s+i,e e,end-i, e-i,s
//       start+i,end end,end-i end-i,start
// [] -> left alone
// [1] -> left alone
// [1,2][3,4] 1,2 -> 3,1
//            3,4    4,2
// 1,2,3 4,5,6 7,8,9 // only one ring
// 1,2,3,4
// 4,5,6,4
// 7,8,9,4   
// 1,2,3,4       
void RotateMatrix(vector<vector<int>>* square_matrix_ptr) {
  vector<vector<int>> &square = *square_matrix_ptr;
  for (int ring = 0; ring < static_cast<int>(square.size()/2); ++ring) { //0-1
    const int start = ring; // 1
    const int end = square.size() - 1 - ring; // 2
    for (int i = 0; i < end-start; ++i) { // 1
      int &upper_left = square[start][start+i]; 
      int &upper_right = square[start+i][end];
      int &lower_right = square[end][end-i];
      int &lower_left = square[end-i][start];

      swap(upper_left, upper_right); // 1,1 1,2
      swap(upper_left, lower_right); // 1,1 2,2
      swap(upper_left, lower_left); // 1,1 2,1
    }
  }
}




vector<vector<int>> RotateMatrixWrapper(vector<vector<int>> square_matrix) {
  RotateMatrix(&square_matrix);
  return square_matrix;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "matrix_rotation.cc", "matrix_rotation.tsv",
                         &RotateMatrixWrapper, DefaultComparator{},
                         param_names);
}
