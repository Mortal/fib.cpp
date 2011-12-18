CPPFLAGS=-O3 -Wall -Wextra -Wno-type-limits
OBJECTS=fib.o lookup.o
PROGRAM=fib

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CPPFLAGS) -o $@ $^

clean:
	rm -f $(OBJECTS) $(PROGRAM) fibdebug.o fib.s

test: $(PROGRAM)
	seq 0 10 | ./$(PROGRAM)

fib.s: fibdebug.o
	objdump -S $^ > $@

fibdebug.o: fib.cpp
	$(CXX) $(CPPFLAGS) -g -c -o $@ $^

fib.cpp: fib.h

lookup.cpp: fib.h
