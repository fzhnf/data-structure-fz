#[derive(Clone)]
enum Link<T> {
    None,
    Link { item: T, next: Box<Link<T>> },
}

#[derive(Clone)]
struct Cursor<T> {
    curr: Link<T>,
}

impl<T> Link<T>
where
    T: Copy,
{
    pub fn new() -> Self {
        Self::None
    }

    pub fn pop(&mut self) -> Option<T> {
        match self {
            Self::None => None,
            Self::Link { item, next } => {
                let mut n = Box::new(Self::None);
                let item = *item;
                std::mem::swap(next, &mut n);
                self.to_next(*n);
                Some(item)
            }
        }
    }

    pub fn push(&mut self, x: T) {
        match self {
            Self::None => self.to_link(x),
            Self::Link { next, .. } => next.push(x),
        };
    }

    fn to_none(&mut self) {
        *self = std::mem::replace(self, Link::None);
    }

    fn to_next(&mut self, nxt: Link<T>) {
        *self = nxt;
    }

    fn to_link(&mut self, x: T) {
        *self = match self {
            Self::None => Self::Link {
                item: x,
                next: Box::new(Self::None),
            },
            _ => {
                panic!("something went wrong");
            }
        };
    }
}

impl<T> IntoIterator for Link<T>
where
    T: Copy,
{
    type Item = T;
    type IntoIter = Cursor<T>;

    fn into_iter(self) -> Self::IntoIter {
        Cursor { curr: self }
    }
}

impl<T> Iterator for Cursor<T>
where
    T: Copy,
{
    type Item = T;

    fn next(&mut self) -> Option<T> {
        let nxt = match self.curr {
            Link::None => None,
            Link::Link { item, ref mut next } => {
                let mut n = Box::new(Link::None);
                std::mem::swap(next, &mut n);
                self.curr = *n;
                Some(item)
            }
        };
        nxt
    }
}

fn main() {
    let mut list: Link<i32> = Link::new();
    let mut list2: Link<i32> = Link::new();

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
