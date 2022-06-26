#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// [8,1,5,6]
using std::min;
using std::max;
using std::numeric_limits;

double BuyAndSellStockTwice(const vector<double>& prices) {
  vector<double> first(prices.size(), 0);
  vector<double> second(prices.size(), 0);
  double max_profit = 0;
  double min_so_far = numeric_limits<double>::max();
  if (prices.empty()) {
    return 0.0;
  }

  for (auto i = 0; i < prices.size(); ++i) {
    max_profit = max(max_profit, prices[i]-min_so_far);
    first[i] = max_profit;
    min_so_far = min(min_so_far, prices[i]);
  }
  
  max_profit = 0;
  double max_so_far = numeric_limits<double>::min();
  for (int i = prices.size() - 1; i >= 0; --i) {
    max_profit = max(max_profit, max_so_far-prices[i]);
    second[i] = max_profit;
    max_so_far = max(max_so_far, prices[i]);
  }

  double first_value = 0;
  max_profit = 0;
  for (auto i = 0; i < prices.size(); ++i) {
    max_profit = max(max_profit, first_value + second[i]);
    first_value = first[i];
  }
  
  return max_profit;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
