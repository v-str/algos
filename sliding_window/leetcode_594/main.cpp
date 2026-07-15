#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
 public:
  int findLHS(vector<int>& nums) {
    if (nums.size() == 0) {
      return 0;
    }

    sort(nums.begin(), nums.end());

    int l = 0, r = 0, maxLen = 0;

    while (r < nums.size()) {
      auto tempVal = nums[r] - nums[l];

      while (tempVal > 1) {
        ++l;
        tempVal = nums[r] - nums[l];
      }

      if (tempVal == 1) {
        maxLen = max(maxLen, (r - l) + 1);
      }

      ++r;
    }

    return maxLen;
  }
};

int AiSearchFunc(vector<int>& nums) {
  sort(nums.begin(), nums.end());
  int best = 0;
  int i = 0;
  for (int j = 0; j < (int)nums.size(); ++j) {
    while (nums[j] - nums[i] > 1) ++i;
    if (nums[j] - nums[i] == 1) best = max(best, j - i + 1);
  }
  return best;
}

void printNums(const vector<int>& nums) {
  cout << '[';
  for (size_t i = 0; i < nums.size(); ++i) {
    if (i) cout << ", ";
    cout << nums[i];
  }
  cout << ']';
}

void runTest(int num, vector<int> nums) {
  auto numsForAi = nums;

  cout << format("Test #{}\n", num);
  cout << "nums: ";
  printNums(nums);
  cout << '\n';

  Solution s;
  int userResult = s.findLHS(nums);
  int aiResult = AiSearchFunc(numsForAi);

  cout << format("user: {}\n", userResult);
  cout << format("ai:   {}\n", aiResult);

  if (userResult == aiResult)
    cout << "result: PASS\n";
  else
    cout << "result: FAIL\n";
  cout << '\n';
}

int main() {
  runTest(1, {1, 3, 2, 2, 5, 2, 3, 7});
  runTest(2, {1, 2, 3, 4});
  runTest(3, {1, 1, 1, 1});
  runTest(4, {1});
  runTest(5, {1, 2});
  runTest(6, {1, 1, 1, 1, 1, 1, 3, 5, 5, 6});

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> lenDist(1, 15);
  uniform_int_distribution<> valDist(0, 10);

  for (int i = 0; i < 5; ++i) {
    int len = lenDist(gen);
    vector<int> nums(len);
    for (int j = 0; j < len; ++j) nums[j] = valDist(gen);
    runTest(i + 6, nums);
  }
}
