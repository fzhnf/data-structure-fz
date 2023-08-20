#include <fstream> // Sertakan file header yang diperlukan untuk input/output file
#include <iostream> // Sertakan file header yang diperlukan untuk input/output standar
#include <iterator> // Sertakan file header yang diperlukan untuk operasi iterator
#include <string>   // Sertakan file header yang diperlukan untuk operasi string
#include <vector>   // Sertakan file header yang diperlukan untuk operasi vektor

class Node {
public:
  Node *next;
  std::string value;

  Node()
      : next(nullptr) {
  } // Konstruktor menginisialisasi pointer next menjadi nullptr
};

class Queue {
public:
  Node *front;
  Node *rear;

  Queue()
      : front(nullptr), rear(nullptr) {
  } // Konstruktor menginisialisasi pointer front dan rear menjadi nullptr

  bool isEmpty() const {
    return front == nullptr;
  } // Periksa apakah antrian kosong

  void enqueue(const std::string &value) {
    Node *node = new Node(); // Buat instance Node baru
    node->value = value;     // Assign value ke Node
    node->next = nullptr;    // Set pointer next menjadi nullptr
    if (isEmpty()) {
      front = rear =
          node; // Jika antrian kosong, set front dan rear menjadi node baru
    } else {
      rear->next = node; // Jika tidak, tambahkan node baru di belakang antrian
      rear = node;
    }
  }

  std::string dequeue() {
    if (isEmpty()) {
      std::cout << "Indeks di luar jangkauan"
                << std::endl; // Cetak pesan kesalahan jika antrian kosong
      return "";
    }
    Node *node = front;  // Dapatkan node bagian depan
    front = front->next; // Pindahkan front ke node berikutnya
    if (front == nullptr) {
      rear =
          nullptr; // Jika front menjadi nullptr, set rear menjadi nullptr juga
    }
    std::string value = node->value; // Dapatkan nilai dari node yang di-dequeue
    delete node;                     // Hapus node yang di-dequeue
    return value;
  }

  void swap(int index1, int index2) {
    if (index1 == index2) {
      return; // Jika indeks sama, tidak perlu ditukar
    }
    if (index1 > index2) {
      std::swap(index1, index2); // Pastikan index1 lebih kecil dari index2
    }
    Node *node1 = front;
    Node *node2 = front;
    for (int i = 0; i < index1 && node1; ++i) {
      node1 = node1->next; // Pindahkan node1 ke indeks yang diinginkan
    }
    for (int i = 0; i < index2 && node2; ++i) {
      node2 = node2->next; // Pindahkan node2 ke indeks yang diinginkan
    }
    if (node1 && node2) {
      std::swap(node1->value,
                node2->value); // Tukar nilai node pada index1 dan index2
    }
  }

  std::string get(int index) {
    Node *node = front;
    for (int i = 0; i < index && node; ++i) {
      node = node->next; // Pindahkan node ke indeks yang diinginkan
    }
    if (node) {
      return node->value; // Kembalikan nilai pada indeks yang ditentukan
    } else {
      std::cout
          << "Indeks di luar jangkauan"
          << std::endl; // Cetak pesan kesalahan jika indeks di luar jangkauan
      return "";
    }
  }
};

Queue csv_to_queue(const std::string &filename) {
  Queue queue;
  std::ifstream csvfile(filename); // Buka file CSV input
  std::string line;
  std::vector<std::string> lines;

  while (std::getline(csvfile, line)) {
    queue.enqueue(line); // Masukkan setiap baris dari file CSV ke dalam antrian
  }

  return queue;
}

void queue_to_csv(const Queue &queue, const std::string &filename) {
  std::ofstream csvfile(filename); // Buka file CSV output
  Node *current = queue.front;
  while (current) {
    csvfile << current->value
            << std::endl; // Tulis setiap nilai dari antrian ke dalam file CSV
    current = current->next;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout
        << "Penggunaan: " << argv[0] << " <operasi> <argumen...>"
        << std::endl; // Cetak petunjuk penggunaan jika argumen tidak mencukupi
    return 1;
  }

  Queue queue = csv_to_queue("List.csv"); // Konversi file CSV menjadi antrian

  std::string operation = argv[1];

  if (operation == "swap" && argc == 4) {
    queue.swap(std::stoi(argv[2]),
               std::stoi(argv[3])); // Lakukan operasi tukar pada antrian
  } else if (operation == "enqueue" && argc == 3) {
    queue.enqueue(argv[2]); // Lakukan operasi enqueue pada antrian
  } else if (operation == "dequeue") {
    queue.dequeue(); // Lakukan operasi dequeue pada antrian
  } else if (operation == "get" && argc == 3) {
    std::cout
        << queue.get(std::stoi(argv[2]))
        << std::endl; // Lakukan operasi get pada antrian dan cetak hasilnya
  } else {
    std::cout << "Operasi tidak valid"
              << std::endl; // Cetak pesan kesalahan untuk operasi tidak valid
  }

  queue_to_csv(queue, "List.csv"); // Konversi antrian kembali menjadi file CSV

  return 0;
}
