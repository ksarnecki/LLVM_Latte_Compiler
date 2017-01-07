#ifndef LLVM_OPT
#define LLVM_OPT

#include "Register.h"
#include "LLVMProgram.h"
#include <cstdio>
#include <map>
#include <algorithm>
#include <vector>

class Opt {
private:
  static void o0ReturnDeadCode(LLVMProgram& program);
  static void o0CheckPhiEntries(LLVMProgram& program);
  static void o0IfDeadCode(LLVMProgram& program);
public:
  static void o0(LLVMProgram&);
};

#endif