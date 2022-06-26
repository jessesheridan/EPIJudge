#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

// null -> null
// 1 -> 1
// 1->2->3 => 1->2->3
// 1->1->2->3->3->3->5->5 => 1->2->3->5

shared_ptr<ListNode<int>> RemoveDuplicates(const shared_ptr<ListNode<int>>& L) {
  auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
  auto iter = dummy_head->next;
  while (iter) {
    while (iter->next && iter->data == iter->next->data) {
      iter->next = iter->next->next;
    }
    iter = iter->next;
  }

  return dummy_head->next;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "remove_duplicates_from_sorted_list.cc",
                         "remove_duplicates_from_sorted_list.tsv",
                         &RemoveDuplicates, DefaultComparator{}, param_names);
}
