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
  BuilderEnviroment prev = enviroment;
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
  LLVMFunctionType fRetType = LLVMFunctionType::createVoid();
  if(const VoidType *arg = dynamic_cast<const VoidType*>(fndef->lattetype_)) {
  } else 
    fRetType = LLVMFunctionType::createObj(getRegisterKindFromLatteType(fndef->lattetype_));

  /*
  * 3. Argumenty
  */
  LLVMFunctionArgumentArray fArgs = LLVMFunctionArgumentArray();
  for (ListArg::iterator i = fndef->listarg_->begin() ; i != fndef->listarg_->end() ; ++i)
    if(Ar *arg = dynamic_cast<Ar*>(*i)) {
      Object o = getNextObjectByLatteType(arg->lattetype_);
      updateEnviroment(arg->ident_, o);
      if(o.isBasic() && o.asBasic().isInt())
        fArgs.Insert(LLVMFunctionArgument(o.asBasic().asInt(), arg->ident_));
      if(o.isBasic() && o.asBasic().isBool())
        fArgs.Insert(LLVMFunctionArgument(o.asBasic().asBool(), arg->ident_));
      if(o.isBasic() && o.asBasic().isString())
        fArgs.Insert(LLVMFunctionArgument(o.asBasic().asString(), arg->ident_));
      if(o.isArray())
        fArgs.Insert(LLVMFunctionArgument(o.asArray(), arg->ident_));
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

  if(fRetType.isVoid())
    visitVRet(new VRet());

  LLVMBlockArray fBlocks = actBlocks;
  program.getFunctions().Insert(LLVMFunction(fName, fRetType, fArgs, fBlocks));

  enviroment = prev;
  updateEnviroment(fName, Object::createFunction(FunctionObject(fRetType)));
}

void CodeBuilder::visitAr(Ar *ar)
{
  ar->lattetype_->accept(this);
  visitIdent(ar->ident_);
}

void CodeBuilder::visitBlk(Blk *blk)
{
  BuilderEnviroment env = enviroment;
  blk->liststmt_->accept(this);
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
  for (ListItem::iterator i = decl->listitem_->begin() ; i != decl->listitem_->end() ; ++i)
    if(Init *item = dynamic_cast<Init*>(*i)) {
      item->expr_->accept(this);
      if(IntType *type = dynamic_cast<IntType*>(decl->lattetype_)) {
        updateEnviroment(item->ident_, Object::createBasic(BasicObject::createInt(registerData.getLastRegister())));
      } else if(BoolType *type = dynamic_cast<BoolType*>(decl->lattetype_)) {
        updateEnviroment(item->ident_, Object::createBasic(BasicObject::createBool(registerData.getLastRegister())));
      } else if(StrType *type = dynamic_cast<StrType*>(decl->lattetype_)) {
        updateEnviroment(item->ident_, Object::createBasic(BasicObject::createString(registerData.getLastRegister())));
      } else if(ArrType *type = dynamic_cast<ArrType*>(decl->lattetype_)) {
        Register sizeReg = registerData.getLastRegister();
        initArray(type->lattetype_, item->ident_);
        Register strPtr = registerData.getLastRegister();
        Register sizePtr = getArraySizePtr(strPtr);
        addInstr(Instr::createStoreInstr(StoreInstr(sizeReg, sizePtr)));
        Register arrPtr = getArrayPtr(strPtr);
        Register allReg = getNextRegister(RegisterKind::createPtr(getRegisterKindFromLatteType(type->lattetype_)));
        addInstr(Instr::createAllocaInstr(AllocaInstr(AllocaInstrCount::createMultiple(sizeReg), allReg)));
        addInstr(Instr::createStoreInstr(StoreInstr(allReg, arrPtr)));
        registerData.getLastRegister() = sizeReg;
      } else  
        throw Exception("[CodeBuilder::visitDecl] Init exp type not supported");
    } else if(NoInit *item = dynamic_cast<NoInit*>(*i)) {
      if(IntType *type = dynamic_cast<IntType*>(decl->lattetype_)) {
        visitInteger(0);
        updateEnviroment(item->ident_, Object::createBasic(BasicObject::createInt(registerData.getLastRegister())));
      } else if(BoolType *type = dynamic_cast<BoolType*>(decl->lattetype_)) {
        visitELitFalse(new ELitFalse());
        updateEnviroment(item->ident_, Object::createBasic(BasicObject::createBool(registerData.getLastRegister())));
      } else if(ArrType *type = dynamic_cast<ArrType*>(decl->lattetype_)) {
        initArray(type->lattetype_, item->ident_);
      } else  if(StrType *type = dynamic_cast<StrType*>(decl->lattetype_)) {
        visitString("");
        updateEnviroment(item->ident_, Object::createBasic(BasicObject::createString(registerData.getLastRegister())));
      } else 
        throw Exception("[CodeBuilder::visitDecl] Init exp type not supported");
    
    }
}

