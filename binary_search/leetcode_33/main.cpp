#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1;

    while (l <= r) {
      auto mid = l + (r - l) / 2;

      if (nums[mid] == target) {
        return mid;
      }

      if (nums[l] == target) {
        return l;
      }

      if (nums[r] == target) {
        return r;
      }

      if (nums[l] <= nums[mid]) {
        if (nums[l] < target && target < nums[mid]) {
          r = mid - 1;
          continue;
        } else {
          l = mid + 1;
        }
      }

      if (nums[mid] <= nums[r]) {
        if (nums[mid] < target && target < nums[r]) {
          l = mid + 1;
          continue;
        } else {
          r = mid - 1;
        }
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
  vector<int> test1 = {4, 5, 6, 7, 0, 1, 2};
  runTest(1, test1, 5);
  runTest(2, test1, 3);

  vector<int> test2 = {4, 5, 6, 7, 8, 1, 2, 3};
  runTest(3, test2, 8);

  vector<int> test3 = {1};
  runTest(4, test3, 0);

  vector<int> test4 = {5, 1, 2, 3, 4};
  runTest(5, test4, 1);

  // random_device rd;
  // mt19937 gen(rd());
  // uniform_int_distribution<> lenDist(5, 10);
  // uniform_int_distribution<> valDist(-10, 10);
  // uniform_int_distribution<> pivotDist(1, 5);

  // for (int i = 0; i < 5; ++i) {
  //   int n = lenDist(gen);
  //   vector<int> nums;
  //   nums.reserve(n);
  //   for (int j = 0; j < n; ++j) nums.push_back(valDist(gen));
  //   sort(nums.begin(), nums.end());
  //   nums.erase(unique(nums.begin(), nums.end()), nums.end());

  //   int pivot = pivotDist(gen) % nums.size();
  //   rotate(nums.begin(), nums.begin() + pivot, nums.end());

  //   int target = valDist(gen);

  //   runTest(i + 4, nums, target);
  // }
}
