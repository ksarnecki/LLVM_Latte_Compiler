#ifndef LLVM_OPT
#define LLVM_OPT

#include "Register.h"
#include "LLVMProgram.h"
#include <cstdio>
#include <map>

class Opt {
private:
  static void o0ReturnDeadCode(LLVMProgram& program);
public:
  static void o0(LLVMProgram&);
};

#endif