#include "list_node.h"
#include "test_framework/generic_test.h"
// dh->0->1->2->3->4->5 => 0->2->4->1->3->5
//     ^        ^
// dh->2->1->3->4->5
// null -> null
// 1->null => 1
// 1->2->null => 2->1->null
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
  if (!L) {
    return L;
  }
  auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
  auto last_even = dummy_head->next, odd = dummy_head->next->next, iter = dummy_head->next;
  while (iter->next && iter->next->next) { // 1 && 2
    iter = iter->next; // 1
    auto even = odd->next; // 2
    auto next_odd = even->next; // null
    even->next = last_even->next; // 2->1
    last_even->next = even; // dh->2	
    odd->next = next_odd; // 1->null
    odd = next_odd; // null
    last_even = even; // 2
  } // dh->2->4->1->3->5->null
  return dummy_head->next; // 2
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
