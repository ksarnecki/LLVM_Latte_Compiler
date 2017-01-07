#!/bin/bash
echo "***COMPILING***"
../llvm_latte_compiler.bin < $1/$1.ins > tmp/$1.ll
echo "***COMPILING...***"
llvm-as -o tmp/$1.bc tmp/$1.ll
llvm-as -o runtime.bc runtime.ll
echo "***RUNTIME LINKING***"
llvm-link -o tmp/out.bc tmp/$1.bc runtime.bc 
echo "***START***"
lli tmp/out.bc
#cat $1/$1.output
