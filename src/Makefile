CC = g++
LDFLAGS = -L/usr/local/opt/flex/lib
CPPFLAGS = -Wall -I/usr/local/opt/flex/include

TARGETS = ocl

all: $(TARGETS)

ocl: main.o ocl-parser.o ocl-driver.o ocl-scanner.o line.o expr.o Symbol.o SymbolTable.o
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

main.o: main.cpp ocl-driver.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

ocl-driver.o: ocl-driver.cpp ocl-driver.h ocl-scanner.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

ocl-scanner.o: ocl-scanner.cpp 
	$(CC) $(CPPFLAGS) -c -o $@ $<

expr.o: expr.cpp expr.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

line.o: line.cpp line.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

Symbol.o: Symbol.cpp symbol.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

SymbolTable.o: SymbolTable.cpp SymbolTable.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

ocl-scanner.cpp: ocl-scanner.ll ocl-parser.h ocl-scanner.h
	flex -o$@ $<

ocl-parser.o: ocl-parser.cpp ocl-parser.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

ocl-parser.cpp ocl-parser.h: ocl-parser.yy
	bison -v -o ocl-parser.cpp $<

clean:
	rm -f $(TARGETS) *.o ocl-scanner.cpp ocl-parser.h ocl-parser.cpp ocl-parser.output *.hh