void CodeBuilder::visitAss(Ass *ass)
{
  ass->expr_->accept(this);
  Register r = registerData.getLastRegister();
  Object o = getObjectByIdent(ass->ident_);
  if(o.isBasic()) {
    if(o.asBasic().isInt())
      updateStore(ass->ident_, Object::createBasic(BasicObject::createInt(r)));
    else if(o.asBasic().isBool())
      updateStore(ass->ident_, Object::createBasic(BasicObject::createBool(r)));
    else if(o.asBasic().isString())
      updateStore(ass->ident_, Object::createBasic(BasicObject::createString(r)));
    else
      throw Exception("[CodeBuilder::visitAss] Object not supported");
  } else if(o.isArray()) {
    /* TODO
    Register strPtr = getArraySizePtr(o.asArray());
    Register sizePtr = getArraySizePtr(strPtr);
    addInstr(Instr::createStoreInstr(StoreInstr(registerData.getLastRegister(), sizePtr)));
    Register arrPtr = getArrayPtr(strPtr);
    addInstr(Instr::createAllocaInstr(AllocaInstr(AllocaInstrCount::createMultiple(registerData.getLastRegister()), arrPtr)));
    registerData.getLastRegister() = strPtr;
    */
  } else
    throw Exception("[CodeBuilder::visitAss] Object not supported");
}

void CodeBuilder::visitIncr(Incr *incr)
{
  visitIdent(incr->ident_);
  BinaryOperationArgument lArg = BinaryOperationArgument::createRegister(registerData.getLastRegister());
  BinaryOperationArgument rArg = BinaryOperationArgument::createNumber("1");
  RegisterKind regKind = getBinaryOperationRegisterKind(lArg.asRegister(), lArg.asRegister()); //todo generalnie ta funkcja do wywalenia
  Register outReg = getNextRegister(regKind);
  registerData.getLastRegister() = outReg;
  BinaryOperation bon = BinaryOperation(outReg, regKind, lArg, rArg, BinaryOperator::createAdd());
  Instr instr = Instr::createBinaryOperationInstr(bon);
  addInstr(instr);
  updateStore(incr->ident_, Object::createBasic(BasicObject::createInt(outReg)));
}

void CodeBuilder::visitDecr(Decr *decr)
{
  visitIdent(decr->ident_);
  BinaryOperationArgument lArg = BinaryOperationArgument::createRegister(registerData.getLastRegister());
  BinaryOperationArgument rArg = BinaryOperationArgument::createNumber("1");
  RegisterKind regKind = getBinaryOperationRegisterKind(lArg.asRegister(), lArg.asRegister()); //todo generalnie ta funkcja do wywalenia
  Register outReg = getNextRegister(regKind);
  registerData.getLastRegister() = outReg;
  BinaryOperation bon = BinaryOperation(outReg, regKind, lArg, rArg, BinaryOperator::createSub());
  Instr instr = Instr::createBinaryOperationInstr(bon);
  addInstr(instr);
  updateStore(decr->ident_, Object::createBasic(BasicObject::createInt(outReg)));
}

void CodeBuilder::visitRet(Ret *ret)
{
  ret->expr_->accept(this);
  addInstr(Instr::createReturnInstr(ReturnInstr::createValue(registerData.getLastRegister())));
}

void CodeBuilder::visitVRet(VRet *vret)
{
    addInstr(Instr::createReturnInstr(ReturnInstr::createEmpty()));
}

void CodeBuilder::visitCond(Cond *cond)
{
  /*
  * Generujemy nazwy bloków
  */
  AnsiString wcondblock = getNextBlockNameByPrefix("if_cond");
  AnsiString wbodyblock = getNextBlockNameByPrefix("if_body");
  AnsiString wendblock = getNextBlockNameByPrefix("if_end");

  //skok do if_cond
  addInstr(Instr::createBrInstr(BrInstr(wcondblock)));

  /*
  * Generujemy blok warunku
  */
  initBlock(wcondblock);
  cond->expr_->accept(this);

  bool constExpr = registerData.getLastRegister().getPlain().isTrue();
  bool constVal = registerData.getLastRegister().getPlain().isTrue() && registerData.getLastRegister().getPlain().asTrue() == "1";

  if(!constExpr) {
    addInstr(Instr::createBrIfInstr(BrIfInstr(registerData.getLastRegister(), wbodyblock, wendblock)));
  } else {
    if(constVal) {
      addInstr(Instr::createBrInstr(wbodyblock));
    } else {
      addInstr(Instr::createBrInstr(wendblock));
    }
  } 
  
  DynSet<Object> objs;
  DynSet<AnsiString> idents;
  for(int i=0;i<enviroment.getIdents().Size();i++) {
    Object o = getObjectById(enviroment.getIdents()[i].getStoreId());
    if(o.isBasic()) {
      objs.Insert(o);
      idents.Insert(enviroment.getIdents()[i].getIdent());
    }
  }

  BuilderEnviroment e = enviroment;
  Store s = store;

  /*
  * Generujemy ciało if
  */
  initBlock(wbodyblock);
  cond->stmt_->accept(this);
  addInstr(Instr::createBrInstr(BrInstr(wendblock)));

  initBlock(wendblock);
  for(int i=0;i<enviroment.getIdents().Size();i++) {
    Object o = getObjectById(enviroment.getIdents()[i].getStoreId());
    if(o.isBasic()) {
      if(o.asBasic().isInt()) {
        Register r = addPhiCase(enviroment.getIdents()[i].getIdent(), o.asBasic().asInt(), wbodyblock, wendblock);
        updateEnviroment(enviroment.getIdents()[i].getIdent(), Object::createBasic(BasicObject::createInt(r)));
      } else if(o.asBasic().isBool()) {
        Register r = addPhiCase(enviroment.getIdents()[i].getIdent(), o.asBasic().asBool(), wbodyblock, wendblock);
        updateEnviroment(enviroment.getIdents()[i].getIdent(), Object::createBasic(BasicObject::createBool(r)));
      } else if(o.asBasic().isString()) {
        Register r = addPhiCase(enviroment.getIdents()[i].getIdent(), o.asBasic().asString(), wbodyblock, wendblock);
        updateEnviroment(enviroment.getIdents()[i].getIdent(), Object::createBasic(BasicObject::createString(r)));
      }
    }
  }
  for(int i=0;i<objs.Size();i++) {
    Object o = objs[i];
    if(o.isBasic()) {
      if(o.asBasic().isInt()) {
        addPhiCase(idents[i], o.asBasic().asInt(), wcondblock, wendblock);
      } else if(o.asBasic().isBool()) {
        addPhiCase(idents[i], o.asBasic().asBool(), wcondblock, wendblock);
      } else if(o.asBasic().isString()) {
        addPhiCase(idents[i], o.asBasic().asString(), wcondblock, wcondblock);
      }
    }
  }
  enviroment = e;
  store = s;

}

