#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

// null -> null
// 1->null -> null
// 1->2->3->4->2
// ^        ^
#include <unordered_set>
using std::unordered_set;
int CountCycleLength(shared_ptr<ListNode<int>> list) {
  shared_ptr<ListNode<int>> counter = list->next;
  int cycle_length = 1;
  while (counter != list) {
    counter = counter->next;
    ++cycle_length;
  }
  return cycle_length;
}

shared_ptr<ListNode<int>> FindCycleStart(const shared_ptr<ListNode<int>>& list, int cycle_length) {
  shared_ptr<ListNode<int>> left = list, right = list;
  for (auto i = 0; i < cycle_length; ++i) {
    right = right->next;
  }
  while (left != right) {
    left = left->next;
    right = right->next;
  }

  return left;
}

shared_ptr<ListNode<int>> HasCycle(const shared_ptr<ListNode<int>>& list) {
  shared_ptr<ListNode<int>> slow = list;
  shared_ptr<ListNode<int>> fast = list->next;
  bool update_slow = false;
  bool found_cycle = false;
  while (slow && fast) {
    if (slow == fast) {
      found_cycle = true;
      break;
    }
    if (update_slow = !update_slow) {
      slow = slow->next;
    }
    fast = fast->next;
  }
  if (!found_cycle) {
    return nullptr;
  }
  int cycle_length = CountCycleLength(slow);
  return FindCycleStart(list, cycle_length);
}

void HasCycleWrapper(TimedExecutor& executor,
                     const shared_ptr<ListNode<int>>& head, int cycle_idx) {
  int cycle_length = 0;
  if (cycle_idx != -1) {
    if (!head) {
      throw std::runtime_error("Can't cycle empty list");
    }
    shared_ptr<ListNode<int>> cycle_start, cursor = head;
    while (cursor->next) {
      if (cursor->data == cycle_idx) {
        cycle_start = cursor;
      }
      cursor = cursor->next;
      cycle_length += !!cycle_start;
    }
    if (cursor->data == cycle_idx) {
      cycle_start = cursor;
    }
    if (!cycle_start) {
      throw std::runtime_error("Can't find a cycle start");
    }
    cursor->next = cycle_start;
    cycle_length++;
  }
  shared_ptr<ListNode<int>> result =
      executor.Run([&] { return HasCycle(head); });

  if (cycle_idx == -1) {
    if (result != nullptr) {
      throw TestFailure("Found a non-existing cycle");
    }
  } else {
    if (result == nullptr) {
      throw TestFailure("Existing cycle was not found");
    }

    auto cursor = result;
    do {
      cursor = cursor->next;
      cycle_length--;
      if (!cursor || cycle_length < 0) {
        throw TestFailure(
            "Returned node does not belong to the cycle or is not the "
            "closest node to the head");
      }
    } while (cursor != result);

    if (cycle_length != 0) {
      throw TestFailure(
          "Returned node does not belong to the cycle or is not the closest "
          "node to the head");
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "head", "cycle_idx"};
  return GenericTestMain(args, "is_list_cyclic.cc", "is_list_cyclic.tsv",
                         &HasCycleWrapper, DefaultComparator{}, param_names);
}
