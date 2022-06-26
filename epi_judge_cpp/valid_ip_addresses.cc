#include <algorithm>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;
using std::max; using std::min; using std::to_string;
// 1111
void ProcessNextOctet(const string& s, int idx, int octet, string ip_addr, vector<string> &result) {
  int num_digits = max(static_cast<int>(s.size() - idx - (9 - octet*3)), 1);//1
  int max_digits = min(static_cast<int>(s.size() - idx - (3-octet)), 3);//1
  while (num_digits <= max_digits) {//1<=1
    string temp_str = s.substr(idx, num_digits);//0,1 "1"
    int octet_num = stoi(temp_str);//1
    if (temp_str[0] == '0' && num_digits > 1 || octet_num > 255) {//false
      num_digits++;
      continue;
    }
    string next_ip_addr = ip_addr + temp_str;//"255"
    if (octet == 3) {
      result.push_back(next_ip_addr);
    }
    else {
      next_ip_addr += '.';
      ProcessNextOctet(s, idx+num_digits, octet+1, next_ip_addr, result);
    }
    num_digits++;
  }
}

vector<string> GetValidIpAddress(const string& s) {
  vector<string> result;
  string ip_addr;
  ProcessNextOctet(s, 0, 0, ip_addr, result);
  return result;
}





int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "valid_ip_addresses.cc",
                         "valid_ip_addresses.tsv", &GetValidIpAddress,
                         UnorderedComparator{}, param_names);
}