void CodeBuilder::visitCondElse(CondElse *condelse)
{
  /*
  * Generujemy nazwy bloków
  */
  AnsiString wcondblock = getNextBlockNameByPrefix("if_cond");
  AnsiString wbodyblock = getNextBlockNameByPrefix("if_body");
  AnsiString welseblock = getNextBlockNameByPrefix("if_else");
  AnsiString wendblock = getNextBlockNameByPrefix("if_end");

  //skok do if_cond
  addInstr(Instr::createBrInstr(BrInstr(wcondblock)));

  /*
  * Generujemy blok warunku
  */

  initBlock(wcondblock);
  condelse->expr_->accept(this);

  bool constExpr = registerData.getLastRegister().getPlain().isTrue();
  bool constVal = registerData.getLastRegister().getPlain().isTrue() && registerData.getLastRegister().getPlain().asTrue() == "1";
  if(!constExpr) {
     addInstr(Instr::createBrIfInstr(BrIfInstr(registerData.getLastRegister(), wbodyblock, welseblock)));
  } else {
    if(constVal) {
      addInstr(Instr::createBrInstr(wbodyblock));
    } else {
      addInstr(Instr::createBrInstr(welseblock));
    }
  } 
  
  BuilderEnviroment e = enviroment;
  Store s = store;
  /*
  * Generujemy ciało if_body
  */
  initBlock(wbodyblock);
  condelse->stmt_1->accept(this);
  addInstr(Instr::createBrInstr(BrInstr(wendblock)));

  DynSet<Object> objs;
  DynSet<AnsiString> idents;
  for(int i=0;i<enviroment.getIdents().Size();i++) {
    Object o = getObjectById(enviroment.getIdents()[i].getStoreId());
    if(o.isBasic()) {
      objs.Insert(o);
      idents.Insert(enviroment.getIdents()[i].getIdent());
    }
  }

  enviroment = e;
  store = s;
  /*
  * Generujemy ciało if_else
  */
  initBlock(welseblock);
  condelse->stmt_2->accept(this);
  addInstr(Instr::createBrInstr(BrInstr(wendblock)));

  initBlock(wendblock);
  for(int i=0;i<enviroment.getIdents().Size();i++) {
    Object o = getObjectById(enviroment.getIdents()[i].getStoreId());
    if(o.isBasic()) {
      if(o.asBasic().isInt()) {
        Register r = addPhiCase(enviroment.getIdents()[i].getIdent(), o.asBasic().asInt(), welseblock, wendblock);
        updateEnviroment(enviroment.getIdents()[i].getIdent(), Object::createBasic(BasicObject::createInt(r)));
      } else if(o.asBasic().isBool()) {
        Register r = addPhiCase(enviroment.getIdents()[i].getIdent(), o.asBasic().asBool(), welseblock, wendblock);
        updateEnviroment(enviroment.getIdents()[i].getIdent(), Object::createBasic(BasicObject::createBool(r)));
      } else if(o.asBasic().isString()) {
        Register r = addPhiCase(enviroment.getIdents()[i].getIdent(), o.asBasic().asString(), welseblock, wendblock);
        updateEnviroment(enviroment.getIdents()[i].getIdent(), Object::createBasic(BasicObject::createString(r)));
      }
    }
  }
  for(int i=0;i<objs.Size();i++) {
    Object o = objs[i];
    if(o.isBasic()) {
      if(o.asBasic().isInt()) {
        addPhiCase(idents[i], o.asBasic().asInt(), wbodyblock, wendblock);
      } else if(o.asBasic().isBool()) {
        addPhiCase(idents[i], o.asBasic().asBool(), wbodyblock, wendblock);
      } else if(o.asBasic().isString()) {
        addPhiCase(idents[i], o.asBasic().asString(), wbodyblock, wcondblock);
      }
    }
  }
}

