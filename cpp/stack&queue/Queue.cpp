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

class Queue {
public:
  Node *front;
  Node *rear;

  Queue() : front(nullptr), rear(nullptr) {}

  bool isEmpty() const { return front == nullptr; }

  void enqueue(const std::string &value) {
    Node *node = new Node();
    node->value = value;
    node->next = nullptr;
    if (isEmpty()) {
      front = rear = node;
    } else {
      rear->next = node;
      rear = node;
    }
  }

  std::string dequeue() {
    if (isEmpty()) {
      std::cout << "Index out of range" << std::endl;
      return "";
    }
    Node *node = front;
    front = front->next;
    if (front == nullptr) {
      rear = nullptr;
    }
    std::string value = node->value;
    delete node;
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

  std::string get(int index) {
    Node *node = front;
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
};

Queue csv_to_queue(const std::string &filename) {
  Queue queue;
  std::ifstream csvfile(filename);
  std::string line;
  std::vector<std::string> lines;

  while (std::getline(csvfile, line)) {
    queue.enqueue(line);
  }

  return queue;
}

void queue_to_csv(const Queue &queue, const std::string &filename) {
  std::ofstream csvfile(filename);
  Node *current = queue.front;
  while (current) {
    csvfile << current->value << std::endl;
    current = current->next;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <operation> <args...>" << std::endl;
    return 1;
  }

  Queue queue = csv_to_queue("List.csv");

  std::string operation = argv[1];

  if (operation == "swap" && argc == 4) {
    queue.swap(std::stoi(argv[2]), std::stoi(argv[3]));
  } else if (operation == "enqueue" && argc == 3) {
    queue.enqueue(argv[2]);
  } else if (operation == "dequeue") {
    queue.dequeue();
  } else if (operation == "get" && argc == 3) {
    std::cout << queue.get(std::stoi(argv[2])) << std::endl;
  } else {
    std::cout << "Invalid operation" << std::endl;
  }

  queue_to_csv(queue, "List.csv");

  return 0;
}
