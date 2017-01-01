/*** BNFC-Generated Visitor Design Pattern TypeChecker. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "TypeChecker.h"

void TypeChecker::visitProgram(Program* t) {} //abstract class
void TypeChecker::visitTopDef(TopDef* t) {} //abstract class
void TypeChecker::visitArg(Arg* t) {} //abstract class
void TypeChecker::visitBlock(Block* t) {} //abstract class
void TypeChecker::visitStmt(Stmt* t) {} //abstract class
void TypeChecker::visitItem(Item* t) {} //abstract class
void TypeChecker::visitLatteType(LatteType* t) {} //abstract class
void TypeChecker::visitExpr(Expr* t) {} //abstract class
void TypeChecker::visitAddOp(AddOp* t) {} //abstract class
void TypeChecker::visitMulOp(MulOp* t) {} //abstract class
void TypeChecker::visitRelOp(RelOp* t) {} //abstract class

void TypeChecker::visitProg(Prog *prog)
{
  prog->listtopdef_->accept(this);
}

void TypeChecker::visitFnDef(FnDef *fndef)
{
  fndef->lattetype_->accept(this);
  Type funRetType = actType;
  TypeArray funArgs;
  TypeCheckerEnviroment fenv = enviroment;
  for (ListArg::iterator i = fndef->listarg_->begin() ; i != fndef->listarg_->end() ; ++i)
  {
    if(Ar *arg = dynamic_cast<Ar*>(*i)) {
      arg->lattetype_->accept(this);
      funArgs.Insert(actType);
      TypeCheckerManager::addIdent(arg->ident_, actType, 0, fenv, store);
    } else {
      throw Exception("[typeChecker::visitFnDef] unknown arg kind");
    }
  }
  actRet = Type::createNull();

  Type function = Type::createFunction(FunctionType(funRetType, funArgs, fenv));

  TypeCheckerManager::addIdent(fndef->ident_, function, actNesting, function.asFunction().getEnv(), store);

  TypeCheckerManager::addIdent(fndef->ident_, function, actNesting, enviroment, store);


  TypeCheckerEnviroment prev = enviroment;
  enviroment = function.asFunction().getEnv();
  fndef->block_->accept(this);
  enviroment = prev;

  if(!TypeCheckerManager::cmp(funRetType, actRet)) {
    addError(fndef->lattetype_->line_number, "Bad return type");
  }

}

void TypeChecker::visitAr(Ar *ar)
{
  ar->lattetype_->accept(this);
  visitIdent(ar->ident_);
}

void TypeChecker::visitBlk(Blk *blk)
{
  TypeCheckerEnviroment env = enviroment;
  actNesting++;
  blk->liststmt_->accept(this);
  actNesting--;
  enviroment = env;
}

void TypeChecker::visitEmpty(Empty *empty)
{
}

void TypeChecker::visitBStmt(BStmt *bstmt)
{
  bstmt->block_->accept(this);
}

void TypeChecker::visitDecl(Decl *decl)
{
  decl->lattetype_->accept(this);
  Type declType = actType;
  for (ListItem::iterator i = decl->listitem_->begin() ; i != decl->listitem_->end() ; ++i)
  {
    if(Init *item = dynamic_cast<Init*>(*i)) {
      item->expr_->accept(this);
      if(!TypeCheckerManager::cmp(declType, actType)) {
        addError(item->expr_->line_number, "Bad init expression type");
      } else 
        TypeCheckerManager::addIdent(item->ident_, declType, actNesting, enviroment, store);
    } else if(NoInit *item = dynamic_cast<NoInit*>(*i)) {
      TypeCheckerManager::addIdent(item->ident_, declType, actNesting, enviroment, store);
    } else {
      throw Exception("[TypeChecker::visitDecl] casting error");
    }
  }
}

void TypeChecker::visitAss(Ass *ass)
{
  visitIdent(ass->ident_);
  Type identType = actType;
  ass->expr_->accept(this);
  Type exprType = actType;
  if(!TypeCheckerManager::cmp(identType, exprType)) {
    addError(ass->expr_->line_number, "Bad assigment expression type");
  }
}

void TypeChecker::visitIncr(Incr *incr)
{
  visitIdent(incr->ident_);
  if(TypeCheckerManager::txt(actType)) {
    addError(incr->line_number, "Bad expression type");
  }
}

void TypeChecker::visitDecr(Decr *decr)
{
  visitIdent(decr->ident_);
  if(TypeCheckerManager::txt(actType)) {
    addError(decr->line_number, "Bad expression type");
  }
}

void TypeChecker::visitRet(Ret *ret)
{
  ret->expr_->accept(this);
  actRet = actType;
}

void TypeChecker::visitVRet(VRet *vret)
{
  actRet = Type::createBasic(BasicType::createVoid());
}

void TypeChecker::visitCond(Cond *cond)
{
  cond->expr_->accept(this);
  if(!TypeCheckerManager::bsc(actType)) {
    addError(cond->expr_->line_number, "Bad expression type");
  }
  cond->stmt_->accept(this);
}

void TypeChecker::visitCondElse(CondElse *condelse)
{
  condelse->expr_->accept(this);
  if(!TypeCheckerManager::bsc(actType)) {
    addError(condelse->expr_->line_number, "Bad expression type");
  }
  condelse->stmt_1->accept(this);
  condelse->stmt_2->accept(this);
}

void TypeChecker::visitWhileStmnt(WhileStmnt *whilestmnt)
{
  whilestmnt->expr_->accept(this);
  if(!TypeCheckerManager::bsc(actType)) {
    addError(whilestmnt->expr_->line_number, "Bad expression type");
  }
  whilestmnt->stmt_->accept(this);
}

void TypeChecker::visitSExp(SExp *sexp)
{
  sexp->expr_->accept(this);
}

void TypeChecker::visitNoInit(NoInit *noinit)
{
  /*
  Nieużywane
  visitIdent(noinit->ident_);
  */
}

