#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

#include <memory>
using std::unique_ptr;
BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0, const unique_ptr<BinaryTreeNode<int>>& node1) {
  auto temp0 = node0.get();
  int node0_depth = 0, node1_depth = 0;
  while (temp0) {
    temp0 = temp0->parent;
    node0_depth++;
  }
  temp0 = node1.get();
  while (temp0) {
    temp0 = temp0->parent;
    node1_depth++;
  }
  temp0 = node0.get();
  auto temp1 = node1.get();
  while (node0_depth > node1_depth) {
    temp0 = temp0->parent;
    node0_depth--;
  } 
  while (node1_depth > node0_depth) {
    temp1 = temp1->parent;
    node1_depth--;
  }
  
  while (temp0 != temp1) {
    temp0 = temp0->parent;
    temp1 = temp1->parent;
  }

  return temp0;
}


int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
