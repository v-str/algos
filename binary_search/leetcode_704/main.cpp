#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;

    while (left <= right) {
      int mid = left + (right - left) / 2;

      if (nums[mid] == target) return mid;

      if (nums[mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    return -1;
  }
};

void runTest(int num, vector<int>& nums, int target) {
  Solution s;
  int result = s.search(nums, target);

  cout << format("Test #{}\nnums: [", num);
  for (int j = 0; j < nums.size(); ++j) {
    if (j) cout << ", ";
    cout << format("{:>3}", nums[j]);
  }
  cout << format("], target = {:>2}\n", target);
  cout << format("search() = {}\n\n", result);
}

int main() {
  vector<int> test1 = {-1, 0, 3, 5, 9, 12};
  runTest(1, test1, 9);
  runTest(2, test1, 2);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> lenDist(5, 10);
  uniform_int_distribution<> valDist(-10, 10);

  for (int i = 0; i < 5; ++i) {
    int n = lenDist(gen);
    vector<int> nums;
    nums.reserve(n);
    for (int j = 0; j < n; ++j) nums.push_back(valDist(gen));
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    int target = valDist(gen);

    runTest(i + 3, nums, target);
  }
}
