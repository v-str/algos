#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

vector<int> randVector() {
  random_device rd;
  mt19937 gen(rd());
  normal_distribution<> dist(0.0, 7.0);

  vector<int> v;
  v.reserve(10);
  for (int i = 0; i < 10; ++i)
    v.push_back(clamp<int>(round(dist(gen)), -15, 15));
  return v;
}

int randK() {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(1, 5);
  return dist(gen);
}

/*

[8, -5, 1, 3, 6, 10], k = 3

*/

class Solution {
 public:
  double findMaxAverage(vector<int>& nums, int k) {
    // if (nums.empty() || k == 0 || k < 0) return 0.0;
    // if (k > nums.size()) k = nums.size();

    int maxSum = 0, windowSum = 0;

    for (auto i = 0; i < k; ++i) {
      windowSum += nums[i];
    }

    maxSum = windowSum;

    for (auto i = k; i < nums.size(); ++i) {
      windowSum += nums[i] - nums[i - k];
      maxSum = max(windowSum, maxSum);
    }

    return static_cast<double>(maxSum) / k;
  }
};

int main() {
  Solution s;

  for (int i = 0; i < 10; ++i) {
    auto nums = randVector();
    int k = randK();

    cout << format("Test #{}\nnums: [", i + 1);
    for (int j = 0; j < nums.size(); ++j) {
      if (j) cout << ", ";
      cout << format("{:>3}", nums[j]);
    }
    cout << format("], k = {}\n", k);

    double avg = s.findMaxAverage(nums, k);
    cout << format("findMaxAverage = {}\n\n", avg);
  }
}
