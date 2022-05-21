package main

import (
	"fmt"
	"log"
	"os"
	"time"

	aoc2015 "github.com/e3b0c442/aoc/2015/go"
)

func main() {
	if len(os.Args) < 2 {
		log.Fatal("must provide path to input file")
	}

	start := time.Now()
	if err := aoc2015.Day1(os.Args[1]); err != nil {
		log.Fatal(err)
	}
	fmt.Printf("\tCompleted in %s\n", time.Now().Sub(start))
}
