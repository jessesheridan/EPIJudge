#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

#include <stack>
#include <vector>
using std::stack; using std::vector; using std::pair;
vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<int> result;

  stack<pair<const BinaryTreeNode<int>*, bool>> in_process;
  in_process.emplace(tree.get(), false);
  while (!in_process.empty()) {
    auto temp = in_process.top();
    in_process.pop();
    if (temp.first) {
      if (temp.second) {
        result.emplace_back(temp.first->data);
      } else {
        in_process.emplace(temp.first->right.get(), false);
        in_process.emplace(temp.first, true);
        in_process.emplace(temp.first->left.get(), false);
      }
    }
  }

  return result;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
