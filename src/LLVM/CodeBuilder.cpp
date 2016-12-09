/*** BNFC-Generated Visitor Design Pattern CodeBuilder. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "CodeBuilder.h"

void CodeBuilder::visitProgram(Program* t) {} //abstract class
void CodeBuilder::visitTopDef(TopDef* t) {} //abstract class
void CodeBuilder::visitArg(Arg* t) {} //abstract class
void CodeBuilder::visitBlock(Block* t) {} //abstract class
void CodeBuilder::visitStmt(Stmt* t) {} //abstract class
void CodeBuilder::visitItem(Item* t) {} //abstract class
void CodeBuilder::visitLatteType(LatteType* t) {} //abstract class
void CodeBuilder::visitExpr(Expr* t) {} //abstract class
void CodeBuilder::visitAddOp(AddOp* t) {} //abstract class
void CodeBuilder::visitMulOp(MulOp* t) {} //abstract class
void CodeBuilder::visitRelOp(RelOp* t) {} //abstract class

void CodeBuilder::visitProg(Prog *prog)
{
  prog->listtopdef_->accept(this);
}

void CodeBuilder::visitFnDef(FnDef *fndef)
{
  fndef->lattetype_->accept(this);
  Type funRetType = actType;
  TypeArray funArgs;
  for (ListArg::iterator i = fndef->listarg_->begin() ; i != fndef->listarg_->end() ; ++i)
  {
    if(Ar *arg = dynamic_cast<Ar*>(*i)) {
      arg->lattetype_->accept(this);
      funArgs.Insert(actType);
    } else {
      throw Exception("[CodeBuilder::visitFnDef] unknown arg kind");
    }
  }
  actRet = Type::createNull();
  fndef->block_->accept(this);
  //if(!Manager::cmp(funRetType, actRet)) {
    //addError(fndef->lattetype_->line_number, "Bad return type");
  //}
  //Manager::addIdent(fndef->ident_, 
  //  Type::createFunction(FunctionType(funRetType, funArgs)), 
  //  actNesting, enviroment, store);
}

void CodeBuilder::visitAr(Ar *ar)
{
  ar->lattetype_->accept(this);
  visitIdent(ar->ident_);
}

void CodeBuilder::visitBlk(Blk *blk)
{
  BuilderEnviroment env = enviroment;
  actNesting++;
  blk->liststmt_->accept(this);
  actNesting--;
  enviroment = env;
}

void CodeBuilder::visitEmpty(Empty *empty)
{
}

void CodeBuilder::visitBStmt(BStmt *bstmt)
{
  bstmt->block_->accept(this);
}

void CodeBuilder::visitDecl(Decl *decl)
{
  decl->lattetype_->accept(this);
  for (ListItem::iterator i = decl->listitem_->begin() ; i != decl->listitem_->end() ; ++i)
    if(Init *item = dynamic_cast<Init*>(*i))
      item->expr_->accept(this);

  /*decl->lattetype_->accept(this);
  Type declType = actType;
  for (ListItem::iterator i = decl->listitem_->begin() ; i != decl->listitem_->end() ; ++i)
  {
    if(Init *item = dynamic_cast<Init*>(*i)) {
      item->expr_->accept(this);
      if(!Manager::cmp(declType, actType)) {
        //addError(item->expr_->line_number, "Bad init expression type");
      } else 
        Manager::addIdent(item->ident_, declType, actNesting, enviroment, store);
    } else if(NoInit *item = dynamic_cast<NoInit*>(*i)) {
      Manager::addIdent(item->ident_, declType, actNesting, enviroment, store);
    } else {
      throw Exception("[CodeBuilder::visitDecl] casting error");
    }
  }*/
}

void CodeBuilder::visitAss(Ass *ass)
{
  visitIdent(ass->ident_);
  Type identType = actType;
  ass->expr_->accept(this);
  Type exprType = actType;
  //if(!Manager::cmp(identType, exprType)) {
    //addError(ass->expr_->line_number, "Bad assigment expression type");
  //}
}

