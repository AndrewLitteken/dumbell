CC = g++
LDFLAGS = -L/usr/local/opt/flex/lib
CPPFLAGS = -Wall -I/usr/local/opt/flex/include

TARGETS = ocl

all: $(TARGETS)

ocl: main.o tokens.o scanner.o
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

main.o: main.cpp tokens.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

tokens.o: tokens.cpp tokens.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

scanner.o: scanner.cpp tokens.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

scanner.cpp: scanner.ll
	flex++ -o$@ $<

clean:
	rm -f $(TARGETS) *.o scanner.cpp
