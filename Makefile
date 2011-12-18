CPPFLAGS=-O3 -Wall -Wextra -Wno-type-limits -fno-guess-branch-probability
OBJECTS=fib.o lookup.o

all: fib

fib: $(OBJECTS)
	$(CXX) $(CPPFLAGS) -o $@ $^

clean:
	rm -f $(OBJECTS) fib fibdebug.o fib.s fib32.s fibdump.s

test: fib
	seq 0 10 | ./fib

fib.s: fib.cpp
	$(CXX) $(CPPFLAGS) -S -o - $^ | grep -v '^\.L[VBFC]' > $@

fib32.s: fib.cpp
	$(CXX) -m32 $(CPPFLAGS) -S -o - $^ | grep -v '^\.L[VBFC]' > $@

fibdump.s: fibdebug.o
	objdump -S $^ > $@

fibdebug.o: fib.cpp
	$(CXX) $(CPPFLAGS) -g -c -o $@ $^

fib.cpp: fib.h

lookup.cpp: fib.h
