echo "***COMPILING...***"
clang++-3.5 -O0 -o $1.ll -emit-llvm -S $1.c
echo "AS"
llvm-as -o $1.bc $1.ll
echo "***START***"
lli $1.bc
#cat $1/$1.output
