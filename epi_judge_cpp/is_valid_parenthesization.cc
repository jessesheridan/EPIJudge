#include <string>

#include "test_framework/generic_test.h"
using std::string;
// [{()}] ->true
// ""->true
// [[}] -> false
// [ -> false
#include <stack>
#include <unordered_map>
using std::stack; using std::unordered_map;
bool IsWellFormed(const string& str) {
  stack<char> opens;
  const unordered_map<char,char> matching = {
    {'{', '}'},
    {'[', ']'},
    {'(', ')'}
  };
  for (int i = 0; i < str.size(); ++i) {
    if (matching.count(str[i])) {
      opens.emplace(str[i]);
    }
    else {
      if (opens.empty() || matching.at(opens.top()) != str[i]) {
        return false;
      }
      opens.pop();
    }
  }
  return opens.empty();
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
