CC                  := gcc
ifdef OPT
override CCFLAGS    += -Wall -pedantic -std=c17 -O3
else
override CCFLAGS    += -Wall -g -pedantic -std=c17 -Og
endif
override LDFLAGS    += 


DAYNUMS     := 1 
DAYS        := $(addprefix day, $(DAYNUMS))
DAY_BINS    := $(addprefix bin/, $(DAYS))
DAY_OBJS    := $(addprefix obj/, $(addsuffix .o, $(DAYS)))
DAY_MAINS   := $(addprefix obj/main, $(addsuffix .o, $(DAYS)))
LIBS        := lib
LIB_OBJS    := $(addprefix obj/, $(addsuffix .o, $(LIBS)))

.PHONY: clean all aoc2015 $(DAYS)

all: aoc2015 $(DAYS)

aoc2015: obj bin bin/aoc2015

$(DAYS): % : obj bin bin/%

$(DAY_BINS): bin/% : obj/%.o obj/main%.o $(LIB_OBJS)
	$(CC) -o $@ $^ $(CCFLAGS) $(LDFLAGS)

$(DAY_MAINS): src/main.c
	$(CC) -c -o $@ $< -D DAYNUM=$(@:obj/main%.o=%) $(CCFLAGS)

bin/aoc2015: obj/aoc2015.o $(LIB_OBJS) $(DAY_OBJS)
	$(CC) -o $@ $^ $(CCFLAGS) $(LDFLAGS)

obj/aoc2015.o: src/main.c
	$(CC) -c -o $@ $< $(CCFLAGS)

$(DAY_OBJS): obj/%.o : src/%.c
	$(CC) -c -o $@ $< $(CCFLAGS)

$(LIB_OBJS): obj/%.o : src/%.c
	$(CC) -c -o $@ $< $(CCFLAGS)

obj:
	mkdir -p obj

bin:
	mkdir -p bin

clean:
	rm -rf obj
	rm -rf bin