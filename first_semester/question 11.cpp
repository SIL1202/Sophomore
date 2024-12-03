#include <iostream>
#include <string>

using namespace std;

template <class T> class BinarySearchTree {
private:
  struct Node {
    T data;
    Node *left, *right;
    Node(T d) : data(d) {}
  };
  void inorder(Node *cur) {
    if (!cur)
      return;
    inorder(cur->left);
    cout << cur->data << " ";
    inorder(cur->right);
  }
  Node *insert(Node *cur, T d) {
    if (cur == nullptr) {
      return new Node(d);
    } else if (d <= cur->data) {
      cur->left = insert(cur->left, d);
    } else
      cur->right = insert(cur->right, d);
    return cur;
  }
  bool search(Node *cur, T d) {
    if (cur == nullptr)
      return false;
    if (d == cur->data)
      return true;
    else if (d <= cur->data)
      return search(cur->left, d);
    else
      return search(cur->right, d);
  }
  int height(Node *cur) {
    if (cur == nullptr)
      return -1;
    int LeftHeight = height(cur->left);
    int RightHeight = height(cur->right);
    return max(LeftHeight, RightHeight) + 1;
  }

  Node *root;

public:
  BinarySearchTree() : root(nullptr) {}
  void insertElement(T d) { root = insert(root, d); }
  void print() {
    inorder(root);
    cout << endl;
  }
  bool search(T d) { return search(root, d); }
  int height() { return height(root); }
};

int main() {
  int data;
  string command;
  BinarySearchTree<int> *bst = new BinarySearchTree<int>();
  while (true) {
    cin >> command;
    if (command == "insert") {
      cin >> data;
      bst->insertElement(data);
    } else if (command == "search") {
      cin >> data;
      if (bst->search(data))
        cout << "true" << endl;
      else
        cout << "false" << endl;
    } else if (command == "height") {
      cout << bst->height() << endl;
    } else if (command == "print") {
      bst->print();
    } else if (command == "exit") {
      break;
    }
  }
}