void CodeBuilder::visitForStmnt(ForStmnt *forstmnt) {

  Ident looperIdent = Ident("loop_index");
  Ident tabIdent = Ident(forstmnt->ident_2);
  Ident iteratorIdent = Ident(forstmnt->ident_1);

  Object o = getObjectByIdent(tabIdent);
  if(!o.isArray())
    throw Exception("[CodeBuilder::visitForStmnt] Internal error 1");
  AnsiString strName = o.asArray().getKind().asPtr().asStruct();

  ListItem* looperItems = new ListItem();
  looperItems->push_back(new Init(looperIdent, new ELitInt(0)));
  Decl* looperDecl = new Decl(new IntType(), looperItems);
  /*  {
        int looper_index = 0;
        while(looper_index < arr.length) {
          ident = arr[looper_index];
          ...
          ident++;
        }
      }
  */

  ListStmt* whileStmnts = new ListStmt();

  ListItem* iteratorItems = new ListItem();
  iteratorItems->push_back(new Init(iteratorIdent, new EArr(tabIdent, new EVar(looperIdent))));
  
  for(int i=0;i<program.getStructs().Size();i++)
    if(program.getStructs()[i].getName()==strName) {
      RegisterKind reg =program.getStructs()[i].getElems()[1].asPtr();

      Decl* iteratorDecl;

      if(reg.isValueI32()) {
        iteratorDecl = new Decl(new IntType(), iteratorItems);
      } else if(reg.isValueI1()) {
        iteratorDecl = new Decl(new BoolType(), iteratorItems);
      } else if(reg.isValueI32()) {
        iteratorDecl = new Decl(new IntType(), iteratorItems);
      } else 
        throw Exception("[CodeBuilder::visitForStmnt] Internal error 2");
      

      //
      whileStmnts->push_back(iteratorDecl);
      whileStmnts->push_back(forstmnt->stmt_);
      whileStmnts->push_back(new Incr(looperIdent));
      //

      WhileStmnt* whileStmnt = new WhileStmnt(new ERel(new EVar(looperIdent), new LTH(), new EAtt(tabIdent, new EVar(Ident("length"))) ), new BStmt(new Blk(whileStmnts)));


      ListStmt* blkStmnts = new ListStmt();
      blkStmnts->push_back(looperDecl);
      blkStmnts->push_back(whileStmnt);

      Blk* blk = new Blk(blkStmnts);
      visitBlk(blk);
      return;
    }
  throw Exception("[CodeBuilder::visitForStmnt] Internal error 3");
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
  /*
  * Generujemy blok warunku
  */
  initBlock(wcondblock);
  for(int i=0;i<enviroment.getIdents().Size();i++) {
    Object o = getObjectById(enviroment.getIdents()[i].getStoreId());
    if(o.isBasic()) {
      if(o.asBasic().isInt()) {
        Register r = addPhiCase(enviroment.getIdents()[i].getIdent(), o.asBasic().asInt(), actBlocks[actBlocks.Size()-2].getName(), wcondblock);
        updateEnviroment(enviroment.getIdents()[i].getIdent(), Object::createBasic(BasicObject::createInt(r)));
      } else if(o.asBasic().isBool()) {
        Register r = addPhiCase(enviroment.getIdents()[i].getIdent(), o.asBasic().asBool(), actBlocks[actBlocks.Size()-2].getName(), wcondblock);
        updateEnviroment(enviroment.getIdents()[i].getIdent(), Object::createBasic(BasicObject::createBool(r)));
      } else if(o.asBasic().isString()) {
        Register r = addPhiCase(enviroment.getIdents()[i].getIdent(), o.asBasic().asString(), actBlocks[actBlocks.Size()-2].getName(), wcondblock);
        updateEnviroment(enviroment.getIdents()[i].getIdent(), Object::createBasic(BasicObject::createString(r)));
      }
    }
  }
  whilestmnt->expr_->accept(this);
  addInstr(Instr::createBrIfInstr(BrIfInstr(registerData.getLastRegister(), wbodyblock, wendblock)));
  BuilderEnviroment e = enviroment;
  Store s = store;
  /*
  * Generujemy ciało while
  */
  initBlock(wbodyblock);
  whilestmnt->stmt_->accept(this);
  addInstr(Instr::createBrInstr(BrInstr(wcondblock)));
  for(int i=0;i<enviroment.getIdents().Size();i++) {
    Object o = getObjectById(enviroment.getIdents()[i].getStoreId());
    if(o.isBasic())
      if(o.asBasic().isInt())
         addPhiCase(enviroment.getIdents()[i].getIdent(), o.asBasic().asInt(), wbodyblock, wcondblock);
      else if(o.asBasic().isBool())
         addPhiCase(enviroment.getIdents()[i].getIdent(), o.asBasic().asBool(), wbodyblock, wcondblock);
      else if(o.asBasic().isString())
         addPhiCase(enviroment.getIdents()[i].getIdent(), o.asBasic().asString(), wbodyblock, wcondblock);
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

void CodeBuilder::visitObjType(ObjType* p) {
//TODO
}

void CodeBuilder::visitIntType(IntType *inttype)
{
 
}

void CodeBuilder::visitStrType(StrType *strtype)
{
  
}

void CodeBuilder::visitBoolType(BoolType *booltype)
{
  
}

void CodeBuilder::visitArrType(ArrType *arrtype)
{

}

void CodeBuilder::visitVoidType(VoidType *voidtype)
{
 
}

void CodeBuilder::visitFun(Fun *fun)
{

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
  Register outReg = getNextPlainRegister(RegisterKind::createValueI1(), "1");
  registerData.getLastRegister() = outReg;
}

void CodeBuilder::visitELitFalse(ELitFalse *elitfalse)
{
  Register outReg = getNextPlainRegister(RegisterKind::createValueI1(), "0");
  registerData.getLastRegister() = outReg;
}

void CodeBuilder::visitEArr(EArr *earr) {
  
  earr->expr_->accept(this);

  RegisterArray arr;
  arr.Insert(registerData.getLastRegister());

  if(!getObjectByIdent(earr->ident_).isArray())
    throw Exception(AnsiString("") + "[CodeBuilder::visitEArr] is not array " + earr->ident_);
  
  Register strPtr = getObjectByIdent(earr->ident_).asArray();

  Register arrReg1 = getArrayPtr(strPtr);
  Register arrReg = getNextRegister(arrReg1.getKind().asPtr());
  addInstr(Instr::createLoadInstr(LoadInstr(arrReg, arrReg1)));

  Register ptrReg = getNextRegister(arrReg.getKind());
  Register outReg = getNextRegister(arrReg.getKind().asPtr());

  GetElementPtrInstr ginstr(ptrReg, arrReg, arr);
  addInstr(Instr::createGetElementPtrInstr(ginstr));
  
  LoadInstr linstr(outReg, ptrReg);
  addInstr(Instr::createLoadInstr(linstr));

  
  registerData.getLastRegister() = outReg;
  

}

void CodeBuilder::visitArrAss(ArrAss *arrass) {

  arrass->expr_1->accept(this);

  RegisterArray arr;
  arr.Insert(registerData.getLastRegister());

  if(!getObjectByIdent(arrass->ident_).isArray())
    throw Exception("[CodeBuilder::visitArrAss] is not array" + arrass->ident_);
  Register strPtr = getObjectByIdent(arrass->ident_).asArray();

  Register arrPtr = getArrayPtr(strPtr);
  Register arrReg = getNextRegister(arrPtr.getKind().asPtr());
  addInstr(Instr::createLoadInstr(LoadInstr(arrReg, arrPtr)));
  Register ptrReg = getNextRegister(arrReg.getKind());

  GetElementPtrInstr ginstr(ptrReg, arrReg, arr);
  addInstr(Instr::createGetElementPtrInstr(ginstr));
  
  arrass->expr_2->accept(this);

  StoreInstr linstr(registerData.getLastRegister(), ptrReg);
  addInstr(Instr::createStoreInstr(linstr));

}

void CodeBuilder::visitENewArr(ENewArr *enewarr)
{
  /* Code For ENewArr Goes Here */

  enewarr->lattetype_->accept(this);
  enewarr->expr_->accept(this);

}

void CodeBuilder::visitEAtt(EAtt* eatt) {
  Object o = getObjectByIdent(eatt->ident_);
  //ewentualne przechodzenie po .

  if(EVar* evar = dynamic_cast<EVar*>(eatt->expr_)) {
    //atrybut
    if(evar->ident_ == "length" && o.isArray()) {
      Register r = getArraySizePtr(o.asArray());
      Register outReg = getNextRegister(RegisterKind::createValueI32());
      addInstr(Instr::createLoadInstr(LoadInstr(outReg, r)));
      registerData.getLastRegister() = outReg;
    } else
      throw Exception("[CodeBuilder::visitEAtt] Internal error " + o.toJSON() + " " + evar->ident_);
  } else if (true) {

  }

}

void CodeBuilder::visitEApp(EApp *eapp)
{
  AnsiString fName = eapp->ident_;
  Registers fArgs;
  for (ListExpr::iterator i = eapp->listexpr_->begin() ; i != eapp->listexpr_->end() ; ++i) {
    (*i)->accept(this);
    fArgs.Insert(registerData.getLastRegister());
  }
  LLVMFunctionType fType = getObjectByIdent(eapp->ident_).asFunction().getType();
  if(fType.isVoid()) {
    addInstr(Instr::createCallInstr(CallInstr(CallInstrRet::createVoid(), fName, fArgs)));
  } else {
    Register reg = getNextRegister(fType.asObj());
    addInstr(Instr::createCallInstr(CallInstr(CallInstrRet::createObj(reg), fName, fArgs)));
    registerData.getLastRegister() = reg;
  }
}

void CodeBuilder::visitEString(EString *estring)
{
  visitString(estring->string_);
}

void CodeBuilder::visitNeg(Neg *neg)
{
  neg->expr_->accept(this);
  BinaryOperationArgument lArg = BinaryOperationArgument::createNumber("0");
  BinaryOperationArgument rArg = BinaryOperationArgument::createRegister(registerData.getLastRegister());
  RegisterKind regKind = getBinaryOperationRegisterKind(rArg.asRegister(), rArg.asRegister()); //todo generalnie ta funkcja do wywalenia
  Register outReg = getNextRegister(regKind);
  registerData.getLastRegister() = outReg;
  BinaryOperation bon = BinaryOperation(outReg, regKind, lArg, rArg, BinaryOperator::createSub());
  Instr instr = Instr::createBinaryOperationInstr(bon);
  addInstr(instr);
}

void CodeBuilder::visitNott(Nott *nott)
{
  nott->expr_->accept(this);
  BinaryOperationArgument lArg = BinaryOperationArgument::createRegister(registerData.getLastRegister());
  BinaryOperationArgument rArg = BinaryOperationArgument::createNumber("1");
  RegisterKind regKind = getBinaryOperationRegisterKind(lArg.asRegister(), lArg.asRegister()); //todo generalnie ta funkcja do wywalenia
  Register outReg = getNextRegister(regKind);
  registerData.getLastRegister() = outReg;
  BinaryOperation bon = BinaryOperation(outReg, regKind, lArg, rArg, BinaryOperator::createSub());
  Instr instr = Instr::createBinaryOperationInstr(bon);
  addInstr(instr);

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
    bor = BinaryOperator::createMod();
  } else if(Div *mulop = dynamic_cast<Div*>(emul->mulop_)) {
    bor = BinaryOperator::createDiv();
  } else 
    throw Exception("[CodeBuilder::visitEMul] Unknown emul->mulop_ kind.");
  BinaryOperation bon = BinaryOperation(outReg, regKind, lArg, rArg, bor);
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
  if(outReg.getKind().isPtr()) {
    //string
    Registers args;
    args.Insert(lArg.asRegister());
    args.Insert(rArg.asRegister());
    Instr instr = Instr::createCallInstr(CallInstr(CallInstrRet::createObj(outReg), "concatenate", args));
    addInstr(instr);
    registerData.getLastRegister() = outReg;
  } else {
    BinaryOperator bor = BinaryOperator::createDiv();
    if(Plus *addop = dynamic_cast<Plus*>(eadd->addop_)) {
      bor = BinaryOperator::createAdd();
    } else if(Minus *addop = dynamic_cast<Minus*>(eadd->addop_)) {
      bor = BinaryOperator::createSub();
    } else 
      throw Exception("[CodeBuilder::visitEAdd] Unknown eadd->addop_ kind.");
    BinaryOperation bon = BinaryOperation(outReg, outReg.getKind(), lArg, rArg, bor);
    Instr instr = Instr::createBinaryOperationInstr(bon);
    addInstr(instr);
    registerData.getLastRegister() = outReg;
  }
}


void CodeBuilder::visitERel(ERel *erel)
{
  erel->expr_1->accept(this);
  BinaryOperationArgument lArg = BinaryOperationArgument::createRegister(registerData.getLastRegister());
  erel->expr_2->accept(this);
  BinaryOperationArgument rArg = BinaryOperationArgument::createRegister(registerData.getLastRegister());
  Register outReg = getNextRegister(RegisterKind::createValueI1());
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
  BinaryOperation bon = BinaryOperation(outReg, registerData.getLastRegister().getKind(), lArg, rArg, bor);
  Instr instr = Instr::createBinaryOperationInstr(bon);
  addInstr(instr);
  registerData.getLastRegister() = outReg;
}

void CodeBuilder::visitEAnd(EAnd *eand)
{
  AnsiString actBlock = actBlocks[actBlocks.Size()-1].getName();
  AnsiString ifandcond2 = getNextBlockNameByPrefix("if_and_cond2");
  AnsiString ifandend = getNextBlockNameByPrefix("if_and_end");
  eand->expr_1->accept(this);
  addInstr(Instr::createBrIfInstr(BrIfInstr(registerData.getLastRegister(), ifandcond2, ifandend)));
  Register r1 = registerData.getLastRegister();
  initBlock(ifandcond2);
  eand->expr_2->accept(this);
  AnsiString actBlock2 = actBlocks[actBlocks.Size()-1].getName();
  addInstr(Instr::createBrInstr(BrInstr(ifandend)));
  Register r2 = registerData.getLastRegister();
  initBlock(ifandend);
  addPhiCase(ifandend, r1, actBlock, ifandend);
  registerData.getLastRegister() = addPhiCase(ifandend, r2, actBlock2, ifandend);
}

void CodeBuilder::visitEOr(EOr *eor)
{
  AnsiString actBlock = actBlocks[actBlocks.Size()-1].getName();
  AnsiString iforcond2 = getNextBlockNameByPrefix("if_or_cond2");
  AnsiString iforend = getNextBlockNameByPrefix("if_and_end");
  eor->expr_1->accept(this);
  addInstr(Instr::createBrIfInstr(BrIfInstr(registerData.getLastRegister(), iforend, iforcond2)));
  Register r1 = registerData.getLastRegister();
  initBlock(iforcond2);
  eor->expr_2->accept(this);
  AnsiString actBlock2 = actBlocks[actBlocks.Size()-1].getName();
  addInstr(Instr::createBrInstr(BrInstr(iforend)));
  Register r2 = registerData.getLastRegister();
  initBlock(iforend);
  addPhiCase(iforend, r1, actBlock, iforend);
  registerData.getLastRegister() = addPhiCase(iforend, r2, actBlock2, iforend);
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
  BinaryOperation bo = BinaryOperation(outReg, outReg.getKind(), lArg, rArg, BinaryOperator::createAdd());
  Instr instr = Instr::createBinaryOperationInstr(bo);
  addInstr(instr);
  registerData.getLastRegister() = outReg;
}

void CodeBuilder::visitChar(Char x)
{

}

void CodeBuilder::visitDouble(Double x)
{
;
}

void CodeBuilder::visitString(String x)
{
  Register constReg = getNextRegister(RegisterKind::createConstPtr(ConstPtr(RegisterKind::createValueI8(), AnsiString(x).Length()+1)));
  program.getStrings().Insert(LLVMConstString(constReg.getId(), x));

  Register allocReg = getNextRegister(RegisterKind::createPtr(RegisterKind::createPtr(RegisterKind::createValueI8())));
  addInstr(Instr::createAllocaInstr(AllocaInstr(AllocaInstrCount::createSingle(), allocReg)));

  RegisterArray indexes;
  visitInteger(0);
  indexes.Insert(registerData.getLastRegister());
  visitInteger(0);
  indexes.Insert(registerData.getLastRegister());

  Register getReg = getNextRegister(RegisterKind::createPtr(RegisterKind::createValueI8()));

  GetElementPtrInstr ginstr(getReg, constReg, indexes);
  addInstr(Instr::createGetElementPtrInstr(ginstr));

  addInstr(Instr::createStoreInstr(StoreInstr(getReg, allocReg)));
  Register outReg = getNextRegister(RegisterKind::createPtr(RegisterKind::createValueI8()));
  addInstr(Instr::createLoadInstr(LoadInstr(outReg, allocReg)));
  registerData.getLastRegister() = outReg;
}

void CodeBuilder::visitIdent(Ident x)
{
  registerData.getLastRegister() = getRegisterByIdent(x);
}

Register CodeBuilder::getNextRegister(const RegisterKind kind) {
  Register ret = Register(registerData.getRegisters().Size(), kind, RegisterPlain::createFalse());
  registerData.getRegisters().Insert(ret);
  return ret;
}

Register CodeBuilder::getNextPlainRegister(const RegisterKind kind, AnsiString value) {
  Register ret = Register(registerData.getRegisters().Size(), kind, RegisterPlain::createTrue(value));
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

  /*if(r1.getKind().isValueI32()) {
    if(r2.getKind().isValueI32()) {
      return RegisterKind::createValueI32();
    } else 
    return RegisterKind::createValueDouble();
  }*/
  return r1.getKind();
}

RegisterKind CodeBuilder::getRegisterKindFromLatteType(const LatteType* type) {
  if(const IntType *arg = dynamic_cast<const IntType*>(type))
    return RegisterKind::createValueI32();
  if(const StrType *arg = dynamic_cast<const StrType*>(type))
    return RegisterKind::createPtr(RegisterKind::createValueI8());
  if(const BoolType *arg = dynamic_cast<const BoolType*>(type))
    return RegisterKind::createValueI1();
  if(const ArrType *arg = dynamic_cast<const ArrType*>(type))
    return RegisterKind::createPtr(getRegisterKindFromLatteType(arg->lattetype_));
  throw Exception("[getRegisterKindFromType] Unknown type.");
}

void CodeBuilder::initBlock(const AnsiString& name) {
  /*
  * Funkcja inicjuje początek generowania nowego bloku
  */
  actBlocks.Insert(LLVMBlock(name, InstrArray()));
}

AnsiString CodeBuilder::getNextBlockNameByPrefix(const AnsiString& name) {
  static int index = 0;
  AnsiString bname = name+"_"+AnsiString(index++);
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
  for(int i=0;i<enviroment.getIdents().Size();i++) {
    if(enviroment.getIdents()[i].getIdent()==ident) {
      enviroment.getIdents()[i].getStoreId() = storeId;
      return;
    }
  }
  enviroment.getIdents().Insert(BuilderEnviromentElement(ident, storeId));
}

void CodeBuilder::updateStore(const AnsiString& ident, const Object& object) {
  /*
  * Funcja aktualizuje aktualną pamięć
  * Wykorzystywana np. do akutalizowania rejestrów zmiennych podczas przypisań
  */
  for(int i=0;i<enviroment.getIdents().Size();i++) {
    if(enviroment.getIdents()[i].getIdent()==ident) {
      for(int j=0;j<store.Size();j++) {
        if(store[j].getId()==enviroment.getIdents()[i].getStoreId()) {
          store[j].getObj() = object;
          return;
        }
      }
    }
  }
  updateEnviroment(ident, object);
}

Register CodeBuilder::addPhiCase(const AnsiString& ident, const Register& reg, const AnsiString& fromBlock, const AnsiString& toBlock) {
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
            return actBlocks[i].getBody()[j].asPhiInstr().getRet();
          }
        }
      }
      Register r = getNextRegister(reg.getKind());
      PhiCases phiCases;
      phiCases.Insert(PhiCase(reg, fromBlock));
      actBlocks[i].getBody().Insert(Instr::createPhiInstr(PhiInstr(ident, r, phiCases)));
      return r;
    }
}

