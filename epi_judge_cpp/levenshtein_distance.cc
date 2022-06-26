#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;
using std::min; using std::unordered_map; using std::numeric_limits;
// "", "" => 0
// "", "abc" => 
int DistanceHelper(const string& str1, const string& str2, size_t index1, size_t index2, unordered_map<string, int> hash, int count) {
  if (index2 >= str2.length()) {
    if (str1 == str2) {
      return count;
    }
    return numeric_limits<int>::max();
  }
  if (hash.count(str1.substr(index1, str1.length() - index1)) > 0) {
    return hash[str1.substr(index1, str1.length() - index1)];
  }
  if (str1[index1] == str2[index2]) {
    return DistanceHelper(str1, str2, index1 + 1, index2 + 1, hash, count);
  }
  int minDst = numeric_limits<int>::max();
  string strTemp = str1;
  strTemp.insert(str1.begin() + index1, str2[index2]);
  // insert
  minDst = min(DistanceHelper(strTemp, str2, index1 + 1, index2 + 1, hash, count + 1), minDst);

  if (str1.length() - index1 > 0) {
    // delete
    strTemp = str1;
    strTemp.erase(index1, 1);
    minDst = min(DistanceHelper(strTemp, str2, index1, index2 + 1, hash, count + 1), minDst);
  }

  // substitute
  strTemp = str1;
  strTemp.replace(index1, 1, 1, str2[index2]);
  minDst = min(DistanceHelper(strTemp, str2, index1 + 1, index2 + 1, hash, count + 1), minDst);

  hash[str1.substr(index1, str1.length() - index1)] = minDst;
  return minDst;
}

int LevenshteinDistance(const string& str1, const string& str2) {
  unordered_map<string, int> hash;
  return DistanceHelper(str1, str2, 0, 0, hash, 0);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "levenshtein_distance.cc",
                         "levenshtein_distance.tsv", &LevenshteinDistance,
                         DefaultComparator{}, param_names);
}
