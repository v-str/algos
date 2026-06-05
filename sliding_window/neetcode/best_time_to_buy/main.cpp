#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

vector<vector<int>> generateVector() {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> val_dist(0, 100);
  uniform_int_distribution<> len_dist(1, 15);

  vector<vector<int>> result;
  for (int i = 0; i < 10; ++i) {
    int len = len_dist(gen);
    vector<int> v;
    v.reserve(len);
    for (int j = 0; j < len; ++j) v.push_back(val_dist(gen));
    result.push_back(move(v));
  }
  return result;
}

class Solution {
 public:
  // минимум stl
  int maxProfit(vector<int>& prices) {
    int right = 1, left = 0, mP = 0;

    while (right < prices.size()) {
      if (prices[right] <= prices[left]) {
        left = right;
      } else {
        if (mP < (prices[right] - prices[left])) {
          mP = prices[right] - prices[left];
        }
      }

      ++right;
    }

    return mP;
  }
};

int main() {
  auto numsVec = generateVector();

  for (int i = 0; i < numsVec.size(); ++i) {
    auto& nums = numsVec[i];

    cout << format("Test #{}\nprices: [", i + 1);
    for (int j = 0; j < nums.size(); ++j) {
      if (j) cout << ", ";
      cout << nums[j];
    }
    cout << "]\n";

    Solution s;
    int profit = s.maxProfit(nums);
    cout << format("maxProfit = {}\n\n", profit);
  }
}
