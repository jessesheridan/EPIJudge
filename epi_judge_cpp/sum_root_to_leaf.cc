#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

int SumRootToLeafHelper(const unique_ptr<BinaryTreeNode<int>>& tree, int partial_path_sum) {
  if (!tree) {
    return 0;
  }

  partial_path_sum = partial_path_sum * 2 + tree->data;
  if (!tree->left && !tree->right) {
    return partial_path_sum;
  }

  return SumRootToLeafHelper(tree->left, partial_path_sum) + 
         SumRootToLeafHelper(tree->right, partial_path_sum);
}

int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return SumRootToLeafHelper(tree, 0);
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "sum_root_to_leaf.cc", "sum_root_to_leaf.tsv",
                         &SumRootToLeaf, DefaultComparator{}, param_names);
}
