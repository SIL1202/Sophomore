#include <iostream>
#include <map>
#include <string>
using namespace std;

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
      code[v->ch] =
          prefix.empty() ? "0" : prefix; // initial "0" if prefix has no content

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
  std::map<char, std::string> get_code_table() const { return code; }

  std::string operator[](char ch) const {
    auto tar = code.find(ch);
    if (tar == code.end())
      throw "Not in alphabet";
    else
      return tar->second;
  }
};

// ##### STUDENT'S IMPLEMENTATION AREA START #####
// ##### 學生的實作區域 START #####
unsigned long long
calculate_encoded_length(const std::string &text,
                         const HuffmanCode &huffman_encoder) {
  // TODO: Implement this function.
  // TODO: 實作此函式。
  // Iterate through `text`. For each character, get its Huffman code string
  // from `huffman_encoder` and add the length of that code string to a running
  // total. 遍歷 `text`。對每個字元，從 `huffman_encoder` 取得其霍夫曼編碼字串，
  // 並將該編碼字串的長度累加到總長度中。
  unsigned long long total_length = 0;
  // Your code here // 你的程式碼寫在這裡
  auto table = huffman_encoder.get_code_table();
  for (const char c : text) {
    total_length +=
        table[c].length(); // on need to access second object because operator[]
                           // had already access it.
  }
  return total_length;
}
// ##### STUDENT'S IMPLEMENTATION AREA END #####
// ##### 學生的實作區域 END #####

int main() {
  using namespace std;
  string text1;
  std::cin >> text1;
  HuffmanCode encoder1(text1);
  cout << "Huffman codes for '" << text1 << "':" << endl;
  for (auto const &[key, val] : encoder1.get_code_table()) {
    cout << key << ": " << val << endl;
  }
  unsigned long long length1 = calculate_encoded_length(text1, encoder1);
  cout << "Encoded length for '" << text1 << "': " << length1 << endl;
  return 0;
}
