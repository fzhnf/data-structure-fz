#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

class Node {
public:
  Node *next = nullptr;
  int value = 0;
};

class Stack {
public:
  Node *top = nullptr;

  ~Stack() {
    while (top) {
      Node *temp = top;
      top = top->next;
      delete temp;
    }
  }

  void push(int value) {
    Node *newNode = new Node;
    newNode->value = value;
    newNode->next = top;
    top = newNode;
  }

  int pop() {
    if (top) {
      Node *temp = top;
      int value = temp->value;
      top = top->next;
      delete temp;
      return value;
    } else {
      throw std::out_of_range("Index out of range");
    }
  }

  void swap(int index1, int index2) {
    if (index1 == index2) {
      return;
    }
    if (index1 > index2) {
      std::swap(index1, index2);
    }
    Node *node1 = top;
    Node *node2 = top;
    for (int i = 0; i < index1 && node1; ++i) {
      node1 = node1->next;
    }
    for (int i = 0; i < index2 && node2; ++i) {
      node2 = node2->next;
    }
    if (node1 && node2) {
      std::swap(node1->value, node2->value);
    }
  }

  bool hasPop() { return top != nullptr; }

  int get(int index) {
    Node *node = top;
    for (int i = 0; i < index && node; ++i) {
      node = node->next;
    }
    if (node) {
      return node->value;
    } else {
      throw std::out_of_range("Index out of range");
    }
  }
};

Stack csvToStack(const std::string &filename) {
  Stack stack;
  std::ifstream file(filename);
  std::string line;
  std::vector<std::string> lines;

  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
    stack.push(std::stoi(*it));
  }

  return stack;
}

void stackToCsv(const Stack &stack, const std::string &filename) {
  std::ofstream file(filename);
  Node *current = stack.top;
  while (current) {
    file << current->value << std::endl;
    current = current->next;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <operation> <args>" << std::endl;
    return 1;
  }

  Stack stack = csvToStack("List.csv");
  std::string operation = argv[1];

  if (operation == "swap") {
    stack.swap(std::stoi(argv[2]), std::stoi(argv[3]));
  } else if (operation == "pop") {
    stack.pop();
  } else if (operation == "push") {
    stack.push(std::stoi(argv[2]));
  } else if (operation == "hasPop") {
    stack.hasPop();
  } else if (operation == "get") {
    std::cout << stack.get(std::stoi(argv[2])) << std::endl;
  } else {
    std::cout << "Invalid operation" << std::endl;
    return 1;
  }

  stackToCsv(stack, "List.csv");
  return 0;
}
