#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;

/*
Test #1
nums: [  1,   2,   3,   4]
result: [24, 12, 8, 6]

Test #2
nums: [ -1,   1,   0,  -3,   3]
result: []
*/

class Solution {
 public:
  vector<int> productExceptSelf(vector<int>& nums) {
    vector<int> V(nums.size(), 1);

    int temp = 1;
    V[0] = temp;

    for (auto i = 1; i < nums.size(); ++i) {
      temp *= nums[i - 1];
      V[i] = temp;
    }

    temp = 1;
    int i = nums.size() - 1;
    while (i >= 0) {
      V[i] = temp * V[i];
      temp *= nums[i];
      --i;
    }

    return V;
  }
};

void runTest(int num, vector<int>& nums) {
  Solution s;
  auto result = s.productExceptSelf(nums);

  cout << format("Test #{}\nnums: [", num);
  for (int j = 0; j < nums.size(); ++j) {
    if (j) cout << ", ";
    cout << format("{:>3}", nums[j]);
  }
  cout << "]\nresult: [";
  for (int j = 0; j < result.size(); ++j) {
    if (j) cout << ", ";
    cout << format("{:>3}", result[j]);
  }
  cout << "]\n\n";
}

int main() {
  vector<int> test1 = {1, 2, 3, 4};
  vector<int> test2 = {-1, 1, 0, -3, 3};

  runTest(1, test1);
  runTest(2, test2);

  random_device rd;
  mt19937 gen(rd());
  normal_distribution<> valDist(0.0, 5.0);
  uniform_int_distribution<> lenDist(3, 7);

  for (int i = 0; i < 5; ++i) {
    int n = lenDist(gen);
    vector<int> nums;
    nums.reserve(n);
    for (int j = 0; j < n; ++j)
      nums.push_back(clamp<int>(round(valDist(gen)), -5, 5));

    runTest(i + 3, nums);
  }
}
