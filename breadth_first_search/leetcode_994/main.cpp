#include <format>
#include <iostream>
#include <queue>
#include <random>
#include <utility>
#include <vector>

using namespace std;

class Solution {
 public:
  int orangesRotting(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    int freshOranges = 0;

    queue<pair<int, int>> rottenQ;

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == kFresh) {
          ++freshOranges;
        }
        if (grid[i][j] == kRotten) {
          rottenQ.push({i, j});
        }
      }
    }

    if (freshOranges == 0) {
      return 0;
    }

    int minutes = -1;

    int dX[4] = {1, 0, -1, 0};
    int dY[4] = {0, 1, 0, -1};

    while (!rottenQ.empty()) {
      int sz = rottenQ.size();

      while (sz--) {
        auto rottenPair = rottenQ.front();
        rottenQ.pop();

        for (int i = 0; i < 4; ++i) {
          int nX = rottenPair.first + dX[i];
          int nY = rottenPair.second + dY[i];

          if (nX >= 0 && nX < m && nY >= 0 && nY < n &&
              grid[nX][nY] == kFresh) {
            rottenQ.push({nX, nY});
            --freshOranges;
            grid[nX][nY] = kRotten;
          }
        }
      }

      ++minutes;
    }

    int freshRemainder = 0;

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == kFresh) {
          ++freshRemainder;
        }
      }
    }

    if (freshRemainder == 0) {
      return minutes;
    } else {
      return -1;
    }
  }

 private:
  const int kEmpty = 0;
  const int kFresh = 1;
  const int kRotten = 2;
};

int AiSearchFunc(vector<vector<int>>& grid) {
  int m = grid.size(), n = grid[0].size();
  queue<pair<int, int>> q;
  int fresh = 0;

  for (int r = 0; r < m; ++r) {
    for (int c = 0; c < n; ++c) {
      if (grid[r][c] == 2)
        q.push({r, c});
      else if (grid[r][c] == 1)
        ++fresh;
    }
  }

  if (fresh == 0) return 0;

  int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  int minutes = 0;

  while (!q.empty()) {
    ++minutes;
    int sz = q.size();
    while (sz--) {
      auto [cr, cc] = q.front();
      q.pop();
      for (auto& d : dirs) {
        int nr = cr + d[0], nc = cc + d[1];
        if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
        if (grid[nr][nc] != 1) continue;
        grid[nr][nc] = 2;
        --fresh;
        q.push({nr, nc});
      }
    }
    if (fresh == 0) break;
  }

  return fresh == 0 ? minutes : -1;
}

void runTest(int num, vector<vector<int>> grid) {
  vector<vector<int>> gridForAi = grid;

  Solution s;
  int userResult = s.orangesRotting(grid);
  int aiResult = AiSearchFunc(gridForAi);

  cout << format("Test #{}\ngrid:\n", num);
  for (auto& row : grid) {
    cout << "  [";
    for (int j = 0; j < row.size(); ++j) {
      if (j) cout << ", ";
      cout << row[j];
    }
    cout << "]\n";
  }
  cout << format("  user (Solution) = {}\n", userResult);
  cout << format("  ai   (AiSearch) = {}\n\n", aiResult);
}

int main() {
  vector<vector<int>> test1 = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
  vector<vector<int>> test2 = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
  vector<vector<int>> test3 = {{0, 2}};

  runTest(1, test1);
  runTest(2, test2);
  runTest(3, test3);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> mDist(3, 6);
  uniform_int_distribution<> nDist(3, 6);
  uniform_int_distribution<> valDist(0, 2);

  for (int i = 0; i < 5; ++i) {
    int m = mDist(gen);
    int n = nDist(gen);
    vector<vector<int>> grid(m, vector<int>(n));
    for (int r = 0; r < m; ++r)
      for (int c = 0; c < n; ++c) grid[r][c] = valDist(gen);

    runTest(i + 4, grid);
  }
}
