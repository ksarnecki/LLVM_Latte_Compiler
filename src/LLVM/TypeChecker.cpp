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

void TypeChecker::visitFnDef(FnDef *fndef) {
  visitFnDefCheck(fndef, true);
}

void TypeChecker::visitFnDefCheck(FnDef *fndef, bool check)
{
  for(int i=0;i<enviroment.Size();i++)
    if(!check && enviroment[i].getIdent() == fndef->ident_ && store[enviroment[i].getStoreId()].getType().isFunction()) {
      addError(fndef->lattetype_->line_number, "Repeated function name");
      return;
    }
  fndef->lattetype_->accept(this);
  Type funRetType = actType;
  TypeArray funArgs;
  TypeCheckerEnviroment fenv = enviroment;
  DynSet<AnsiString> idents;
  for (ListArg::iterator i = fndef->listarg_->begin() ; i != fndef->listarg_->end() ; ++i)
  {
    if(Ar *arg = dynamic_cast<Ar*>(*i)) {
      arg->lattetype_->accept(this);
      funArgs.Insert(actType);
      for(int j=0;j<idents.Size();j++) {
        if(idents[j]==arg->ident_) {
          addError(fndef->lattetype_->line_number, "Repeated argument name");
          return;
        }
      }
      idents.Insert(arg->ident_);
      TypeCheckerManager::addIdent(arg->ident_, actType, 0, fenv, store);
    } else {
      throw Exception("[typeChecker::visitFnDef] unknown arg kind");
    }
  }
  actRet = DynSet<Type>();
  actOptRet = DynSet<Type>();

  Type function = Type::createFunction(FunctionType(funRetType, funArgs, fenv));

  //TypeCheckerManager::addIdent(fndef->ident_, function, actNesting, function.asFunction().getEnv(), store);

  if(!check)
    TypeCheckerManager::addIdent(fndef->ident_, function, actNesting, enviroment, store);

  TypeCheckerEnviroment prev = enviroment;
  enviroment = function.asFunction().getEnv();

  if(!check) {
    enviroment = prev;
    return;
  }
  fndef->block_->accept(this);
  enviroment = prev;


  if(funRetType.isBasic() && funRetType.asBasic().isVoid() && actRet.Size()==0)
    return;

  if(actRet.Size()==0)
    addError(fndef->lattetype_->line_number, "No return stmnt");

  for(int i=0;i<actRet.Size();i++) {
    if(!TypeCheckerManager::cmp(funRetType, actRet[i])) {
      addError(fndef->lattetype_->line_number, AnsiString("Bad return type ") + actRet[i].toJSON().c_str());
    }
  }

  for(int i=0;i<actOptRet.Size();i++) {
    if(!TypeCheckerManager::cmp(funRetType, actOptRet[i])) {
      addError(fndef->lattetype_->line_number, AnsiString("Bad opt return type ") + actOptRet[i].toJSON().c_str());
    }
  }

}

void TypeChecker::visitAr(Ar *ar)
{
  ar->lattetype_->accept(this);
  if(TypeCheckerManager::findIdent(ar->ident_, enviroment)) {
     visitIdent(ar->ident_);
  } else {
    addError(ar->line_number, AnsiString(ar->ident_) + " ident not found");
    return;
  }
 
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
      for(int i=0;i<enviroment.Size();i++) 
        if(enviroment[i].getIdent()==item->ident_ && enviroment[i].getNesting()==actNesting)
          addError(item->expr_->line_number, "Prev declaration found!");
      item->expr_->accept(this);
      if(!TypeCheckerManager::cmp(declType, actType)) {
        addError(item->expr_->line_number, "Bad init expression type");
      } else 
        TypeCheckerManager::addIdent(item->ident_, declType, actNesting, enviroment, store);
    } else if(NoInit *item = dynamic_cast<NoInit*>(*i)) {
      for(int i=0;i<enviroment.Size();i++) 
        if(enviroment[i].getIdent()==item->ident_ && enviroment[i].getNesting()==actNesting)
          addError(decl->lattetype_->line_number, "Prev declaration found!");
      TypeCheckerManager::addIdent(item->ident_, declType, actNesting, enviroment, store);
    } else {
      throw Exception("[TypeChecker::visitDecl] casting error");
    }
  }
}

