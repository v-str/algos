#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> uMap;
    uMap[0]++;

    size_t count = 0;
    int sum = 0;

    for (int i = 0; i < nums.size(); ++i) {
      sum += nums[i];
      count += uMap[sum - k];
      uMap[sum]++;
    }

    return count;
  }
};

int main() {
  random_device rd;
  mt19937 gen(rd());
  normal_distribution<> valDist(0.0, 10.0);
  uniform_int_distribution<> lenDist(5, 10);
  uniform_int_distribution<> queryCountDist(2, 5);

  for (int i = 0; i < 5; ++i) {
    int n = lenDist(gen);
    vector<int> nums;
    nums.reserve(n);
    for (int j = 0; j < n; ++j)
      nums.push_back(clamp<int>(round(valDist(gen)), -15, 15));

    int q = queryCountDist(gen);
    cout << format("Test #{}\nnums: [", i + 1);
    for (int j = 0; j < n; ++j) {
      if (j) cout << ", ";
      cout << format("{:>3}", nums[j]);
    }
    cout << "]\n";

    Solution s;

    for (int k = 0; k < q; ++k) {
      int target = uniform_int_distribution<>(-10, 10)(gen);
      int result = s.subarraySum(nums, target);
      cout << format("  subarraySum(k = {:>2}) = {}\n", target, result);
    }
    cout << "\n";
  }
}
