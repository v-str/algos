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
  bool isUnivalTree(TreeNode* root) { return dfs(root, root->val); }

  bool dfs(TreeNode* node, const int& ref) {
    if (!node) return true;

    if (node->val != ref) {
      return false;
    }

    bool leftRes = dfs(node->left, ref);
    if (!leftRes) return false;

    bool rightRes = dfs(node->right, ref);
    if (!rightRes) return false;

    return true;
  }
};

bool AiSearchFunc(TreeNode* root) {
  if (!root) return true;
  function<bool(TreeNode*, int)> dfs = [&](TreeNode* node, int val) -> bool {
    if (!node) return true;
    if (node->val != val) return false;
    return dfs(node->left, val) && dfs(node->right, val);
  };
  return dfs(root, root->val);
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

void printSerialized(const vector<optional<int>>& data) {
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
  printSerialized(treeData);
  printTreeVisual(rootForUser);

  Solution s;
  bool userResult = s.isUnivalTree(rootForUser);
  bool aiResult = AiSearchFunc(rootForAi);

  cout << format("user: {}\n", userResult ? "true" : "false");
  cout << format("ai:   {}\n", aiResult ? "true" : "false");

  if (userResult == aiResult)
    cout << "result: PASS\n";
  else
    cout << "result: FAIL\n";
  cout << '\n';

  deleteTree(rootForUser);
  deleteTree(rootForAi);
}

int main() {
  runTest(1, {1, 1, 1, 1, 1, nullopt, 1});
  runTest(2, {2, 2, 2, 5, 2});

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> nodeCount(1, 10);
  uniform_int_distribution<> valDist(1, 5);

  for (int i = 0; i < 4; ++i) {
    int uniform = valDist(gen);
    int remaining = nodeCount(gen);
    function<TreeNode*(int&)> genTree = [&](int& rem) -> TreeNode* {
      if (rem <= 0) return nullptr;
      auto* node = new TreeNode(uniform);
      --rem;
      if (rem > 0) {
        uniform_int_distribution<int> coin(0, 1);
        if (coin(gen)) node->left = genTree(rem);
        if (rem > 0 && coin(gen)) node->right = genTree(rem);
      }
      return node;
    };
    auto* root = genTree(remaining);

    vector<optional<int>> treeData;
    if (root) {
      queue<TreeNode*> q;
      q.push(root);
      treeData.push_back(root->val);
      while (!q.empty()) {
        auto* node = q.front();
        q.pop();
        if (node->left) {
          treeData.push_back(node->left->val);
          q.push(node->left);
        } else {
          treeData.push_back(nullopt);
        }
        if (node->right) {
          treeData.push_back(node->right->val);
          q.push(node->right);
        } else {
          treeData.push_back(nullopt);
        }
      }
      while (!treeData.empty() && !treeData.back().has_value())
        treeData.pop_back();
      deleteTree(root);
    }

    runTest(i + 3, treeData);
  }

  for (int i = 0; i < 2; ++i) {
    int remaining = nodeCount(gen);
    function<TreeNode*(int&)> genMixed = [&](int& rem) -> TreeNode* {
      if (rem <= 0) return nullptr;
      auto* node = new TreeNode(valDist(gen));
      --rem;
      if (rem > 0) {
        uniform_int_distribution<int> coin(0, 1);
        if (coin(gen)) node->left = genMixed(rem);
        if (rem > 0 && coin(gen)) node->right = genMixed(rem);
      }
      return node;
    };
    auto* root = genMixed(remaining);

    vector<optional<int>> treeData;
    if (root) {
      queue<TreeNode*> q;
      q.push(root);
      treeData.push_back(root->val);
      while (!q.empty()) {
        auto* node = q.front();
        q.pop();
        if (node->left) {
          treeData.push_back(node->left->val);
          q.push(node->left);
        } else {
          treeData.push_back(nullopt);
        }
        if (node->right) {
          treeData.push_back(node->right->val);
          q.push(node->right);
        } else {
          treeData.push_back(nullopt);
        }
      }
      while (!treeData.empty() && !treeData.back().has_value())
        treeData.pop_back();
      deleteTree(root);
    }

    runTest(i + 7, treeData);
  }
}