Object CodeBuilder::getObjectByIdent(const AnsiString& ident) {
  for(int i=0;i<enviroment.getIdents().Size();i++) {
    if(enviroment.getIdents()[i].getIdent()==ident) {
      return store[enviroment.getIdents()[i].getStoreId()].getObj();
    }
  }
  throw Exception("[CodeBuilder::getObjectByIdent] Ident "+ident+" not found.");
}

Register CodeBuilder::getRegisterByObject(const Object& o) {
  if(o.isBasic()) {
    BasicObject bo = o.asBasic();
    if(bo.isInt()) {
      return bo.asInt();
    } else if(bo.isBool()) {
      return bo.asBool();
    } else if(bo.isString()) {
      return bo.asString();
    } else
      throw Exception("[CodeBuilder::getRegisterByObject] Unsupported basic object.");
  } if(o.isArray()) {
    return o.asArray();
  } else 
    throw Exception("[CodeBuilder::getRegisterByObject] Unsupported object.");
}

Register CodeBuilder::getRegisterByIdent(const AnsiString& ident) {
  Object o = getObjectByIdent(ident);
  return getRegisterByObject(o);
}

RegisterKind CodeBuilder::getRegisterKindFromObject(const Object& o) {
  if(o.isBasic()) {
    BasicObject bo = o.asBasic();
    if(bo.isInt()) {
      return bo.asInt().getKind();
    } else if(bo.isBool()) {
      return bo.asBool().getKind();
    } else if(bo.isString()) {
      return bo.asString().getKind();
    } else
      throw Exception("[getRegisterByIdent] Unsupported basic object.");
  } else 
    throw Exception("[getRegisterByIdent] Unsupported object.");
}

