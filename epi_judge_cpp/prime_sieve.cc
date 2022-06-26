#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
using std::deque;
// 0 -> {}
// 2 -> [2]
// 3 -> [2,3]
// 7 -> [2,3,5,7,11,13,17]

vector<int> GeneratePrimes(int n) {
  vector<int> primes;
  deque<bool> valid(n+1, true);
  if (n >= 2) {
    primes.emplace_back(2);
    for (size_t j = 2, k = 1; j <= n; k++) {
      valid[j] = false;
      j = k*2;
    }
  }
  for (size_t i = 3; i <= n; i+=2) { // 7
    if (!valid[i]) {
      continue;
    }
    bool divisible = false;
    for (auto prime : primes) {
      if (prime > sqrt(i)) {
        break;
      }
      if ((i % prime) == 0) {
        divisible = true;
        break;
      }
    }
    if (!divisible) {
      primes.push_back(i);
      for (size_t j = i, k = 1; j <= n; k++) {
        valid[j] = false;
        j = k*i;
      }
    }
  }
  return primes;
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
