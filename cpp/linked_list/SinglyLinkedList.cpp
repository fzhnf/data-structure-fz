#include <cstdio>
#include <cstdlib>
#include <iostream>

struct node {
  int val;
  node *next;
} *start;

class singly_linked_list {
public:
  singly_linked_list() { start = NULL; }
  void insert(int x);
  void remove(int x);
  void search(int x);
  void show();
  void reverseShow();
};

void singly_linked_list::insert(int x) {
  node *t = start;
  if (start != NULL) {
    while (t->next != NULL) {
      t = t->next;
    }
    node *n = new node;
    t->next = n;
    n->val = x;
    n->next = NULL;
  } else {
    node *n = new node;
    n->val = x;
    n->next = NULL;
    start = n;
  }
}

void singly_linked_list::remove(int x) {
  node *t = start;
  while (t != NULL && t->val != x) {
    t = t->next;
  }
  if (t == NULL) {
    return;
  }
  if (t == start) {
    start = start->next;
    delete t;
    return;
  }
  node *t2 = start;
  while (t2->next != t) {
    t2 = t2->next;
  }
  t2->next = t->next;
  delete t;
}

void singly_linked_list::search(int x) {
  node *t = start;
  int found = 0;
  while (t != NULL) {
    if (t->val == x) {
      std::cout << "\nFound";
      found = 1;
      break;
    }
    t = t->next;
  }
  if (found == 0) {
    std::cout << "\nNot Found";
  }
}

void singly_linked_list::show() {
  node *t = start;
  while (t != NULL) {
    std::cout << t->val << "\t";
    t = t->next;
  }
}

void singly_linked_list::reverseShow() {
  node *t = start;
  while (t != NULL && t->next != NULL) {
    t = t->next;
  }
  while (t != NULL) {
    std::cout << t->val << "\t";
    t = t->next;
  }
}

int main() {
  int choice, x;
  singly_linked_list ob;
  do {
    std::cout << "\n1. Insert";
    std::cout << "\n2. Delete";
    std::cout << "\n3. Search";
    std::cout << "\n4. Forward print";
    std::cout << "\n5. Reverse print";
    std::cout << "\n\nEnter you choice : ";
    std::cin >> choice;
    switch (choice) {
    case 1:
      std::cout << "\nEnter the element to be inserted : ";
      std::cin >> x;
      ob.insert(x);
      break;
    case 2:
      std::cout << "\nEnter the element to be removed : ";
      std::cin >> x;
      ob.remove(x);
      break;
    case 3:
      std::cout << "\nEnter the element to be searched : ";
      std::cin >> x;
      ob.search(x);
      break;
    case 4:
      ob.show();
      break;
    case 5:
      ob.reverseShow();
      break;
    }
  } while (choice != 0);
  return 0;
}
