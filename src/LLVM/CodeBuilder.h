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
  RegisterData registerData = RegisterData(Register(-1, RegisterKind::createNull(), RegisterPlain::createFalse()), Registers());
  Store store;
  BuilderEnviroment enviroment = BuilderEnviroment(BuilderEnviromentElementArray(), BuilderEnviromentStructArray());
  LLVMBlockArray actBlocks;
  LLVMProgram program = LLVMProgram(LLVMFunctionArray(), LLVMConstStringArray(), LLVMStructElementArray());

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
  void visitArrType(ArrType *p);
  void visitVoidType(VoidType* p);
  void visitFun(Fun* p);
  void visitEVar(EVar* p);
  void visitObjType(ObjType* p);
  void visitELitInt(ELitInt* p);
  void visitELitTrue(ELitTrue* p);
  void visitELitFalse(ELitFalse* p);
  void visitENewArr(ENewArr *p);
  void visitEAtt(EAtt* p);
  void visitEArr(EArr *p);
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
  void visitArrAss(ArrAss *p);

  void visitInteger(Integer x);
  void visitChar(Char x);
  void visitDouble(Double x);
  void visitString(String x);
  void visitIdent(Ident x);

  void addPredefinied() {
    Object o1 = Object::createFunction(FunctionObject(LLVMFunctionType::createVoid()));
    updateEnviroment("printInt", o1);

    LLVMFunctionType type2 = LLVMFunctionType::createObj(RegisterKind::createValueI32());
    Object o2 = Object::createFunction(FunctionObject(type2));
    updateEnviroment("readInt", o2);

    LLVMFunctionType type3 = LLVMFunctionType::createObj(RegisterKind::createPtr(RegisterKind::createValueI8()));
    Object o3 = Object::createFunction(FunctionObject(type3));
    updateEnviroment("readString", o3);

    Object o4 = Object::createFunction(FunctionObject(LLVMFunctionType::createVoid()));
    updateEnviroment("printString", o4);

    Object o5 = Object::createFunction(FunctionObject(LLVMFunctionType::createVoid()));
    updateEnviroment("error", o5);

    LLVMFunctionType type6 = LLVMFunctionType::createObj(RegisterKind::createPtr(RegisterKind::createValueI8()));
    Object o6 = Object::createFunction(FunctionObject(type6));
    updateEnviroment("concatenate", o6);

    //InstrArray readIntInstrs;
    //readIntInstrs.Insert(Instr::createAlloca(getNextRegister(RegisterKind::createValueI32())));
    /*
    %x = alloca i32, align 4
    %1 = call i32 (i8*, ...)* @scanf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32* %x)
    %2 = load i32* %x, align 4
    */
    //LLVMBlockArray readIntBlocks;
    //readIntBlocks.Insert(LLVMBlock("readInt_entry", readIntInstrs));
    //LLVMFunction readInt("readInt", type, LLVMFunctionArgumentArray(), readIntBlocks);

  }

  void visitFnDefs(ListTopDef defs) {
    for(int i=0;i<defs.size();i++) {
      TopDef* def = defs[i];
      if(FnDef *fndef = dynamic_cast<FnDef *>(def)) {
        LLVMFunctionType fRetType = LLVMFunctionType::createVoid();
        if(const VoidType *arg = dynamic_cast<const VoidType*>(fndef->lattetype_)) {
          //printf("%s void\n", fndef->ident_.c_str());
        } else {
          fRetType = LLVMFunctionType::createObj(getRegisterKindFromLatteType(fndef->lattetype_));
          //printf("%s not void\n", fndef->ident_.c_str());
        }
        updateEnviroment(fndef->ident_, Object::createFunction(FunctionObject(fRetType)));
      } else {
        throw Exception("[TypeChecker::visitFnDefs] visitFnDefs internal error.");
      }
    }
  }

  LLVMProgram compile(Visitable *v) {
    addPredefinied();
    if(Prog *defs = dynamic_cast<Prog *>(v)) {
      visitFnDefs(*(defs->listtopdef_));
    } else {
      throw Exception("[TypeChecker::visitFnDefs] check internal error.");
    }
    v->accept(this);
    return program;
  }

  //pomocnicze
  Register getNextRegister(const RegisterKind);
  Register getNextPlainRegister(const RegisterKind, AnsiString);
  RegisterKind getBinaryOperationRegisterKind(const Register&, const Register&);
  RegisterKind getRegisterKindFromLatteType(const LatteType*);
  Object getNextObjectByLatteType(const LatteType*);
  RegisterKind getRegisterKindFromObject(const Object&);

  void initBlock(const AnsiString&);
  AnsiString getNextBlockNameByPrefix(const AnsiString&);
  void addInstr(const Instr);
  Register addPhiCase(const AnsiString&, const Register&, const AnsiString&, const AnsiString&);

  const AnsiString whileToken = "while";

  

  void updateEnviroment(const AnsiString&, const Object&);
  void updateStore(const AnsiString&, const Object&);

  Object getObjectByIdent(const AnsiString&);
  Object getObjectById(const int);


  Register getRegisterByObject(const Object&);
  Register getRegisterByIdent(const AnsiString&);

  void initArray(const LatteType*, AnsiString);
  Register getArrayPtr(const Register&);
  Register getArraySizePtr(const Register&);
};


#endif
