#ifndef CODEBUILDER_HEADER
#define CODEBUILDER_HEADER

#include "Absyn.H"
#include "Store.h"
#include "BuilderEnviroment.h"
#include "LLVMProgram.h"
#include "TypeError.h"

class CodeBuilder : public Visitor
{
private:
  RegisterData registerData = RegisterData(Register(-1, RegisterKind::createNull()), Registers());
  Store store;
  BuilderEnviroment enviroment;
  Type actType = Type::createNull();
  Type actRet = Type::createNull();
  LLVMBlockArray actBlocks;
  LLVMProgram program;
  int actNesting = 0;
  TypeErrors errors;

public:
  void visitProgram(Program* p);
  void visitTopDef(TopDef* p);
  void visitArg(Arg* p);
  void visitBlock(Block* p);
  void visitStmt(Stmt* p);
  void visitItem(Item* p);
  void visitLatteType(LatteType* p);
  void visitExpr(Expr* p);
  void visitAddOp(AddOp* p);
  void visitMulOp(MulOp* p);
  void visitRelOp(RelOp* p);
  void visitProg(Prog* p);
  void visitFnDef(FnDef* p);
  void visitAr(Ar* p);
  void visitBlk(Blk* p);
  void visitEmpty(Empty* p);
  void visitBStmt(BStmt* p);
  void visitDecl(Decl* p);
  void visitNoInit(NoInit* p);
  void visitInit(Init* p);
  void visitAss(Ass* p);
  void visitIncr(Incr* p);
  void visitDecr(Decr* p);
  void visitRet(Ret* p);
  void visitVRet(VRet* p);
  void visitCond(Cond* p);
  void visitCondElse(CondElse* p);
  void visitWhileStmnt(WhileStmnt* p);
  void visitSExp(SExp* p);
  void visitIntType(IntType* p);
  void visitStrType(StrType* p);
  void visitBoolType(BoolType* p);
  void visitVoidType(VoidType* p);
  void visitFun(Fun* p);
  void visitEVar(EVar* p);
  void visitELitInt(ELitInt* p);
  void visitELitTrue(ELitTrue* p);
  void visitELitFalse(ELitFalse* p);
  void visitEApp(EApp* p);
  void visitEString(EString* p);
  void visitNeg(Neg* p);
  void visitNott(Nott* p);
  void visitEMul(EMul* p);
  void visitEAdd(EAdd* p);
  void visitERel(ERel* p);
  void visitEAnd(EAnd* p);
  void visitEOr(EOr* p);
  void visitPlus(Plus* p);
  void visitMinus(Minus* p);
  void visitTimes(Times* p);
  void visitDiv(Div* p);
  void visitMod(Mod* p);
  void visitLTH(LTH* p);
  void visitLE(LE* p);
  void visitGTH(GTH* p);
  void visitGE(GE* p);
  void visitEQU(EQU* p);
  void visitNE(NE* p);
  void visitListTopDef(ListTopDef* p);
  void visitListArg(ListArg* p);
  void visitListStmt(ListStmt* p);
  void visitListItem(ListItem* p);
  void visitListLatteType(ListLatteType* p);
  void visitListExpr(ListExpr* p);

  void visitInteger(Integer x);
  void visitChar(Char x);
  void visitDouble(Double x);
  void visitString(String x);
  void visitIdent(Ident x);

  LLVMProgram compile(Visitable *v) {
    v->accept(this);
    return program;
  }

  //pomocnicze
  Register getNextRegister(const RegisterKind);
  RegisterKind getBinaryOperationRegisterKind(const Register&, const Register&);
  RegisterKind getRegisterKindFromLatteType(const LatteType*);

  void initBlock(const AnsiString&);
  AnsiString getNextBlockNameByPrefix(const AnsiString&);
  void addInstr(const Instr);

  const AnsiString whileToken = "while";

  

  void updateEnviroment(const AnsiString&, const Object&);

  Object getObjectByIdent(const AnsiString&);
  Register getRegisterByIdent(const AnsiString&);
};


#endif
