#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
// 1
// => true
//  1
// 2 3
// => false
//  3
// 1 4
// => true
#include <limits>
#include <memory>
#include <queue>
using std::numeric_limits; using std::unique_ptr; using std::queue;

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
  struct QueueEntry {
    const unique_ptr<BinaryTreeNode<int>>& tree_node;
    int min, max;
  };

  queue<QueueEntry> bfs_entries;
  bfs_entries.emplace(QueueEntry{tree, numeric_limits<int>::min(), numeric_limits<int>::max()});

  while (!bfs_entries.empty()) {
    auto entry = bfs_entries.front();
    if (!entry.tree_node) {
      bfs_entries.pop();
      continue;
    }
    if (entry.tree_node->data < entry.min || entry.tree_node->data > entry.max) {
      return false;
    }
    bfs_entries.emplace(QueueEntry{entry.tree_node->left, entry.min, entry.tree_node->data});
    bfs_entries.emplace(QueueEntry{entry.tree_node->right, entry.tree_node->data, entry.max});
    bfs_entries.pop();
  }

  return true;
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
