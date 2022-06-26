#include <set>
#include <stdexcept>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

// 1->2->3->4->2
//    5->3->4->2
// determine if there is a cycle in list 1 and list 2 (save pointer within the cycles of the lists
// if cycle is in one of them but the other return null
// if no cycle, then look at end of lists (next is null) to see if they match, if they do then return the last node
// if cycle in both then have pointer in cycle in one of the lists and iterate the other pointer in the other list until you reach the other pointer (which means overlap) else if you reach back to the start then no overlap

shared_ptr<ListNode<int>> HasCycle(const shared_ptr<ListNode<int>>& list) {
  if (!list) {
    return list;
  }
  shared_ptr<ListNode<int>> slow = list, fast = list->next;
  while (slow && fast && fast->next && slow != fast) {
    slow = slow->next;
    fast = fast->next->next;
  }
  if (fast && fast->next) {
    return fast;
  }
  return nullptr;
}

shared_ptr<ListNode<int>> FindEnd(shared_ptr<ListNode<int>> list) {
  while (list && list->next) {
    list = list->next;
  }
  return list;
}
// 1->2->3->4->null
//      ^     ^
// 1->2->1
shared_ptr<ListNode<int>> OverlappingLists(shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
  auto l0_has_cycle = HasCycle(l0);
  auto l1_has_cycle = HasCycle(l1);
  if (l0_has_cycle && l1_has_cycle) {
    auto iter = l0_has_cycle->next;
    while (iter != l0_has_cycle) {
      if (iter == l1_has_cycle) {
        return iter;
      }
      iter = iter->next;
    }
    if (iter == l1_has_cycle) {
      return iter;
    }
    return nullptr;
  } else if (l0_has_cycle || l1_has_cycle) {
    return nullptr;
  } else {
    // Find end of lists
    auto l0_end = FindEnd(l0);
    return l0_end == FindEnd(l1) ? l0_end : nullptr;
  }
}

void OverlappingListsWrapper(TimedExecutor& executor,
                             shared_ptr<ListNode<int>> l0,
                             shared_ptr<ListNode<int>> l1,
                             shared_ptr<ListNode<int>> common, int cycle0,
                             int cycle1) {
  if (common) {
    if (!l0) {
      l0 = common;
    } else {
      auto it = l0;
      while (it->next) {
        it = it->next;
      }
      it->next = common;
    }

    if (!l1) {
      l1 = common;
    } else {
      auto it = l1;
      while (it->next) {
        it = it->next;
      }
      it->next = common;
    }
  }

  if (cycle0 != -1 && l0) {
    auto last = l0;
    while (last->next) {
      last = last->next;
    }
    auto it = l0;
    while (cycle0-- > 0) {
      if (!it) {
        throw std::runtime_error("Invalid input data");
      }
      it = it->next;
    }
    last->next = it;
  }

  if (cycle1 != -1 && l1) {
    auto last = l1;
    while (last->next) {
      last = last->next;
    }
    auto it = l1;
    while (cycle1-- > 0) {
      if (!it) {
        throw std::runtime_error("Invalid input data");
      }
      it = it->next;
    }
    last->next = it;
  }

  std::set<shared_ptr<ListNode<int>>> common_nodes;
  auto it = common;
  while (it && common_nodes.count(it) == 0) {
    common_nodes.insert(it);
    it = it->next;
  }

  auto result = executor.Run([&] { return OverlappingLists(l0, l1); });

  if (!((common_nodes.empty() && result == nullptr) ||
        common_nodes.count(result) > 0)) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0",     "l1",
                                       "common",   "cycle0", "cycle1"};
  return GenericTestMain(args, "do_lists_overlap.cc", "do_lists_overlap.tsv",
                         &OverlappingListsWrapper, DefaultComparator{},
                         param_names);
}