void CodeBuilder::visitIncr(Incr *incr)
{
  visitIdent(incr->ident_);
  //if(Manager::txt(actType)) {
    //addError(incr->line_number, "Bad expression type");
  //}
}

void CodeBuilder::visitDecr(Decr *decr)
{
  visitIdent(decr->ident_);
  //if(Manager::txt(actType)) {
    //addError(decr->line_number, "Bad expression type");
  //}
}

void CodeBuilder::visitRet(Ret *ret)
{
  ret->expr_->accept(this);
  actRet = actType;
}

void CodeBuilder::visitVRet(VRet *vret)
{
  actRet = Type::createBasic(BasicType::createVoid());
}

void CodeBuilder::visitCond(Cond *cond)
{
  cond->expr_->accept(this);
  //if(Manager::bsc(actType)) {
    //addError(cond->expr_->line_number, "Bad expression type");
  //}
  cond->stmt_->accept(this);
}

void CodeBuilder::visitCondElse(CondElse *condelse)
{
  condelse->expr_->accept(this);
  //if(Manager::bsc(actType)) {
    //addError(condelse->expr_->line_number, "Bad expression type");
  //}
  condelse->stmt_1->accept(this);
  condelse->stmt_2->accept(this);
}

void CodeBuilder::visitWhileStmnt(WhileStmnt *whilestmnt)
{
  whilestmnt->expr_->accept(this);
  //if(Manager::bsc(actType)) {
    //addError(whilestmnt->expr_->line_number, "Bad expression type");
  //}
  whilestmnt->stmt_->accept(this);
}

void CodeBuilder::visitSExp(SExp *sexp)
{
  sexp->expr_->accept(this);
}

void CodeBuilder::visitNoInit(NoInit *noinit)
{
  /*
  Nieużywane
  visitIdent(noinit->ident_);
  */
}

void CodeBuilder::visitInit(Init *init)
{
  /*
  Nieużywane
  visitIdent(init->ident_);
  init->expr_->accept(this);
  */
}

void CodeBuilder::visitIntType(IntType *inttype)
{
  actType = Type::createBasic(BasicType::createInt());
}

void CodeBuilder::visitStrType(StrType *strtype)
{
  actType = Type::createBasic(BasicType::createString());
}

void CodeBuilder::visitBoolType(BoolType *booltype)
{
  actType = Type::createBasic(BasicType::createBool());
}

void CodeBuilder::visitVoidType(VoidType *voidtype)
{
  actType = Type::createBasic(BasicType::createVoid());
}

void CodeBuilder::visitFun(Fun *fun)
{
  printf("VISIT FUN");
  //TODO
  //actType = Type::createFunction(FunctionType::createInt());
  fun->lattetype_->accept(this);
  Type retType = actType;
  fun->listlattetype_->accept(this);
  //??wtf
}

void CodeBuilder::visitEVar(EVar *evar)
{
  visitIdent(evar->ident_);
}

void CodeBuilder::visitELitInt(ELitInt *elitint)
{
  visitInteger(elitint->integer_);
}

void CodeBuilder::visitELitTrue(ELitTrue *elittrue)
{
   actType = Type::createBasic(BasicType::createBool());
}

void CodeBuilder::visitELitFalse(ELitFalse *elitfalse)
{
  actType = Type::createBasic(BasicType::createBool());
}

void CodeBuilder::visitEApp(EApp *eapp)
{
  visitIdent(eapp->ident_);
  /*Type type = Manager::getTypeByIdent(eapp->ident_, enviroment, store);
  if(type.isFunction()) {
    FunctionType ftype = type.asFunction();
    if(ftype.getArgs().Size()!=eapp->listexpr_->size()) {
      //addError(eapp->line_number, AnsiString(eapp->ident_) + 
      //  " requires " + AnsiString(ftype.getArgs().Size()) + 
      //  " args, " + AnsiString(eapp->listexpr_->size()) + " provided");
    } else {
      int ind = 0;
      for (ListExpr::iterator i = eapp->listexpr_->begin() ; i != eapp->listexpr_->end() ; ++i, ++ind)
      {
        (*i)->accept(this);
        if(!Manager::cmp(actType, ftype.getArgs()[ind])) {
          //addError(eapp->line_number, AnsiString(eapp->ident_)  + " bad " + AnsiString(ind+1) + " argument type");
          break;
        }
      }
    }
  } else {
    //addError(eapp->line_number, AnsiString(eapp->ident_)  + " is not a function.");
  }
  */
}

