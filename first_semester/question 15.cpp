#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// design your won SuffixTreeNode using in SuffixTree
class SuffixTreeNode {
public:
  std::unordered_map<char, SuffixTreeNode *> children;
  int count = 0;
};

class SuffixTree {
private:
  SuffixTreeNode *root;
  std::string text;

  void deleteTrie(SuffixTreeNode *node) {
    for (auto &child : node->children) {
      deleteTrie(child.second);
    }
    delete node;
  }

public:
  SuffixTree(const std::string &text) : text(text) {
    root = new SuffixTreeNode();
    for (int i = 0; i < text.length(); i++) {
      buildSuffixTrie(text.substr(i));
    }
  }

  void buildSuffixTrie(const std::string &s) {
    SuffixTreeNode *current = root;

    for (char c : s) {
      if (!current->children[c]) {
        current->children[c] = new SuffixTreeNode();
      }
      current = current->children[c];
      current->count++;
    }
  }

  bool exist(const std::string &substring) {
    SuffixTreeNode *current = root;
    for (char c : substring) {
      if (!current->children[c]) {
        return false;
      }
      current = current->children[c];
    }
    return true;
  }

  int count(const std::string &substring) {
    SuffixTreeNode *current = root;
    for (auto &c : substring) {
      if (!current->children[c]) {
        return 0;
      }
      current = current->children[c];
    }
    return current->count;
  }

  ~SuffixTree() { deleteTrie(root); }
};

int main() {
  std::string text = "";
  while (true) {
    std::string temp;
    getline(std::cin, temp);
    if (temp == "")
      break;
    text += temp;
  }
  SuffixTree tree(text);

  std::string query;
  while (true) {
    getline(std::cin, query);
    if (query == "")
      break;
    std::cout << "Existence of '" << query
              << "': " << (tree.exist(query) ? "Yes" : "No") << std::endl;
    std::cout << "Count of '" << query << "': " << tree.count(query)
              << std::endl;
  }
  return 0;
}
