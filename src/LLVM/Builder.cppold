/*** BNFC-Generated Visitor Design Pattern LlvmBuilder. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "LLVMBuilder.h"
#include <cstdio>

static int max(int a, int b) {
  if (a>b)
    return a;
  return b;
}

void LlvmBuilder::visitProgram(Program* t) {} //abstract class
void LlvmBuilder::visitStmt(Stmt* t) {} //abstract class
void LlvmBuilder::visitExp(Exp* t) {} //abstract class

void LlvmBuilder::visitProg(Prog *prog) {
  prog->liststmt_->accept(this);
}

void LlvmBuilder::visitSAss(SAss *sass) {
  sass->exp_->accept(this);
  LLVMBinaryOperationArgument lArg = LLVMBinaryOperationArgument::createRegister(llvmRegisterData.getLastRegister());
  LLVMBinaryOperationArgument rArg = LLVMBinaryOperationArgument::createInteger(0);
  visitIdent(sass->ident_);
  Register outReg = getNextVariableRegister(sass->ident_);
  LLVMBinaryOperation llvmbo = LLVMBinaryOperation(outReg, lArg, rArg, LLVMBinaryOperator::createAdd());
  LLVMInstr instr = LLVMInstr::createBinaryOperationInstr(llvmbo);
  llvmProgram.Insert(instr);
  llvmRegisterData.getLastRegister() = outReg;
}

void LlvmBuilder::visitSExp(SExp *sexp) {
  sexp->exp_->accept(this);
  llvmProgram.Insert(LLVMInstr::createPrintInstr(llvmRegisterData.getLastRegister() ));
}

void LlvmBuilder::visitExpAdd(ExpAdd *expadd) {
  expadd->exp_1->accept(this);
  LLVMBinaryOperationArgument lArg = LLVMBinaryOperationArgument::createRegister(llvmRegisterData.getLastRegister());
  expadd->exp_2->accept(this);
   LLVMBinaryOperationArgument rArg = LLVMBinaryOperationArgument::createRegister(llvmRegisterData.getLastRegister());
  Register outReg = getNextIntegerRegister();
  LLVMBinaryOperation llvmbo = LLVMBinaryOperation(outReg, lArg, rArg,LLVMBinaryOperator::createAdd());
  LLVMInstr instr = LLVMInstr::createBinaryOperationInstr(llvmbo);
  llvmProgram.Insert(instr);
  llvmRegisterData.getLastRegister() = outReg;
}

void LlvmBuilder::visitExpSub(ExpSub *expsub) {
  expsub->exp_1->accept(this);
   LLVMBinaryOperationArgument lArg = LLVMBinaryOperationArgument::createRegister(llvmRegisterData.getLastRegister());
  expsub->exp_2->accept(this);
   LLVMBinaryOperationArgument rArg = LLVMBinaryOperationArgument::createRegister(llvmRegisterData.getLastRegister());
  Register outReg = getNextIntegerRegister();
  LLVMBinaryOperation llvmbo = LLVMBinaryOperation(outReg, lArg, rArg, LLVMBinaryOperator::createSub());
  LLVMInstr instr = LLVMInstr::createBinaryOperationInstr(llvmbo);
  llvmProgram.Insert(instr);
  llvmRegisterData.getLastRegister() = outReg;
}

void LlvmBuilder::visitExpMul(ExpMul *expmul) {
  expmul->exp_1->accept(this);
  LLVMBinaryOperationArgument lArg = LLVMBinaryOperationArgument::createRegister(llvmRegisterData.getLastRegister());
  expmul->exp_2->accept(this);
  LLVMBinaryOperationArgument rArg = LLVMBinaryOperationArgument::createRegister(llvmRegisterData.getLastRegister());
  Register outReg = getNextIntegerRegister();
  LLVMBinaryOperation llvmbo = LLVMBinaryOperation(outReg, lArg, rArg, LLVMBinaryOperator::createMul());
  LLVMInstr instr = LLVMInstr::createBinaryOperationInstr(llvmbo);
  llvmProgram.Insert(instr);
  llvmRegisterData.getLastRegister() = outReg;
}

void LlvmBuilder::visitExpDiv(ExpDiv *expdiv) {
  expdiv->exp_1->accept(this);
  LLVMBinaryOperationArgument lArg = LLVMBinaryOperationArgument::createRegister(llvmRegisterData.getLastRegister());
  expdiv->exp_2->accept(this);
  LLVMBinaryOperationArgument rArg = LLVMBinaryOperationArgument::createRegister(llvmRegisterData.getLastRegister());
  Register outReg = getNextIntegerRegister();
  LLVMBinaryOperation llvmbo = LLVMBinaryOperation(outReg, lArg, rArg, LLVMBinaryOperator::createDiv());
  LLVMInstr instr = LLVMInstr::createBinaryOperationInstr(llvmbo);
  llvmProgram.Insert(instr);
  llvmRegisterData.getLastRegister() = outReg;
}

void LlvmBuilder::visitExpLit(ExpLit *explit) {
  visitInteger(explit->integer_);
}

void LlvmBuilder::visitExpVar(ExpVar *expvar) {
  visitIdent(expvar->ident_);
}


void LlvmBuilder::visitListStmt(ListStmt* liststmt) {
  for (auto i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void LlvmBuilder::visitInteger(Integer x) {
  LLVMBinaryOperationArgument lArg = LLVMBinaryOperationArgument::createInteger(x);
  LLVMBinaryOperationArgument rArg = LLVMBinaryOperationArgument::createInteger(0);
  Register outReg = getNextIntegerRegister();
  LLVMBinaryOperation llvmbo = LLVMBinaryOperation(outReg, lArg, rArg, LLVMBinaryOperator::createAdd());
  LLVMInstr instr = LLVMInstr::createBinaryOperationInstr(llvmbo);
  llvmProgram.Insert(instr);
  llvmRegisterData.getLastRegister() = outReg;
}


void LlvmBuilder::visitIdent(Ident x) {
  Register reg = getVariableRegister(x);
  llvmRegisterData.getLastRegister() = reg;
}

Register LlvmBuilder::getNextIntegerRegister() {
  int mIntegerRegister = -1;
  for (int i=0;i<llvmRegisterData.getRegisters().Size();i++)
    if (llvmRegisterData.getRegisters()[i].isIntegerRegister())
      mIntegerRegister = max(mIntegerRegister, llvmRegisterData.getRegisters()[i].asIntegerRegister());
  Register reg = Register::createIntegerRegister(++mIntegerRegister);
  llvmRegisterData.getRegisters().Insert(reg);
  return reg;
}

Register LlvmBuilder::getNextVariableRegister(AnsiString name) {
  int ix = getVariableRegisterPos(name);
  if (ix==-1) {
    Register reg = Register::createVariableRegister(VariableRegister(name, 0));
    llvmRegisterData.getRegisters().Insert(reg); 
    return reg;
  }
  llvmRegisterData.getRegisters()[ix].asVariableRegister().getVersion()++;
  return llvmRegisterData.getRegisters()[ix];
}


int LlvmBuilder::getVariableRegisterPos(AnsiString name) {
  for (int i=0;i<llvmRegisterData.getRegisters().Size();i++)
    if (llvmRegisterData.getRegisters()[i].isVariableRegister() && llvmRegisterData.getRegisters()[i].asVariableRegister().getName()==name)
      return i;
  return -1;
}

Register LlvmBuilder::getVariableRegister(AnsiString name) {
  int ix = getVariableRegisterPos(name);
  if (ix!=-1)
    return llvmRegisterData.getRegisters()[ix];
  return Register::createNull();
}


// Reszta nieobsługiwanych isntrukcji

void LlvmBuilder::visitChar(Char x)
{
  /* Code for Char Goes Here */
}

void LlvmBuilder::visitDouble(Double x)
{
  /* Code for Double Goes Here */
}

void LlvmBuilder::visitString(String x)
{
  /* Code for String Goes Here */
}