void CodeBuilder::visitEString(EString *estring)
{
  visitString(estring->string_);
}

void CodeBuilder::visitNeg(Neg *neg)
{
  neg->expr_->accept(this);
  //if(Manager::bsc(actType)) {
    //addError(neg->expr_->line_number, "Bad expression type");
  //}
}

void CodeBuilder::visitNott(Nott *nott)
{
  nott->expr_->accept(this);
  //if(Manager::bsc(actType)) {
    //addError(nott->expr_->line_number, "Bad expression type");
  //}
}

void CodeBuilder::visitEMul(EMul *emul)
{
  emul->expr_1->accept(this);
  BinaryOperationArgument lArg = BinaryOperationArgument::createRegister(registerData.getLastRegister());
  emul->expr_2->accept(this);
  BinaryOperationArgument rArg = BinaryOperationArgument::createRegister(registerData.getLastRegister());
  RegisterKind regKind = getBinaryOperationRegisterKind(lArg.asRegister(), rArg.asRegister());
  Register outReg = getNextRegister(regKind);
  BinaryOperator bor = BinaryOperator::createDiv();
  if(Times *mulop = dynamic_cast<Times*>(emul->mulop_)) {
    bor = BinaryOperator::createMul();
  } else if(Mod *mulop = dynamic_cast<Mod*>(emul->mulop_)) {
    //bor = BinaryOperator::createMod();
  } else 
    throw Exception("[CodeBuilder::visitEMul] Unknown emul->mulop_ kind.");
  BinaryOperation bon = BinaryOperation(outReg, lArg, rArg, bor);
  Instr instr = Instr::createBinaryOperationInstr(bon);
  program.Insert(instr);
  registerData.getLastRegister() = outReg;
}

void CodeBuilder::visitEAdd(EAdd *eadd)
{
  eadd->expr_1->accept(this);
  BinaryOperationArgument lArg = BinaryOperationArgument::createRegister(registerData.getLastRegister());
  eadd->expr_2->accept(this);
  BinaryOperationArgument rArg = BinaryOperationArgument::createRegister(registerData.getLastRegister());
  RegisterKind regKind = getBinaryOperationRegisterKind(lArg.asRegister(), rArg.asRegister());
  Register outReg = getNextRegister(regKind);
  BinaryOperator bor = BinaryOperator::createDiv();
  if(Plus *mulop = dynamic_cast<Plus*>(eadd->addop_)) {
    bor = BinaryOperator::createAdd();
  } else if(Minus *mulop = dynamic_cast<Minus*>(eadd->addop_)) {
    bor = BinaryOperator::createSub();
  } else 
    throw Exception("[CodeBuilder::visitEAdd] Unknown eadd->addop_ kind.");
  BinaryOperation bon = BinaryOperation(outReg, lArg, rArg, bor);
  Instr instr = Instr::createBinaryOperationInstr(bon);
  program.Insert(instr);
  registerData.getLastRegister() = outReg;
}

void CodeBuilder::visitERel(ERel *erel)
{
  erel->expr_1->accept(this);
  Type exp1 = actType;
  erel->expr_2->accept(this);
  Type exp2 = actType;
  //if(!Manager::cst(exp1, exp2)) { 
    //addError(erel->expr_2->line_number, "Bad rel expression arg type");
  //}
}

void CodeBuilder::visitEAnd(EAnd *eand)
{
  eand->expr_1->accept(this);
  Type exp1 = actType;
  eand->expr_2->accept(this);
  Type exp2 = actType;
  //if(!Manager::bsc(exp1) || !Manager::bsc(exp2)) {
    //addError(eand->expr_2->line_number, "Bad rel expression arg type");
  //}
}

