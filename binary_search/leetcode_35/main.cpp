#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
 public:
  int searchInsert(vector<int>& nums, int target) {
    if (nums.size() == 1) {
      if (nums[0] >= target) {
        return 0;
      } else {
        return 1;
      }
    }

    int l = 0, r = nums.size() - 1;

    while (l <= r) {
      if (nums[l] == target) return l;
      if (nums[r] == target) return r;

      auto mid = l + (r - l) / 2;

      if (nums[mid] == target) {
        return mid;
      }

      if (nums[mid] < target) {
        l = mid + 1;
        continue;
      }

      if (nums[mid] > target) {
        r = mid - 1;
        continue;
      }
    }

    return l;
  }
};

void runTest(int num, vector<int>& nums, int target) {
  Solution s;
  int result = s.searchInsert(nums, target);

  cout << format("Test #{}\nnums: [", num);
  for (int j = 0; j < nums.size(); ++j) {
    if (j) cout << ", ";
    cout << format("{:>3}", nums[j]);
  }
  cout << format("], target = {:>2}\n", target);
  cout << format("searchInsert() = {}\n\n", result);
}

int main() {
  vector<int> test1 = {1, 3, 5, 6};
  runTest(1, test1, 5);
  runTest(2, test1, 2);
  runTest(3, test1, 7);
  runTest(4, test1, 0);

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
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    int target = valDist(gen);

    runTest(i + 5, nums, target);
  }
}
