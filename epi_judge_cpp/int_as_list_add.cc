#include "list_node.h"
#include "test_framework/generic_test.h"

// null,null => null
// 1, null => 1
// 1->2->3 + 1->2->3 => 2->4->6
// 9->9->9->9->9 + 9->1->9 => 8->1->9->0->0->1
shared_ptr<ListNode<int>> AddTwoNumbers(shared_ptr<ListNode<int>> a, shared_ptr<ListNode<int>> b) {
  shared_ptr<ListNode<int>> a_head = make_shared<ListNode<int>>(ListNode<int>{0, a}), b_head = make_shared<ListNode<int>>(ListNode<int>{0, b});
  shared_ptr<ListNode<int>> sum_head = make_shared<ListNode<int>>(ListNode<int>{});
  auto sum_iter = sum_head;
  int carry = 0;
  while (a || b) {
    auto iter = a ? a : b; // a1
    int sum = (a ? a->data : 0) + (b ? b->data : 0) + carry; // 8->1->1->0->1
    iter->data = sum % 10; // a1=2
    sum_iter->next = iter; // dh->a1->a2
    sum_iter = sum_iter->next; // a1
    carry = sum > 9 ? 1 : 0;
    a = a ? a->next : nullptr, b = b ? b->next : nullptr; 
  }
  if (carry) {
    shared_ptr<ListNode<int>> carry_node = make_shared<ListNode<int>>(ListNode<int>{1, nullptr});
    sum_iter->next = carry_node;
  }

  return sum_head->next;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "int_as_list_add.cc", "int_as_list_add.tsv",
                         &AddTwoNumbers, DefaultComparator{}, param_names);
}
