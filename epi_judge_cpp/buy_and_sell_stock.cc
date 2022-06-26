#include <vector>
#include <climits>

#include "test_framework/generic_test.h"
using std::vector;
using std::max;
double BuyAndSellStockOnce(const vector<double>& prices) {
  double max_profit = 0;
  int buy_index = 0;

  for(auto sell_index = 1; sell_index < prices.size(); ++sell_index) {
    double profit = prices[sell_index] - prices[buy_index]; // 1,-2,3,7
    max_profit = max(max_profit, profit); // 1,1,3,7
    if (profit < 0) {
      buy_index = sell_index; // 2
    }
  }

  return max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