void TypeChecker::visitAss(Ass *ass)
{
  if(TypeCheckerManager::findIdent(ass->ident_, enviroment)) {
     visitIdent(ass->ident_);
  } else {
    addError(ass->line_number, AnsiString(ass->ident_) + " ident not found");
    return;
  }
  Type identType = actType;
  ass->expr_->accept(this);
  Type exprType = actType;
  if(!TypeCheckerManager::cmp(identType, exprType)) {
    addError(ass->expr_->line_number, "Bad assigment expression type: " + identType.toJSON() + " ~ " + exprType.toJSON());
  }
}

void TypeChecker::visitIncr(Incr *incr)
{
  if(TypeCheckerManager::findIdent(incr->ident_, enviroment)) {
     visitIdent(incr->ident_);
  } else {
    addError(incr->line_number, AnsiString(incr->ident_) + " ident not found");
    return;
  }
  if(!TypeCheckerManager::cmp(actType, Type::createBasic(BasicType::createInt()))) {
    addError(incr->line_number, "Bad expression type");
  }
}

void TypeChecker::visitDecr(Decr *decr)
{
  if(TypeCheckerManager::findIdent(decr->ident_, enviroment)) {
     visitIdent(decr->ident_);
  } else {
    addError(decr->line_number, AnsiString(decr->ident_) + " ident not found");
    return;
  }
  if(!TypeCheckerManager::cmp(actType, Type::createBasic(BasicType::createInt()))) {
    addError(decr->line_number, "Bad expression type");
  }
}

void TypeChecker::visitRet(Ret *ret)
{
  ret->expr_->accept(this);
  actRet.Insert(actType);
}

void TypeChecker::visitVRet(VRet *vret)
{
  actRet.Insert(Type::createBasic(BasicType::createVoid()));
}

void TypeChecker::visitCond(Cond *cond)
{
  isConstBool = false;
  DynSet<Type> actRetPrev = actRet;
  cond->expr_->accept(this);
  if(!TypeCheckerManager::cmp(actType, Type::createBasic(BasicType::createBool()))) {
    addError(cond->expr_->line_number, "Bad expression type");
  }
  if(!isConstBool || constBoolVal)
    cond->stmt_->accept(this);
  if(!isConstBool) {
    for(int i=actRetPrev.Size();i<actRet.Size();i++) {
      actOptRet.Insert(actRet[i]);
    }
    actRet = actRetPrev;
  }
}

void TypeChecker::visitCondElse(CondElse *condelse)
{
  DynSet<Type> actRetPrev = actRet;
  condelse->expr_->accept(this);
  if(!TypeCheckerManager::cmp(actType, Type::createBasic(BasicType::createBool()))) {
    addError(condelse->expr_->line_number, "Bad expression type");
  }
  if(isConstBool) {
    if(constBoolVal) {
      condelse->stmt_1->accept(this);
    } else {
      condelse->stmt_2->accept(this);
    }
  } else {
    bool twoPaths;
    condelse->stmt_1->accept(this);
    for(int i=actRetPrev.Size();i<actRet.Size();i++) {
      actOptRet.Insert(actRet[i]);
    }
    twoPaths = actRet.Size() - actRetPrev.Size() > 0;
    actRet = actRetPrev;
    condelse->stmt_2->accept(this);
    twoPaths = twoPaths && actRet.Size() - actRetPrev.Size() > 0;
    if(twoPaths)
      return;
    for(int i=actRetPrev.Size();i<actRet.Size();i++) {
      actOptRet.Insert(actRet[i]);
    }
    actRet = actRetPrev;
  }
}

