#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

template <class T> class BinaryThreadedTreeNode {
private:
protected:
public:
  T *data;
  BinaryThreadedTreeNode *left, *right;
  bool isThread = false;
  BinaryThreadedTreeNode(T d) : right(nullptr), left(nullptr) {
    data = new T{d};
  }
  BinaryThreadedTreeNode() : data(nullptr), right(nullptr), left(nullptr) {}
};

template <class T> class BinarySearchThreadedTree : BinaryThreadedTreeNode<T> {
private:
  void CreateThread(BinaryThreadedTreeNode<T> *root,
                    BinaryThreadedTreeNode<T> *&pre) {
    if (!root)
      return;

    // left
    CreateThread(root->left, pre);

    // set thread for pre node
    if (pre && pre->right == nullptr) {
      pre->right = root;
      pre->isThread = true;
    }

    // update pre node
    pre = root;

    // right
    CreateThread(root->right, pre);
  }

public:
  BinarySearchThreadedTree() : BinaryThreadedTreeNode<T>() {}
  BinarySearchThreadedTree *insert(T d) {
    if (!this->data) {
      this->data = new T{d};
      this->left = new BinarySearchThreadedTree();
      this->right = new BinarySearchThreadedTree();
      return this;
    } else {
      if (*this->data > d)
        return (static_cast<BinarySearchThreadedTree<T> *>(this->left))
            ->insert(d);
      else
        return (static_cast<BinarySearchThreadedTree<T> *>(this->right))
            ->insert(d);
    }
  }
  void print() {
    BinaryThreadedTreeNode<T> *prev = nullptr;
    CreateThread(this, prev);
    BinaryThreadedTreeNode<T> *cur = this;
    while (cur && cur->left)
      cur = cur->left;
    while (cur) {
      if (cur->data)
        cout << *cur->data << " ";
      if (cur->isThread) {
        cur = cur->right;
      } else {
        cur = cur->right;
        while (cur && cur->left)
          cur = cur->left;
      }
    }
  }
};

int main() {
  int j;
  BinarySearchThreadedTree<int> bstt;
  srand(time(nullptr));
  for (j = 0; j < 10; j++)
    bstt.insert(rand() % 100);
  bstt.print();
}