Object CodeBuilder::getObjectById(const int id) {
  for(int i=0;i<store.Size();i++) {
    if(store[i].getId()==id) {
      return store[i].getObj();
    }
  }
  throw Exception("[CodeBuilder::getObjectById] Id not found " + AnsiString(id) + ".");
}

Object CodeBuilder::getNextObjectByLatteType(const LatteType* type) {
  if(const IntType *arg = dynamic_cast<const IntType*>(type))
    return Object::createBasic(BasicObject::createInt(getNextRegister(RegisterKind::createValueI32())));
  if(const StrType *arg = dynamic_cast<const StrType*>(type))
    return Object::createBasic(BasicObject::createString(getNextRegister(RegisterKind::createPtr(RegisterKind::createValueI8()))));
  if(const BoolType *arg = dynamic_cast<const BoolType*>(type))
    return Object::createBasic(BasicObject::createBool(getNextRegister(RegisterKind::createValueI1())));
  if(const ArrType *arg = dynamic_cast<const ArrType*>(type)) {
    AnsiString strName;
    if(const IntType *arg2 = dynamic_cast<const IntType*>(arg->lattetype_))
      strName = "int";
    if(const StrType *arg2 = dynamic_cast<const StrType*>(arg->lattetype_))
      strName = "string";
    if(const BoolType *arg2 = dynamic_cast<const BoolType*>(arg->lattetype_))
      strName = "bool";
    return Object::createArray(getNextRegister(RegisterKind::createPtr(RegisterKind::createStruct(strName))));
  }
}

