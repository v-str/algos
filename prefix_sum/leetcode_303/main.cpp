#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class NumArray {
 public:
  NumArray(vector<int>& nums) : m_prefixVector(nums.size() + 1, 0) {
    for (int i = 0; i < nums.size(); ++i) {
      m_prefixVector[i + 1] = nums[i] + m_prefixVector[i];
    }
  }

  int sumRange(int left, int right) {
    return m_prefixVector[right + 1] - m_prefixVector[left];
  }

 private:
  vector<int> m_prefixVector;
};

int main() {
  random_device rd;
  mt19937 gen(rd());
  normal_distribution<> valDist(0.0, 10.0);
  uniform_int_distribution<> lenDist(5, 10);
  uniform_int_distribution<> queryCountDist(2, 5);

  for (int i = 0; i < 5; ++i) {
    int n = lenDist(gen);
    vector<int> nums;
    nums.reserve(n);
    for (int j = 0; j < n; ++j)
      nums.push_back(clamp<int>(round(valDist(gen)), -15, 15));

    NumArray na(nums);

    int q = queryCountDist(gen);
    cout << format("Test #{}\nnums: [", i + 1);
    for (int j = 0; j < n; ++j) {
      if (j) cout << ", ";
      cout << format("{:>3}", nums[j]);
    }
    cout << "]\n";

    for (int k = 0; k < q; ++k) {
      int left = uniform_int_distribution<>(0, n - 1)(gen);
      int right = uniform_int_distribution<>(left, n - 1)(gen);
      int result = na.sumRange(left, right);
      cout << format("  sumRange({}, {}) = {}\n", left, right, result);
    }
    cout << "\n";
  }
}
