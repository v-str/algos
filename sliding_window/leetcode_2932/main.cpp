#include <algorithm>
#include <cmath>
#include <format>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

using namespace std;

vector<vector<int>> generateVector() {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> len_dist(1, 10);
  uniform_int_distribution<> val_dist(1, 25);

  vector<vector<int>> result;
  for (int i = 0; i < 1; ++i) {
    int len = len_dist(gen);
    vector<int> v;
    v.reserve(len);
    for (int j = 0; j < len; ++j) v.push_back(val_dist(gen));
    result.push_back(move(v));
  }
  return result;
}

// class Solution {
//  public:
//   int maximumStrongPairXor(vector<int>& nums) {
//     vector<pair<int, int>> strongVec;
//     int maxXor = 0;

//     int i = 0, j = 0;
//     while (j < nums.size()) {
//       pair<int, int> p;

//       p.first = nums[i];
//       p.second = nums[j];

//       auto absVal = abs(p.first - p.second);
//       auto minVal = min(p.first, p.second);

//       if (absVal <= minVal) {
//         strongVec.push_back(p);
//       }

//       if (j == (nums.size() - 1)) {
//         j = i;
//         ++i;
//       }

//       ++j;
//     }

//     for (auto i : strongVec) {
//       maxXor = max(maxXor, i.first ^ i.second);
//     }

//     return maxXor;
//   }
// };

class Solution {
 public:
  int maximumStrongPairXor(vector<int>& nums) {
    int maxXor = 0;

    int i = 0, j = 0;
    while (j < nums.size()) {
      if (abs(nums[i] - nums[j]) <= min(nums[i], nums[j])) {
        maxXor = max(maxXor, nums[i] ^ nums[j]);
      }

      if (j == (nums.size() - 1)) {
        j = i;
        ++i;
      }

      ++j;
    }

    return maxXor;
  }
};

int main() {
  auto numsVec = generateVector();

  // vector<int> numsVec = {1, 2, 3, 4, 5};

  for (int i = 0; i < numsVec.size(); ++i) {
    auto& nums = numsVec[i];

    cout << format("Test #{}\nnums: [", i + 1);

    for (int j = 0; j < nums.size(); ++j) {
      if (j) cout << ", ";
      cout << nums[j];
    }
    cout << "]\n";

    cout << endl;

    Solution s;
    int result = s.maximumStrongPairXor(nums);
    cout << format("maximumStrongPairXor = {}\n\n", result);
  }
}
