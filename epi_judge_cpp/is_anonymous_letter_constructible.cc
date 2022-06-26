#include <string>

#include "test_framework/generic_test.h"
using std::string;
#include <unordered_map>
using std::unordered_map;
// "carisa", "apple"
// a1p2l1e1 => p2l1e1 => false
// "myapple", "alpepym" => true
// a1l1p2e1y1m1 => 
// 1123, 123 => 
// 112131 
bool IsLetterConstructibleFromMagazine(const string& letter, const string& magazine) {
  unordered_map<char, int> hash_map;
  for (char c : letter) {
    ++hash_map[c];
  }
  
  for (char c : magazine) {
    if (auto iter = hash_map.find(c); iter != hash_map.cend()) {
      --iter->second;
      if (iter->second == 0) {
        hash_map.erase(iter);
        if (hash_map.empty()) {
          return true;
        }
      }
    }
  }
  
  return hash_map.empty();
} 


 
int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
