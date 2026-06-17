#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int findMaxK(vector<int>& nums) {
    unordered_map<int, int> uMap;

    /*
    сохраняю ключ равный значению из nums, а value равный индексу, наоборот в
    общем

    чтобы получить условно такой вот результат:
    дан вектор [-1, 2, -3, 3]
    преобразую его в мапу
    uMap[-1] = 0
    uMap[2] = 1
    uMap[-3] = 2
    uMap[3] = 3
    */

    for (auto i = 0; i < nums.size(); ++i) {
      uMap[nums[i]] = i;
    }

    int maxK = -1;
    for (auto i = 0; i < nums.size(); ++i) {
      int tKey = nums[i];
      if (tKey > 0) {
        tKey = -tKey;
      } else {
        tKey = abs(tKey);
      }

      if (uMap.find(tKey) != uMap.end()) {
        maxK = max(maxK, abs(tKey));
      }
    }

    return maxK;
  }
};

void runTest(int num, vector<int>& nums) {
  Solution s;
  int result = s.findMaxK(nums);

  cout << format("Test #{}\nnums: [", num);
  for (int j = 0; j < nums.size(); ++j) {
    if (j) cout << ", ";
    cout << format("{:>3}", nums[j]);
  }
  cout << format("]\nfindMaxK() = {}\n\n", result);
}

int main() {
  vector<int> test1 = {-1, 2, -3, 3};
  vector<int> test2 = {-1, 10, 6, 7, -7, 1};
  vector<int> test3 = {-10, 8, 6, 7, -2, -3};

  runTest(1, test1);
  runTest(2, test2);
  runTest(3, test3);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> lenDist(5, 10);
  normal_distribution<> valDist(0.0, 5.0);

  for (int i = 0; i < 5; ++i) {
    int n = lenDist(gen);
    vector<int> nums;
    nums.reserve(n);
    for (int j = 0; j < n; ++j) {
      int v = clamp<int>(round(valDist(gen)), -5, 5);
      if (v == 0) v = 1;
      nums.push_back(v);
    }

    runTest(i + 4, nums);
  }
}
