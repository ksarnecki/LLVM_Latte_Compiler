#ifndef SKELETON_HEADER
#define SKELETON_HEADER
/* You might want to change the above name. */

#include "Absyn.H"


class Skeleton : public Visitor
{
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

  void visit"Integer"("Integer" x);
  void visit"Char"("Char" x);
  void visit"Double"("Double" x);
  void visit"String"("String" x);
  void visit"Ident"("Ident" x);

};


#endif