void TypeChecker::visitObjType(ObjType* p) {
//TODO
}

void TypeChecker::visitForStmnt(ForStmnt* p) {
  //TODO
}

void TypeChecker::visitEAtt(EAtt* p) {
//TODO
}

void TypeChecker::visitWhileStmnt(WhileStmnt *whilestmnt)
{
  whilestmnt->expr_->accept(this);
  if(!TypeCheckerManager::cmp(actType, Type::createBasic(BasicType::createBool()))) {
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
   constBoolVal = true;
   isConstBool = true;
}

void TypeChecker::visitELitFalse(ELitFalse *elitfalse)
{
  actType = Type::createBasic(BasicType::createBool());
  constBoolVal = false;
  isConstBool = true;
}

void TypeChecker::visitEArr(EArr *earr) {
  earr->expr_->accept(this);
  if(!TypeCheckerManager::cmp(actType, Type::createBasic(BasicType::createInt())))
    addError(earr->line_number, "Array index exp not int");
  if(TypeCheckerManager::findIdent(earr->ident_, enviroment)) {
     visitIdent(earr->ident_);
  } else {
    addError(earr->line_number, AnsiString(earr->ident_) + " ident not found");
    return;
  }
  Type t =  actType.asArray();
  actType = t;
}

void TypeChecker::visitArrAss(ArrAss *p) {
  //TODO
}

void TypeChecker::visitENewArr(ENewArr *enewarr)
{
  enewarr->expr_->accept(this);
  if(!TypeCheckerManager::cmp(actType, Type::createBasic(BasicType::createInt())))
    addError(enewarr->line_number, "Array init exp not int");

  enewarr->lattetype_->accept(this);
  actType = Type::createArray(actType);
}

void TypeChecker::visitEApp(EApp *eapp)
{
  if(TypeCheckerManager::findIdent(eapp->ident_, enviroment)) {
    visitIdent(eapp->ident_);
  } else {
    addError(eapp->line_number, AnsiString(eapp->ident_) + " ident not found");
    return;
  }
    
  Type type = TypeCheckerManager::getTypeByIdent(eapp->ident_, enviroment, store);
  if(type.isFunction()) {
    FunctionType ftype = type.asFunction();
    if(ftype.getArgs().Size()!=eapp->listexpr_->size()) {
      addError(eapp->line_number, AnsiString(eapp->ident_) + 
        " requires " + AnsiString(ftype.getArgs().Size()) + 
        " args, " + AnsiString((int)eapp->listexpr_->size()) + " provided");
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
      actType = ftype.getReturnType();
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
  if(!TypeCheckerManager::cmp(actType, Type::createBasic(BasicType::createInt()))) {
    addError(neg->expr_->line_number, "Bad expression type");
  }
}

void TypeChecker::visitNott(Nott *nott)
{
  nott->expr_->accept(this);
  if(!TypeCheckerManager::cmp(actType, Type::createBasic(BasicType::createBool()))) {
    addError(nott->expr_->line_number, "Bad expression type");
  }
  constBoolVal = !constBoolVal;
}

void TypeChecker::visitEMul(EMul *emul)
{
  emul->expr_1->accept(this);
  Type exp1 = actType;
  emul->expr_2->accept(this);
  Type exp2 = actType;

  if(!TypeCheckerManager::cmp(exp1, Type::createBasic(BasicType::createInt())) || !TypeCheckerManager::cmp(exp2, Type::createBasic(BasicType::createInt()))) {
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
    if(Plus *mulop = dynamic_cast<Plus*>(eadd->addop_)) {
      if(!TypeCheckerManager::txt(exp2)) {
        addError(eadd->expr_2->line_number, "Bad add expression arg type");
      }
    } else {
      addError(eadd->expr_2->line_number, "Bad add expression arg type");
    }  
  } else if(!TypeCheckerManager::cmp(exp1, Type::createBasic(BasicType::createInt())) || !TypeCheckerManager::cmp(exp2, Type::createBasic(BasicType::createInt()))) {
    addError(eadd->expr_2->line_number, "Bad add expression arg type");
  }
}

void TypeChecker::visitERel(ERel *erel)
{
  isConstBool = false;
  erel->expr_1->accept(this);
  Type exp1 = actType;
  bool constBoolValPrev = constBoolVal;
  bool isConstBoolPrev = isConstBool;
  isConstBool = false;
  erel->expr_2->accept(this);
  Type exp2 = actType;

  if(isConstBoolPrev && isConstBool) {
    if(EQU* e = dynamic_cast<EQU*>(erel->relop_)) {
      if(constBoolValPrev == constBoolVal) {
        constBoolVal = true;
      } else {
        constBoolVal = false;
      }
    } else if(NE* e = dynamic_cast<NE*>(erel->relop_)) {
      if(constBoolValPrev == constBoolVal) {
        constBoolVal = false;
      } else {
        constBoolVal = true;
      }
    } else 
      addError(erel->expr_2->line_number, "Bad rel expression arg type");
  } else {
    isConstBool = false;
  }

  if(!TypeCheckerManager::cmp(exp1, exp2)) {
    addError(erel->expr_2->line_number, "Bad rel expression arg type");
  }
  if(!TypeCheckerManager::cmp(exp1, Type::createBasic(BasicType::createInt())) && !TypeCheckerManager::cmp(exp1, Type::createBasic(BasicType::createBool()))) {
     addError(erel->expr_2->line_number, "Bad rel expression arg type");
  }
  actType = Type::createBasic(BasicType::createBool());
}

void TypeChecker::visitEAnd(EAnd *eand)
{
  isConstBool = false;
  eand->expr_1->accept(this);
  Type exp1 = actType;
  bool constBoolValPrev = constBoolVal;
  bool isConstBoolPrev = isConstBool;
  isConstBool = false;
  eand->expr_2->accept(this);
  Type exp2 = actType;
  if(isConstBoolPrev && isConstBool) {
    if(constBoolValPrev && constBoolVal) {
      //nothing
    } else {
      constBoolVal = false;
    }
  } else {
    isConstBool = false;
  }
  if(!TypeCheckerManager::cmp(exp1, Type::createBasic(BasicType::createBool())) || !TypeCheckerManager::cmp(exp2, Type::createBasic(BasicType::createBool()))) {
    addError(eand->expr_2->line_number, "Bad rel expression arg type");
  }
}

void TypeChecker::visitEOr(EOr *eor)
{
  isConstBool = false;
  eor->expr_1->accept(this);
  Type exp1 = actType;
  bool constBoolValPrev = constBoolVal;
  bool isConstBoolPrev = isConstBool;
  isConstBool = false;
  eor->expr_2->accept(this);
  Type exp2 = actType;
  if(isConstBoolPrev && isConstBool) {
    if(constBoolValPrev || constBoolVal) {
     constBoolVal = true;
    } else {
      //nothing
    }
  } else {
    isConstBool = false;
  }
  if(!TypeCheckerManager::cmp(exp1, Type::createBasic(BasicType::createBool())) || !TypeCheckerManager::cmp(exp2, Type::createBasic(BasicType::createBool()))) {
    addError(eor->expr_2->line_number, "Bad rel expression arg type");
  }
}

void TypeChecker::visitArrType(ArrType *arrtype)
{
  arrtype->lattetype_->accept(this);
  actType = Type::createArray(actType);
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
    if(VRet* block = dynamic_cast<VRet*>(*i)) {
      (*i)->accept(this);
      return;
    } else if(Ret* block = dynamic_cast<Ret*>(*i)) {
      (*i)->accept(this);
      return;
    }
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

}

void TypeChecker::visitDouble(Double x)
{

}

void TypeChecker::visitString(String x)
{
  actType = Type::createBasic(BasicType::createString());
}

void TypeChecker::visitIdent(Ident x)
{
  actType = TypeCheckerManager::getTypeByIdent(x, enviroment, store);
}


//TODO
//DODAĆ REKURENYJNE SPRAWDZANIE TYPU!

bool TypeCheckerManager::cmp(const Type& t1, const Type& t2) {
  Type c1 = t1;
  Type c2 = t2;
  if(t1.isNull() || t2.isNull())
    return false;

  if(t1.isFunction()) {
    c1 = t1.asFunction().getReturnType();
  }
  if(t2.isFunction()) {
    c2 = t2.asFunction().getReturnType();
  }
  if(t1.isArray() || t2.isArray()) {
    if(t1.isArray() && t2.isArray()) {
      c1 = t1.asArray();
      c2 = t2.asArray();
    } else {
      return false;
    }
  }
  if(c1.isBasic() && c2.isBasic()) {
    if(c1.asBasic().isInt() && c2.asBasic().isInt())
      return true;
    if(c1.asBasic().isBool() && c2.asBasic().isBool())
      return true;
    if(c1.asBasic().isString() && c2.asBasic().isString())
      return true;
    if(c1.asBasic().isVoid() && c2.asBasic().isVoid())
      return true;
    return false;
  } 
  throw Exception("[TypeCheckerManager::cmp] Not supported." + t1.toJSON() + " " + t2.toJSON());
}

bool TypeCheckerManager::txt(const Type& t) {
  if(t.isBasic())
    return t.asBasic().isString();
  return false;
}

void TypeCheckerManager::addIdent(const Ident& ident, const Type& t, int nesting, TypeCheckerEnviroment& env, TypeCheckerStore& str) {
  int id = str.Size();
  str.Insert(TypeCheckerStoreElement(id, t));
  for(int i=0;i<env.Size();i++) {
    if(env[i].getIdent()==ident) {
      env[i].getStoreId() = id;
      return;
    }
  }
  env.Insert(TypeCheckerEnviromentElement(ident, id, nesting));
}

bool TypeCheckerManager::findIdent(const Ident& ident, TypeCheckerEnviroment& env) {
  for(int i=0;i<env.Size();i++) {
    if(env[i].getIdent() == ident) {
      return true;
    }
  }
  return false;
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
  throw Exception("[TypeCheckerManager::getTypeByIdent] ident not found: " + ident);
}

void TypeChecker::addPredefinied() {
  {
    //printInt
    TypeArray ta;
    ta.Insert(Type::createBasic(BasicType::createInt()));
    TypeCheckerManager::addIdent("printInt", Type::createFunction(FunctionType(Type::createBasic(BasicType::createVoid()), ta, TypeCheckerEnviroment())), 0, enviroment, store);
  }
  {
    //readInt
    TypeCheckerManager::addIdent("readInt", Type::createFunction(FunctionType(Type::createBasic(BasicType::createInt()), TypeArray(), TypeCheckerEnviroment())), 0, enviroment, store);
  }

   {
    //readString
    TypeCheckerManager::addIdent("readString", Type::createFunction(FunctionType(Type::createBasic(BasicType::createString()), TypeArray(), TypeCheckerEnviroment())), 0, enviroment, store);
  }
  {
    //printInt
    TypeArray ta;
    ta.Insert(Type::createBasic(BasicType::createString()));
    TypeCheckerManager::addIdent("printString", Type::createFunction(FunctionType(Type::createBasic(BasicType::createVoid()), ta, TypeCheckerEnviroment())), 0, enviroment, store);
  }
  {
    //error
    TypeCheckerManager::addIdent("error", Type::createFunction(FunctionType(Type::createBasic(BasicType::createVoid()), TypeArray(), TypeCheckerEnviroment())), 0, enviroment, store);
  }
}
