#include <format>
#include <functional>
#include <iostream>
#include <optional>
#include <queue>
#include <random>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

TreeNode* buildTree(const vector<optional<int>>& data) {
  if (data.empty() || !data[0].has_value()) return nullptr;

  auto* root = new TreeNode(data[0].value());
  queue<TreeNode*> q;
  q.push(root);

  for (size_t i = 1; i < data.size(); i += 2) {
    auto* node = q.front();
    q.pop();

    if (data[i].has_value()) {
      node->left = new TreeNode(data[i].value());
      q.push(node->left);
    }

    if (i + 1 < data.size() && data[i + 1].has_value()) {
      node->right = new TreeNode(data[i + 1].value());
      q.push(node->right);
    }
  }

  return root;
}

void deleteTree(TreeNode* root) {
  if (!root) return;
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

class Solution {
 public:
  vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> leveledResult;
    if (!root) {
      return leveledResult;
    }

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
      auto size = q.size();
      vector<int> level;

      while (size != 0) {
        auto node = q.front();
        q.pop();
        level.push_back(node->val);

        if (node->left) {
          q.push(node->left);
        }

        if (node->right) {
          q.push(node->right);
        }

        --size;
      }

      if (!level.empty()) {
        leveledResult.push_back(level);
      }
    }

    return leveledResult;
  }
};

vector<vector<int>> AiSearchFunc(TreeNode* root) {
  if (!root) return {};

  vector<vector<int>> result;
  queue<TreeNode*> q;
  q.push(root);

  while (!q.empty()) {
    int sz = q.size();
    vector<int> level;
    level.reserve(sz);

    while (sz--) {
      auto* node = q.front();
      q.pop();
      level.push_back(node->val);

      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);
    }

    result.push_back(move(level));
  }

  return result;
}

void printLevels(const vector<vector<int>>& levels) {
  cout << '[';
  for (size_t i = 0; i < levels.size(); ++i) {
    if (i) cout << ", ";
    cout << '[';
    for (size_t j = 0; j < levels[i].size(); ++j) {
      if (j) cout << ", ";
      cout << levels[i][j];
    }
    cout << ']';
  }
  cout << "]\n";
}

void printTreeSerialized(const vector<optional<int>>& data) {
  cout << "  [";
  for (size_t i = 0; i < data.size(); ++i) {
    if (i) cout << ", ";
    if (data[i].has_value())
      cout << data[i].value();
    else
      cout << "null";
  }
  cout << "]\n";
}

struct RenderBox {
  vector<string> lines;
  int rootCol;

  int width() const { return lines.empty() ? 0 : (int)lines[0].size(); }
  int height() const { return (int)lines.size(); }
};

RenderBox renderTree(TreeNode* root) {
  if (!root) return {{}, 0};

  string val = to_string(root->val);
  int vw = (int)val.size();

  auto left = renderTree(root->left);
  auto right = renderTree(root->right);

  if (!root->left && !root->right) {
    return {{val}, vw / 2};
  }

  int gap = 2;
  RenderBox result;

  auto renderSingle = [&](const RenderBox& child, bool isLeft) -> RenderBox {
    int cw = child.width();
    int ch = child.height();
    int totalW = max(vw, cw);
    int valC = (totalW - vw) / 2;
    int childC = (totalW - cw) / 2;
    int shift = 1;

    if (isLeft) {
      if (childC > 0) {
        childC -= shift;
        valC += shift;
      }
    } else {
      if (valC > 0) {
        valC -= shift;
        childC += shift;
      }
    }
    if (childC + cw > totalW) totalW = childC + cw;
    if (valC + vw > totalW) totalW = valC + vw;

    int connCol = childC + child.rootCol;

    result.lines.resize(2 + ch);
    result.lines[0] = string(valC, ' ') + val;
    result.lines[1] = string(totalW, ' ');
    result.lines[1][connCol] = isLeft ? '/' : '\\';

    for (int i = 0; i < ch; ++i) {
      string line = string(childC, ' ') + child.lines[i];
      if ((int)line.size() < totalW)
        line += string(totalW - (int)line.size(), ' ');
      result.lines[2 + i] = line;
    }

    result.rootCol = valC + vw / 2;
    return result;
  };

  if (!root->left) return renderSingle(right, false);
  if (!root->right) return renderSingle(left, true);

  int lw = left.width();
  int rw = right.width();
  int childrenW = lw + gap + rw;
  int totalW = max(vw, childrenW);
  int valOff = max(0, (totalW - vw) / 2);
  int leftOff = (totalW - childrenW) / 2;
  int rightOff = leftOff + lw + gap;
  int ch = max(left.height(), right.height());

  result.lines.resize(2 + ch);
  result.lines[0] = string(valOff, ' ') + val;
  result.lines[1] = string(totalW, ' ');

  int vm = valOff + vw / 2;
  int lrc = leftOff + left.rootCol;
  int rrc = rightOff + right.rootCol;

  if (lrc < vm)
    result.lines[1][lrc] = '/';
  else if (lrc > vm)
    result.lines[1][lrc] = '\\';

  if (rrc > vm)
    result.lines[1][rrc] = '\\';
  else if (rrc < vm)
    result.lines[1][rrc] = '/';

  auto pad = [&](const RenderBox& box, int w, int h) -> vector<string> {
    vector<string> out = box.lines;
    while ((int)out.size() < h) out.push_back(string(w, ' '));
    for (auto& line : out)
      if ((int)line.size() < w) line += string(w - (int)line.size(), ' ');
    return out;
  };

  auto lp = pad(left, lw, ch);
  auto rp = pad(right, rw, ch);

  for (int i = 0; i < ch; ++i)
    result.lines[2 + i] = lp[i] + string(gap, ' ') + rp[i];

  result.rootCol = vm;
  return result;
}

void printTreeVisual(TreeNode* root) {
  auto box = renderTree(root);
  if (box.lines.empty()) {
    cout << "  null\n";
    return;
  }
  for (auto& line : box.lines) {
    while (!line.empty() && line.back() == ' ') line.pop_back();
    cout << "  " << line << '\n';
  }
}

void runTest(int num, const vector<optional<int>>& treeData) {
  auto* rootForUser = buildTree(treeData);
  auto* rootForAi = buildTree(treeData);

  cout << format("Test #{}\n", num);
  cout << "tree:\n";
  printTreeSerialized(treeData);
  printTreeVisual(rootForUser);

  Solution s;
  auto userResult = s.levelOrder(rootForUser);
  auto aiResult = AiSearchFunc(rootForAi);

  cout << "user: ";
  printLevels(userResult);
  cout << "ai:   ";
  printLevels(aiResult);
  cout << "\n";

  deleteTree(rootForUser);
  deleteTree(rootForAi);
}

TreeNode* generateRandomTree(mt19937& gen, int& remainingNodes) {
  if (remainingNodes <= 0) return nullptr;

  uniform_int_distribution<int> valDist(0, 99);
  auto* node = new TreeNode(valDist(gen));
  --remainingNodes;

  if (remainingNodes > 0) {
    uniform_int_distribution<int> coin(0, 1);
    if (coin(gen)) node->left = generateRandomTree(gen, remainingNodes);
    if (remainingNodes > 0 && coin(gen))
      node->right = generateRandomTree(gen, remainingNodes);
  }

  return node;
}

int main() {
  runTest(1, {3, 9, 20, nullopt, nullopt, 15, 7});
  runTest(2, {1});
  runTest(3, {});
}
