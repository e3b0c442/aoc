package main

import (
	"fmt"
	"log"
	"os"
	"path"
	"time"

	aoc2015 "github.com/e3b0c442/aoc/2015/go"
)

var days = []func(string) error{
	aoc2015.Day1,
}

func main() {
	if len(os.Args) < 2 {
		log.Fatal("must provide path to input files")
	}

	start := time.Now()
	for i, day := range days {
		dayStart := time.Now()
		if err := day(path.Join(os.Args[1], fmt.Sprintf("%d.txt", i+1))); err != nil {
			log.Fatal(err)
		}
		dayEnd := time.Now()
		fmt.Printf("\tCompleted in %s\n", dayEnd.Sub(dayStart))
	}
	fmt.Printf("All puzzles completed in %s\n", time.Now().Sub(start))
}