Register CodeBuilder::getArrayPtr(const Register& strPtr) {
  RegisterArray indexes;
  indexes.Insert(getNextPlainRegister(RegisterKind::createValueI32(), "0"));
  indexes.Insert(getNextPlainRegister(RegisterKind::createValueI32(), "1"));

  if(!strPtr.getKind().isPtr())
    throw Exception("[CodeBuilder::getArrayPtr] Bad strPtr kind!");
  AnsiString strName = strPtr.getKind().asPtr().asStruct();

  for(int i=0;i<enviroment.getStructs().Size();i++) {
    if(enviroment.getStructs()[i].getName()==strName) {
      Register getReg = getNextRegister(RegisterKind::createPtr(enviroment.getStructs()[i].getElems()[1].getKind()));
      GetElementPtrInstr ginstr(getReg, strPtr, indexes);
      addInstr(Instr::createGetElementPtrInstr(ginstr));
      return getReg;
    }
  }
  throw Exception("[CodeBuilder::getArrayPtr]");
}

Register CodeBuilder::getArraySizePtr(const Register& strPtr) {
  RegisterArray indexes;
  indexes.Insert(getNextPlainRegister(RegisterKind::createValueI32(), "0"));
  indexes.Insert(getNextPlainRegister(RegisterKind::createValueI32(), "0"));

  Register getReg = getNextRegister(RegisterKind::createPtr(RegisterKind::createValueI32()));

  GetElementPtrInstr ginstr(getReg, strPtr, indexes);
  addInstr(Instr::createGetElementPtrInstr(ginstr));
  return getReg;
}

