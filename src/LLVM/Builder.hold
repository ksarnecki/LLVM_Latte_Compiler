#ifndef LlvmBuilder_HEADER
#define LlvmBuilder_HEADER
/* You might want to change the above name. */

#include "Absyn.H"
#include "LLVMData.h"

class LlvmBuilder : public Visitor
{
private:
  LLVMRegisterData llvmRegisterData = LLVMRegisterData(Register::createNull(), Registers());
  LLVMProgram llvmProgram;
public:
  void visitProgram(Program* p);
  void visitStmt(Stmt* p);
  void visitExp(Exp* p);
  void visitProg(Prog* p);
  void visitSAss(SAss* p);
  void visitSExp(SExp* p);
  void visitExpAdd(ExpAdd* p);
  void visitExpSub(ExpSub* p);
  void visitExpMul(ExpMul* p);
  void visitExpDiv(ExpDiv* p);
  void visitExpLit(ExpLit* p);
  void visitExpVar(ExpVar* p);
  void visitListStmt(ListStmt* p);

  void visitInteger(Integer x);
  void visitChar(Char x);
  void visitDouble(Double x);
  void visitString(String x);
  void visitIdent(Ident x);

  LLVMProgram compile(Visitable *v) {
    v->accept(this);
    return llvmProgram;
  }
  
  Register getNextIntegerRegister();
  Register getNextVariableRegister(AnsiString);

  Register getVariableRegister(AnsiString);
  int getVariableRegisterPos(AnsiString);
};

#endif
