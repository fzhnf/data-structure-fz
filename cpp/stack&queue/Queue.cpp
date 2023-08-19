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

class Queue {
public:
  Node *front = nullptr;
  Node *rear = nullptr;

  ~Queue() {
    while (front) {
      Node *temp = front;
      front = front->next;
      delete temp;
    }
  }

  bool isEmpty() { return front == nullptr; }

  void enqueue(int value) {
    Node *newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;
    if (rear) {
      rear->next = newNode;
    } else {
      front = newNode;
    }
    rear = newNode;
  }

  int dequeue() {
    if (isEmpty()) {
      throw std::out_of_range("Index out of range");
    }
    Node *temp = front;
    int value = temp->value;
    front = front->next;
    delete temp;
    if (!front) {
      rear = nullptr;
    }
    return value;
  }

  void swap(int index1, int index2) {
    if (index1 == index2) {
      return;
    }
    if (index1 > index2) {
      std::swap(index1, index2);
    }
    Node *node1 = front;
    Node *node2 = front;
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

  int get(int index) {
    Node *node = front;
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

Queue csvToQueue(const std::string &filename) {
  Queue queue;
  std::ifstream file(filename);
  std::string line;
  std::vector<std::string> lines;

  while (std::getline(file, line)) {
    queue.enqueue(std::stoi(line));
  }

  return queue;
}

void queueToCsv(const Queue &queue, const std::string &filename) {
  std::ofstream file(filename);
  Node *current = queue.front;
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

  Queue queue = csvToQueue("List.csv");
  std::string operation = argv[1];

  if (operation == "swap") {
    queue.swap(std::stoi(argv[2]), std::stoi(argv[3]));
  } else if (operation == "enqueue") {
    queue.enqueue(std::stoi(argv[2]));
  } else if (operation == "dequeue") {
    queue.dequeue();
  } else if (operation == "get") {
    std::cout << queue.get(std::stoi(argv[2])) << std::endl;
  } else {
    std::cout << "Invalid operation" << std::endl;
    return 1;
  }

  queueToCsv(queue, "List.csv");
  return 0;
}
