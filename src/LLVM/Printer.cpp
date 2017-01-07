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
  if(kind.isStruct())
    return "%struct." + kind.asStruct();
  if(kind.isConstPtr())
    return "[ " + AnsiString(kind.asConstPtr().getCount()) + " x " + renderRegisterKind(kind.asConstPtr().getKind()) + "]*";
  throw Exception("[Printer::renderRegisterKind] Unsupported register kind.");
}

AnsiString Printer::renderBlock(const LLVMBlock& block) {
  return block.getName() + ": \n" + renderBody(block.getBody());
}

void Printer::printFunction(const LLVMFunction& function) {
  AnsiString outString = "define ";
  if(function.getType().isVoid()) {
    outString += "void";
  } else {
    outString += renderRegisterKind(function.getType().asObj());
  }
  outString +=  " @" + function.getName() + "(";
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
  AnsiString pre = "declare void @printInt(i32);\n";
  pre += "declare i32 @scanf(i8*, ...)\n";
  pre += "declare i32 @readInt()\n";
  pre += "declare i8* @readString()\n";
  pre += "declare void @printString(i8*)\n";
  pre += "declare void @error()\n";
  pre += "declare i8* @concatenate(i8*, i8*)\n";

  for(int i=0;i<program.getStrings().Size();i++)
    pre += "@.str"+AnsiString(program.getStrings()[i].getId())+" = private unnamed_addr constant ["+AnsiString(program.getStrings()[i].getValue().Length()+1)+" x i8] c\""+program.getStrings()[i].getValue()+"\\00\", align 1\n";

  for(int i=0;i<program.getStructs().Size();i++) {
    pre += "%struct." + program.getStructs()[i].getName() + " = type { ";
    for(int j=0;j<program.getStructs()[i].getElems().Size();j++) {
      if(j>0)
        pre += ", ";
      pre += renderRegisterKind(program.getStructs()[i].getElems()[j]) + " ";
    }
    pre += "}\n";
  }

  printf("%s", pre.c_str());

  for(int i=0;i<program.getFunctions().Size();i++)
    printFunction(program.getFunctions()[i]);
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
    } else if (instr.isCommentInstr()) {
      outString += ";" + instr.asCommentInstr();
    } else if (instr.isAllocaInstr()) {
      outString += "  " + renderAllocaInstr(instr.asAllocaInstr());
    } else if (instr.isLoadInstr()) {
      outString += "  " + renderLoadInstr(instr.asLoadInstr());
    } else if (instr.isStoreInstr()) {
      outString += "  " + renderStoreInstr(instr.asStoreInstr());
    } else if (instr.isGetElementPtrInstr()) {
      outString += "  " + renderGetElementPtrInstr(instr.asGetElementPtrInstr());
    } else{
      throw Exception("[LLVMProgramPrinter::print] Unknown instr type!");
    }
    outString += "\n";
  }
  return outString;
}

