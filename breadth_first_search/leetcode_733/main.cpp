#include <format>
#include <iostream>
#include <queue>
#include <random>
#include <utility>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc,
                                int color) {
    vector<vector<int>> result(image);
    vector<vector<bool>> visited(image.size(),
                                 vector<bool>(image[0].size(), false));
    queue<pair<int, int>> q;

    int dX[4] = {0, 1, 0, -1};
    int dY[4] = {1, 0, -1, 0};

    q.push({sr, sc});

    int changingColor = image[sr][sc];

    while (!q.empty()) {
      auto p = q.front();
      q.pop();

      int x = p.first, y = p.second;
      visited[x][y] = true;

      if (result[x][y] == changingColor) {
        result[x][y] = color;
      }

      for (int k = 0; k < 4; ++k) {
        int nX = x + dX[k];
        int nY = y + dY[k];

        if (nX >= 0 && nX < image.size() && nY >= 0 && nY < image[0].size()) {
          if (visited[nX][nY] == false && result[nX][nY] == changingColor) {
            q.push({nX, nY});
          }
        }
      }
    }

    return result;
  }
};

void runTest(int num, vector<vector<int>> image, int sr, int sc, int color) {
  Solution s;
  auto result = s.floodFill(image, sr, sc, color);

  cout << format("Test #{}\nimage:\n", num);
  for (auto& row : image) {
    cout << "  [";
    for (int j = 0; j < row.size(); ++j) {
      if (j) cout << ", ";
      cout << format("{:>2}", row[j]);
    }
    cout << "]\n";
  }
  cout << format("sr = {}, sc = {}, color = {}\n", sr, sc, color);
  cout << "result:\n";
  for (auto& row : result) {
    cout << "  [";
    for (int j = 0; j < row.size(); ++j) {
      if (j) cout << ", ";
      cout << format("{:>2}", row[j]);
    }
    cout << "]\n";
  }
  cout << "\n";
}

int main() {
  vector<vector<int>> test1 = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
  runTest(1, test1, 1, 1, 2);

  vector<vector<int>> test2 = {{0, 0, 0}, {0, 0, 0}};
  runTest(2, test2, 0, 0, 0);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> mDist(3, 6);
  uniform_int_distribution<> nDist(3, 6);
  uniform_int_distribution<> valDist(0, 3);
  uniform_int_distribution<> coordDist(0, 5);
  uniform_int_distribution<> colorDist(0, 5);

  for (int i = 0; i < 5; ++i) {
    int m = mDist(gen);
    int n = nDist(gen);
    vector<vector<int>> img(m, vector<int>(n));
    for (int r = 0; r < m; ++r)
      for (int c = 0; c < n; ++c) img[r][c] = valDist(gen);

    int sr = coordDist(gen) % m;
    int sc = coordDist(gen) % n;
    int color = colorDist(gen);

    runTest(i + 3, img, sr, sc, color);
  }
}
