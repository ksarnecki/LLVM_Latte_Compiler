#include "Printer.h"

AnsiString Printer::renderFunctionArgument(const LLVMFunctionArgument& arg) {
  return renderRegisterKind(arg.getReg().getKind()) + " " + renderRegister(arg.getReg());
}

AnsiString Printer::renderRegisterKind(const RegisterKind& kind) {
  if(kind.isPtr())
    return renderRegisterKind(kind.asPtr()) + "*";
  if(kind.isValueI1())
    return "i1";
  if(kind.isValueI8())
    return "i8";
  if(kind.isValueI32())
    return "i32";
  if(kind.isValueDouble())
    return "double";
  throw Exception("[Printer::renderRegisterKind] Unsupported register kind.");
}

AnsiString Printer::renderBlock(const LLVMBlock& block) {
  return block.getName() + ": \n" + renderBody(block.getBody());
}

void Printer::printFunction(const LLVMFunction& function) {
  AnsiString outString = "define ";
  outString += renderRegisterKind(function.getType()) + " @" + function.getName() + "(";
  for(int i=0;i<function.getArgs().Size();i++) {
    if(i>0)
      outString += ", ";
    outString += renderFunctionArgument(function.getArgs()[i]);
  }
  outString += ") {\n";
  for(int i=0;i<function.getBlocks().Size();i++)
    outString += renderBlock(function.getBlocks()[i]);
  outString += "}\n";
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
    } else if (instr.isCallInstr()) {
      outString += "  " + renderCallInstr(instr.asCallInstr());
    } else if (instr.isBrInstr()) {
      outString += "  " + renderBrInstr(instr.asBrInstr());
    } else if (instr.isBrIfInstr()) {
      outString += "  " + renderBrIfInstr(instr.asBrIfInstr());
    } else if (instr.isReturnInstr()) {
      outString += "  " + renderReturnInstr(instr.asReturnInstr());
    } else if (instr.isPhiInstr()) {
      outString += "  " + renderPhiInstr(instr.asPhiInstr());
    } else {
      throw Exception("[LLVMProgramPrinter::print] Unknown instr type!");
    }
    outString += "\n";
  }
  return outString;
}

AnsiString Printer::renderCallInstr(const CallInstr& instr) {
  AnsiString outString = "call ";
  if(instr.getRetType().isNull())
    outString += "void";
  else
    outString += renderRegisterKind(instr.getRetType());
  outString += " @" + instr.getFunction() + "(";
  for(int i=0;i<instr.getArgs().Size();i++) {
    if(i>0)
      outString += ",";
    outString += renderRegisterKind(instr.getArgs()[i].getKind()) + " ";
    outString += renderRegister(instr.getArgs()[i]);
  }
  outString += ")";
  return outString;
}

AnsiString Printer::renderPrintInstr(const Register& reg) {
  return "call void @printInt(i32 " + renderRegister(reg) + ")";
}

AnsiString Printer::renderBrInstr(const BrInstr& br) {
  return "br label %" + br.getBlock();
}

AnsiString Printer::renderPhiInstr(const PhiInstr& phi) {
  AnsiString ret;
  ret = renderRegister(phi.getRet()) + " ";
  ret += " = phi " + renderRegisterKind(phi.getRet().getKind()) + " ";
  for(int i=0;i<phi.getCaseses().Size();i++) {
    if(i>0)
      ret += ",";
    ret += "[" + renderRegister(phi.getCaseses()[i].getValue()) + ", %" + phi.getCaseses()[i].getLabel() + "]";
  }
  return ret;
}

AnsiString Printer::renderBrIfInstr(const BrIfInstr& br) {
  return "br i1 " + renderRegister(br.getCond()) + ", label %" + br.getIfTrueBlock() + ", label %" + br.getIfFalseBlock();
}

AnsiString Printer::renderReturnInstr(const Register& ret) {
  return "ret " + renderRegisterKind(ret.getKind()) + " " + renderRegister(ret);
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
  // add, sub, div, mul, mod, lth, le, gth, ge, equ, ne
  if (binaryOperator.isAdd()) { 
    return "add i32";
  } else if (binaryOperator.isDiv()) {
    return "udiv i32";
  } else if (binaryOperator.isSub()) {
    return "sub i32";
  } else if (binaryOperator.isMul()) {
    return "mul i32";
  } else if (binaryOperator.isLth()) {
    return "icmp ult i32";
  } else if (binaryOperator.isLe()) {
    return "icmp ule i32";
  } else if (binaryOperator.isGth()) {
    return "icmp ugt i32";
  } else if (binaryOperator.isGe()) {
    return "icmp uge i32";
  } else if (binaryOperator.isEqu()) {
    return "icmp eq i32";
  } else if (binaryOperator.isNe()) {
    return "icmp ne i32";
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
