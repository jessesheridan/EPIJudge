#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
using std::bind;
using std::iota;
using std::vector;
#include <algorithm>
#include <vector>
#include <random>

using std::vector; using std::iota; using std::random_device; using std::default_random_engine; using std::uniform_int_distribution; using std::swap; using std::unordered_map;
vector<int> RandomSubset(int n, int k) {
  vector<int> result;
  unordered_map<int,int> seen_values;
  random_device rd;
  default_random_engine seed(rd());
  auto i = 0;
  for (i; i < k; ++i) {
    uniform_int_distribution<int> distributor(i, n-1);
    int rand_num = distributor(seed);
    int right_value, left_value;
    if (seen_values.find(i) == seen_values.end()) {
      right_value = i;
    }
    else {
      right_value = seen_values[i];
    }

    auto existing_it = seen_values.find(rand_num);
    if (existing_it == seen_values.end()) {
      left_value = rand_num;
    }
    else {
      left_value = seen_values[rand_num];
    }
    
    seen_values[i] = left_value;
    if (i != rand_num) {
      seen_values[rand_num] = right_value;
    }
    result.emplace_back(left_value);
  }
  return result;
}















bool RandomSubsetRunner(TimedExecutor& executor, int n, int k) {
  using namespace test_framework;
  vector<vector<int>> results;

  executor.Run([&] {
    std::generate_n(back_inserter(results), 100000,
                    std::bind(RandomSubset, n, k));
  });

  int total_possible_outcomes = BinomialCoefficient(n, k);
  vector<int> A(n);
  iota(begin(A), end(A), 0);
  vector<vector<int>> combinations;
  for (int i = 0; i < BinomialCoefficient(n, k); ++i) {
    combinations.emplace_back(ComputeCombinationIdx(A, n, k, i));
  }
  vector<int> sequence;
  for (vector<int> result : results) {
    sort(begin(result), end(result));
    sequence.emplace_back(
        distance(begin(combinations),
                 find(begin(combinations), end(combinations), result)));
  }
  return CheckSequenceIsUniformlyRandom(sequence, total_possible_outcomes,
                                        0.01);
}

void RandomSubsetWrapper(TimedExecutor& executor, int n, int k) {
  RunFuncWithRetries(bind(RandomSubsetRunner, std::ref(executor), n, k));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "n", "k"};
  return GenericTestMain(args, "random_subset.cc", "random_subset.tsv",
                         &RandomSubsetWrapper, DefaultComparator{},
                         param_names);
}
