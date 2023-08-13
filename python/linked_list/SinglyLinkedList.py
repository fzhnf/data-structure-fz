from __future__ import annotations
from typing import Any
import csv
import argparse


class Node:
    def __init__(self, value: Any, next: Any) -> None:
        self.value = value
        self.next = next


class SinglyLinkedList:
    def __init__(self) -> None:
        self.first: Node | None = None

    def insert_first(self, value: Any) -> None:
        self.first = Node(value, self.first)

    def insert_last(self, value: Any) -> None:
        if self.first:
            current = self.first
            while current.next:
                current = current.next
            current.next = Node(value, None)
        else:
            self.insert_first(value)

    def insert_mid(self, value: Any, index: int) -> None:
        if index == 0:
            self.insert_first(value)
            return
        current = self.first
        for _ in range(index - 1):
            if current:
                current = current.next
            else:
                raise IndexError("Index out of range")
        if current:
            current.next = Node(value, current.next)
        else:
            raise IndexError("Index out of range")

    def remove_first(self) -> None:
        if self.first:
            self.first = self.first.next
        else:
            raise IndexError("Index out of range")

    def remove_last(self) -> None:
        if self.first:
            current = self.first
            while current.next:
                current = current.next
            current.next = None
        else:
            raise IndexError("Index out of range")

    def remove_mid(self, index: int) -> None:
        if index == 0:
            self.remove_first()
            return
        current = self.first
        for _ in range(index - 1):
            if current:
                current = current.next
            else:
                raise IndexError("Index out of range")
        if current:
            current.next = current.next.next
        else:
            raise IndexError("Index out of range")

    def replace_first(self, value: Any) -> None:
        if self.first:
            self.first.value = value
        else:
            raise IndexError("Index out of range")

    def replace_last(self, value: Any) -> None:
        if self.first:
            current = self.first
            while current.next:
                current = current.next
            current.value = value
        else:
            raise IndexError("Index out of range")

    def replace_mid(self, value: Any, index: int) -> None:
        current = self.first
        for _ in range(index):
            if current:
                current = current.next
            else:
                raise IndexError("Index out of range")
        if current:
            current.value = value
        else:
            raise IndexError("Index out of range")

    def swap(self, index1: int, index2: int) -> None:
        current = self.first
        for _ in range(index1):
            if current:
                current = current.next
            else:
                raise IndexError("Index out of range")
        if current:
            node1 = current
            value1 = node1.value
        else:
            raise IndexError("Index out of range")
        for _ in range(index2 - index1 - 1):
            if current:
                current = current.next
            else:
                raise IndexError("Index out of range")
        if current:
            node2 = current.next
            value2 = node2.value
        else:
            raise IndexError("Index out of range")
        node1.value = value2
        node2.value = value1

    def get_first(self) -> Any:
        if self.first:
            return self.first.value
        else:
            raise IndexError("Index out of range")

    def get_last(self) -> Any:
        if self.first:
            current = self.first
            while current.next:
                current = current.next
            return current.value
        else:
            raise IndexError("Index out of range")

    def get_mid(self, index: int) -> Any:
        current = self.first
        for _ in range(index):
            if current:
                current = current.next
            else:
                raise IndexError("Index out of range")
        if current:
            return current.value
        else:
            raise IndexError("Index out of range")

    def __str__(self) -> str:
        current = self.first
        string = ""
        while current:
            if not current.next:
                string += str(current.value)
                break
            string += str(current.value) + ","
            current = current.next
        return string

    def __iter__(self) -> Any:
        current = self.first
        while current:
            yield current.value
            current = current.next


def csv_to_linked_list(filename: str) -> SinglyLinkedList:
    linked_list = SinglyLinkedList()
    with open(filename, newline="") as csvfile:
        reader = csv.reader(csvfile)
        for _ in reversed(list(*reader)):
            linked_list.insert_first(_)
    return linked_list


def linked_list_to_csv(linked_list: SinglyLinkedList) -> None:
    with open("linked_list.csv", "w", newline="") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(iter(linked_list))


def main():
    parser = argparse.ArgumentParser(
        description="Perform operations on a linked list from a CSV file."
    )
    parser.add_argument(
        "operation",
        choices=["swap", "insert", "remove", "replace", "get"],
        help="Operation to perform on the linked list",
    )
    parser.add_argument(
        "args", nargs="*", help="Additional arguments for the operation"
    )

    args = parser.parse_args()
    linked_list = csv_to_linked_list("linked_list.csv")

    match args.operation:
        case "swap":
            linked_list.swap(int(args.args[0]), int(args.args[1]))
        case "insert":
            match args.args[0]:
                case "first":
                    linked_list.insert_first(args.args[1])
                case "last":
                    linked_list.insert_last(args.args[1])
                case "mid":
                    linked_list.insert_mid(int(args.args[1]), int(args.args[2]))
        case "remove":
            match args.args[0]:
                case "first":
                    linked_list.remove_first()
                case "last":
                    linked_list.remove_last()
                case "mid":
                    linked_list.remove_mid(int(args.args[1]))
        case "replace":
            match args.args[0]:
                case "first":
                    linked_list.replace_first(args.args[1])
                case "last":
                    linked_list.replace_last(args.args[1])
                case "mid":
                    linked_list.replace_mid(int(args.args[1]), int(args.args[2]))
        case "get":
            match args.args[0]:
                case "first":
                    print(linked_list.get_first())
                case "last":
                    print(linked_list.get_last())
                case "mid":
                    print(linked_list.get_mid(int(args.args[1])))

    linked_list_to_csv(linked_list)


if __name__ == "__main__":
    main()
