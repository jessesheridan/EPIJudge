#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"

// given a node find its successor, which is the next node printed in an inorder traversal.
// if left and right do not exist then if parent's left equal this node then return parent, otherwise repeat going up parents until we find that the node came from the left side, if found then return that node otherwise nullptr
// if right exists then go to right and look at all lefts if they exist and repeat

//        1
//       / \
//      2   3
//     /   / \
//    4   5   6
// no right then go to parent, if child came from right then keep going up to parent
// if right then go right and find the furthest left node
using std::unique_ptr;
BinaryTreeNode<int>* FindSuccessor(const unique_ptr<BinaryTreeNode<int>>& node) {
  BinaryTreeNode<int>* iter = node.get();
  if (!iter->right) {
    auto child = iter;
    iter = iter->parent;
    while (iter && iter->right.get() == child) {
      child = iter;
      iter = iter->parent;
    }
    return iter;
  }
  
  iter = iter->right.get();
  while (iter->left) {
    iter = iter->left.get();
  }
  return iter;
}

int FindSuccessorWrapper(const unique_ptr<BinaryTreeNode<int>>& tree,
                         int node_idx) {
  auto result = FindSuccessor(MustFindNode(tree, node_idx));
  return result ? result->data : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "node_idx"};
  return GenericTestMain(args, "successor_in_tree.cc", "successor_in_tree.tsv",
                         &FindSuccessorWrapper, DefaultComparator{},
                         param_names);
}
