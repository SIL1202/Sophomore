#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct TrieNode {
  unordered_map<char, TrieNode *> children; // 子節點的映射
  vector<char> order;                       // 記錄插入順序
  bool EndOfWord;

  TrieNode() : EndOfWord(false) {}
};

class Trie {
private:
  TrieNode *root;

  // Helper function for preorder traversal
  void preorderHelper(TrieNode *node, string current, int level) {
    if (!node)
      return;

    // 如果當前節點是單詞結尾，打印該字串並根據層級縮排
    if (node->EndOfWord || node->children.size() != 1) {
      cout << string(level * 2, ' ') << current << endl;
    }

    // 遍歷子節點，按照插入順序處理
    for (char c : node->order) {
      preorderHelper(node->children[c], current + c, level + 1);
    }
  }

  // Helper function to delete the trie
  void deleteTrie(TrieNode *node) {
    for (auto &child : node->children) {
      deleteTrie(child.second);
    }
    delete node;
  }

public:
  Trie() { root = new TrieNode(); }

  ~Trie() { deleteTrie(root); }

  void insert(string value) {
    TrieNode *current = root;
    for (char c : value) {
      if (!current->children[c]) {
        current->children[c] = new TrieNode();
        current->order.push_back(c); // 記錄插入順序
      }
      current = current->children[c];
    }
    current->EndOfWord = true;
  }

  bool search(string key) {
    TrieNode *current = root;
    for (char c : key) {
      if (!current->children[c]) {
        return false;
      }
      current = current->children[c];
    }
    return current->EndOfWord;
  }

  void preorder() {
    cout << "[]" << endl; // Start of trie display
    preorderHelper(root, "", -1);
  }
};

int main() {
  Trie *trie = new Trie();
  string command, key, value;

  while (true) {
    cin >> command;
    if (command == "insert") {
      cin >> value;
      trie->insert(value);
    } else if (command == "search") {
      cin >> key;
      if (trie->search(key))
        cout << "exist" << endl;
      else
        cout << "not exist" << endl;
    } else if (command == "print") {
      trie->preorder();
    } else if (command == "exit") {
      break;
    }
  }

  delete trie; // Clean up memory
  return 0;
}
