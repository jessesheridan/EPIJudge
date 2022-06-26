#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

//     1->3->4->6->7
// 8->9->10->4->6->7
// 1->2->3
// 4->5->6->7->8
shared_ptr<ListNode<int>> OverlappingNoCycleLists(shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
  shared_ptr<ListNode<int>> l0_runner = l0, l1_runner = l1;
  int l0_length = 1, l1_length = 1;
  while (l0_runner && l0_runner->next) {
    l0_runner = l0_runner->next;
    ++l0_length;
  }
  while (l1_runner && l1_runner->next) {
    l1_runner = l1_runner->next;
    ++l1_length;
  }
  while (l0_length > l1_length) {
    l0 = l0->next;
    --l0_length;
  } 
  while (l1_length > l0_length) {
    l1 = l1->next;
    --l1_length;
  }
  if (!l0 || !l1) {
    return nullptr;
  }
  while (l0 != l1) {
    l0 = l0->next;
    l1 = l1->next;
  }

  return l0;
}

void OverlappingNoCycleListsWrapper(TimedExecutor& executor,
                                    shared_ptr<ListNode<int>> l0,
                                    shared_ptr<ListNode<int>> l1,
                                    shared_ptr<ListNode<int>> common) {
  if (common) {
    if (l0) {
      auto i = l0;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l0 = common;
    }

    if (l1) {
      auto i = l1;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l1 = common;
    }
  }

  auto result = executor.Run([&] { return OverlappingNoCycleLists(l0, l1); });

  if (result != common) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0", "l1", "common"};
  return GenericTestMain(
      args, "do_terminated_lists_overlap.cc", "do_terminated_lists_overlap.tsv",
      &OverlappingNoCycleListsWrapper, DefaultComparator{}, param_names);
}
