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


class Stack:
    def __init__(self) -> None:
        self.top: Node | None = None

    def __iter__(self):
        node = self.top
        while node:
            yield node.value
            node = node.next

    def __str__(self):
        return str(list(self))

    def hasPop(self) -> bool:
        return self.top is not None

    def push(self, value: Any) -> None:
        node = Node()
        node.value = value
        node.next = self.top
        self.top = node

    def pop(self) -> Any:
        hasPop = self.hasPop()
        if hasPop:
            if self.top:
                value = self.top.value
                self.top = self.top.next
                return value
        else:
            print("Index out of range")

    def swap(self, index1, index2):
        if index1 == index2:
            return
        if index1 > index2:
            index1, index2 = index2, index1
        node1 = self.top
        node2 = self.top
        for _ in range(index1):
            if node1:
                node1 = node1.next
        for _ in range(index2):
            if node2:
                node2 = node2.next
        if node1 and node2:
            node1.value, node2.value = node2.value, node1.value

    def get(self, index):
        node = self.top
        for _ in range(index):
            if node:
                node = node.next
        if node:
            return node.value
        else:
            print("Index out of range")


def csv_to_stack(filename: str) -> Stack:
    stack = Stack()
    with open(filename, newline="") as csvfile:
        reader = csv.reader(csvfile)
        for _ in reversed(list(*reader)):
            stack.push(_)
    return stack


def stack_to_csv(stack: Stack, filename: str) -> None:
    with open(filename, "w", newline="") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(iter(stack))


def main():
    parser = argparse.ArgumentParser(
        description="Perform operations on a Stack Data Structure from a CSV file."
    )
    parser.add_argument(
        "operation",
        choices=["swap", "pop", "push", "hasPop", "get"],
        help="Operation to perform on the Stack data structure",
    )
    parser.add_argument(
        "args", nargs="*", help="Additional arguments for the operation"
    )

    args = parser.parse_args()
    stack = csv_to_stack("List.csv")

    match args.operation:
        case "swap":
            stack.swap(int(args.args[0]), int(args.args[1]))
        case "pop":
            stack.pop()
        case "push":
            stack.push(args.args[0])
        case "hasPop":
            stack.hasPop()
        case "get":
            print(stack.get(int(args.args[0])))
        case _:
            print("Invalid operation")

    stack_to_csv(stack, "List.csv")


if __name__ == "__main__":
    main()
