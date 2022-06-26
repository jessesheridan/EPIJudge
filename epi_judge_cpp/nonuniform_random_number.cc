#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>
#include <random>
#include <limits>

#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
using std::abs;
using std::bind;
using std::unordered_map;
using std::vector;
using std::numeric_limits; using std::random_device; using std::default_random_engine; using std::uniform_int_distribution; using std::uniform_real_distribution; using std::generate_canonical; using std::numeric_limits; 
using std::partial_sum; using std::back_inserter; using std::cbegin; using std::cend;

int NonuniformRandomNumberGeneration(const vector<int>& values,
                                     const vector<double>& probabilities) {
  random_device rd;
  default_random_engine seed(rd());
  uniform_real_distribution<double> distributor(0,1);
  double rand_num = distributor(seed);    
  vector<double> prefix_sums_of_probabilities;
  partial_sum(cbegin(probabilities), cend(probabilities), back_inserter(prefix_sums_of_probabilities));
  const double uniform_0_1 = generate_canonical<double, numeric_limits<double>::digits>(seed);
  const int interval_idx = distance(cbegin(prefix_sums_of_probabilities), upper_bound(cbegin(prefix_sums_of_probabilities), cend(prefix_sums_of_probabilities), uniform_0_1));
  return values[interval_idx];
}

bool NonuniformRandomNumberGenerationRunner(
    TimedExecutor& executor, const vector<int>& values,
    const vector<double>& probabilities) {
  constexpr int kN = 1000000;
  vector<int> results;

  executor.Run([&] {
    for (int i = 0; i < kN; ++i) {
      results.emplace_back(
          NonuniformRandomNumberGeneration(values, probabilities));
    }
  });

  unordered_map<int, int> counts;
  for (int result : results) {
    ++counts[result];
  }
  for (int i = 0; i < values.size(); ++i) {
    const int v = values[i];
    const double p = probabilities[i];
    if (kN * p < 50 || kN * (1.0 - p) < 50) {
      continue;
    }
    const double sigma = sqrt(kN * p * (1.0 - p));
    if (abs(counts[v] - (p * kN)) > 5 * sigma) {
      return false;
    }
  }
  return true;
}

void NonuniformRandomNumberGenerationWrapper(
    TimedExecutor& executor, const vector<int>& values,
    const vector<double>& probabilities) {
  RunFuncWithRetries(bind(NonuniformRandomNumberGenerationRunner,
                          std::ref(executor), std::cref(values),
                          std::cref(probabilities)));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "values", "probabilities"};
  return GenericTestMain(args, "nonuniform_random_number.cc",
                         "nonuniform_random_number.tsv",
                         &NonuniformRandomNumberGenerationWrapper,
                         DefaultComparator{}, param_names);
}
