#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;
// 1->2->3, 2 => 2->3->1
// 1->2->3->4->5, 3 3->4->5->1->2->null
// n mod k
// 1->2->null, 5->1, dh->3
// 
int Length(shared_ptr<ListNode<int>> L) {
  int length=0;
  while (L->next) {
    L = L->next;
    ++length;
  }
  return length;
}
shared_ptr<ListNode<int>> GetNthNode(int n, shared_ptr<ListNode<int>> L) {
  while (n--) {
    L = L->next;
  }
  return L;
}
// 1->2->3, 2 => 2->3->1
// 1->2->3, 1 => 
// 0, null or 5,null or 0,1->2->3->4 => null
// 1,1->null => 1->null
shared_ptr<ListNode<int>> CyclicallyRightShiftList(shared_ptr<ListNode<int>> L, int k) {
  if (!L) {
    return L;
  }
  auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
  shared_ptr<ListNode<int>> iter = dummy_head;
  int length = Length(iter);
  k = k % length;
  int shift = length - k;
  if (shift < 1 || shift >= length) {
    return L;
  }
  iter = GetNthNode(shift, dummy_head);
  auto last_node = GetNthNode(length, dummy_head);
  auto temp = iter->next;
  iter->next = nullptr;
  last_node->next = dummy_head->next;
  dummy_head->next = temp;

  return dummy_head->next;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(
      args, "list_cyclic_right_shift.cc", "list_cyclic_right_shift.tsv",
      &CyclicallyRightShiftList, DefaultComparator{}, param_names);
}
