#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

#include <list>
#include <unordered_map>
using std::list; using std::unordered_map;
struct ISBN {
  bool operator=(const ISBN& that) {
    return data == that.data;
  }

  int data;
  int price = 0;
  list<ISBN>::iterator it;
};

class LruCache {
 public:
  LruCache(size_t capacity) : _capacity(capacity) {}
  int Lookup(int isbn) {
    int price = -1;
    if (auto it = cache.find(isbn); it != end(cache)) {
      ISBN temp = it->second;
      price = temp.price;
      lru.erase(it->second.it);
      lru.push_front(temp);
      it->second.it = lru.begin();
    }
    return price;
  }
  void Insert(int isbn, int price) {
    if (auto it = cache.find(isbn); it != end(cache)) {
      ISBN temp = it->second;
      lru.erase(it->second.it);
      lru.push_front(temp);
      it->second.it = lru.begin();
      return;
    } 
    if (lru.size() == _capacity) {
      int oldest_isbn = lru.back().data;
      cache.erase(oldest_isbn);
      lru.pop_back();
    }
    lru.push_front({isbn, price, lru.end()});
    lru.front().it = lru.begin();
    cache.insert({isbn, lru.front()});
  }
  bool Erase(int isbn) {
    if (auto it = cache.find(isbn); it != end(cache)) {
      lru.erase(it->second.it);
      cache.erase(isbn);
      return true;
    } 
    return false;
  }
  size_t _capacity = 0;
  list<ISBN> lru;
  unordered_map<int, ISBN> cache;
};



struct Op {
  std::string code;
  int arg1;
  int arg2;
};

namespace test_framework {
template <>
struct SerializationTrait<Op> : UserSerTrait<Op, std::string, int, int> {};
}  // namespace test_framework

void LruCacheTester(const std::vector<Op>& commands) {
  if (commands.empty() || commands[0].code != "LruCache") {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++) {
    auto& cmd = commands[i];
    if (cmd.code == "lookup") {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else if (cmd.code == "insert") {
      cache.Insert(cmd.arg1, cmd.arg2);
    } else if (cmd.code == "erase") {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"commands"};
  return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &LruCacheTester,
                         DefaultComparator{}, param_names);
}
