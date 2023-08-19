#include <iostream>

// Node class
class Node {
public:
  int data;
  Node *next;

  Node(int value) : data(value), next(nullptr) {}
};

// Stack class
class Stack {
private:
  Node *top;

public:
  Stack() : top(nullptr) {}

  void push(int value) {
    Node *newNode = new Node(value);
    newNode->next = top;
    top = newNode;
  }

  bool haspop() { return top != nullptr; }

  int pop() {
    if (!haspop()) {
      std::cerr << "Stack underflow!" << std::endl;
      return -1; // You can choose an appropriate error value
    }

    Node *temp = top;
    int poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
  }
};

int main() {
  Stack stack;

  stack.push(10);
  stack.push(20);
  stack.push(30);

  if (stack.haspop()) {
    std::cout << "Popped: " << stack.pop() << std::endl;
  }

  if (stack.haspop()) {
    std::cout << "Popped: " << stack.pop() << std::endl;
  }

  return 0;
}
