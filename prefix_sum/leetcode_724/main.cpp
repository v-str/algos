#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
 public:
  int pivotIndex(vector<int>& nums) {
    vector<int> leftVec(nums.size(), 0);
    vector<int> rightVec(nums.size(), 0);
    int sum = 0;

    for (int i = 1; i < nums.size(); ++i) {
      sum += nums[i - 1];
      leftVec[i] += sum;
    }

    sum = 0;

    for (int i = nums.size() - 2; i >= 0; --i) {
      sum += nums[i + 1];
      rightVec[i] = sum;
    }

    for (int i = 0; i < leftVec.size(); ++i) {
      if (leftVec[i] == rightVec[i]) {
        return i;
      }
    }

    return -1;
  }
};

void runTest(int num, vector<int>& nums) {
  Solution s;
  int result = s.pivotIndex(nums);

  cout << format("Test #{}\nnums: [", num);
  for (int j = 0; j < nums.size(); ++j) {
    if (j) cout << ", ";
    cout << format("{:>3}", nums[j]);
  }
  cout << format("]\npivotIndex() = {}\n\n", result);
}

int main() {
  vector<int> test1 = {1, 7, 3, 6, 5, 6};
  vector<int> test2 = {1, 2, 3};
  vector<int> test3 = {2, 1, -1};
  vector<int> test4 = {5, -5, 0};

  runTest(1, test1);
  runTest(2, test2);
  runTest(3, test3);
  runTest(4, test4);

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

    runTest(i + 5, nums);
  }
}
