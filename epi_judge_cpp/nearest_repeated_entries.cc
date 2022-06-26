#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

#include <unordered_map>
using std::unordered_map; using std::pair; using std::numeric_limits; using std::min;
int FindNearestRepetition(const vector<string>& paragraph) {
  unordered_map<string, vector<int>> unique_words;
  for (int i = 0; i < paragraph.size(); ++i) {
    unique_words[paragraph[i]].push_back(i);
  }
  int min_distance = numeric_limits<int>::max();
  for (auto word_indices : unique_words) {
    if (word_indices.second.size() > 1) {
      for (int i = 1; i < word_indices.second.size(); ++i) {
        min_distance = min(min_distance, word_indices.second[i] - word_indices.second[i-1]);
      }
    }
  }
  if (min_distance == numeric_limits<int>::max()) {
    return -1;
  }
  return min_distance;
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
