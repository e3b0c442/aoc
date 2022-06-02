use simple_error::{bail, simple_error};
use std::error::Error;
use std::fs;
use std::time::Instant;

pub fn day1(input_file: &str) -> Result<(), Box<dyn Error>> {
    println!("Day 1: Not Quite Lisp");

    let input = fs::read_to_string(input_file)?;

    let start = Instant::now();
    println!("\tPart 1: {} ({:?})", part1(&input)?, start.elapsed());
    let second = Instant::now();
    println!("\tPart 2: {} ({:?})", part2(&input)?, second.elapsed());
    println!("\t\t Completed in {:?}", start.elapsed());
    Ok(())
}

fn part1(input: &str) -> Result<i32, Box<dyn Error>> {
    input.chars().try_fold(0, |floor, c| match c {
        '(' => Ok(floor + 1),
        ')' => Ok(floor - 1),
        _ => bail!("Invalid input: {}", c),
    })
}

#[derive(Debug)]
enum Basement {
    Step(i32),
    Err(Box<dyn Error>),
}
impl std::error::Error for Basement {}
impl std::fmt::Display for Basement {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "")
    }
}

fn part2(input: &str) -> Result<i32, Box<dyn Error>> {
    match input
        .chars()
        .enumerate()
        .try_fold(0, |mut floor, (step, c)| match c {
            '(' => Ok(floor + 1),
            ')' => {
                floor -= 1;
                if floor < 0 {
                    Err(Basement::Step(step as i32))
                } else {
                    Ok(floor)
                }
            }
            _ => Err(Basement::Err(simple_error!("Invalid input").into())),
        }) {
        Err(Basement::Step(step)) => Ok(step),
        Err(Basement::Err(err)) => Err(err),
        _ => bail!("Solution not found"),
    }
}
