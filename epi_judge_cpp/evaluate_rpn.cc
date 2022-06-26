#include <string>

#include "test_framework/generic_test.h"
using std::string;
// RPN
// "-412,12,+,2,x,5,/"
#include <stack>
#include <unordered_map>
using std::stoi; using std::stack; using std::stringstream; using std::unordered_map; using std::function;
// "11,8,10,*,+,7,12,*,+,12,7,*,+,9,14,*,+,17,+"
int Evaluate(const string& expression) {
  stack<int> intermediate_results;
  stringstream ss(expression);
  string token;
  const char kDelimeter = ',';
  while (getline(ss, token, kDelimeter)) {
    if (token == "+" || token == "-" || token == "*" || token == "/") {
      const int y = intermediate_results.top();
      intermediate_results.pop();
      const int x = intermediate_results.top();
      intermediate_results.pop();
      switch (token[0]) {
        case '+':
          intermediate_results.emplace(x + y);
        break;
        case '-':
          intermediate_results.emplace(x - y);
        break;
        case '*':
          intermediate_results.emplace(x * y);
        break;
        case '/':
          intermediate_results.emplace(x / y);
        break;
      }
    } else {
      intermediate_results.emplace(stoi(token));
    }
  }
  return intermediate_results.top();
}




int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
