#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class Node {
public:
  Node() : next(nullptr), pre(nullptr) {}
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
    for (int j = 0; j < n; j++)
      generate();
  }

  void generate() {
    Node *buf = new Node(rand() % 100); // 限制隨機數範圍
    buf->setNext(list);
    if (list != nullptr)
      list->setPre(buf);
    list = buf;
  }

  // 4 3 5 6 6 5 3
  //       |
  //       V
  // 3 4 5 6 5 3 6
  // 3 4 5 5 3 6 6
  // 3 4 5 3 5 6 6
  // 3 4 3 5 5 6 6
  // 3 3 4 5 5 6 6
  // swapped == false;
  // break;
  void bubbleSort() {
    bool swapped;
    for (int i = 0; i < 9; i++) {
      Node *current = list;
      swapped = false;
      while (current->getNext() != nullptr) {
        if (current->getData() > current->getNext()->getData()) {
          int temp = current->getData();
          current->setData(current->getNext()->getData());
          current->getNext()->setData(temp);
          swapped = true;
        }
        current = current->getNext();
      }
      if (!swapped)
        break;
    }
  }
  // 4 3 5 6 6 5 3
  // 3 4 5
  void selectionSort() {
    Node *current = list;
    while (current != nullptr && current->getNext() != nullptr) {
      Node *minIndex = current;
      Node *current2 = current->getNext();
      while (current2 != nullptr) {
        if (current2->getData() < minIndex->getData()) {
          minIndex = current2;
        }
        current2 = current2->getNext();
      }
      if (minIndex != current) {
        int temp = current->getData();
        current->setData(minIndex->getData());
        minIndex->setData(temp);
      }
      current = current->getNext();
    }
  }

  // 4 3 5 6 6 5 3
  // 3 4 5
  //     ^
  //     |
  //     q

  void insertionSort() {
    Node *current = list;
    Node *sorted = nullptr; // 開始時排序鏈表為空

    while (current != nullptr) {
      Node *next = current->getNext(); // 儲存下一個節點以便處理

      // 將 current 插入到排序鏈表中
      if (sorted == nullptr || sorted->getData() >= current->getData()) {
        // 插入到排序鏈表的頭部
        current->setNext(sorted);
        if (sorted != nullptr) {
          sorted->setPre(current);
        }
        current->setPre(nullptr);
        sorted = current; // 更新 sorted 為新的頭部
      } else {
        // 找到正確的位置進行插入
        Node *temp = sorted;
        while (temp->getNext() != nullptr &&
               temp->getNext()->getData() < current->getData()) {
          temp = temp->getNext();
        }

        // 在 temp 之後插入 current
        current->setNext(temp->getNext());
        temp->setNext(current);
        current->setPre(temp);
        if (current->getNext() != nullptr) {
          current->getNext()->setPre(current);
        }
      }
      current = next; // 移動到原始鏈表中的下一個節點
    }
    list = sorted; // 更新鏈表指向新的排序鏈表
  }

  void print() {
    Node *cur = list;
    while (cur != nullptr) {
      cout << cur->getData() << " ";
      cur = cur->getNext();
    }
    cout << endl;
  }

  ~List() {
    while (list != nullptr) {
      Node *temp = list;
      list = list->getNext();
      delete temp; // 釋放內存
    }
  }

private:
  Node *list;
};

int main() {
  srand(static_cast<unsigned int>(time(nullptr)));

  // 測試氣泡排序
  List *l1 = new List(10);
  cout << "Before Bubble Sort: ";
  l1->print();
  l1->bubbleSort();
  cout << "After Bubble Sort: ";
  l1->print();
  delete l1;

  // 測試選擇排序
  List *l2 = new List(10);
  cout << "Before Selection Sort: ";
  l2->print();
  l2->selectionSort();
  cout << "After Selection Sort: ";
  l2->print();
  delete l2;

  // 測試插入排序
  List *l3 = new List(10);
  cout << "Before Insertion Sort: ";
  l3->print();
  l3->insertionSort();
  cout << "After Insertion Sort: ";
  l3->print();
  delete l3;

  return 0;
}