void TypeChecker::visitInit(Init *init)
{
  /*
  Nieużywane
  visitIdent(init->ident_);
  init->expr_->accept(this);
  */
}

void TypeChecker::visitIntType(IntType *inttype)
{
  actType = Type::createBasic(BasicType::createInt());
}

void TypeChecker::visitStrType(StrType *strtype)
{
  actType = Type::createBasic(BasicType::createString());
}

void TypeChecker::visitBoolType(BoolType *booltype)
{
  actType = Type::createBasic(BasicType::createBool());
}

void TypeChecker::visitVoidType(VoidType *voidtype)
{
  actType = Type::createBasic(BasicType::createVoid());
}

void TypeChecker::visitFun(Fun *fun)
{
  //todo ???
  fun->lattetype_->accept(this);
  Type retType = actType;
  fun->listlattetype_->accept(this);
}

void TypeChecker::visitEVar(EVar *evar)
{
  visitIdent(evar->ident_);
}

void TypeChecker::visitELitInt(ELitInt *elitint)
{
  visitInteger(elitint->integer_);
}

void TypeChecker::visitELitTrue(ELitTrue *elittrue)
{
   actType = Type::createBasic(BasicType::createBool());
}

void TypeChecker::visitELitFalse(ELitFalse *elitfalse)
{
  actType = Type::createBasic(BasicType::createBool());
}

