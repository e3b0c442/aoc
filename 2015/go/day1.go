package aoc2015

import (
	"fmt"
	"os"
	"time"
)

func Day1(filename string) error {
	fmt.Println("Day 1: Not Quite Lisp")

	input, err := os.ReadFile(filename)
	if err != nil {
		return err
	}

	start := time.Now()
	solution, err := day1Part1(string(input))
	end := time.Now()
	if err != nil {
		return err
	}
	fmt.Printf("\tPart 1: %d (%s)\n", solution, end.Sub(start))

	start = time.Now()
	solution, err = day1Part2(string(input))
	end = time.Now()
	if err != nil {
		return err
	}
	fmt.Printf("\tPart 2: %d (%s)\n", solution, end.Sub(start))

	return nil
}

func day1Part1(input string) (int, error) {
	floor := 0
	for _, c := range input {
		switch c {
		case '(':
			floor++
		case ')':
			floor--
		default:
			return 0, fmt.Errorf("invalid input: %c", c)
		}
	}

	return floor, nil
}

func day1Part2(input string) (int, error) {
	floor := 0

	for i, c := range input {
		switch c {
		case '(':
			floor++
		case ')':
			floor--
		default:
			return 0, fmt.Errorf("invalid input: %c", c)
		}
		if floor == -1 {
			return i + 1, nil
		}
	}

	return 0, fmt.Errorf("no solution found")
}
