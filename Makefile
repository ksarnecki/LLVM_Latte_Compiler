LFLAGS=-Wall -O2 
CC=g++

CC_FLAGS = $(shell find src/ -type d | sed -e 's/^/-I.\//') -I./build -I./src/Data -w -std=c++1y
DD_FILES = $(shell find src/Data/ -type f -name '*.dd')
CPP_FILES_GEN = $(patsubst src/Data/%.dd, src/Data/%.cpp, $(DD_FILES))
CPP_FILES = $(shell find src/ -type f -name '*.cpp') 
OBJ_FILES = $(patsubst src/%.cpp, build/%.o, $(CPP_FILES))
DOBJ_FILES = $(shell find build/Data -type f -name '*.o')
COBJ_FILES = $(shell find build/Common -type f -name '*.o')
LOBJ_FILES = $(shell find build/LLVM -type f -name '*.o')

all: data LLVM_Compiler 

LLVM_Compiler: $(OBJ_FILES)
	$(CC) $(LFLAGS) -o llvm_latte_compiler.bin $(COBJ_FILES) $(LOBJ_FILES) $(DOBJ_FILES)

src/Data/Types.cpp: src/Data/Types.dd
	bin/CodeGen -json < src/Data/Types.dd && \
    mv Types.cpp src/Data && \
    mv Types.h src/Data

src/Data/%.cpp: src/Data/%.dd
	bin/CodeGen -json < $< && \
    mv *.cpp src/Data && \
    mv *.h src/Data

build/%.o: src/%.cpp
	   mkdir -p "$(@D)"
	   g++ $(CC_FLAGS) -c -o $@ $<

bnfc: src/LatteCPP.cf
	cp src/LatteCPP.cf build/ && \
	cd build && \
	mkdir -p Common && \
        ../bin/bnfc -cpp -m -l LatteCPP.cf && \
	make && \
	rm Test.o Printer.o TestLatteCPP && \
	mv *.o Common/

data: data_clean data_make

data_clean: 
	rm -f src/Data/*.cpp src/Data/*.h

data_make: $(CPP_FILES_GEN)

clean:
	rm -f *.bin
	rm -f build/*.* build/Makefile
	rm -f -r build/LLVM/* build/Common/* build/Data/*
