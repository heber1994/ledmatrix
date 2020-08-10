SOURCE=main
TARGET=main

all: clean compile run

clean :
	rm -f *.exe *.exe.stackdump *.txt
	
compile :
	x86_64-w64-mingw32-g++.exe -std=c++14 --static -static-libstdc++ -static-libgcc $(SOURCE).cpp -I /customheaders -o $(TARGET).exe

gnucompile:
	g++ -std=c++14 --static -static-libstdc++ -static-libgcc $(SOURCE).cpp -I /customheaders -o $(TARGET).exe

run: 
	./$(TARGET).exe

.PHONY: all