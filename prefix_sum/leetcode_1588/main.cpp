#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
 public:
  int sumOddLengthSubarrays(vector<int>& arr) {
    // считаем каждый элемент
    int total = 0;
    for (auto num : arr) {
      total += num;
    }

    // начинаем суммировать окна, первое минимальное окно нечетных массивов - 3
    auto left = 0, right = 0, tmpSum = 0;

    while (left < arr.size()) {
      tmpSum += arr[right];

      // нечетное
      if ((right - left) % 2 == 0) {
        if (right != left) {
          total += tmpSum;
        }
      }

      ++right;

      if (right == arr.size()) {
        right = ++left;
        tmpSum = 0;
      }
    }

    return total;
  }
};

void runTest(int num, vector<int>& arr) {
  Solution s;
  int result = s.sumOddLengthSubarrays(arr);

  cout << format("Test #{}\narr: [", num);
  for (int j = 0; j < arr.size(); ++j) {
    if (j) cout << ", ";
    cout << format("{:>3}", arr[j]);
  }
  cout << format("]\nsumOddLengthSubarrays() = {}\n\n", result);
}

int main() {
  vector<int> test1 = {1, 4, 2, 5, 3};
  vector<int> test2 = {1, 2};
  vector<int> test3 = {10, 11, 12};

  runTest(1, test1);
  runTest(2, test2);
  runTest(3, test3);

  random_device rd;
  mt19937 gen(rd());
  normal_distribution<> valDist(5.0, 3.0);
  uniform_int_distribution<> lenDist(3, 7);

  for (int i = 0; i < 5; ++i) {
    int n = lenDist(gen);
    vector<int> arr;
    arr.reserve(n);
    for (int j = 0; j < n; ++j)
      arr.push_back(clamp<int>(round(valDist(gen)), 1, 20));

    runTest(i + 4, arr);
  }
}
