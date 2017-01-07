#!/bin/bash
echo "***COMPILING***"
../llvm_latte_compiler.bin < $1.lat > tmp/last.ll
echo "***COMPILING...***"
rm -f tmp/last.bc
llvm-as -o tmp/last.bc tmp/last.ll
if [ -f tmp/last.bc ]; then
  llvm-as -o runtime.bc runtime.ll
  echo "***RUNTIME LINKING***"
  llvm-link -o tmp/out.bc tmp/last.bc runtime.bc 
  echo "***START***"
  echo "-37 foo bar" | lli tmp/out.bc > tmp/last.output
fi
cat tmp/last.output
echo "***DIFF**"
diff tmp/last.output $1.output
echo "**END DIFF**"
