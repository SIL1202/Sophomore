// PREPEND BEGIN
/*some text*/
// PREPEND END

// TEMPLATE BEGIN
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
using namespace std;

template <class T> class Node {
public:
  Node() { data = new T; }
  Node(T d) {
    data = new T;
    (*data) = d;
  }
  Node &operator=(T d) {
    (*data) = d;
    return *this;
  }
  friend std::ostream &operator<<(std::ostream &out, Node n) {
    out << *(n.data);
    return out;
  }
  friend std::ostream &operator<<(std::ostream &out, Node *n) {
    out << *(n->data);
    return out;
  }
  void setData(T d) { *data = d; }
  T &getData() const { return *data; }

protected:
  T *data;
};

template <class T> class BinaryTreeNode : public Node<T> {
public:
  BinaryTreeNode() : Node<T>() {
    left = NULL;
    right = NULL;
  }
  BinaryTreeNode(T d) : Node<T>(d) {
    left = NULL;
    right = NULL;
  }
  BinaryTreeNode(BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>() {
    left = l;
    right = r;
  }
  BinaryTreeNode(T d, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>(d) {
    left = l;
    right = r;
  }
  void setLeft(BinaryTreeNode<T> *l) { left = l; }
  void setRight(BinaryTreeNode<T> *r) { right = r; }
  BinaryTreeNode<T> *&getLeft() { return left; }
  BinaryTreeNode<T> *&getRight() { return right; }
  bool operator>(BinaryTreeNode<T> n) {
    if (*(this->data) > *(n.data))
      return true;
    return false;
  }
  bool operator==(BinaryTreeNode<T> n) {
    if (*(this->data) == *(n.data))
      return true;
    return false;
  }

private:
  BinaryTreeNode<T> *left, *right;
};

template <class T> class AVLTree {
private:
  BinaryTreeNode<T> *root;

  int height(BinaryTreeNode<T> *node) {
    if (!node)
      return 0;
    return max(height(node->getLeft()), height(node->getRight())) + 1;
  }

  int getBalance(BinaryTreeNode<T> *node) {
    if (!node)
      return 0;
    return height(node->getLeft()) - height(node->getRight());
  }

  BinaryTreeNode<T> *rightRotate(BinaryTreeNode<T> *y) {
    BinaryTreeNode<T> *x = y->getLeft();
    BinaryTreeNode<T> *T2 = x->getRight();

    x->setRight(y);
    y->setLeft(T2);

    return x;
  }

  BinaryTreeNode<T> *leftRotate(BinaryTreeNode<T> *x) {
    BinaryTreeNode<T> *y = x->getRight();
    BinaryTreeNode<T> *T2 = y->getLeft();

    y->setLeft(x);
    x->setRight(T2);

    return y;
  }

  BinaryTreeNode<T> *insertNode(BinaryTreeNode<T> *node, T d) {
    if (!node)
      return new BinaryTreeNode<T>(d);

    if (d < node->getData())
      node->setLeft(insertNode(node->getLeft(), d));
    else if (d > node->getData())
      node->setRight(insertNode(node->getRight(), d));
    else
      return node; // Duplicate keys are not allowed

    int balance = getBalance(node);

    // Left-Left Case
    if (balance > 1 && d < node->getLeft()->getData())
      return rightRotate(node);

    // Right-Right Case
    if (balance < -1 && d > node->getRight()->getData())
      return leftRotate(node);

    // Left-Right Case
    if (balance > 1 && d > node->getLeft()->getData()) {
      node->setLeft(leftRotate(node->getLeft()));
      return rightRotate(node);
    }

    // Right-Left Case
    if (balance < -1 && d < node->getRight()->getData()) {
      node->setRight(rightRotate(node->getRight()));
      return leftRotate(node);
    }

    return node;
  }

  void inorderTraversal(BinaryTreeNode<T> *cur, int n) {
    if (cur == NULL)
      return;
    inorderTraversal(cur->getRight(), n + 1);
    for (int j = 0; j < n; j++)
      cout << "  ";
    cout << cur << endl;
    inorderTraversal(cur->getLeft(), n + 1);
  }

public:
  AVLTree() { root = NULL; }

  void insert(T d) { root = insertNode(root, d); }

  void inorder() { inorderTraversal(root, 0); }
};

int main() {
  AVLTree<int> *tree = new AVLTree<int>();
  srand(0);
  int j, k, i;
  for (j = 0; j < 20; j++) {
    tree->insert(rand() % 100);
    tree->inorder();
  }
}
