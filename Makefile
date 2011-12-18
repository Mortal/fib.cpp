CPPFLAGS=-O3 -Wall -Wextra -Wno-type-limits
OBJECTS=fib.o lookup.o
PROGRAM=fib

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CPPFLAGS) -o $@ $^
clean:
	rm -f $(OBJECTS) $(PROGRAM)

test: $(PROGRAM)
	seq 0 10 | ./$(PROGRAM)

fib.cpp: fib.h

lookup.cpp: fib.h
