#include "list_node.h"
#include "test_framework/generic_test.h"
// 1,2,3,4,5,6 => 
shared_ptr<ListNode<int>> ReverseList(shared_ptr<ListNode<int>> L) {
  auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
  auto iter = L;
  while (L && L->next) {
    auto new_head = L->next; // 2,3,4
    auto old_head = dummy_head->next; // 1,2,3
    dummy_head->next = new_head;// dh->2,dh->3,dh->4
    L->next = new_head->next;// 1->3,1->4,1->5
    new_head->next = old_head;// 2->1,3->2,4->3
  } // dh->4->3->2->1->5
  return dummy_head->next;
}

bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>> L) {
  shared_ptr<ListNode<int>> slow = L, fast = L;
  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
  }

  auto first_half_iter = L, second_half_iter = ReverseList(slow);
  while (second_half_iter && first_half_iter) {
    if (second_half_iter->data != first_half_iter->data) {
      return false;
    }
    first_half_iter = first_half_iter->next;
    second_half_iter = second_half_iter->next;
  }

  return true;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "is_list_palindromic.cc",
                         "is_list_palindromic.tsv", &IsLinkedListAPalindrome,
                         DefaultComparator{}, param_names);
}
