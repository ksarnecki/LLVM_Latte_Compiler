LFLAGS=-Wall -O2 
CC=g++

CC_FLAGS = $(shell find src/ -type d | sed -e 's/^/-I.\//') -I./build -I./src/Data -w -std=c++1y
DD_FILES = $(shell find src/Data/ -type f -name '*.dd')
CPP_FILES_GEN = $(patsubst src/Data/%.dd, src/Data/%.cpp, $(DD_FILES))
CPP_FILES = $(shell find src/ -type f -name '*.cpp') 
OBJ_FILES = $(patsubst src/%.cpp, build/%.o, $(CPP_FILES))
COBJ_FILES = $(shell find build/Common -type f -name '*.o')
LOBJ_FILES = $(shell find build/LLVM -type f -name '*.o')

all: LLVM_Compiler 

LLVM_Compiler: build/Parser.C $(OBJ_FILES)
	$(CC) $(LFLAGS) -o insc_llvm.bin $(COBJ_FILES) $(LOBJ_FILES)

src/Data/%.cpp: src/Data/%.dd
	bin/CodeGen < $< && \
        mv *.cpp src/Data && \
        mv *.h src/Data

build/%.o: src/%.cpp
	   mkdir -p "$(@D)"
	   g++ $(CC_FLAGS) -c -o $@ $<

build/Parser.C: src/LatteCPP.cf
	cp src/LatteCPP.cf build/ && \
	cd build && \
	mkdir -p Common && \
        bnfc -cpp_stl -m LatteCPP.cf && \
	make && \
	rm Test.o Printer.o TestLatteCPP && \
	mv *.o Common/

clean:
	rm -f *.bin
	rm -f build/*.* build/Makefile
	rm -f -r build/LLVM/* build/Common/*

data : $(CPP_FILES_GEN)