#include "LLVMProgramPrinter.h"

void LLVMProgramPrinter::print(const LLVMProgram& program) {
  AnsiString outString;
  outString += "declare void @printInt(i32);\n";
  outString += "define i32 @main(i32 %argc, i8** %argv) {\n";
  for (int i=0;i<program.Size();i++) {
    LLVMInstr instr = program[i];
    if (instr.isBinaryOperationInstr()) {
      outString += "  " + renderBinaryOperationInstr(instr.asBinaryOperationInstr());
    } else if (instr.isPrintInstr()) {
      outString += "  " + renderPrintInstr(instr.asPrintInstr());
    } else {
      throw Exception("[LLVMProgramPrinter::print] Unknown instr type!");
    }
    outString += "\n";
  }
  outString += "  ret i32 0\n";
  outString += "}";
  printf("%s\n", outString.c_str());
}

AnsiString LLVMProgramPrinter::renderPrintInstr(const Register& reg) {
  return "call void @printInt(i32 " + renderRegister(reg) + ")";
}

AnsiString LLVMProgramPrinter::renderBinaryOperationInstr(const LLVMBinaryOperation& operation) {
  AnsiString ret;
  ret += renderRegister(operation.getOutReg()) + " = ";
  ret += renderBinaryOperator(operation.getBop()) + " ";
  ret += renderBinaryOperationArgument(operation.getLArg()) + ", ";
  ret += renderBinaryOperationArgument(operation.getRArg());
  return ret;
}

AnsiString LLVMProgramPrinter::renderBinaryOperator(const LLVMBinaryOperator& binaryOperator) {
  if (binaryOperator.isAdd()) { 
    return "add i32";
  } else if (binaryOperator.isDiv()) {
    return "udiv i32";
  } else if (binaryOperator.isSub()) {
    return "sub i32";
  } else if (binaryOperator.isMul()) {
    return "mul i32";
  } else {
    throw Exception("[LLVMProgramPrinter::renderBinaryOperationArgument] Unknown argument type!");
  }
}

AnsiString LLVMProgramPrinter::renderBinaryOperationArgument(const LLVMBinaryOperationArgument& argument) {
  if (argument.isRegister())
    return renderRegister(argument.asRegister());
  if (argument.isInteger())
    return AnsiString(argument.asInteger());
  throw Exception("[LLVMProgramPrinter::renderBinaryOperationArgument] Unknown argument type!");
}

AnsiString LLVMProgramPrinter::renderRegister(const Register& r) {
  if (r.isVariableRegister()) {
    return "%" + r.asVariableRegister().getName() + "_.v" + AnsiString(r.asVariableRegister().getVersion());
  } else if (r.isIntegerRegister()) {
    return "%reg_" + AnsiString(r.asIntegerRegister());
  } else if (r.isNull()) {
    return "0";
  }
  throw Exception("[LLVMProgramPrinter::renderRegister] Unknown register type!");
}
