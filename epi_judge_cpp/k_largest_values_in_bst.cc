#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

// null=>empty, 1,0=>empty
// 1,1=>1
//   4
// 2   7
//    6
//k=1=>7
//k=2=>7,6
//k=5=>
//      3
//    2   5
//   1   4 6
//k=2 => 
// inverted in-order traversal using a k sized deque
#include <memory>
#include <deque>
using std::unique_ptr; using std::deque;
vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
  struct VisitationNode {
    const unique_ptr<BstNode<int>>& tree_node;
    bool right_visited = false;
  };

  if (!tree || k < 1) {
    return {};
  }
  deque<VisitationNode> inorder_queue; //6,5
  inorder_queue.emplace_front(VisitationNode{tree}); //6
  vector<int> result;
  while (!inorder_queue.empty()) {
    auto& front = inorder_queue.front();
    if (front.tree_node->right && !front.right_visited) {
      if (inorder_queue.size() == k) {
        inorder_queue.pop_back();
      }
      inorder_queue.emplace_front(VisitationNode{front.tree_node->right});
      front.right_visited = true;
    } else {
      result.emplace_back(front.tree_node->data);
      if (result.size() == k) {
        return result;
      }
      inorder_queue.pop_front();
      if (front.tree_node->left) {
        inorder_queue.emplace_front(VisitationNode{front.tree_node->left});
      }
    }
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         UnorderedComparator{}, param_names);
}
