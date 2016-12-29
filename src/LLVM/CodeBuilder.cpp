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
  /*
  * Budujemy obiekt 
  *
  *
  */

  /*
  * 1. Nazwa funkcji
  */
  AnsiString fName = fndef->ident_;
  /*
  * 2. Typ zwracany
  */
  RegisterKind fRetType = getRegisterKindFromLatteType(fndef->lattetype_);

  /*
  * 3. Argumenty
  */
  LLVMFunctionArgumentArray fArgs = LLVMFunctionArgumentArray();
  for (ListArg::iterator i = fndef->listarg_->begin() ; i != fndef->listarg_->end() ; ++i)
    if(Ar *arg = dynamic_cast<Ar*>(*i)) {
      RegisterKind rk = getRegisterKindFromLatteType(arg->lattetype_);
      Register r = getNextRegister(rk);
      updateEnviroment(arg->ident_, Object::createBasic(BasicObject::createInt(r)));
      fArgs.Insert(LLVMFunctionArgument(r, arg->ident_));
    }
    else
      throw Exception("[CodeBuilder::visitFnDef] Unknown arg kind.");

  /*
  * 4. Ciało funkcji
  */
  actBlocks = LLVMBlockArray();
  initBlock(fName+"_entry");
  updateEnviroment(fName, Object::createFunction(FunctionObject(fRetType)));
  fndef->block_->accept(this);
  LLVMBlockArray fBlocks = actBlocks;
  program.Insert(LLVMFunction(fName, fRetType, fArgs, fBlocks));


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
    if(Init *item = dynamic_cast<Init*>(*i)) {
      item->expr_->accept(this);
      updateEnviroment(item->ident_, Object::createBasic(BasicObject::createInt(registerData.getLastRegister())));
    } 
      

  //TODO -> updateEnviroment();



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
  ass->expr_->accept(this);
  updateStore(ass->ident_, Object::createBasic(BasicObject::createInt(registerData.getLastRegister())));
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
  addInstr(Instr::createReturnInstr(registerData.getLastRegister()));
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

  /*
  * Generujemy nazwy bloków
  */
  AnsiString wcondblock = getNextBlockNameByPrefix("while_cond");
  AnsiString wbodyblock = getNextBlockNameByPrefix("while_body");
  AnsiString wendblock = getNextBlockNameByPrefix("while_end");

  //skok do while_cond
  addInstr(Instr::createBrInstr(BrInstr(wcondblock)));
  BuilderEnviroment e = enviroment;
  Store s = store;
  /*
  * Generujemy blok warunku
  */
  initBlock(wcondblock);
  for(int i=0;i<e.Size();i++) {
    if(getObjectByIdent(e[i].getIdent()).isBasic()) {
      Register r = getNextRegister(RegisterKind::createValueI32());
      PhiCases phiCases;
      phiCases.Insert(PhiCase(getRegisterByIdent(e[i].getIdent()), actBlocks[actBlocks.Size()-2].getName()));
      addInstr(Instr::createPhiInstr(PhiInstr(e[i].getIdent(), r, phiCases)));
      updateEnviroment(e[i].getIdent(), Object::createBasic(BasicObject::createInt(r)));
    }
  }
  whilestmnt->expr_->accept(this);
  addInstr(Instr::createBrIfInstr(BrIfInstr(registerData.getLastRegister(), wbodyblock, wendblock)));
  e = enviroment;
  s = store;
  /*
  * Generujemy ciało while
  */
  initBlock(wbodyblock);
  whilestmnt->stmt_->accept(this);
  addInstr(Instr::createBrInstr(BrInstr(wcondblock)));
  for(int i=0;i<enviroment.Size();i++) {
    if(getObjectByIdent(enviroment[i].getIdent()).isBasic())
      addPhiCase(enviroment[i].getIdent(), getRegisterByIdent(enviroment[i].getIdent()), wbodyblock, wcondblock);
  }

  initBlock(wendblock);
  enviroment = e;
  store = s;
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
  RegisterKind fType = getObjectByIdent(eapp->ident_).asFunction().getType();
  AnsiString fName = eapp->ident_;
  Registers fArgs;
  for (ListExpr::iterator i = eapp->listexpr_->begin() ; i != eapp->listexpr_->end() ; ++i) {
    (*i)->accept(this);
    fArgs.Insert(registerData.getLastRegister());
  }
  addInstr(Instr::createCallInstr(CallInstr(fType, fName, fArgs)));
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
  addInstr(instr);
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
  addInstr(instr);
  registerData.getLastRegister() = outReg;
}

