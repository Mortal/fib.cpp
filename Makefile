CPPFLAGS=-O3 -Wall -Wextra -Wno-type-limits -fno-guess-branch-probability

FIBCPPDEP=fib.cpp fib.h tctc.h

# Driver targets

all: fib fib128

symbolic: fib.s fib32.s

debug: fibdebug

clean:
	rm -f *.o *.s fib fib128

test: fib
	seq 0 10 | ./fib

speedtest: fib
	./fib speedarray & sleep 5; kill $$!; wait
	./fib speedsearch & sleep 5; kill $$!; wait
	./fib speedlinear & sleep 5; kill $$!; wait

.PHONY: all symbolic clean test speedtest

# Executable targets

fib: fib.o lookup.o
	$(CXX) $(CPPFLAGS) -o $@ $^

fibdebug: fibdebug.o lookupdebug.o
	$(CXX) $(CPPFLAGS) -g -o $@ $^

fib128: fib128.o lookup128.o
	$(CXX) $(CPPFLAGS) -DFIB128 -o $@ $^

# Symbolic targets

fib.s: $(FIBCPPDEP)
	$(CXX) $(CPPFLAGS) -S -o - fib.cpp | grep -v '^\.L[VBFC]' > $@

fib32.s: $(FIBCPPDEP)
	$(CXX) -m32 $(CPPFLAGS) -S -o - fib.cpp | grep -v '^\.L[VBFC]' > $@

fibdump.s: fibdebug.o
	objdump -S $^ > $@

lookup.s: lookup.cpp
	$(CXX) $(CPPFLAGS) -S -o - $^ | grep -v '^\.L[VBFC]' > $@

# Relocatable targets

fibdebug.o: $(FIBCPPDEP)
	$(CXX) $(CPPFLAGS) -g -c -o $@ fib.cpp

lookupdebug.o: lookup.cpp
	$(CXX) $(CPPFLAGS) -g -c -o $@ $^

fib128.o: $(FIBCPPDEP)
	$(CXX) $(CPPFLAGS) -DFIB128 -c -o $@ fib.cpp

lookup128.o: lookup.cpp
	$(CXX) $(CPPFLAGS) -DFIB128 -c -o $@ $^

# Source-level dependencies

fib.o: $(FIBCPPDEP)
lookup.o: lookup.cpp fib.h