void CodeBuilder::visitEOr(EOr *eor)
{
  eor->expr_1->accept(this);
  Type exp1 = actType;
  eor->expr_2->accept(this);
  Type exp2 = actType;
  //if(!Manager::bsc(exp1) || !Manager::bsc(exp2)) {
    //addError(eor->expr_2->line_number, "Bad rel expression arg type");
  //}
}


void CodeBuilder::visitPlus(Plus *plus)
{
  
}

void CodeBuilder::visitMinus(Minus *minus)
{
  
}

void CodeBuilder::visitTimes(Times *times)
{
  
}

void CodeBuilder::visitDiv(Div *div)
{
  
}

void CodeBuilder::visitMod(Mod *mod)
{
  
}

void CodeBuilder::visitLTH(LTH *lth)
{
  

}

void CodeBuilder::visitLE(LE *le)
{
  
}

void CodeBuilder::visitGTH(GTH *gth)
{
  
}

void CodeBuilder::visitGE(GE *ge)
{
  
}

void CodeBuilder::visitEQU(EQU *equ)
{
  
}

void CodeBuilder::visitNE(NE *ne)
{
  
}

void CodeBuilder::visitListTopDef(ListTopDef* listtopdef)
{
  for (ListTopDef::iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void CodeBuilder::visitListArg(ListArg* listarg)
{
  for (ListArg::iterator i = listarg->begin() ; i != listarg->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void CodeBuilder::visitListStmt(ListStmt* liststmt)
{
  for (ListStmt::iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void CodeBuilder::visitListItem(ListItem* listitem)
{
  for (ListItem::iterator i = listitem->begin() ; i != listitem->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void CodeBuilder::visitListLatteType(ListLatteType* listlattetype)
{
  for (ListLatteType::iterator i = listlattetype->begin() ; i != listlattetype->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void CodeBuilder::visitListExpr(ListExpr* listexpr)
{
  for (ListExpr::iterator i = listexpr->begin() ; i != listexpr->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void CodeBuilder::visitInteger(Integer x)
{
  BinaryOperationArgument lArg = BinaryOperationArgument::createInteger(x);
  BinaryOperationArgument rArg = BinaryOperationArgument::createInteger(0);
  Register outReg = getNextRegister(RegisterKind::createValueI32());
  BinaryOperation bo = BinaryOperation(outReg, lArg, rArg, BinaryOperator::createAdd());
  Instr instr = Instr::createBinaryOperationInstr(bo);
  program.Insert(instr);
  registerData.getLastRegister() = outReg;
}

void CodeBuilder::visitChar(Char x)
{
  //TODO
  //actType = Type::createBasic(BasicType::createChar());
}

void CodeBuilder::visitDouble(Double x)
{
  //TODO
  //actType = Type::createBasic(BasicType::createDouble());
}

void CodeBuilder::visitString(String x)
{
  //TODO
  //actType = Type::createBasic(BasicType::createString());
}

void CodeBuilder::visitIdent(Ident x)
{
  //TODO
  //actType = Manager::getTypeByIdent(x, enviroment, store);
}


Register CodeBuilder::getNextRegister(const RegisterKind kind) {
  Register ret = Register(registerData.getRegisters().Size(), kind);
  registerData.getRegisters().Insert(ret);
  return ret;
}

RegisterKind CodeBuilder::getBinaryOperationRegisterKind(const Register& r1, const Register& r2) {
  /*
  *
  * Zwraca rodzaj rejestru który będzie przechowywał 
  * wynik operacji binarnej na rejestrach r1, r2.
  * Funkcja sprawdza typy i ewentualnie decyduje o rzutowaniu
  */

  if(r1.getKind().isValueI32()) {
    if(r2.getKind().isValueI32()) {
      return RegisterKind::createValueI32();
    } else 
    return RegisterKind::createValueDouble();
  }
  RegisterKind::createValueDouble();
}


