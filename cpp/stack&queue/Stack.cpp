#include <fstream> // Mengimpor header file yang diperlukan untuk operasi file
#include <iostream> // Mengimpor header file yang diperlukan untuk operasi input/output standar
#include <iterator> // Mengimpor header file yang diperlukan untuk operasi iterator
#include <string> // Mengimpor header file yang diperlukan untuk operasi string
#include <vector> // Mengimpor header file yang diperlukan untuk operasi vektor

class Node {
public:
  Node *next;        // Pointer ke node berikutnya
  std::string value; // Nilai yang disimpan dalam node

  Node()
      : next(nullptr) {
  } // Konstruktor menginisialisasi pointer next menjadi nullptr
};

class Stack {
private:
  class StackIterator {
  private:
    Node *current;

  public:
    StackIterator(Node *start)
        : current(start) {
    } // Konstruktor iterator, menginisialisasi current dengan start

    bool operator!=(const StackIterator &other)
        const { // Operator perbandingan tidak sama (!=) untuk iterator
      return current != other.current;
    }

    StackIterator &operator++() { // Operator peningkatan (++) untuk iterator
      current = current->next;    // Memindahkan iterator ke node berikutnya
      return *this;
    }

    std::string operator*() const {
      return current->value;
    } // Operator dereferensi (*) untuk mengembalikan nilai dari current node
  };

public:
  Node *top; // Pointer ke node paling atas pada stack

  Stack()
      : top(nullptr) {
  } // Konstruktor menginisialisasi pointer top menjadi nullptr

  bool hasPop() const {
    return top != nullptr;
  } // Mengembalikan true jika stack memiliki elemen untuk di-pop

  void push(const std::string &value) {
    Node *node = new Node(); // Membuat instance Node baru
    node->value = value;     // Menetapkan nilai pada Node
    node->next = top;        // Mengatur next node baru ke top node lama
    top = node;              // Mengubah top node menjadi node baru
  }

  std::string pop() {
    if (hasPop()) {
      std::string value =
          top->value;   // Mendapatkan nilai dari top node yang akan di-pop
      Node *temp = top; // Membuat pointer sementara ke top node
      top = top->next;  // Menggeser top ke node berikutnya
      delete temp;      // Menghapus node yang di-pop dari memori
      return value;     // Mengembalikan nilai yang di-pop
    } else {
      std::cout << "Indeks di luar jangkauan"
                << std::endl; // Mencetak pesan kesalahan jika stack kosong
      return "";
    }
  }

  void swap(int index1, int index2) {
    if (index1 == index2) {
      return; // Tidak perlu tukar jika indeks sama
    }
    if (index1 > index2) {
      std::swap(index1, index2); // Memastikan index1 lebih kecil dari index2
    }
    Node *node1 = top;
    Node *node2 = top;
    for (int i = 0; i < index1 && node1; ++i) {
      node1 = node1->next; // Memindahkan node1 ke indeks yang diinginkan
    }
    for (int i = 0; i < index2 && node2; ++i) {
      node2 = node2->next; // Memindahkan node2 ke indeks yang diinginkan
    }
    if (node1 && node2) {
      std::swap(
          node1->value,
          node2->value); // Menukar nilai antara node pada index1 dan index2
    }
  }

  std::string get(int index) {
    Node *node = top;
    for (int i = 0; i < index && node; ++i) {
      node = node->next; // Memindahkan node ke indeks yang diinginkan
    }
    if (node) {
      return node->value; // Mengembalikan nilai pada indeks yang ditentukan
    } else {
      std::cout << "Indeks di luar jangkauan"
                << std::endl; // Mencetak pesan kesalahan jika indeks di luar
                              // jangkauan
      return "";
    }
  }

  StackIterator begin() const {
    return StackIterator(top);
  } // Memberikan iterator untuk elemen pertama stack

  StackIterator end() const {
    return StackIterator(nullptr);
  } // Memberikan iterator untuk elemen setelah elemen terakhir stack
};

Stack csv_to_stack(const std::string &filename) {
  Stack stack;
  std::ifstream csvfile(filename); // Membuka file CSV input
  std::string line;
  std::vector<std::string> lines;

  while (std::getline(csvfile, line)) {
    lines.push_back(
        line); // Menambahkan setiap baris dari file CSV ke dalam vektor
  }

  for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
    stack.push(*it); // Menambahkan setiap elemen dari vektor ke dalam stack
                     // secara terbalik
  }

  return stack;
}

void stack_to_csv(const Stack &stack, const std::string &filename) {
  std::ofstream csvfile(filename); // Membuka file CSV output
  for (const std::string &value : stack) {
    csvfile << value
            << std::endl; // Menulis setiap nilai dari stack ke dalam file CSV
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Penggunaan: " << argv[0] << " <operasi> <argumen...>"
              << std::endl; // Mencetak petunjuk penggunaan jika argumen tidak
                            // mencukupi
    return 1;
  }

  Stack stack = csv_to_stack("List.csv"); // Mengonversi file CSV menjadi stack

  std::string operation = argv[1];

  if (operation == "swap" && argc == 4) {
    stack.swap(std::stoi(argv[2]),
               std::stoi(argv[3])); // Melakukan operasi tukar pada stack
  } else if (operation == "pop") {
    stack.pop(); // Melakukan operasi pop pada stack
  } else if (operation == "push" && argc == 3) {
    stack.push(argv[2]); // Melakukan operasi push pada stack
  } else if (operation == "hasPop") {
    stack.hasPop(); // Memeriksa apakah stack memiliki elemen yang dapat di-pop
  } else if (operation == "get" && argc == 3) {
    std::cout
        << stack.get(std::stoi(argv[2]))
        << std::endl; // Melakukan operasi get pada stack dan mencetak hasilnya
  } else {
    std::cout
        << "Operasi tidak valid"
        << std::endl; // Mencetak pesan kesalahan untuk operasi tidak valid
  }

  stack_to_csv(stack, "List.csv"); // Mengonversi stack kembali menjadi file CSV

  return 0;
}