void CodeBuilder::visitERel(ERel *erel)
{
  erel->expr_1->accept(this);
  BinaryOperationArgument lArg = BinaryOperationArgument::createRegister(registerData.getLastRegister());
  erel->expr_2->accept(this);
  BinaryOperationArgument rArg = BinaryOperationArgument::createRegister(registerData.getLastRegister());
  RegisterKind regKind = getBinaryOperationRegisterKind(lArg.asRegister(), rArg.asRegister());
  Register outReg = getNextRegister(regKind);
  BinaryOperator bor = BinaryOperator::createLth();
  if(LE *relop = dynamic_cast<LE*>(erel->relop_)) {
    bor = BinaryOperator::createLe();
  }  else if(LTH *relop = dynamic_cast<LTH*>(erel->relop_)) {
    bor = BinaryOperator::createLth();
  }  else if(GTH *relop = dynamic_cast<GTH*>(erel->relop_)) {
    bor = BinaryOperator::createGth();
  } else if(GE *relop = dynamic_cast<GE*>(erel->relop_)) {
    bor = BinaryOperator::createGe();
  } else if(EQU *relop = dynamic_cast<EQU*>(erel->relop_)) {
    bor = BinaryOperator::createEqu();
  } else if(NE *relop = dynamic_cast<NE*>(erel->relop_)) {
    bor = BinaryOperator::createNe();
  } else 
    throw Exception("[CodeBuilder::visitEAdd] Unknown erel->relop_ kind.");
  BinaryOperation bon = BinaryOperation(outReg, lArg, rArg, bor);
  Instr instr = Instr::createBinaryOperationInstr(bon);
  addInstr(instr);
  registerData.getLastRegister() = outReg;
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
  BinaryOperationArgument lArg = BinaryOperationArgument::createNumber(x);
  BinaryOperationArgument rArg = BinaryOperationArgument::createNumber(0);
  Register outReg = getNextRegister(RegisterKind::createValueI32());
  BinaryOperation bo = BinaryOperation(outReg, lArg, rArg, BinaryOperator::createAdd());
  Instr instr = Instr::createBinaryOperationInstr(bo);
  addInstr(instr);
  registerData.getLastRegister() = outReg;
}

void CodeBuilder::visitChar(Char x)
{
  BinaryOperationArgument lArg = BinaryOperationArgument::createNumber(x);
  BinaryOperationArgument rArg = BinaryOperationArgument::createNumber(0);
  Register outReg = getNextRegister(RegisterKind::createValueI8());
  BinaryOperation bo = BinaryOperation(outReg, lArg, rArg, BinaryOperator::createAdd());
  Instr instr = Instr::createBinaryOperationInstr(bo);
  addInstr(instr);
  registerData.getLastRegister() = outReg;
}

void CodeBuilder::visitDouble(Double x)
{
  BinaryOperationArgument lArg = BinaryOperationArgument::createNumber(x);
  BinaryOperationArgument rArg = BinaryOperationArgument::createNumber(0);
  Register outReg = getNextRegister(RegisterKind::createValueDouble());
  BinaryOperation bo = BinaryOperation(outReg, lArg, rArg, BinaryOperator::createAdd());
  Instr instr = Instr::createBinaryOperationInstr(bo);
  addInstr(instr);
  registerData.getLastRegister() = outReg;
}

void CodeBuilder::visitString(String x)
{
  //TODO
  //actType = Type::createBasic(BasicType::createString());
}

