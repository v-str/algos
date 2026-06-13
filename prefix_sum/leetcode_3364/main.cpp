#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
 public:
  int minimumSumSubarray(vector<int>& nums, int l, int r) {
    int minSum = INT32_MAX;

    for (int curDist = l; curDist <= r; ++curDist) {
      int left = 0, right = 0, windowSum = 0;

      // накопим первое окно сум
      while (right < curDist) {
        windowSum += nums[right];
        ++right;
      }
      if (windowSum > 0) {
        minSum = min(minSum, windowSum);
      }

      // двигаем окно, считаем минимальную сумму
      while (right < nums.size()) {
        windowSum += nums[right] - nums[left];
        ++right;
        ++left;

        if (windowSum > 0) {
          minSum = min(minSum, windowSum);
        }
      }
    }

    if (minSum == INT32_MAX)
      return -1;
    else
      return minSum;
  }
};

void runTest(int num, vector<int>& nums, int l, int r) {
  Solution s;
  int result = s.minimumSumSubarray(nums, l, r);

  cout << format("Test #{}\nnums: [", num);
  for (int j = 0; j < nums.size(); ++j) {
    if (j) cout << ", ";
    cout << format("{:>3}", nums[j]);
  }
  cout << format("], l = {}, r = {}\n", l, r);
  cout << format("minimumSumSubarray() = {}\n\n", result);
}

int main() {
  vector<int> test1 = {3, -2, 1, 4};
  vector<int> test2 = {-2, 2, -3, 1};
  vector<int> test3 = {1, 2, 3, 4};

  runTest(1, test1, 2, 3);
  runTest(2, test2, 2, 3);
  runTest(3, test3, 2, 4);

  random_device rd;
  mt19937 gen(rd());
  normal_distribution<> valDist(0.0, 5.0);
  uniform_int_distribution<> lenDist(4, 8);
  uniform_int_distribution<> lDist(1, 2);

  for (int i = 0; i < 5; ++i) {
    int n = lenDist(gen);
    int l = lDist(gen);
    int r = uniform_int_distribution<>(l, min(l + 2, n))(gen);

    vector<int> nums;
    nums.reserve(n);
    for (int j = 0; j < n; ++j)
      nums.push_back(clamp<int>(round(valDist(gen)), -5, 5));

    runTest(i + 4, nums, l, r);
  }
}