AnsiString Printer::renderCallInstr(const CallInstr& instr) {
  AnsiString outString;
  if(instr.getRetType().isObj())
    outString += renderRegister(instr.getRetType().asObj()) + " = ";
  outString += "call ";
  if(instr.getRetType().isVoid())
    outString += "void";
  else
    outString += renderRegisterKind(instr.getRetType().asObj().getKind());
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

AnsiString Printer::renderAllocaInstr(const AllocaInstr& alloca) {
  if(alloca.getCount().isSingle())
    return renderRegister(alloca.getRet()) + " = alloca " + renderRegisterKind(alloca.getRet().getKind().asPtr());
  return renderRegister(alloca.getRet()) + " = alloca " + renderRegisterKind(alloca.getRet().getKind().asPtr()) + ", i32 " + renderRegister(alloca.getCount().asMultiple());
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

AnsiString Printer::renderReturnInstr(const ReturnInstr& ret) {
  if(ret.isValue())
    return "ret " + renderRegisterKind(ret.asValue().getKind()) + " " + renderRegister(ret.asValue());
  return "ret void";
}

AnsiString Printer::renderBinaryOperationInstr(const BinaryOperation& operation) {
  AnsiString ret;
  
  if(!operation.getBop().isMod()) {
    ret += renderRegister(operation.getOutReg()) + " = ";
    ret += renderBinaryOperator(operation.getBop()) + " " + renderRegisterKind(operation.getKind()) + " ";
    ret += renderBinaryOperationArgument(operation.getLArg()) + ", ";
    ret += renderBinaryOperationArgument(operation.getRArg());
  } else {
    //TODO dodać do generatora
    AnsiString pomReg1 = "%srem" + AnsiString(operation.getOutReg().getId()) + "_1";
    AnsiString pomReg2 = "%srem" + AnsiString(operation.getOutReg().getId()) + "_2";
    AnsiString pomReg3 = "%srem" + AnsiString(operation.getOutReg().getId()) + "_3";
    AnsiString pomReg4 = "%srem" + AnsiString(operation.getOutReg().getId()) + "_4";
    ret += "  " + pomReg1 + " = alloca i32, align 4\n";
    ret += "  " + pomReg2 + " = alloca i32, align 4\n";
    ret += "  store i32 " + renderBinaryOperationArgument(operation.getLArg()) + ", i32* " + pomReg1 + ", align 4\n";
    ret += "  store i32 " + renderBinaryOperationArgument(operation.getRArg()) + ", i32* " + pomReg2 + ", align 4\n";
    ret += "  " + pomReg3 + " = load i32* " + pomReg1 +", align 4\n";
    ret += "  " + pomReg4 + " = load i32* " + pomReg2 +", align 4\n";
    ret += "  " + renderRegister(operation.getOutReg()) + " = srem i32 " + pomReg3 + ", " + pomReg4;

  }
  
  return ret;
}

AnsiString Printer::renderLoadInstr(const LoadInstr& load) {
  AnsiString ret;
  ret += renderRegister(load.getRet()) + " = ";
  ret += "load ";
  ret += renderRegisterKind(load.getPtr().getKind()) + " ";
  ret += renderRegister(load.getPtr());
  return ret;
}

AnsiString Printer::renderStoreInstr(const StoreInstr& store) {
  AnsiString ret;
  ret += "store ";
  ret += renderRegisterKind(store.getVal().getKind()) + " ";
  ret += renderRegister(store.getVal()) + ", ";
  ret += renderRegisterKind(store.getPtr().getKind()) + " ";
  ret += renderRegister(store.getPtr());
  return ret;
}

AnsiString Printer::renderGetElementPtrInstr(const GetElementPtrInstr& get) {
  AnsiString ret;
  ret += renderRegister(get.getRet()) + " = ";
  ret += "getelementptr ";
  ret += renderRegisterKind(get.getPtr().getKind()) + " ";
  ret += renderRegister(get.getPtr());
  for(int i=0;i<get.getIndexes().Size();i++) {
    ret += ", " + renderRegisterKind(get.getIndexes()[i].getKind()) + " ";
    ret += renderRegister(get.getIndexes()[i]);
  }
  return ret;
}

AnsiString Printer::renderBinaryOperator(const BinaryOperator& binaryOperator) {
  // add, sub, div, mul, mod, lth, le, gth, ge, equ, ne
  if (binaryOperator.isAdd()) { 
    return "add";
  } else if (binaryOperator.isDiv()) {
    return "udiv";
  } else if (binaryOperator.isSub()) {
    return "sub";
  } else if (binaryOperator.isMul()) {
    return "mul";
  } else if (binaryOperator.isLth()) {
    return "icmp slt";
  } else if (binaryOperator.isLe()) {
    return "icmp sle";
  } else if (binaryOperator.isGth()) {
    return "icmp sgt";
  } else if (binaryOperator.isGe()) {
    return "icmp sge";
  } else if (binaryOperator.isEqu()) {
    return "icmp eq";
  } else if (binaryOperator.isNe()) {
    return "icmp ne";
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
  if(r.getPlain().isTrue())
    return r.getPlain().asTrue();
  if(r.getKind().isConstPtr())
    return "@.str" + AnsiString(r.getId());
  return "%reg_" + AnsiString(r.getId());
}