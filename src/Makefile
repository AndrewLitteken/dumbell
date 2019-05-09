CC = g++
LDFLAGS = -L/usr/local/opt/flex/lib
CPPFLAGS = -Wall -I/usr/local/opt/flex/include

TARGETS = dbl

all: $(TARGETS)

dbl: main.o DblParser.o DblDriver.o DblScanner.o Line.o Expr.o Symbol.o Type.o SymbolTable.o
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

main.o: main.cpp DblDriver.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

DblDriver.o: DblDriver.cpp DblDriver.h DblScanner.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

DblScanner.o: DblScanner.cpp 
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

DblScanner.cpp: DblScanner.ll DblParser.h DblScanner.h
	flex -o$@ $<

DblParser.o: DblParser.cpp DblParser.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

DblParser.cpp DblParser.h: DblParser.yy
	bison -v -o DblParser.cpp $<

clean:
	rm -f $(TARGETS) *.o DblScanner.cpp DblParser.h DblParser.cpp DblParser.output *.hh
