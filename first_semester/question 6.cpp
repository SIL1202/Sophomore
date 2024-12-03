#include <cstdlib>
#include <ctime>
#include <iostream>

#define SIZE 100

using namespace std;

class Node {
public:
  Node() : data(0), next(nullptr), pre(nullptr) {}
  Node(int n) : data(n), next(nullptr), pre(nullptr) {}

  int getData() { return data; }
  Node *getNext() { return next; }
  Node *getPre() { return pre; }
  void setData(int d) { data = d; }
  void setNext(Node *n) { next = n; }
  void setPre(Node *p) { pre = p; }

private:
  int data;
  Node *next, *pre;
};

class List {
public:
  List() : list(nullptr) {}
  List(int n) { generate(n); }

  void generate(int n) {
    list = nullptr;
    for (int j = 0; j < n; j++) {
      generate();
    }
  }

  void generate() {
    Node *buf = new Node(rand() % 100);
    buf->setNext(list);
    if (list != nullptr) {
      list->setPre(buf);
    }
    list = buf;
  }

  void bubbleSort() {
    if (list == nullptr)
      return;
    bool swapped;
    Node *current;
    Node *last = nullptr;

    do {
      swapped = false;
      current = list;

      while (current->getNext() != last) {
        if (current->getData() > current->getNext()->getData()) {
          Node *nextNode = current->getNext();
          swapNodes(current, nextNode);
          swapped = true;
          current = nextNode;
        }
        current = current->getNext();
      }
      last =
          current; // 將 last 更新為
                   // current，這樣在下一次遍歷時，就不再檢查已經排序好的節點。
    } while (swapped);
  }

  void selectionSort() {
    if (list == nullptr)
      return;
    Node *start = list;

    while (start != nullptr) {
      Node *minNode = start;
      Node *current = start->getNext();
      // current為在剩餘的未排序序列中移動的點

      while (current != nullptr) {
        if (current->getData() < minNode->getData()) { // 找到比目前最小值的還小
          minNode = current;
        }
        current = current->getNext();
      }

      // 檢查 minNode 是否與 start 相同。如果不同，則調用
      if (minNode != start) {
        swapNodes(start, minNode);
      }
      start = start->getNext();
    }
  }

  void insertionSort() {
    if (list == nullptr)
      return;
    Node *sorted = list;
    Node *current = list->getNext();

    while (current != nullptr) {
      Node *nextNode = current->getNext();
      Node *temp = sorted;

      // 再以排序的數列中找要插入的位置
      while (temp != current && temp->getData() <= current->getData()) {
        temp = temp->getNext();
      }

      if (temp != current) {
        swapNodes(current, temp);
      }

      current = nextNode;
    }
  }

  void print() {
    Node *current = list;
    while (current != nullptr) {
      cout << current->getData() << " ";
      current = current->getNext();
    }
    cout << endl;
  }

private:
  Node *list;
  void swapNodes(Node *a, Node *b) {
    if (a == b)
      return;

    // prevA -> a -> nextA -> prevB -> b -> nextB
    //
    // prevA -> b -> nextA
    //          |      |
    //        prevB -> a -> nextB

    Node *prevA = a->getPre();
    Node *nextA = a->getNext();
    Node *prevB = b->getPre();
    Node *nextB = b->getNext();

    if (nextA == b) { // a在前面 a->b
      if (prevA)      // 確保當前的a不是鏈表的頭節點
        prevA->setNext(b);
      b->setPre(prevA);

      if (nextB)
        nextB->setPre(a);
      a->setNext(nextB);

      b->setNext(a);
      a->setPre(b);
    }

    else if (nextB == a) { // b在前面 b->a
      if (prevB)
        prevB->setNext(a);
      a->setPre(prevB);

      if (nextA)
        nextA->setPre(b);
      b->setNext(nextA);

      a->setNext(b);
      b->setPre(a);
    }

    else { // a、b不相連
      if (prevA)
        prevA->setNext(b);
      if (nextA)
        nextA->setPre(b);
      b->setPre(prevA);
      b->setNext(nextA);

      if (prevB)
        prevB->setNext(a);
      if (nextB)
        nextB->setPre(a);
      a->setPre(prevB);
      a->setNext(nextB);
    }

    if (list == a) // 如果 a 是鏈表的頭部，則更新為 b
      list = b;
    else if (list == b)
      list = a; // 如果 b 是鏈表的頭部，則更新為 a
  }
};

int main() {
  srand(time(nullptr));
  List *l = new List(10);
  l->print();
  l->bubbleSort();
  l->print();

  l = new List(10);
  l->print();
  l->insertionSort();
  l->print();

  l = new List(10);
  l->print();
  l->selectionSort();
  l->print();

  return 0;
}