void CodeBuilder::visitIdent(Ident x)
{
  fprintf(stderr, "VisitIdent %s reg %d\n", x.c_str(), getRegisterByIdent(x).getId());
  registerData.getLastRegister() = getRegisterByIdent(x);
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

RegisterKind CodeBuilder::getRegisterKindFromLatteType(const LatteType* type) {
  if(const IntType *arg = dynamic_cast<const IntType*>(type))
    return RegisterKind::createValueI32();
  if(const StrType *arg = dynamic_cast<const StrType*>(type))
    return RegisterKind::createPtr(RegisterKind::createValueI8());
  if(const BoolType *arg = dynamic_cast<const BoolType*>(type))
    return RegisterKind::createValueI1();
  throw Exception("[getRegisterKindFromType] Unknown type.");
}

void CodeBuilder::initBlock(const AnsiString& name) {
  /*
  * Funkcja inicjuje początek generowania nowego bloku
  */
  actBlocks.Insert(LLVMBlock(name, InstrArray()));
}

AnsiString CodeBuilder::getNextBlockNameByPrefix(const AnsiString& name) {
  int index = 0;
  for(int i=0;i<actBlocks.Size();i++) {
    const AnsiString bname = actBlocks[i].getName();
    if(bname.Length() > name.Length() && bname.SubString(1, name.Length()) == name)
      index++;
  }
  AnsiString bname = name+"_"+AnsiString(index);
  return bname;
}

void CodeBuilder::addInstr(const Instr instr) {
  actBlocks[actBlocks.Size()-1].getBody().Insert(instr);
}

void CodeBuilder::updateEnviroment(const AnsiString& ident, const Object& object) {
  /*
  * Funcja aktualizuje aktualne środowisko
  * Wykorzystywana np. do przesłaniania zmiennych
  */
  int storeId = store.Size();
  store.Insert(StoreElement(storeId, object));
  for(int i=0;i<enviroment.Size();i++) {
    if(enviroment[i].getIdent()==ident) {
      enviroment[i].getStoreId() = storeId;
      return;
    }
  }
  enviroment.Insert(BuilderEnviromentElement(ident, storeId));
}

void CodeBuilder::updateStore(const AnsiString& ident, const Object& object) {
  /*
  * Funcja aktualizuje aktualną pamięć
  * Wykorzystywana np. do akutalizowania rejestrów zmiennych podczas przypisań
  */
  for(int i=0;i<enviroment.Size();i++) {
    if(enviroment[i].getIdent()==ident) {
      for(int j=0;j<store.Size();j++) {
        if(store[j].getId()==enviroment[i].getStoreId()) {
          store[j].getObj() = object;
          return;
        }
      }
    }
  }
  updateEnviroment(ident, object);
}

void CodeBuilder::addPhiCase(const AnsiString& ident, const Register& reg, const AnsiString& fromBlock, const AnsiString& toBlock) {
  /*
  * Funcja dodaje kolejne opcje pochodzenia zmiennych
  * Wykorzystywana do odpowiedniego generowanie operacji phi na początku bloku
  */
  for(int i=0;i<actBlocks.Size();i++)
    if(actBlocks[i].getName()==toBlock) {
      for(int j=0;j<actBlocks[i].getBody().Size();j++) {
        if(actBlocks[i].getBody()[j].isPhiInstr()) {
          if(actBlocks[i].getBody()[j].asPhiInstr().getIdent()==ident) {
            actBlocks[i].getBody()[j].asPhiInstr().getCaseses().Insert(PhiCase(reg, fromBlock));
          }
        }
      }
      return;
    }
}

Object CodeBuilder::getObjectByIdent(const AnsiString& ident) {
  for(int i=0;i<enviroment.Size();i++) {
    if(enviroment[i].getIdent()==ident) {
      return store[enviroment[i].getStoreId()].getObj();
    }
  }
  throw Exception("[CodeBuilder::getObjectByIdent] Ident "+ident+" not found.");
}

Register CodeBuilder::getRegisterByIdent(const AnsiString& ident) {
  Object o = getObjectByIdent(ident);
  if(o.isBasic()) {
    BasicObject bo = o.asBasic();
    if(bo.isInt()) {
      return bo.asInt();
    } else
      throw Exception("[getRegisterByIdent] Unsupported basic object.");
  } else 
    throw Exception("[getRegisterByIdent] Unsupported object " + ident + ".");
}