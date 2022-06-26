#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;


// create a queue of all children
// for each child save its data to a new vector for that depth and add their children to a new queue.
// In this way we create queues containing children for each depth and we iterate through those children and add them to a depth vector
// null => [[]]
// 1 => [[1]]
// 1,2(4(8),5),3(6,7) => {1},{2,3},
#include <vector>
#include <queue>
using std::vector; using std::queue; using std::shared_ptr;
vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<vector<int>> depths;
  queue<BinaryTreeNode<int>*> q;
  if (tree.get()) {
    q.push(tree.get());
  }
  while (!q.empty()) {
    vector<int> depth;
    queue<BinaryTreeNode<int>*> next_q;
    while (!q.empty()) {
      depth.push_back(q.front()->data); 
      if (q.front()->left) {
        next_q.push(q.front()->left.get()); // 4,6
      }
      if (q.front()->right) {
        next_q.push(q.front()->right.get()); // 5,7
      }
      q.pop(); // 3,{},
    }
    depths.push_back(depth);
    q = next_q;
  }
  return depths;
}




int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
