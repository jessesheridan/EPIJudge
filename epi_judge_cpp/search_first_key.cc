#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& array, int key) {
  int lower, middle, upper;
  lower = 0, upper = array.size() - 1; // 5
  while (lower <= upper) { // 0 <= 5
    middle = lower + (upper - lower) / 2; // 2
    if (array[middle] == key) {
      if (middle > 0 && array[middle-1] == key) {
        upper = middle - 1;
      } else {
        return middle;
      }
    } else if (array[middle] > key) {
      upper = middle - 1;
    } else {
      lower = middle + 1;
    }
  }

  return -1;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
