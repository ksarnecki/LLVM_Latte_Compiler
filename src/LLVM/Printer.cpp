#include "Printer.h"

AnsiString Printer::renderFunctionArgument(const LLVMFunctionArgument& arg) {
  return renderRegisterKind(arg.getType()) + " " + arg.getName();
}

AnsiString Printer::renderRegisterKind(const RegisterKind& kind) {
  //TODO
  return "i32";
}

AnsiString Printer::renderBlock(const LLVMBlock& block) {
  return block.getName() + ": \n" + renderBody(block.getBody());
}

void Printer::printFunction(const LLVMFunction& function) {
  AnsiString outString = "define ";
  outString += renderRegisterKind(function.getType()) + " " + function.getName() + "(";
  for(int i=0;i<function.getArgs().Size();i++) {
    if(i>0)
      outString += ", ";
    outString += renderFunctionArgument(function.getArgs()[i]);
  }
  outString += ") {\n";
  for(int i=0;i<function.getBlocks().Size();i++)
    outString += renderBlock(function.getBlocks()[i]);
  printf("%s\n", outString.c_str());
}

void Printer::print(const LLVMProgram& program) {
  printf("declare void @printInt(i32);\n");
  for(int i=0;i<program.Size();i++)
    printFunction(program[i]);
}

AnsiString Printer::renderBody(const InstrArray& instrs) {
  AnsiString outString;
  for (int i=0;i<instrs.Size();i++) {
    Instr instr = instrs[i];
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
  return outString;
}

AnsiString Printer::renderPrintInstr(const Register& reg) {
  return "call void @printInt(i32 " + renderRegister(reg) + ")";
}

AnsiString Printer::renderBinaryOperationInstr(const BinaryOperation& operation) {
  AnsiString ret;
  ret += renderRegister(operation.getOutReg()) + " = ";
  ret += renderBinaryOperator(operation.getBop()) + " ";
  ret += renderBinaryOperationArgument(operation.getLArg()) + ", ";
  ret += renderBinaryOperationArgument(operation.getRArg());
  return ret;
}

AnsiString Printer::renderBinaryOperator(const BinaryOperator& binaryOperator) {
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

AnsiString Printer::renderBinaryOperationArgument(const BinaryOperationArgument& argument) {
  if (argument.isRegister())
    return renderRegister(argument.asRegister());
  if (argument.isNumber())
    return argument.asNumber();
  throw Exception("[LLVMProgramPrinter::renderBinaryOperationArgument] Unknown argument type!");
}

AnsiString Printer::renderRegister(const Register& r) {
  return "%reg_" + AnsiString(r.getId());
}
