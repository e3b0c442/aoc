#!/usr/bin/env python3

import sys
import time
from lib import format_duration


def day(input_file: str) -> None:
    with open(input_file) as f:
        input = f.read()

    print("Day 1: Not Quite Lisp")
    start = time.time()
    print(f"\tPart 1: {_part1(input)} ({format_duration(time.time() - start)})")
    start = time.time()
    print(f"\tPart 2: {_part2(input)} ({format_duration(time.time() - start)})")


def _part1(input: str) -> int:
    floor: int = 0

    for c in input:
        match c:
            case "(":
                floor += 1
            case ")":
                floor -= 1
            case _:
                raise RuntimeError("invalid input")

    return floor


def _part2(input: str) -> int:
    floor: int = 0

    for (i, c) in enumerate(input):
        match c:
            case "(":
                floor += 1
            case ")":
                floor -= 1
            case _:
                raise RuntimeError("invalid input")

        if floor < 0:
            return i + 1

    raise RuntimeError("no solution found")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        raise RuntimeError("must provide path to input file")
    start = time.time()
    day(sys.argv[1])
    print(f"\tCompleted in {format_duration(time.time() - start)}")
