#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int low = 0, fast = 1;

    while (fast < nums.size()) {
      if (nums[low] != nums[fast]) {
        nums[low + 1] = nums[fast];
        ++low;
      }

      ++fast;
    }

    return low + 1;
  }
};

void runTest(int num, vector<int>& nums) {
  vector<int> original = nums;
  Solution s;
  int k = s.removeDuplicates(nums);

  cout << format("Test #{}\nnums: [", num);
  for (int j = 0; j < original.size(); ++j) {
    if (j) cout << ", ";
    cout << format("{:>3}", original[j]);
  }
  cout << "]\n";
  cout << format("k = {}\n", k);
  cout << "unique: [";
  for (int j = 0; j < k; ++j) {
    if (j) cout << ", ";
    cout << format("{:>3}", nums[j]);
  }
  cout << "]\n\n";
}

int main() {
  vector<int> test1 = {1, 1, 2};
  vector<int> test2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};

  runTest(1, test1);
  runTest(2, test2);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> lenDist(5, 10);
  uniform_int_distribution<> valDist(0, 5);

  for (int i = 0; i < 5; ++i) {
    int n = lenDist(gen);
    vector<int> nums;
    nums.reserve(n);
    for (int j = 0; j < n; ++j) nums.push_back(valDist(gen));
    sort(nums.begin(), nums.end());

    runTest(i + 3, nums);
  }
}
