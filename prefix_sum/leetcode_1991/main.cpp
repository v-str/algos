#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
 public:
  int findMiddleIndex(vector<int>& nums) {
    int total = 0;
    for (auto num : nums) total += num;

    int lSum = 0;
    for (auto i = 0; i < nums.size(); ++i) {
      if (lSum == total - lSum - nums[i]) {
        return i;
      }
      lSum += nums[i];
    }

    return -1;
  }
};

void runTest(int num, vector<int>& nums) {
  Solution s;
  int result = s.findMiddleIndex(nums);

  cout << format("Test #{}\nnums: [", num);
  for (int j = 0; j < nums.size(); ++j) {
    if (j) cout << ", ";
    cout << format("{:>3}", nums[j]);
  }
  cout << format("]\nfindMiddleIndex() = {}\n\n", result);
}

int main() {
  vector<int> test1 = {2, 3, -1, 8, 4};
  vector<int> test2 = {1, -1, 4};
  vector<int> test3 = {2, 5};

  runTest(1, test1);
  runTest(2, test2);
  runTest(3, test3);

  random_device rd;
  mt19937 gen(rd());
  normal_distribution<> valDist(0.0, 10.0);
  uniform_int_distribution<> lenDist(5, 10);

  for (int i = 0; i < 5; ++i) {
    int n = lenDist(gen);
    vector<int> nums;
    nums.reserve(n);
    for (int j = 0; j < n; ++j)
      nums.push_back(clamp<int>(round(valDist(gen)), -15, 15));

    runTest(i + 4, nums);
  }
}
