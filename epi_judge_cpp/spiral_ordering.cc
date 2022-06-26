#include <vector>
#include <cmath>
#include "test_framework/generic_test.h"
#include <array>
using std::vector;
using std::sqrt;
using std::array;
// [] -> []
// [1] -> [1]
// [[1,2],[3,4]] -> 
vector<int> MatrixInSpiralOrder(vector<vector<int>> square_matrix) {
  const array<array<int, 2>, 4> kShift = {{{0,1}, {1,0}, {0,-1}, {-1,0}}};
  int dir = 0, x = 0, y = 0;
  vector<int> spiral_ordering;

  for (int i = 0; i < square_matrix.size() * square_matrix.size(); ++i) { // 3-3
    spiral_ordering.emplace_back(square_matrix[x][y]); // 1,2,4,3
    square_matrix[x][y] = 0; // [[0,0],[0,0]]
    int next_x = x + kShift[dir][0], next_y = y + kShift[dir][1];// 1,-1
    if (next_x < 0 || next_x >= square_matrix.size() || next_y < 0 || next_y >= square_matrix.size() || square_matrix[next_x][next_y] == 0) {
      dir = (dir + 1) % 4; // 3
      next_x = x + kShift[dir][0], next_y = y + kShift[dir][1];//0,0
    }
    x = next_x, y = next_y; //0,0
  }
  return spiral_ordering;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
