#include <cmath>
#include <format>
#include <functional>
#include <iostream>
#include <optional>
#include <queue>
#include <random>
#include <string>
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
  vector<double> averageOfLevels(TreeNode* root) {
    queue<TreeNode*> q;
    vector<double> res;

    q.push(root);

    while (!q.empty()) {
      auto sz = q.size();
      double levelSize = sz;

      double sum = 0.0;

      while (sz--) {
        auto node = q.front();
        q.pop();
        sum += node->val;

        if (node->left) {
          q.push(node->left);
        }
        if (node->right) {
          q.push(node->right);
        }
      }

      res.push_back(sum / levelSize);
    }

    return res;
  }
};

vector<double> AiSearchFunc(TreeNode* root) {
  if (!root) return {};

  vector<double> result;
  queue<TreeNode*> q;
  q.push(root);

  while (!q.empty()) {
    int sz = q.size();
    long long sum = 0;

    for (int i = 0; i < sz; ++i) {
      auto* node = q.front();
      q.pop();
      sum += node->val;

      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);
    }

    result.push_back((double)sum / sz);
  }

  return result;
}

bool approxEqual(const vector<double>& a, const vector<double>& b) {
  if (a.size() != b.size()) return false;
  for (size_t i = 0; i < a.size(); ++i)
    if (abs(a[i] - b[i]) > 1e-5) return false;
  return true;
}

void printDoubles(const vector<double>& v) {
  cout << '[';
  for (size_t i = 0; i < v.size(); ++i) {
    if (i) cout << ", ";
    cout << v[i];
  }
  cout << ']';
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

void runTest(int num, const vector<optional<int>>& treeData) {
  auto* rootForUser = buildTree(treeData);
  auto* rootForAi = buildTree(treeData);

  cout << format("Test #{}\n", num);
  cout << "tree:\n";
  printTreeSerialized(treeData);
  printTreeVisual(rootForUser);

  Solution s;
  auto userResult = s.averageOfLevels(rootForUser);
  auto aiResult = AiSearchFunc(rootForAi);

  cout << "user: ";
  printDoubles(userResult);
  cout << '\n';
  cout << "ai:   ";
  printDoubles(aiResult);
  cout << '\n';

  if (approxEqual(userResult, aiResult))
    cout << "result: PASS\n";
  else
    cout << "result: FAIL\n";
  cout << '\n';

  deleteTree(rootForUser);
  deleteTree(rootForAi);
}

TreeNode* generateRandomTree(mt19937& gen, int& remainingNodes) {
  if (remainingNodes <= 0) return nullptr;

  uniform_int_distribution<int> valDist(-10, 99);
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
  runTest(2, {3, 9, 20, 15, 7});

  // random_device rd;
  // mt19937 gen(rd());
  // uniform_int_distribution<> nodeCount(1, 12);

  // for (int i = 0; i < 6; ++i) {
  //   int remaining = nodeCount(gen);
  //   auto* root = generateRandomTree(gen, remaining);

  //   vector<optional<int>> treeData;
  //   if (root) {
  //     queue<TreeNode*> q;
  //     q.push(root);
  //     treeData.push_back(root->val);
  //     while (!q.empty()) {
  //       auto* node = q.front();
  //       q.pop();
  //       if (node->left) {
  //         treeData.push_back(node->left->val);
  //         q.push(node->left);
  //       } else {
  //         treeData.push_back(nullopt);
  //       }
  //       if (node->right) {
  //         treeData.push_back(node->right->val);
  //         q.push(node->right);
  //       } else {
  //         treeData.push_back(nullopt);
  //       }
  //     }
  //     while (!treeData.empty() && !treeData.back().has_value())
  //       treeData.pop_back();
  //     deleteTree(root);
  //   }

  //   runTest(i + 3, treeData);
  // }
}
