//go:build ignore

package main

import (
	"fmt"
	"os"
	"path"
	"text/template"
)

var singleTmpl = `package main

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
	if err := aoc2015.Day{{ . }}(os.Args[1]); err != nil {
		log.Fatal(err)
	}
	fmt.Printf("\tCompleted in %s\n", time.Now().Sub(start))
}
`

var allTmpl = `package main

import (
	"fmt"
	"log"
	"os"
	"path"
	"time"

	aoc2015 "github.com/e3b0c442/aoc/2015/go"
)

var days = []func(string) error{
	{{ range . -}}aoc2015.Day{{.}},{{- end }}
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
`

func main() {
	single := template.New("single")
	single = template.Must(single.Parse(singleTmpl))

	fmt.Println("generating mains")
	days := os.Args[1:]
	wd, err := os.Getwd()
	if err != nil {
		panic(err)
	}

	for _, day := range days {
		dayPath := path.Join(wd, "cmd", fmt.Sprintf("day%s", day))
		os.MkdirAll(dayPath, 0755)
		f, err := os.Create(path.Join(dayPath, "main.go"))
		if err != nil {
			panic(err)
		}
		if err := single.Execute(f, day); err != nil {
			panic(err)
		}
		f.Close()
	}

	all := template.New("all")
	all = template.Must(all.Parse(allTmpl))

	allPath := path.Join(wd, "cmd", "aoc2015")
	os.MkdirAll(allPath, 0755)
	f, err := os.Create(path.Join(allPath, "main.go"))
	if err != nil {
		panic(err)
	}
	if err := all.Execute(f, days); err != nil {
		panic(err)
	}
	f.Close()
}
