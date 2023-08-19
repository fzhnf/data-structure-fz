from __future__ import annotations
from typing import Any
import csv
import argparse


class Node:
    value: Any
    next: Node | None

    def __init__(self) -> None:
        value: Any = None
        next: Node | None = None

class Stack:
    def __init__(self) -> None:
        self.top: Node | None = None

    def __iter__(self):
        # TODO

    def __str__(self):
        # TODO

    def hasPop(self) -> bool:
        return self.top is not None

    def push(self, value: Any) -> None:
        node = Node()
        node.value = value
        node.next = self.top
        self.top = node

    def pop(self) -> Any:
        if self.top is None:
            return None
        else:
            value = self.top.value
            self.top = self.top.next
            return value

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


def csv_to_stack(filename: str, stack: Stack) -> Stack:
    with open(filename, newline="") as csvfile:
        reader = csv.reader(csvfile)
        for _ in reversed(list(*reader)):
            stack.push(_)
    return stack


def stack_to_csv(stack: Stack, filename: str) -> None:
    with open(filename, "w", newline="") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(iter(stack))
