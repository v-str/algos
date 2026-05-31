#include <algorithm>
#include <format>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

vector<pair<string, string>> generateVector() {
  random_device rd;
  mt19937 gen(rd());

  normal_distribution<> len_dist(10.0, 4.0);
  uniform_int_distribution<> char_dist(0, 51);
  uniform_real_distribution<> prob(0.0, 1.0);

  auto random_char = [&]() -> char {
    int r = char_dist(gen);
    if (r < 26) return 'a' + r;
    return 'A' + r - 26;
  };

  auto random_string = [&](int max_len) -> string {
    int len = clamp<int>(round(len_dist(gen)), 1, max_len);
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) s += random_char();
    return s;
  };

  vector<pair<string, string>> result;
  result.reserve(5);

  for (int i = 0; i < 1; ++i) {
    string first = random_string(20);
    int target_len = prob(gen) < 0.8
                         ? max(1, static_cast<int>(first.size()) / 3)
                         : clamp<int>(round(len_dist(gen)), 1, 20);

    string second;
    double r = prob(gen);

    if (r < 0.3) {
      int start = uniform_int_distribution<>(0, first.size() - 1)(gen);
      int sub_len = uniform_int_distribution<>(
          1, static_cast<int>(first.size()) - start)(gen);
      second = first.substr(start, sub_len);
      shuffle(second.begin(), second.end(), gen);
    } else {
      second.reserve(target_len);
      double r2 = prob(gen);

      if (r2 < 0.7) {
        for (int j = 0; j < target_len; ++j)
          second += first[uniform_int_distribution<>(0, first.size() - 1)(gen)];
      } else if (r2 < 0.9) {
        uniform_int_distribution<> pick(0, first.size() - 1);
        uniform_int_distribution<> repeat(2, 4);
        while (static_cast<int>(second.size()) < target_len) {
          char c = first[pick(gen)];
          int n =
              min(repeat(gen), target_len - static_cast<int>(second.size()));
          second.append(n, c);
        }
      } else {
        second = random_string(target_len);
      }
    }

    result.emplace_back(move(first), move(second));
  }

  return result;
}

class Solution {
 public:
  string minWindow(string s, string t) {
    auto m = s.length();
    auto n = t.length();
    string minSubstr;

    return minSubstr;
  }
};

int main() {
  auto vec = generateVector();

  pair<string, string> f("GBFCACCBBOECODABENC", "ABBC");
  Solution sol;

  // for (const auto& [a, b] : vec) {
  //   cout << format("(\"{}\", \"{}\")  ({}, {}) minWindow: {}\n", a, b,
  //   a.size(),
  //                  b.size(), sol.minWindow(a, b));
  // }

  // auto f = vec.at(0);
  auto r = sol.minWindow(f.first, f.second);

  cout << format("s: {}, t: {}, res: {}\n", f.first, f.second, r);

  return 0;
}
