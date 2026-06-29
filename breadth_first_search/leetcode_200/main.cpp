#include <algorithm>
#include <format>
#include <iostream>
#include <queue>
#include <random>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct PairHash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2>& p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);
    // Combine hashes (e.g., using XOR or boost::hash_combine style)
    return h1 ^ h2;
  }
};

class Solution {
 public:
  int numIslands(vector<vector<char>>& grid) {
    int islands = 0;

    int n = grid.size(), m = grid[0].size();
    vector<vector<char>> visited(n, vector<char>(m, '0'));
    queue<pair<int, int>> q;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (grid[i][j] == '1' && visited[i][j] == '0') {
          ++islands;
          q.push({i, j});
          visited[i][j] = '1';

          while (!q.empty()) {
            auto p = q.front();
            q.pop();

            for (int k = 0; k < 4; ++k) {
              int cx = p.second + DIR_X[k];
              int cy = p.first + DIR_Y[k];

              if (cx >= 0 && cx < m && cy >= 0 && cy < n &&
                  grid[cy][cx] == '1' && visited[cy][cx] == '0') {
                q.push({cy, cx});
                visited[cy][cx] = '1';
              }
            }
          }
        }
      }
    }

    return islands;
  }

 private:
  // 2 массива для поиска смежных ячеек
  const int DIR_X[4] = {0, 0, 1, -1};
  const int DIR_Y[4] = {1, -1, 0, 0};
};

int AiSearchFunc(vector<vector<char>>& grid) {
  int m = grid.size(), n = grid[0].size();
  int islands = 0;
  int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  for (int r = 0; r < m; ++r) {
    for (int c = 0; c < n; ++c) {
      if (grid[r][c] != '1') continue;

      ++islands;
      queue<pair<int, int>> q;
      q.push({r, c});
      grid[r][c] = '0';

      while (!q.empty()) {
        auto [cr, cc] = q.front();
        q.pop();

        for (auto& d : dirs) {
          int nr = cr + d[0], nc = cc + d[1];
          if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
          if (grid[nr][nc] != '1') continue;
          grid[nr][nc] = '0';
          q.push({nr, nc});
        }
      }
    }
  }

  return islands;
}

void runTest(int num, vector<vector<char>>& grid) {
  vector<vector<char>> gridForUser = grid;
  vector<vector<char>> gridForAi = grid;

  Solution s;
  int userResult = s.numIslands(gridForUser);
  int aiResult = AiSearchFunc(gridForAi);

  cout << format("Test #{}\ngrid:\n", num);
  for (auto& row : grid) {
    cout << "  [";
    for (int j = 0; j < row.size(); ++j) {
      if (j) cout << ", ";
      cout << format("'{}'", row[j]);
    }
    cout << "]\n";
  }
  cout << format("  user (Solution) = {}\n", userResult);
  cout << format("  ai   (AiSearch) = {}\n\n", aiResult);
}

int main() {
  vector<vector<char>> test1 = {{'1', '1', '1', '1', '0'},
                                {'1', '1', '0', '1', '0'},
                                {'1', '1', '0', '0', '0'},
                                {'0', '0', '0', '0', '0'}};

  vector<vector<char>> test2 = {{'1', '1', '0', '0', '0'},
                                {'1', '1', '0', '0', '0'},
                                {'0', '0', '1', '0', '0'},
                                {'0', '0', '0', '1', '1'}};

  runTest(1, test1);
  runTest(2, test2);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> mDist(3, 6);
  uniform_int_distribution<> nDist(3, 6);
  uniform_int_distribution<> valDist(0, 1);

  for (int i = 0; i < 5; ++i) {
    int m = mDist(gen);
    int n = nDist(gen);
    vector<vector<char>> grid(m, vector<char>(n));
    for (int r = 0; r < m; ++r)
      for (int c = 0; c < n; ++c) grid[r][c] = valDist(gen) ? '1' : '0';

    runTest(i + 3, grid);
  }
}