void TypeChecker::visitEApp(EApp *eapp)
{
  visitIdent(eapp->ident_);
  Type type = TypeCheckerManager::getTypeByIdent(eapp->ident_, enviroment, store);
  if(type.isFunction()) {
    FunctionType ftype = type.asFunction();
    if(ftype.getArgs().Size()!=eapp->listexpr_->size()) {
      addError(eapp->line_number, AnsiString(eapp->ident_) + 
        " requires " + AnsiString(ftype.getArgs().Size()) + 
        " args, " + AnsiString(eapp->listexpr_->size()) + " provided");
    } else {
      int ind = 0;
      for (ListExpr::iterator i = eapp->listexpr_->begin() ; i != eapp->listexpr_->end() ; ++i, ++ind)
      {
        (*i)->accept(this);
        if(!TypeCheckerManager::cmp(actType, ftype.getArgs()[ind])) {
          addError(eapp->line_number, AnsiString(eapp->ident_)  + " bad " + AnsiString(ind+1) + " argument type");
          break;
        }
      }
    }
  } else {
    addError(eapp->line_number, AnsiString(eapp->ident_)  + " is not a function.");
  }
  
}

void TypeChecker::visitEString(EString *estring)
{
  visitString(estring->string_);
}

void TypeChecker::visitNeg(Neg *neg)
{
  neg->expr_->accept(this);
  if(!TypeCheckerManager::bsc(actType)) {
    addError(neg->expr_->line_number, "Bad expression type");
  }
}

void TypeChecker::visitNott(Nott *nott)
{
  nott->expr_->accept(this);
  if(!TypeCheckerManager::bsc(actType)) {
    addError(nott->expr_->line_number, "Bad expression type");
  }
}

void TypeChecker::visitEMul(EMul *emul)
{
  emul->expr_1->accept(this);
  Type exp1 = actType;
  emul->expr_2->accept(this);
  Type exp2 = actType;
  if(TypeCheckerManager::txt(exp1) || TypeCheckerManager::txt(exp2)  || !TypeCheckerManager::bsc(exp1) || !TypeCheckerManager::bsc(exp2)) {
    addError(emul->expr_2->line_number, "Bad mul expression arg type");
  }
}

void TypeChecker::visitEAdd(EAdd *eadd)
{
  eadd->expr_1->accept(this);
  Type exp1 = actType;
  eadd->expr_2->accept(this);
  Type exp2 = actType;
  if(TypeCheckerManager::txt(exp1)) {
    addError(eadd->expr_2->line_number, "Bad add expression arg type");
  } else if(TypeCheckerManager::txt(exp2)) {
    addError(eadd->expr_2->line_number, "Bad add expression arg type");
  } else if(!TypeCheckerManager::bsc(exp1)) {
    addError(eadd->expr_2->line_number, "Bad add expression arg type");
  } else if(!TypeCheckerManager::bsc(exp2)) {
    addError(eadd->expr_2->line_number, "Bad add expression arg type");
  } 
}

void TypeChecker::visitERel(ERel *erel)
{
  erel->expr_1->accept(this);
  Type exp1 = actType;
  erel->expr_2->accept(this);
  Type exp2 = actType;
  if(!TypeCheckerManager::cst(exp1, exp2)) { 
    addError(erel->expr_2->line_number, "Bad rel expression arg type");
  }
  actType = Type::createBasic(BasicType::createBool());
}

void TypeChecker::visitEAnd(EAnd *eand)
{
  eand->expr_1->accept(this);
  Type exp1 = actType;
  eand->expr_2->accept(this);
  Type exp2 = actType;
  if(!TypeCheckerManager::bsc(exp1) || !TypeCheckerManager::bsc(exp2)) {
    addError(eand->expr_2->line_number, "Bad rel expression arg type");
  }
}

void TypeChecker::visitEOr(EOr *eor)
{
  eor->expr_1->accept(this);
  Type exp1 = actType;
  eor->expr_2->accept(this);
  Type exp2 = actType;
  if(!TypeCheckerManager::bsc(exp1) || !TypeCheckerManager::bsc(exp2)) {
    addError(eor->expr_2->line_number, "Bad rel expression arg type");
  }
}


void TypeChecker::visitPlus(Plus *plus)
{
  
}

void TypeChecker::visitMinus(Minus *minus)
{
  
}

void TypeChecker::visitTimes(Times *times)
{
  
}

void TypeChecker::visitDiv(Div *div)
{
  
}

