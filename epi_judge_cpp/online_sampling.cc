#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include <random>

#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
using std::bind; using std::sort; using std::vector; using std::unordered_set; using std::default_random_engine; using std::uniform_int_distribution; using std::random_device;
// Assumption: there are at least k elements in the stream.
// k=0, returns empty
// [2], k=1 -> [2]
// [2,3,4,5], k=2 ->
vector<int> OnlineRandomSample(vector<int>::const_iterator stream_begin,
                               const vector<int>::const_iterator stream_end,
                               int k) {
  vector<int> result;
  for (auto i = 0; i < k; ++i, ++stream_begin) {
    result.emplace_back(*stream_begin);
  }
  int items_processed = k;
  
  random_device rng;
  default_random_engine seed(rng());
  for(; stream_begin != stream_end; ++stream_begin) {
    ++items_processed;
    uniform_int_distribution<> distributor(0, items_processed-1);
    const int replace_item = distributor(seed);
    if (replace_item < k) {
      result[replace_item] = *stream_begin;
    }
  }
  return result;
}
bool OnlineRandomSamplingRunner(TimedExecutor& executor, vector<int> stream,
                                int k) {
  using namespace test_framework;
  vector<vector<int>> results;

  executor.Run([&] {
    std::generate_n(
        back_inserter(results), 100000,
        std::bind(OnlineRandomSample, cbegin(stream), cend(stream), k));
  });

  int total_possible_outcomes = BinomialCoefficient(stream.size(), k);
  sort(begin(stream), end(stream));
  vector<vector<int>> combinations;
  for (int i = 0; i < BinomialCoefficient(stream.size(), k); ++i) {
    combinations.emplace_back(
        ComputeCombinationIdx(stream, stream.size(), k, i));
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

void OnlineRandomSampleWrapper(TimedExecutor& executor,
                               const vector<int>& stream, int k) {
  RunFuncWithRetries(bind(OnlineRandomSamplingRunner, std::ref(executor),
                          std::cref(stream), k));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "stream", "k"};
  return GenericTestMain(args, "online_sampling.cc", "online_sampling.tsv",
                         &OnlineRandomSampleWrapper, DefaultComparator{},
                         param_names);
}




