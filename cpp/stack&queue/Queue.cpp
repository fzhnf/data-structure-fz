#include <iostream>
#include <string>
#include <vector>

class Node {
public:
  Node(int val) : data(val), next(nullptr) {}
  Node(std::string val) : data_str(val), next(nullptr) {}

  int getData() const { return data; }
  std::string getDataStr() const { return data_str; }

  Node *getNext() const { return next; }
  void setNext(Node *n) { next = n; }

private:
  int data;
  std::string data_str;
  Node *next;
};

class Queue {
public:
  Queue() : front(nullptr), rear(nullptr) {}

  bool isEmpty() const { return front == nullptr; }

  void enqueue(int val) {
    Node *newNode = new Node(val);
    if (isEmpty()) {
      front = rear = newNode;
    } else {
      rear->setNext(newNode);
      rear = newNode;
    }
  }

  void enqueue(std::string val) {
    Node *newNode = new Node(val);
    if (isEmpty()) {
      front = rear = newNode;
    } else {
      rear->setNext(newNode);
      rear = newNode;
    }
  }

  bool hasQueue() const { return !isEmpty(); }

  void dequeue() {
    if (!isEmpty()) {
      Node *temp = front;
      front = front->getNext();
      delete temp;
    }
  }

  void swap() {
    if (front != nullptr && front->getNext() != nullptr) {
      Node *first = front;
      Node *second = front->getNext();
      front = second;
      first->setNext(second->getNext());
      second->setNext(first);
      if (first == rear) {
        rear = second;
      }
    }
  }

private:
  Node *front;
  Node *rear;
};

int main() {
  Queue queue;

  // Test case 1: Dequeue when queue is empty
  std::cout << "hasQueue(): " << queue.hasQueue() << std::endl;
  queue.dequeue();

  // Test case 2: Enqueue integers and strings
  queue.enqueue(42);
  queue.enqueue("Hello");
  queue.enqueue(7);

  // Test case 3: Dequeue integers and strings
  queue.dequeue();
  queue.dequeue();
  queue.dequeue();

  // Test case 4: Swap elements
  queue.enqueue("OpenAI");
  queue.enqueue("GPT-3.5");
  queue.swap();

  return 0;
}
