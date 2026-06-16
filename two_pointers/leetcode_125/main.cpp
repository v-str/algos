#include <algorithm>
#include <cctype>
#include <format>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isPalindrome(string s) {
    if (s.size() == 0) return true;

    size_t left = 0, right = s.size() - 1;

    while (left < right) {
      while (left < right && !isalnum(s[left])) ++left;
      while (left < right && !isalnum(s[right])) --right;

      if (left >= right) break;

      if (tolower(s[left]) != tolower(s[right])) {
        return false;
      }

      ++left;
      --right;
    }

    return true;
  }
};

void runTest(int num, string s) {
  Solution sol;
  bool result = sol.isPalindrome(s);

  cout << format("Test #{}\ns: \"{}\"\n", num, s);
  cout << format("isPalindrome() = {}\n\n", result);
}

string generatePalindrome(mt19937& gen) {
  string alnum = "abcdefghijklmnopqrstuvwxyz0123456789";
  uniform_int_distribution<> alnumLenDist(3, 5);
  uniform_int_distribution<> alnumDist(0, alnum.size() - 1);
  uniform_int_distribution<> noiseLenDist(0, 3);

  string core, padded;
  int half = alnumLenDist(gen);
  core.reserve(half);
  for (int j = 0; j < half; ++j) core.push_back(alnum[alnumDist(gen)]);

  string alnumPart = core;
  for (int j = half - 1; j >= 0; --j) alnumPart.push_back(core[j]);

  string noise = " .,:;!?-";
  uniform_int_distribution<> noiseDist(0, noise.size() - 1);

  for (int j = 0; j < alnumPart.size(); ++j) {
    int before = noiseLenDist(gen);
    for (int k = 0; k < before; ++k) padded.push_back(noise[noiseDist(gen)]);
    padded.push_back(alnumPart[j]);
  }
  int trailing = noiseLenDist(gen);
  for (int k = 0; k < trailing; ++k) padded.push_back(noise[noiseDist(gen)]);

  return padded;
}

string generateRandomString(mt19937& gen) {
  uniform_int_distribution<> lenDist(5, 15);
  uniform_int_distribution<> isPalindromeDist(0, 99);

  if (isPalindromeDist(gen) < 75) return generatePalindrome(gen);

  int n = lenDist(gen);
  string chars =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 .,:;!?-";
  uniform_int_distribution<> charDist(0, chars.size() - 1);

  string s;
  s.reserve(n);
  for (int j = 0; j < n; ++j) s.push_back(chars[charDist(gen)]);
  return s;
}

int main() {
  runTest(1, "A man, a plan, a canal: Panama");
  runTest(2, "race a car");
  runTest(3, " ");

  random_device rd;
  mt19937 gen(rd());

  for (int i = 0; i < 5; ++i) {
    string s = generateRandomString(gen);
    runTest(i + 4, s);
  }
}
