#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::unordered_set;
// Check if a partially filled matrix has any conflicts.

// check each column for duplicates with a hash set
// reset the hash set after each column
// check each row...
// reset...
// check top row 0,0 0,1 0,2 2nd row 1,0 3rd row 2,0  1,1 1,2 2,1 2,2
// [. . .]
//  . . .
//  . . .
// row start=0, row end = 2, col start = 0, col end = 2
// increment columns to end, then increment row and reset column to col start
// repeat until col end and row end
// [[1,1,1,1,1,1,1,1,1], [1,1,1,1,1,1,1,1,1], ... ] -> false
// zeros -> returns true
// zeros have a problem -> fixed by checking for zero
bool HasDuplicates(int value, unordered_set<int> &value_tracking) {
  if (value > 0 && value_tracking.find(value) != value_tracking.end()) {
        return true;
  }
  value_tracking.insert(value);
  return false;
}

bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
  for (auto i = 0; i < 9; ++i) {
    unordered_set<int> found_so_far;
    for (auto j = 0; j < 9; ++j) { // [0,0] [0,1] [0,2]
      if (HasDuplicates(partial_assignment[i][j], found_so_far)) {
        return false;
      }
    }
  }
  for (auto j = 0; j < 9; ++j) {
    unordered_set<int> found_so_far;
    for (auto i = 0; i < 9; ++i) {
      if (HasDuplicates(partial_assignment[i][j], found_so_far)) {
        return false;
      }
    }
  }

  for (auto row_start = 0; row_start < 9; row_start += 3) {
    for (auto col_start = 0; col_start < 9; col_start += 3) {
      unordered_set<int> found_so_far;
      for (auto i = row_start; i < row_start+3; ++i) {
        for (auto j = col_start; j < col_start+3; ++j) {
          if (HasDuplicates(partial_assignment[i][j], found_so_far)) {
            return false;
          }
        }
      }
    }
  }

  return true;
}




int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
