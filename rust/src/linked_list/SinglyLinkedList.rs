#[derive(Clone)]
enum Node<T> {
    None,
    Node { value: T, next: Box<Node<T>> },
}

#[derive(Clone)]
struct Cursor<T> {
    curr: Node<T>,
}

impl<T> Node<T>
where
    T: Copy,
{
    pub fn new() -> Self {
        Self::None
    }

    pub fn pop(&mut self) -> Option<T> {
        match self {
            Self::None => None,
            Self::Node { value, next } => {
                let mut n = Box::new(Self::None);
                let value = *value;
                std::mem::swap(next, &mut n);
                self.to_next(*n);
                Some(value)
            }
        }
    }

    pub fn push(&mut self, x: T) {
        match self {
            Self::None => self.to_link(x),
            Self::Node { next, .. } => next.push(x),
        };
    }

    fn to_none(&mut self) {
        *self = std::mem::replace(self, Node::None);
    }

    fn to_next(&mut self, nxt: Node<T>) {
        *self = nxt;
    }

    fn to_link(&mut self, x: T) {
        *self = match self {
            Self::None => Self::Node {
                value: x,
                next: Box::new(Self::None),
            },
            _ => {
                panic!("something went wrong");
            }
        };
    }
}

impl<T> IntoIterator for Node<T>
where
    T: Copy,
{
    type value = T;
    type IntoIter = Cursor<T>;

    fn into_iter(self) -> Self::IntoIter {
        Cursor { curr: self }
    }
}

impl<T> Iterator for Cursor<T>
where
    T: Copy,
{
    type value = T;

    fn next(&mut self) -> Option<T> {
        let nxt = match self.curr {
            Node::None => None,
            Node::Node {
                value,
                ref mut next,
            } => {
                let mut n = Box::new(Node::None);
                std::mem::swap(next, &mut n);
                self.curr = *n;
                Some(value)
            }
        };
        nxt
    }
}

fn main() {
    let mut list: Node<i32> = Node::new();
    let mut list2: Node<i32> = Node::new();

    list.push(1);
    list.push(2);
    list.push(3);
    list.push(4);

    list2.push(10);
    list2.push(20);
    list2.push(30);

    println!("{}", list2.pop().unwrap());
    println!("{}", list2.pop().unwrap());
    println!("{}", list2.pop().unwrap());
    println!("---");

    for i in list.clone() {
        println!("{}", i);
    }

    for i in list.clone().into_iter().map(|x| x * 2) {
        println!("{}", i)
    }

    for (i, x) in list.into_iter().enumerate() {
        println!("iter2: {}, {}", i, x);
    }
}
