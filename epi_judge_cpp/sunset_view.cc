#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// null, null => empty vector
// 1, end => 0
// 1,2,3 => 2
// 3,2,1 => 2,1,0
// 1,3,2,4 => 3
// 6,3,4 => 0,2
// buildings will be specified starting from the far east to the west
#include <stack>
using std::stack;
struct Building {
  int id;
  int height;
};
vector<int> ExamineBuildingsWithSunset(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end)
{
  stack<Building> mins;
  int i = 0;
  for (sequence_begin; sequence_begin != sequence_end; ++sequence_begin) {
    if (!mins.empty() && *sequence_begin >= mins.top().height) {
      while (!mins.empty() && *sequence_begin >= mins.top().height) {
        mins.pop();
      }	
    }
    mins.push({i, *sequence_begin});
    ++i;
  }

  vector<int> result;
  while (!mins.empty()) {
    result.push(mins.top().id);
    mins.pop();
  }
  return result; 
}

vector<int> ExamineBuildingsWithSunsetWrapper(const vector<int>& sequence) {
  return ExamineBuildingsWithSunset(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "sunset_view.cc", "sunset_view.tsv",
                         &ExamineBuildingsWithSunsetWrapper,
                         DefaultComparator{}, param_names);
}
