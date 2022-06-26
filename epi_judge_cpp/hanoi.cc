#include <array>
#include <stack>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::array;
using std::stack;
using std::vector;
const int kNumPegs = 3;
// n1 = move to destination <== base case
// n2 = move both out, recompile back to destination <== base case
// n3 = n2 for right, n1 to middle, n2 from right to middle <== recurse
// n4 = n3 for right, n1 to middle, n3 from right to middle
// n8 = n7 to right, n1 to middle, n7 from right to middle
// 0 => empty
// 1 => {{0, 1}}
// 2 => {{0, 2}, {0, 1}, {2, 1}}
// 3 => { {0, 1}, {0, 2}, {1, 2}   {0, 1}      {2, 0}, {2, 1}, {0, 1}}
vector<vector<int>> ComputeTowerHanoiHelper(int num_rings, int src, int dest) {
  int temp = 0;
  if (src != 2 && dest != 2) {
    temp = 2;
  } else if (src != 1 && dest != 1) {
    temp = 1;
  } 
  if (num_rings < 1) {
    return {{}};
  }
  if (num_rings == 1) {
    return {{src, dest}};
  } else if (num_rings == 2) {
    return {{src, temp}, {src, dest}, {temp, dest}};
  }
  vector<vector<int>> left = ComputeTowerHanoiHelper(num_rings - 1, src, temp);
  vector<vector<int>> middle = ComputeTowerHanoiHelper(1, src, dest);
  vector<vector<int>> right = ComputeTowerHanoiHelper(num_rings - 1, temp, dest);
  left.insert(left.end(), middle.begin(), middle.end());
  left.insert(left.end(), right.begin(), right.end());
  return left;
}

vector<vector<int>> ComputeTowerHanoi(int num_rings) {
  return ComputeTowerHanoiHelper(num_rings, 0, 1);
}



void ComputeTowerHanoiWrapper(TimedExecutor& executor, int num_rings) {
  array<stack<int>, kNumPegs> pegs;
  for (int i = num_rings; i >= 1; --i) {
    pegs[0].push(i);
  }

  vector<vector<int>> result =
      executor.Run([&] { return ComputeTowerHanoi(num_rings); });

  for (const vector<int>& operation : result) {
    int from_peg = operation[0], to_peg = operation[1];
    if (!pegs[to_peg].empty() && pegs[from_peg].top() >= pegs[to_peg].top()) {
      throw TestFailure("Illegal move from " +
                        std::to_string(pegs[from_peg].top()) + " to " +
                        std::to_string(pegs[to_peg].top()));
    }
    pegs[to_peg].push(pegs[from_peg].top());
    pegs[from_peg].pop();
  }
  array<stack<int>, kNumPegs> expected_pegs1, expected_pegs2;
  for (int i = num_rings; i >= 1; --i) {
    expected_pegs1[1].push(i);
  }
  for (int i = num_rings; i >= 1; --i) {
    expected_pegs2[2].push(i);
  }
  if (pegs != expected_pegs1 && pegs != expected_pegs2) {
    throw TestFailure("Pegs doesn't place in the right configuration");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "num_rings"};
  return GenericTestMain(args, "hanoi.cc", "hanoi.tsv",
                         &ComputeTowerHanoiWrapper, DefaultComparator{},
                         param_names);
}
