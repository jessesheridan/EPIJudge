#include <memory>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;
struct LCAStatus {
  void Merge(const LCAStatus& theirs) {
    found_node1 = found_node1 ? found_node1 : theirs.found_node1;
    found_node2 = found_node2 ? found_node2 : theirs.found_node2;
  }
  bool found_node1 = false, found_node2 = false;
  BinaryTreeNode<int>* parent = nullptr;
};

LCAStatus FindLCA(const unique_ptr<BinaryTreeNode<int>>& tree, const unique_ptr<BinaryTreeNode<int>>& node1, const unique_ptr<BinaryTreeNode<int>>& node2) {
  if (!tree) {
    return {};
  }
  LCAStatus result;
  if (tree == node1) {
    result.found_node1 = true;
  }
  if (tree == node2) {
    result.found_node2 = true;
  }
  auto result_left = FindLCA(tree->left, node1, node2);
  if (result_left.parent) {
    return result_left;
  }
  result.Merge(result_left);
  if (result.found_node1 && result.found_node2) {
    result.parent = tree.get();
    return result;
  }
  auto result_right = FindLCA(tree->right, node1, node2);
  if (result_right.parent) {
    return result_right;
  }
  result.Merge(result_right);
  if (result.found_node1 && result.found_node2) {
    result.parent = tree.get();
    return result;
  }
  return result;
}

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& tree, const unique_ptr<BinaryTreeNode<int>>& node1, const unique_ptr<BinaryTreeNode<int>>& node2) {
  return FindLCA(tree, node1, node2).parent;
}


int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(tree, node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