void CodeBuilder::initArray(const LatteType* type, AnsiString ident) {
  RegisterKindArray rkarr;
  rkarr.Insert(RegisterKind::createValueI32());
  rkarr.Insert(RegisterKind::createPtr(getRegisterKindFromLatteType(type)));

  AnsiString strName = "";
  if(const IntType *arg = dynamic_cast<const IntType*>(type))
    strName = "int";
  if(const StrType *arg = dynamic_cast<const StrType*>(type))
    strName = "string";
  if(const BoolType *arg = dynamic_cast<const BoolType*>(type))
    strName = "bool";

  int i=0;
  for(;i<program.getStructs().Size();i++)
    if(program.getStructs()[i].getName()==strName)
      break;
  if(i==program.getStructs().Size()) {
    program.getStructs().Insert(LLVMStruct(strName, rkarr));
    BuilderEnviromentStructElemArray elems;
    elems.Insert(BuilderEnviromentStructElem("lenght", rkarr[0]));
    elems.Insert(BuilderEnviromentStructElem("", rkarr[1]));
    enviroment.getStructs().Insert(BuilderEnviromentStruct(strName, elems));
  }


  Register strPtr = getNextRegister(RegisterKind::createPtr(RegisterKind::createStruct(strName)));
  addInstr(Instr::createAllocaInstr(AllocaInstr(AllocaInstrCount::createSingle(), strPtr)));


  Register getReg = getArraySizePtr(strPtr);

  addInstr(Instr::createStoreInstr(StoreInstr(getNextPlainRegister(RegisterKind::createValueI32(), "0"), getReg)));

  updateEnviroment(ident, Object::createArray(strPtr));
  registerData.getLastRegister() = strPtr;
}