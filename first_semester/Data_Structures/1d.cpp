#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int calculate(char o1, char o2, int i1, int i2, int i3) {
  int intermediate_result;

  switch (o1) {
  case '+':
    intermediate_result = i1 + i2;
    break;
  case '-':
    intermediate_result = i1 - i2;
    break;
  case '*':
    intermediate_result = i1 * i2;
    break;
  case '/':
    if (i2 == 0)
      throw "Division by zero in first operator";
    intermediate_result = i1 / i2;
    break;
  default:
    throw o1;
  }

  switch (o2) {
  case '+':
    return intermediate_result + i3;
  case '-':
    return intermediate_result - i3;
  case '*':
    return intermediate_result * i3;
  case '/':
    if (i3 == 0)
      throw "Division by zero in second operator";
    return intermediate_result / i3;
  default:
    throw o2;
  }
}

int main() {
  char o1, o2;
  int i1, i2, i3;

  while (true) {
    cout << "Enter two operators and three integers (e.g., + - 5 2 3): ";
    cin >> o1 >> o2 >> i1 >> i2 >> i3;

    try {
      int result = calculate(o1, o2, i1, i2, i3);
      cout << "Result: " << result << endl;
    } catch (char op) {
      cout << "Error: Unknown operator '" << op << "'" << endl;
    } catch (const char *err) {
      cout << "Error: " << err << endl;
    }

    // Option to break the loop
    char choice;
    cout << "Do you want to try again? (y/n): ";
    cin >> choice;
    if (choice != 'y')
      break;
  }

  return 0;
}
