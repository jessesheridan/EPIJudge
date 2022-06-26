#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
                                                                                                         //   / \
//  * 2 * 1
// /
//* 1

//      * -1
//     / \
//    *   * 3,1
//   /     \
//  * 2   1 *
// /         
//* 1         
using std::unique_ptr; using std::max;
int CalculateHeightBalanced(const unique_ptr<BinaryTreeNode<int>>& root) {
  if (!root) {
    return 0;
  }
  int left = CalculateHeightBalanced(root->left);
  if (left < 0) {
    return -1;
  }
  int right = CalculateHeightBalanced(root->right);
  if (right < 0) {
    return -1;
  }
  if (abs(left - right) > 1) {
    return -1;
  }
  return max(left,right) + 1;
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& root) {
  int result = CalculateHeightBalanced(root);
  if (result < 0) {
    return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
