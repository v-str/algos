#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::format;
using std::string;
using std::unordered_map;
using std::vector;

static vector<string> vec = {"abcabcbb", "bbbbb", "pwwkew"};

string generateRandomString() {
  thread_local std::mt19937 gen{std::random_device{}()};
  thread_local std::normal_distribution<> lenDist{25.0, 10.0};
  thread_local std::uniform_int_distribution<> charDist{32, 126};

  int len = std::clamp(static_cast<int>(std::round(lenDist(gen))), 1, 50);
  string s;
  s.reserve(len);
  for (int i = 0; i < len; ++i) {
    s.push_back(static_cast<char>(charDist(gen)));
  }
  return s;
}

void printSubStr(string s, int left, int right) {
  for (auto i = 0; i < s.length(); ++i) {
    if (i == left) {
      cout << "[";
    }

    cout << format("{0}", s.at(i));

    if (i == right) {
      cout << "]";
    }
  }

  if (right == s.length()) {
    cout << "]";
  }
  cout << "\n";
}

class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    int maxSubLen = 0, curLen = 0;
    int left = 0, right = left;
    unordered_map<char, int> uMap;

    if (s.length() == 1) {
      return 1;
    }

    while (right < s.length()) {
      auto isInserted = uMap.insert({s.at(right), right}).second;

      if (!isInserted) {
        auto oldIdx = uMap[s.at(right)];

        if (oldIdx >= left) {
          left = oldIdx + 1;
        }

        uMap[s.at(right)] = right;
      }

      ++right;

      curLen = right - left;

      if (curLen > maxSubLen) {
        maxSubLen = curLen;
      }
    }

    return maxSubLen;
  }
};

int main() {
  for (int i = 0; i < 5; ++i) {
    vec.push_back(generateRandomString());
  }

  Solution solution;

  for (auto it : vec) {
    auto len = solution.lengthOfLongestSubstring(it);
    cout << format("input len: {0}, str: {1}: {2}\n", it.length(), it, len);
  }
}
