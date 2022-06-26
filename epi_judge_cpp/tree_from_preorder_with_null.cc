#include <string>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;
using std::pair; using std::make_pair; using std::make_unique; using std::move;

// empty preorder => nullptr
// 1,null,null => 1,null,null
// 1,2,3,null,null,null,4,null,null (9) =>
//       1
//      / \
//     2   4
//    /
//   3

pair<unique_ptr<BinaryTreeNode<int>>, size_t> ReconstructPreorderHelper(const vector<int*>& preorder, size_t index) {
  if (index >= preorder.size() || !preorder[index]) {
    return make_pair(nullptr, index+1); // 4,5,6
  }
  auto left = ReconstructPreorderHelper(preorder, index+1); //1,2,3
  auto right = ReconstructPreorderHelper(preorder, left.second); //4,5
  return make_pair(make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{*preorder[index], move(left.first), move(right.first)}), right.second); //3,null,null, 5;
}

unique_ptr<BinaryTreeNode<int>> ReconstructPreorder(const vector<int*>& preorder) {
  return ReconstructPreorderHelper(preorder, 0).first;
}

unique_ptr<BinaryTreeNode<int>> ReconstructPreorderWrapper(
    TimedExecutor& executor, const vector<string>& preorder) {
  vector<int> values;
  vector<int*> ptrs;
  values.reserve(preorder.size());
  for (auto& s : preorder) {
    if (s == "null") {
      ptrs.push_back(nullptr);
    } else {
      int i = std::stoi(s);
      values.push_back(i);
      ptrs.push_back(&values.back());
    }
  }

  return executor.Run([&] { return ReconstructPreorder(ptrs); });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "preorder"};
  return GenericTestMain(args, "tree_from_preorder_with_null.cc",
                         "tree_from_preorder_with_null.tsv",
                         &ReconstructPreorderWrapper, DefaultComparator{},
                         param_names);
}
