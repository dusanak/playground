#[derive(Debug)]
struct Rectangle {
    height: u32,
    width: u32
}

impl Rectangle {
    fn area(&self) -> u32 {
        self.height * self.width
    }

    fn can_hold(&self, other: &Rectangle) -> bool {
        if self.width < other.width {
            return false
        }
        if self.height < other.height {
            return false
        }
        true
    }

    fn square(size: u32) -> Rectangle {
        Rectangle {
            height: size,
            width: size
        }
    }
}

fn main() {
    let rect = Rectangle {
        height: 30,
        width: 50
    };

    println!("{}", rect.area());

    println!("{:?}", rect);

    let rect1 = Rectangle {
        width: 30,
        height: 50,
    };
    let rect2 = Rectangle::square(30);
    let rect3 = Rectangle {
        width: 60,
        height: 45,
    };

    println!("Can rect1 hold rect2? {}", rect1.can_hold(&rect2));
    println!("Can rect1 hold rect3? {}", rect1.can_hold(&rect3));
}

