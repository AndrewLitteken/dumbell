CC = g++
LDFLAGS = -L/usr/local/opt/flex/lib
CPPFLAGS = -Wall -I/usr/local/opt/flex/include

TARGETS = ocl

all: $(TARGETS)

ocl: main.o OclParser.o OclDriver.o OclScanner.o Line.o Expr.o Symbol.o Type.o SymbolTable.o
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

main.o: main.cpp OclDriver.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

OclDriver.o: OclDriver.cpp OclDriver.h OclScanner.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

OclScanner.o: OclScanner.cpp 
	$(CC) $(CPPFLAGS) -c -o $@ $<

Expr.o: Expr.cpp Expr.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

Line.o: Line.cpp Line.h Expr.h Type.h Symbol.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

Type.o: Type.cpp Line.h Expr.h Type.h Symbol.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

Symbol.o: Symbol.cpp Symbol.h Type.h Expr.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

SymbolTable.o: SymbolTable.cpp SymbolTable.h Symbol.h Type.h Expr.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

OclScanner.cpp: OclScanner.ll OclParser.h OclScanner.h
	flex -o$@ $<

OclParser.o: OclParser.cpp OclParser.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

OclParser.cpp OclParser.h: OclParser.yy
	bison -v -o OclParser.cpp $<

clean:
	rm -f $(TARGETS) *.o OclScanner.cpp OclParser.h OclParser.cpp OclParser.output *.hh
