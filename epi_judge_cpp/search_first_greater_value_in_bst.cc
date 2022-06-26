#include <memory>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
// null=>null
// 1,1 =>null
// 2,1 =>2
#include <memory>
using std::unique_ptr;
BstNode<int>* FindFirstGreaterThanKHelper(const unique_ptr<BstNode<int>>& tree, int key, BstNode<int>* lower_bound) {
  if (!tree) {
    if (lower_bound && lower_bound->data > key) {
      return lower_bound;
    } else {
      return nullptr;
    }
  }
  if (tree->data > key) {
    return FindFirstGreaterThanKHelper(tree->left, key, tree.get());
  }
  
  if (tree->data > lower_bound->data) {
    lower_bound = tree.get();
  }
  return FindFirstGreaterThanKHelper(tree->right, key, lower_bound);
}

BstNode<int>* FindFirstGreaterThanK(const unique_ptr<BstNode<int>>& tree, int key) {
  return FindFirstGreaterThanKHelper(tree, key, tree.get());
}

int FindFirstGreaterThanKWrapper(const unique_ptr<BstNode<int>>& tree, int k) {
  auto result = FindFirstGreaterThanK(tree, k);
  return result ? result->data : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "search_first_greater_value_in_bst.cc",
                         "search_first_greater_value_in_bst.tsv",
                         &FindFirstGreaterThanKWrapper, DefaultComparator{},
                         param_names);
}
