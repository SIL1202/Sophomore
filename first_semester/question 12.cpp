#include <cctype>
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

class ExpressionTree {
private:
  struct Node {
    std::string value;
    Node *left;
    Node *right;

    Node(const std::string &val) : value(val), left(nullptr), right(nullptr) {}
  };

  Node *root;

public:
  ExpressionTree(const std::string &expression) {
    std::vector<std::string> tokens = tokenize(expression);
    std::vector<std::string> postfix = infixToPostfix(tokens);
    root = buildTree(postfix);
  }

  ~ExpressionTree() { deleteTree(root); }

  void deleteTree(Node *node) {
    if (node == nullptr)
      return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }

  void printInFixOrder() {
    inorder(root);
    std::cout << std::endl;
  }

  void printPreFixOrder() {
    preorder(root);
    std::cout << std::endl;
  }

  void printPostFixOrder() {
    postorder(root);
    std::cout << std::endl;
  }

  int eval() { return evaluate(root); }

private:
  std::vector<std::string> tokenize(const std::string &expr) {
    std::vector<std::string> tokens;
    std::stringstream ss(expr);
    std::string token;
    while (ss >> token)
      tokens.push_back(token);
    return tokens;
  }

  int precedence(const std::string &op) {
    if (op == "+" || op == "-")
      return 1;
    if (op == "*" || op == "/" || op == "%")
      return 2;
    return 0;
  }

  bool isOperator(const std::string &token) {
    return token == "+" || token == "-" || token == "*" || token == "/" ||
           token == "%";
  }

  std::vector<std::string>
  infixToPostfix(const std::vector<std::string> &tokens) {
    std::vector<std::string> postfix;
    std::stack<std::string> opStack;

    for (const std::string &token : tokens) {
      if (isdigit(token[0]) ||
          (token.size() > 1 && token[0] == '-' && isdigit(token[1]))) {
        postfix.push_back(token);
      } else if (token == "(") {
        opStack.push(token);
      } else if (token == ")") {
        while (!opStack.empty() && opStack.top() != "(") {
          postfix.push_back(opStack.top());
          opStack.pop();
        }
        opStack.pop();
      } else {
        while (!opStack.empty() &&
               precedence(opStack.top()) >= precedence(token)) {
          postfix.push_back(opStack.top());
          opStack.pop();
        }
        opStack.push(token);
      }
    }

    while (!opStack.empty()) {
      postfix.push_back(opStack.top());
      opStack.pop();
    }

    return postfix;
  }

  Node *buildTree(const std::vector<std::string> &postfix) {
    std::stack<Node *> treeStack;
    for (const std::string &token : postfix) {
      Node *node = new Node(token);
      if (isOperator(token)) {
        node->right = treeStack.top();
        treeStack.pop();
        node->left = treeStack.top();
        treeStack.pop();
      }
      treeStack.push(node);
    }
    return treeStack.top();
  }

  void inorder(Node *node) {
    if (!node)
      return;
    if (isOperator(node->value))
      std::cout << "(";
    inorder(node->left);
    std::cout << node->value << " ";
    inorder(node->right);
    if (isOperator(node->value))
      std::cout << ")";
  }

  void preorder(Node *node) {
    if (!node)
      return;
    std::cout << node->value << " ";
    preorder(node->left);
    preorder(node->right);
  }

  void postorder(Node *node) {
    if (!node)
      return;
    postorder(node->left);
    postorder(node->right);
    std::cout << node->value << " ";
  }

  int evaluate(Node *node) {
    if (!node)
      return 0;
    if (!isOperator(node->value))
      return std::stoi(node->value);

    int left = evaluate(node->left);
    int right = evaluate(node->right);

    if (node->value == "+")
      return left + right;
    if (node->value == "-")
      return left - right;
    if (node->value == "*")
      return left * right;
    if (node->value == "/")
      return left / right;
    if (node->value == "%")
      return left % right;

    throw std::invalid_argument("Invalid operator");
  }
};
- 12 3 + 4 * 5 % int main() {
  std::string infix = "( -12 + 3 ) * 4 % 5";
  ExpressionTree exprTree(infix);

  std::cout << "Inorder: ";
  exprTree.printInFixOrder();
  std::cout << "Preorder: ";
  exprTree.printPreFixOrder();
  std::cout << "Postorder: ";
  exprTree.printPostFixOrder();
  std::cout << "Evaluated result: " << exprTree.eval() << std::endl;

  return 0;
}
