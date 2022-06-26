#include <set>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;

void EvenOdd(vector<int>* A_ptr) {
  size_t a = 0;
  size_t z = A_ptr->size() - 1;
  while (a < z) {
    while (a < z && (A_ptr->at(a) & 1) == 0) {
      a++;
    }
    while (a < z && A_ptr->at(z) & 1) {
      z--;
    }
    if (a < z) {
      A_ptr->at(a) ^= A_ptr->at(z); 
      A_ptr->at(z) ^= A_ptr->at(a);
      A_ptr->at(a) ^= A_ptr->at(z);
    }
  }
  return;
}

void EvenOddWrapper(TimedExecutor& executor, vector<int> A) {
  std::multiset<int> before(begin(A), end(A));

  executor.Run([&] { EvenOdd(&A); });

  bool in_odd = false;
  for (int a : A) {
    if (a % 2 == 0) {
      if (in_odd) {
        throw TestFailure("Even elements appear in odd part");
      }
    } else {
      in_odd = true;
    }
  }

  std::multiset<int> after(begin(A), end(A));
  if (before != after) {
    throw TestFailure("Elements mismatch");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(args, "even_odd_array.cc", "even_odd_array.tsv",
                         &EvenOddWrapper, DefaultComparator{}, param_names);
}