void TypeChecker::visitMod(Mod *mod)
{
  
}

void TypeChecker::visitLTH(LTH *lth)
{
  

}

void TypeChecker::visitLE(LE *le)
{
  
}

void TypeChecker::visitGTH(GTH *gth)
{
  
}

void TypeChecker::visitGE(GE *ge)
{
  
}

void TypeChecker::visitEQU(EQU *equ)
{
  
}

void TypeChecker::visitNE(NE *ne)
{
  
}

void TypeChecker::visitListTopDef(ListTopDef* listtopdef)
{
  for (ListTopDef::iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void TypeChecker::visitListArg(ListArg* listarg)
{
  for (ListArg::iterator i = listarg->begin() ; i != listarg->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void TypeChecker::visitListStmt(ListStmt* liststmt)
{
  for (ListStmt::iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void TypeChecker::visitListItem(ListItem* listitem)
{
  for (ListItem::iterator i = listitem->begin() ; i != listitem->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void TypeChecker::visitListLatteType(ListLatteType* listlattetype)
{
  for (ListLatteType::iterator i = listlattetype->begin() ; i != listlattetype->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void TypeChecker::visitListExpr(ListExpr* listexpr)
{
  for (ListExpr::iterator i = listexpr->begin() ; i != listexpr->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void TypeChecker::visitInteger(Integer x)
{
  actType = Type::createBasic(BasicType::createInt());
}

void TypeChecker::visitChar(Char x)
{
  actType = Type::createBasic(BasicType::createChar());
}

void TypeChecker::visitDouble(Double x)
{
  actType = Type::createBasic(BasicType::createDouble());
}

void TypeChecker::visitString(String x)
{
  actType = Type::createBasic(BasicType::createString());
}

void TypeChecker::visitIdent(Ident x)
{
  actType = TypeCheckerManager::getTypeByIdent(x, enviroment, store);
}



bool TypeCheckerManager::cmp(const Type& t1, const Type& t2) {
  if(t1.isBasic() && t2.isBasic()) {
    if(t1.asBasic().isInt() && t2.asBasic().isInt())
      return true;
    if(t1.asBasic().isBool() && t2.asBasic().isBool())
      return true;
    if(t1.asBasic().isString() && t2.asBasic().isString())
      return true;
    if(t1.asBasic().isChar() && t2.asBasic().isChar())
      return true;
    if(t1.asBasic().isVoid() && t2.asBasic().isVoid())
      return true;
  } 
  if(t1.isFunction() && t2.isFunction()) {
    //TODO
  }
  return false;
}

bool TypeCheckerManager::bsc(const Type& t) {
  return t.isBasic();
}

bool TypeCheckerManager::txt(const Type& t) {
  if(t.isBasic())
    return t.asBasic().isString() || t.asBasic().isChar();
  return false;
}

bool TypeCheckerManager::cst(const Type& t1, const Type& t2) {
  //TODO
  return cmp(t1, t2);
}


void TypeCheckerManager::addIdent(const Ident& ident, const Type& t, int nesting, TypeCheckerEnviroment& env, TypeCheckerStore& str) {
  int id = str.Size();
  str.Insert(TypeCheckerStoreElement(id, t));
  env.Insert(TypeCheckerEnviromentElement(ident, id, nesting));
}

Type TypeCheckerManager::getTypeByIdent(const Ident& ident, TypeCheckerEnviroment& env, TypeCheckerStore& str) {
  for(int i=0;i<env.Size();i++) {
    if(env[i].getIdent() == ident) {
      for(int j=0;j<str.Size();j++) {
        if(env[i].getStoreId()==str[j].getId())
          return str[j].getType();
      }
      throw Exception("[TypeCheckerManager::getTypeByIdent] internal error");
    }
  }
  //todo
  throw Exception("[TypeCheckerManager::getTypeByIdent] ident not found: " + ident);
  return Type::createNull();
}

