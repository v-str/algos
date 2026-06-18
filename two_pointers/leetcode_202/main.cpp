#include <algorithm>
#include <cmath>
#include <format>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isHappy(int n) {
    int current = n;
    unordered_set<int> isAlreadySeen;

    while (true) {
      auto strN = to_string(current);
      int sum = 0;

      for (auto s : strN) {
        int digit = s - '0';
        sum += digit * digit;
      }

      if (sum == 1) {
        return true;
      }

      auto res = isAlreadySeen.insert(sum);
      if (!res.second) {
        // endless cycle
        break;
      }

      current = sum;
    }

    return false;
  }
};

void runTest(int num, int n) {
  Solution s;
  bool result = s.isHappy(n);

  cout << format("Test #{}\nn = {}\n", num, n);
  cout << format("isHappy() = {}\n\n", result);
}

int main() {
  runTest(1, 19);
  runTest(2, 2);
  runTest(3, 1);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(1, 100);

  for (int i = 0; i < 5; ++i) {
    int n = dist(gen);
    runTest(i + 4, n);
  }
}
