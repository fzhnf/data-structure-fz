from __future__ import annotations
from typing import Any
import csv
import argparse


class Node:
    value: Any
    next: Node | None

    def __init__(self) -> None:
        self.value: Any = None
        self.next: Node | None = None


class Queue:
    def __init__(self) -> None:
        self.front: Node | None = None
        self.rear: Node | None = None

    def __iter__(self) -> Any:
        node = self.front
        while node:
            yield node.value
            node = node.next

    def __str__(self) -> str:
        return str(list(self))

    def isEmpty(self) -> bool:
        return self.front is None

    def enqueue(self, value: Any) -> None:
        node = Node()
        node.value = value
        if self.rear is None:
            self.front = self.rear = node
        else:
            self.rear.next = node
            self.rear = node

    def dequeue(self) -> Any:
        if self.isEmpty():
            print("Index out of range")
            return
        node = self.front
        if node:
            self.front = node.next
        if self.front is None:
            self.rear = None
        if node:
            return node.value

    def swap(self, index1, index2):
        if index1 == index2:
            return
        if index1 > index2:
            index1, index2 = index2, index1
        node1 = self.front
        node2 = self.front
        for _ in range(index1):
            if node1:
                node1 = node1.next
        for _ in range(index2):
            if node2:
                node2 = node2.next
        if node1 and node2:
            node1.value, node2.value = node2.value, node1.value

    def get(self, index):
        node = self.front
        for _ in range(index):
            if node:
                node = node.next
        if node:
            return node.value
        else:
            print("Index out of range")


def csv_to_queue(filename: str) -> Queue:
    queue = Queue()
    with open(filename, newline="") as csvfile:
        reader = csv.reader(csvfile)
        for _ in list(*reader):
            queue.enqueue(_)
    return queue


def queue_to_csv(queue: Queue, filename: str) -> None:
    with open(filename, "w", newline="") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(iter(queue))


def main():
    parser = argparse.ArgumentParser(
        description="Perform operations on a Queue Data Structure from a CSV file."
    )
    parser.add_argument(
        "operation",
        choices=["swap", "enqueue", "dequeue", "get"],
        help="Operation to perform on the Queue data structure",
    )
    parser.add_argument(
        "args", nargs="*", help="Additional arguments for the operation"
    )

    args = parser.parse_args()
    stack = csv_to_queue("List.csv")

    match args.operation:
        case "swap":
            stack.swap(int(args.args[0]), int(args.args[1]))
        case "enqueue":
            stack.enqueue(args.args[0])
        case "dequeue":
            stack.dequeue()
        case "get":
            print(stack.get(int(args.args[0])))
        case _:
            print("Invalid operation")

    queue_to_csv(stack, "List.csv")


if __name__ == "__main__":
    main()
