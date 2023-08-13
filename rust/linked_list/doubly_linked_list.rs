// Doubly Linked List
pub struct DoublyLinkedList<T> {
    head: Option<Box<DNode<T>>>,
    tail: Option<*mut DNode<T>>,
}

struct DNode<T> {
    data: T,
    prev: Option<*mut DNode<T>>,
    next: Option<Box<DNode<T>>>,
}

impl<T: std::fmt::Display> DoublyLinkedList<T> {
    pub fn new() -> Self {
        DoublyLinkedList {
            head: None,
            tail: None,
        }
    }

    pub fn is_empty(&self) -> bool {
        self.head.is_none()
    }

    pub fn push_front(&mut self, data: T) {
        let new_node = Box::new(DNode {
            data: data,
            prev: None,
            next: self.head.take(),
        });
        let raw_node = Box::into_raw(new_node);

        unsafe {
            if let Some(ref mut node) = &mut self.head {
                node.prev = Some(raw_node);
            }
            self.head = Some(Box::from_raw(raw_node));
            if self.tail.is_none() {
                self.tail = Some(raw_node);
            }
        }
    }

    pub fn pop_front(&mut self) -> Option<T> {
        if let Some(mut old_head) = self.head.take() {
            self.head = old_head.next.take();
            if let Some(new_head) = &mut self.head {
                new_head.prev = None;
            }
            if let Some(tail) = self.tail {
                if tail == &mut *old_head as *mut _ {
                    self.tail = Some(tail);
                }
            }
            Some(old_head.data)
        } else {
            None
        }
    }

    pub fn push_back(&mut self, data: T) {
        let new_node = Box::new(DNode {
            data: data,
            prev: self.tail,
            next: None,
        });
        let raw_node = Box::into_raw(new_node);

        unsafe {
            if let Some(tail) = self.tail {
                (*tail).next = Some(Box::from_raw(raw_node));
            } else {
                self.head = Some(Box::from_raw(raw_node));
            }
            self.tail = Some(raw_node);
        }
    }

    pub fn pop_back(&mut self) -> Option<T> {
        if let Some(tail) = self.tail {
            unsafe {
                let old_tail = Box::from_raw(tail);
                if let Some(prev) = old_tail.prev {
                    (*prev).next = None;
                    self.tail = Some(prev);
                } else {
                    self.head = None;
                    self.tail = None;
                }
                Some(old_tail.data)
            }
        } else {
            None
        }
    }

    pub fn display(&self) {
        let mut current = &self.head;
        while let Some(node) = current {
            print!("{} ", node.data);
            current = &node.next;
        }
        println!();
    }
    pub fn display_with_addresses(&self) {
        let mut current = &self.head;
        while let Some(node) = current {
            let address = node.as_ref() as *const DNode<T>;
            print!("Data: {}, Address: {:p} ", node.data, address);
            current = &node.next;
        }
        println!();
    }
}
