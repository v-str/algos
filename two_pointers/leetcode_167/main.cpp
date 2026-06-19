#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> twoSum(vector<int>& numbers, int target) {
    int l = 0, r = numbers.size() - 1;

    while (l < r) {
      auto sum = numbers[l] + numbers[r];

      if (sum == target) break;
      if (sum < target) ++l;
      if (sum > target) --r;
    }

    return {l + 1, r + 1};
  }
};

void runTest(int num, vector<int>& numbers, int target) {
  Solution s;
  auto result = s.twoSum(numbers, target);

  cout << format("Test #{}\nnumbers: [", num);
  for (int j = 0; j < numbers.size(); ++j) {
    if (j) cout << ", ";
    cout << format("{:>3}", numbers[j]);
  }
  cout << format("], target = {}\n", target);
  cout << format("twoSum() = [{}, {}]\n\n", result[0], result[1]);
}

int main() {
  vector<int> test1 = {2, 7, 11, 15};
  vector<int> test2 = {2, 3, 4};
  vector<int> test3 = {-1, 0};

  runTest(1, test1, 9);
  runTest(2, test2, 6);
  runTest(3, test3, -1);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> lenDist(4, 8);
  uniform_int_distribution<> valDist(-10, 10);

  for (int i = 0; i < 5; ++i) {
    int n = lenDist(gen);
    vector<int> nums;
    nums.reserve(n);
    for (int j = 0; j < n; ++j) nums.push_back(valDist(gen));
    sort(nums.begin(), nums.end());

    int target = nums[0] + nums[n - 1];

    runTest(i + 4, nums, target);
  }
}
