#include <algorithm>
#include <format>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

class Solution {
 public:
  int missingNumber(vector<int>& nums) {
    if (nums.size() == 1) {
      if (nums[0] == 0) {
        return 1;
      }
      return 0;
    }

    // считаем ожидаемую сумму от 0 до n
    auto expected = nums.size() * (nums.size() + 1) / 2;

    // считаем сумму всех чисел в массиве
    auto real = accumulate(nums.begin(), nums.end(), 0);

    if (expected != real) {
      return expected - real;
    } else {
      return 0;
    }
  }
};

void runTest(int num, vector<int>& nums) {
  Solution s;
  int result = s.missingNumber(nums);

  cout << format("Test #{}\nnums: [", num);
  for (int j = 0; j < nums.size(); ++j) {
    if (j) cout << ", ";
    cout << format("{:>3}", nums[j]);
  }
  cout << format("]\nmissingNumber() = {}\n\n", result);
}

int main() {
  vector<int> test1 = {3, 0, 1};
  vector<int> test2 = {0, 1};
  vector<int> test3 = {9, 6, 4, 2, 3, 5, 7, 0, 1};
  vector<int> test4 = {0};
  vector<int> test5 = {1, 2, 3};

  runTest(1, test1);
  runTest(2, test2);
  runTest(3, test3);
  runTest(4, test4);
  runTest(5, test5);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> nDist(3, 10);

  for (int i = 0; i < 5; ++i) {
    int n = nDist(gen);
    vector<int> nums;
    nums.reserve(n);
    for (int j = 0; j < n; ++j) nums.push_back(j);
    nums.erase(nums.begin() + uniform_int_distribution<>(0, n)(gen));
    shuffle(nums.begin(), nums.end(), gen);

    runTest(i + 6, nums);
  }
}
