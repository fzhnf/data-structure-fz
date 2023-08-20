#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

class Node {
public:
  Node *next;
  std::string value;

  Node() : next(nullptr) {}
};

class Stack {
private:
  class StackIterator {
  private:
    Node *current;

  public:
    StackIterator(Node *start) : current(start) {}

    bool operator!=(const StackIterator &other) const {
      return current != other.current;
    }

    StackIterator &operator++() {
      current = current->next;
      return *this;
    }

    std::string operator*() const { return current->value; }
  };

public:
  Node *top;

  Stack() : top(nullptr) {}

  bool hasPop() const { return top != nullptr; }

  void push(const std::string &value) {
    Node *node = new Node();
    node->value = value;
    node->next = top;
    top = node;
  }

  std::string pop() {
    if (hasPop()) {
      std::string value = top->value;
      Node *temp = top;
      top = top->next;
      delete temp;
      return value;
    } else {
      std::cout << "Index out of range" << std::endl;
      return "";
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

  std::string get(int index) {
    Node *node = top;
    for (int i = 0; i < index && node; ++i) {
      node = node->next;
    }
    if (node) {
      return node->value;
    } else {
      std::cout << "Index out of range" << std::endl;
      return "";
    }
  }

  StackIterator begin() const { return StackIterator(top); }

  StackIterator end() const { return StackIterator(nullptr); }
};

Stack csv_to_stack(const std::string &filename) {
  Stack stack;
  std::ifstream csvfile(filename);
  std::string line;
  std::vector<std::string> lines;

  while (std::getline(csvfile, line)) {
    lines.push_back(line);
  }

  for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
    stack.push(*it);
  }

  return stack;
}

void stack_to_csv(const Stack &stack, const std::string &filename) {
  std::ofstream csvfile(filename);
  for (const std::string &value : stack) {
    csvfile << value << std::endl;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <operation> <args...>" << std::endl;
    return 1;
  }

  Stack stack = csv_to_stack("List.csv");

  std::string operation = argv[1];

  if (operation == "swap" && argc == 4) {
    stack.swap(std::stoi(argv[2]), std::stoi(argv[3]));
  } else if (operation == "pop") {
    stack.pop();
  } else if (operation == "push" && argc == 3) {
    stack.push(argv[2]);
  } else if (operation == "hasPop") {
    stack.hasPop();
  } else if (operation == "get" && argc == 3) {
    std::cout << stack.get(std::stoi(argv[2])) << std::endl;
  } else {
    std::cout << "Invalid operation" << std::endl;
  }

  stack_to_csv(stack, "List.csv");

  return 0;
}
