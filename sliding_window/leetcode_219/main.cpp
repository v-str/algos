#include <algorithm>
#include <format>
#include <iostream>
#include <map>
#include <random>
#include <vector>

using namespace std;

vector<vector<int>> generateVector() {
  random_device rd;
  mt19937 gen(rd());
  normal_distribution<> val_dist(0.0, 20.0);
  uniform_int_distribution<> len_dist(1, 10);

  vector<vector<int>> result;
  for (int i = 0; i < 10; ++i) {
    int len = len_dist(gen);
    vector<int> v;
    v.reserve(len);
    for (int j = 0; j < len; ++j)
      v.push_back(clamp<int>(round(val_dist(gen)), -15, 15));
    result.push_back(move(v));
  }
  return result;
}

class Solution {
 public:
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    map<int, int> m;
    int left = 0, right = 0;
    while (right < nums.size()) {
      if (m.find(nums[right]) != m.end()) {
        return true;
      }
      m[nums[right]]++;
      if (m.size() > k) {
        m.erase(nums[left]);
        ++left;
      }
      ++right;
    }
    return false;
  }
};

int main() {
  random_device rd;
  mt19937 gen(rd());

  // vector<int> v1 = {1, 2, 3, 1};
  // vector<int> v2 = {1, 0, 1, 1};
  // vector<int> v3 = {1, 2, 3, 1, 2, 3};

  auto numsVec = generateVector();

  Solution s;
  // bool result = s.containsNearbyDuplicate(v1, 3);
  // cout << format("containsNearbyDuplicate = {}\n\n", result);

  // result = s.containsNearbyDuplicate(v2, 1);
  // cout << format("containsNearbyDuplicate = {}\n\n", result);

  // result = s.containsNearbyDuplicate(v3, 2);
  // cout << format("containsNearbyDuplicate = {}\n\n", result);

  for (int i = 0; i < numsVec.size(); ++i) {
    auto& nums = numsVec[i];
    int k = uniform_int_distribution<>(0, 5)(gen);

    cout << format("Test #{}\nnums: [", i + 1);
    for (int j = 0; j < nums.size(); ++j) {
      if (j) cout << ", ";
      cout << nums[j];
    }
    cout << format("], k = {}\n", k);

    Solution s;
    bool result = s.containsNearbyDuplicate(nums, k);
    cout << format("containsNearbyDuplicate = {}\n\n", result);
  }
}
