#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;

vector<vector<int>> generateVector(mt19937& gen) {
  normal_distribution<> val_dist(50.0, 20.0);
  uniform_int_distribution<> len_dist(1, 10);

  vector<vector<int>> result;
  for (int i = 0; i < 5; ++i) {
    int len = len_dist(gen);
    vector<int> v;
    v.reserve(len);
    for (int j = 0; j < len; ++j)
      v.push_back(clamp<int>(round(val_dist(gen)), 1, 100));
    result.push_back(move(v));
  }
  return result;
}

class Solution {
 public:
  int minSubArrayLen(int target, vector<int>& nums) {
    int minLen = INT32_MAX;
    int curSum = 0, right = 0, left = 0;

    while (right < nums.size()) {
      curSum += nums[right];

      while (curSum >= target) {
        minLen = min(minLen, (right + 1) - left);
        curSum -= nums[left];
        ++left;
      }

      ++right;
    }

    return (minLen == INT32_MAX) ? 0 : minLen;
  }
};

int main() {
  random_device rd;
  mt19937 gen(rd());
  auto numsVec = generateVector(gen);

  Solution s;

  for (int i = 0; i < numsVec.size(); ++i) {
    auto& nums = numsVec[i];
    int target = uniform_int_distribution<>(1, 200)(gen);

    cout << format("Test #{}\nnums: [", i + 1);
    for (int j = 0; j < nums.size(); ++j) {
      if (j) cout << ", ";
      cout << nums[j];
    }
    cout << format("], target = {}\n", target);

    int result = s.minSubArrayLen(target, nums);
    cout << format("minSubArrayLen = {}\n\n", result);
  }
}