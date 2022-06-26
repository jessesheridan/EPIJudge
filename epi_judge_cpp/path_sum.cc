#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

// nullptr
//    1
//   / \
//  0  -4
// / \
//4   3
// 1 => false , 0 => false, 4 => true, -3 => true
bool HasPathSumHelper(const unique_ptr<BinaryTreeNode<int>>& tree, int weight, int sum) {
  if (!tree) {
    return false;
  }

  sum += tree->data;
  if (sum == weight && !tree->left && !tree->right) {
    return true;
  }

  return HasPathSumHelper(tree->left, weight, sum) ? true :           HasPathSumHelper(tree->right, weight, sum);
}
bool HasPathSum(const unique_ptr<BinaryTreeNode<int>>& tree, int weight) {
  return HasPathSumHelper(tree, weight, 0);
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "remaining_weight"};
  return GenericTestMain(args, "path_sum.cc", "path_sum.tsv", &HasPathSum,
                         DefaultComparator{}, param_names);
}
