#include <format>
#include <iostream>
#include <random>

using namespace std;

class Solution {
 public:
  bool isPerfectSquare(int num) {
    size_t l = 1, r = num, mid = 0;

    while (l <= r) {
      mid = l + (r - l) / 2;

      size_t sq = mid * mid;

      if (sq == num) {
        return true;
      }

      if (sq > num) {
        r = mid - 1;
      }

      if (sq < num) {
        l = mid + 1;
      }
    }

    return false;
  }
};

void runTest(int num, int n) {
  Solution s;
  bool result = s.isPerfectSquare(n);

  cout << format("Test #{}\nn = {}\n", num, n);
  cout << format("isPerfectSquare() = {}\n\n", result);
}

int main() {
  runTest(1, 16);
  runTest(2, 14);
  runTest(3, 1);
  runTest(4, 2147395600);
  runTest(5, 81);
  runTest(6, 121);
  runTest(7, 1225);

  // random_device rd;
  // mt19937 gen(rd());
  // uniform_int_distribution<> dist(1, 10000);

  // for (int i = 0; i < 5; ++i) {
  //   int n = dist(gen);
  //   runTest(i + 5, n);
  // }
}
