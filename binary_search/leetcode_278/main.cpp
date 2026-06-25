#include <format>
#include <iostream>
#include <random>

using namespace std;

static int firstBad = 1;

bool isBadVersion(int version) { return version >= firstBad; }

class Solution {
 public:
  int firstBadVersion(int n) {
    if (n == 1) {
      return 1;
    }

    int left = 1, right = n;

    while (left < right) {
      auto mid = left + (right - left) / 2;

      if (isBadVersion(mid)) {
        if (!isBadVersion(mid - 1)) {
          return mid;
        }
        right = mid;
      } else {
        left = mid + 1;
      }
    }

    return left;
  }
};

void runTest(int num, int n, int bad) {
  firstBad = bad;
  Solution s;
  int result = s.firstBadVersion(n);

  cout << format("Test #{}\nn = {}, bad = {}\n", num, n, bad);
  cout << format("firstBadVersion() = {}\n\n", result);
}

int main() {
  runTest(1, 5, 4);
  runTest(2, 1, 1);
  runTest(3, 10, 10);
  runTest(4, 10, 1);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> nDist(2, 100);
  uniform_int_distribution<> badDist(1, 100);

  for (int i = 0; i < 5; ++i) {
    int n = nDist(gen);
    int bad = uniform_int_distribution<>(1, n)(gen);
    runTest(i + 5, n, bad);
  }
}
