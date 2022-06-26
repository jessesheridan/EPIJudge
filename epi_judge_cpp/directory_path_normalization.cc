#include <string>

#include "test_framework/generic_test.h"
using std::string;
// remove double slashes "//", remove '.', if stack has elements and we encounter a ".." then remove top of stack. remove trailing slash
#include <string>
#include <deque>
using std::stringstream; using std::deque;
// "" => ""
// "foo" => "foo"
// "foo/bar" => "foo/bar"
// "/foo/bar/../bar/" => "/foo/bar"
// "../../test" => ""
string ShortestEquivalentPath(const string& path) {
  stringstream ss(path);
  const char kDelimeter = '/';
  string token;
  deque<string> tokens;
  while (getline(ss, token, kDelimeter)) {
    if (token == ".." && !tokens.empty() && tokens.back() != "..") {
      tokens.pop_back();
    }
    else if (token != "." && token.size()) {
      tokens.emplace_back(token);
    }
  }
  string normalized_path;
  if (path.size()) {
    normalized_path = path[0] == '/' ? "/" : "";
  }
  for (auto iter = tokens.begin(); iter != tokens.end(); ++iter) {
    normalized_path += *iter;
    if (iter+1 != tokens.end()) {
      normalized_path += "/";
    }
  }
  return normalized_path;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"path"};
  return GenericTestMain(args, "directory_path_normalization.cc",
                         "directory_path_normalization.tsv",
                         &ShortestEquivalentPath, DefaultComparator{},
                         param_names);
}
