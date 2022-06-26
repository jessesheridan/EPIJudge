#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;

// print root first
// look for and print out all the leaves
// as you start, if you go left from the root then print the node and continue printing nodes left until the leaf.
// If you end up going right from root then add the next node to a stack and continue adding the nodes to the stack if you keep going right, except for the leaf.
// Keep track of left or right with variables you pass to the recursion
// null => empty exterior
// 1 => 1
//     -1
//    /   \
//  -2    -5
//    \   /  
//    13 5   
//     \  
//      10 
//=> -1,-2,10,5,-5
#include <vector>
#include <memory>
#include <stack>
using std::unique_ptr; using std::vector; using std::stack;
void ExteriorBinaryTreeHelper(
    const unique_ptr<BinaryTreeNode<int>>& tree, bool& addLeft, bool& addRight, bool goingLeft,  bool goingRight, 
    vector<const unique_ptr<BinaryTreeNode<int>>*>& exterior, stack<const 
    unique_ptr<BinaryTreeNode<int>>*>& right_stack) {
  if (!tree) {
    return;
  }
  if (!tree->left && !tree->right) {
    exterior.emplace_back(&tree);
    addLeft = false, addRight = false;
    return;
  }
  if (addLeft && goingLeft) {
    exterior.emplace_back(&tree);
  } else if (addRight && goingRight) {
    right_stack.push(&tree);
  }
  if (goingRight && !tree->right) {
    ExteriorBinaryTreeHelper(tree->left, addLeft, addRight, goingLeft, goingRight, exterior, right_stack);
  } else {
    ExteriorBinaryTreeHelper(tree->left, addLeft, addLeft, goingLeft, false, exterior, right_stack);
  }
  ExteriorBinaryTreeHelper(tree->right, addLeft, addRight, goingLeft, goingRight, exterior, right_stack);
} 

vector<const unique_ptr<BinaryTreeNode<int>>*> ExteriorBinaryTree(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<const unique_ptr<BinaryTreeNode<int>>*> exterior;
  stack<const unique_ptr<BinaryTreeNode<int>>*> right_stack;
  if (!tree) {
    return exterior;
  }
  exterior.emplace_back(&tree);
  bool addLeft = true, addRight = false;
  ExteriorBinaryTreeHelper(tree->left, addLeft, addRight, true, false, exterior, right_stack);
  addRight = true; addLeft = false;
  ExteriorBinaryTreeHelper(tree->right, addLeft, addRight, false, true, exterior, right_stack);
  while (!right_stack.empty()) {
    exterior.emplace_back(right_stack.top());
    right_stack.pop();
  }

  return exterior;
}


vector<int> CreateOutputVector(
    const vector<const unique_ptr<BinaryTreeNode<int>>*>& L) {
  if (std::find(std::begin(L), std::end(L), nullptr) != std::end(L)) {
    throw TestFailure("Resulting list contains nullptr");
  }
  std::vector<int> output;
  for (const auto* l : L) {
    output.push_back((*l)->data);
  }
  return output;
}

vector<int> ExteriorBinaryTreeWrapper(
    TimedExecutor& executor, const unique_ptr<BinaryTreeNode<int>>& tree) {
  auto result = executor.Run([&] { return ExteriorBinaryTree(tree); });

  return CreateOutputVector(result);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree"};
  return GenericTestMain(args, "tree_exterior.cc", "tree_exterior.tsv",
                         &ExteriorBinaryTreeWrapper, DefaultComparator{},
                         param_names);
}
