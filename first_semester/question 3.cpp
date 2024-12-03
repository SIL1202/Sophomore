
// push 這個函數會把 data push 進 stack 裡，如果成功會回傳 1 ，如果失敗會回傳 -1

// pop 會從 stack 裡 pop
// 最上面的資料出來，如果成功就回傳指向該資料的指標，如果失敗就回傳 NULL

// Please finish two function push and pop

// Function push will push the data into stack and return 1 if success, return
// -1 if not.

// Function pop will pop the top data from stack and return a pointer point to
// the data, return NULL if there is no data.

#include <cstring>
#include <iostream>

#define SIZE 100

using namespace std;

class Stack { // last in, first out
public:
  Stack() { top = 0; }

  int push(int data) {
    if (top >= SIZE)
      return -1; // stack is fall

    this->data[top] = data;
    top++;
    return 1;
  }

  int *pop() {
    if (top == 0) {
      return NULL;
    }
    top--;
    return &data[top];
  }

private:
  int data[SIZE];
  int top;
};

int main() {
  int data, *temp;
  char command[50];
  Stack *stack = new Stack();

  while (1) {
    cin >> command;

    if (strcmp(command, "exit") == 0) {
      break;
    }

    else if (strcmp(command, "push") == 0) {

      cout << "Please input a integer data:";
      cin >> data;

      if (stack->push(data) == 1) {
        cout << "Successfully push data " << data << " into stack.\n";
      } else {
        cout << "Failed to push data into stack.\n";
      }
    }

    else if (strcmp(command, "pop") == 0) {

      temp = stack->pop();

      if (temp == NULL) {
        cout << "Failed to pop a data from stack.\n";
      } else {
        cout << "Pop data " << *temp << " from stack.\n" << endl;
      }
    }
  }
}

// 如果你成功的完成了指定的函數，你可以得到100分

// You can get 100 point if finish this two function.
