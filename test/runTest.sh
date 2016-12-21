#!/bin/bash
../llvm_latte_compiler.bin < $1/$1.ins
../llvm_latte_compiler.bin < $1/$1.ins > tmp/$1.ll
llvm-as -o tmp/$1.bc tmp/$1.ll
#llvm-link -o tmp/out.bc tmp/$1.bc runtime.bc
#lli tmp/out.bc
#cat $1/$1.output
