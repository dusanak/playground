use std::io;
use rand::Rng;
use std::cmp::Ordering;

fn main() {
    println!("Guess the number!");

    let random_number = rand::thread_rng().gen_range(1..101);

    loop {
        println!("Input a guess.");
        
        let mut guess = String::new();
        io::stdin()
            .read_line(&mut guess)
            .expect("Read line failure");

        let guess: i32 = match guess.trim().parse() {
            Ok(number) => number,
            Err(_) => {
                println!("Input should be a number.");
                continue;
            }
        };
        
        println!("Your guess is: {}", guess);

        match guess.cmp(&random_number) {
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => {
                println!("You win!");
                break;
            }
        }
    }
}
