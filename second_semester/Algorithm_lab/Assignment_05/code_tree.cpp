// digraph hierarchy {
//     1 [label = ""]
//     2 [label = "C"]
//     3 [label = ""]
//     6 [label = "A"]
//     7 [label = "B"]
//     1 -> 2 [label = "0"]
//     1 -> 3 [label = "1"]
//     3 -> 6 [label = "0"]
//     3 -> 7 [label = "1"]
//
// }
//
#include <map>
#include <queue>
#include <string>
#include <vector>

class HuffmanCode {
private:
  struct Node {
    Node *e0, *e1;
    int freq;
    char ch = -1;
    int id; // Unique insertion ID for tie-breaking
  };

  Node *root;
  std::map<char, std::string> code;

  struct node_comp {
    bool operator()(const Node *a, const Node *b) const {
      if (a->freq == b->freq)
        return a->id > b->id; // Smaller ID means higher priority
      return a->freq > b->freq;
    }
  };
  void travel(const Node *v, std::string prefix) {
    if (v->e0 == nullptr && v->e1 == nullptr)
      code[v->ch] = prefix.empty() ? "0" : prefix;

    if (v->e0)
      travel(v->e0, prefix + "0");
    if (v->e1)
      travel(v->e1, prefix + "1");
  }

public:
  HuffmanCode(std::string text) {
    std::map<char, int> ch_count;
    std::priority_queue<Node *, std::vector<Node *>, node_comp> trees;
    for (char ch : text) {
      if (ch_count.find(ch) == ch_count.end())
        ch_count[ch] = 1; // if not found
      else
        ch_count[ch]++; // if found then increment freq
    }

    int uid = 0;
    for (auto &[ch, freq] : ch_count) {
      trees.push(new Node{nullptr, nullptr, freq, ch, uid++});
    }

    // step 2 and 3
    while (true) {
      Node *t0 = trees.top();
      trees.pop();
      // if t1 is only one tree
      if (trees.empty()) {
        root = t0;
        break;
      }
      Node *t1 = trees.top();
      trees.pop();

      // For internal nodes:
      trees.push(new Node{t0, t1, t0->freq + t1->freq, -1, uid++});
    }
    travel(root, "");
  }

  std::string operator[](char ch) const {
    auto tar = code.find(ch);
    if (tar == code.end())
      throw "Not in alphabet";
    else
      return tar->second;
  }
};
