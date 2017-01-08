#ifndef TYPECHECKER_HEADER
#define TYPECHECKER_HEADER

#include "Absyn.H"
#include "TypeCheckerStore.h"
#include "TypeCheckerEnviroment.h"
#include "TypeError.h"

class TypeCheckerManager
{
public:
  static bool cmp(const Type&, const Type&);
  static bool bsc(const Type&);
  static bool cst(const Type&, const Type&);
  static bool txt(const Type&);
  static void addIdent(const Ident&, const Type&, int, TypeCheckerEnviroment&, TypeCheckerStore&);
  static Type getTypeByIdent(const Ident&, TypeCheckerEnviroment&, TypeCheckerStore&);
  static bool findIdent(const Ident&, TypeCheckerEnviroment&);
};

class TypeChecker : public Visitor
{
private:
  TypeCheckerStore store;
  TypeCheckerEnviroment enviroment;
  Type actType = Type::createNull();
  DynSet<Type> actRet;
  DynSet<Type> actOptRet;
  int actNesting = 0;
  int lineNumber = 0;
  TypeErrors errors;
  bool isConstBool;
  bool constBoolVal;

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
  void visitFnDefCheck(FnDef* p, bool);
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
  void visitArrType(ArrType *p);
  void visitFun(Fun* p);
  void visitArrAss(ArrAss *p);
  void visitEAtt(EAtt* p);
  void visitEVar(EVar* p);
  void visitELitInt(ELitInt* p);
  void visitELitTrue(ELitTrue* p);
  void visitELitFalse(ELitFalse* p);
  void visitEArr(EArr *p);
  void visitObjType(ObjType* p);
  void visitENewArr(ENewArr *enewarr);
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

  void addError(int line, AnsiString msg) {
    errors.Insert(TypeError(line, msg));
  }

  void addPredefinied();

  void visitFnDefs(ListTopDef defs) {
    for(int i=0;i<defs.size();i++) {
      TopDef* def = defs[i];
      if(FnDef *fdef = dynamic_cast<FnDef *>(def)) {
        visitFnDefCheck(fdef, false);
      } else {
        throw Exception("[TypeChecker::visitFnDefs] visitFnDefs internal error.");
      }
    }
  }

  bool check(Visitable *v) {
    addPredefinied();
    if(Prog *defs = dynamic_cast<Prog *>(v)) {
      visitFnDefs(*(defs->listtopdef_));
    } else {
      throw Exception("[TypeChecker::visitFnDefs] check internal error.");
    }
    v->accept(this);
    if(errors.Size()>0) {
      for(int i=0;i<errors.Size();i++) {
        fprintf(stderr, "Type error at %d: %s\n", errors[i].getLine(), errors[i].getMsg().c_str());
      }
      return false;
    }
    return true;
  }
};


#endif
