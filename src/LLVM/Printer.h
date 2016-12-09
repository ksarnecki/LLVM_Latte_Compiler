#ifndef LLVM_PROGRAM_PRINTER
#define LLVM_PROGRAM_PRINTER

#include "Register.h"
#include "LLVMProgram.h"
#include <cstdio>

class Printer {
private:
  static AnsiString renderRegister(const Register&);
  static AnsiString renderBinaryOperationInstr(const BinaryOperation&);
  static AnsiString renderPrintInstr(const Register&);
  static AnsiString renderBinaryOperationArgument(const BinaryOperationArgument&);
  static AnsiString renderBinaryOperator(const BinaryOperator&);
public:
  static void print(const LLVMProgram&);
};

#endif
