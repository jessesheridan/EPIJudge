#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

//   *              true
//  / \
// 1   2            false, false
//    *              
//   / \
//  1   1           true 
// /
//3                 false
//     *              
//   /   \
//  1     1           true 
// / \   / \
//3   2 2   3           false
using std::unique_ptr;
bool LeftAndRightSymmetric(const unique_ptr<BinaryTreeNode<int>>& left, const unique_ptr<BinaryTreeNode<int>>& right) {
  if (left && right) {
    if (left->data != right->data) {
     return false;
    }
    if (!LeftAndRightSymmetric(left->left, right->right)) {
      return false;
    }
    if (!LeftAndRightSymmetric(left->right, right->left)) {
      return false;
    }
    return true;
  } else if (left || right) {
    return false;
  }
  return true;
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (tree) {
    return LeftAndRightSymmetric(tree->left, tree->right);
  }
  return true;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
