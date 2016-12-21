#ifndef _LLVMPROGRAM_GEN_H_
#define _LLVMPROGRAM_GEN_H_
#include "DynSet.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- Register ---------------
#include "Register.h"
//----------------------------------

//------------- RegisterKind ---------------
#include "Register.h"
//----------------------------------

//------------- Registers ---------------
#include "Register.h"
//----------------------------------

//------------- BinaryOperationArgument ---------------
class BinaryOperationArgument {
  int _type;
  void* _ptr;

  static const int _TypeRegister;
  static const int _TypeNumber;

  virtual void init(int, void*);
  virtual void clean();
  BinaryOperationArgument();
public:
  BinaryOperationArgument(const BinaryOperationArgument&);
  virtual BinaryOperationArgument& operator=(const BinaryOperationArgument&);

  virtual bool isRegister() const;
  virtual bool isNumber() const;

  virtual const Register& asRegister() const;
  virtual Register& asRegister();
  virtual const AnsiString& asNumber() const;
  virtual AnsiString& asNumber();


  virtual ~BinaryOperationArgument();

  static BinaryOperationArgument createRegister(const Register&);
  static BinaryOperationArgument createNumber(const AnsiString&);

};
//----------------------------------

//------------- BinaryOperator ---------------
class BinaryOperator {
  int _type;
  void* _ptr;

  static const int _TypeAdd;
  static const int _TypeSub;
  static const int _TypeDiv;
  static const int _TypeMul;
  static const int _TypeMod;
  static const int _TypeLth;
  static const int _TypeLe;
  static const int _TypeGth;
  static const int _TypeGe;
  static const int _TypeEqu;
  static const int _TypeNe;

  virtual void init(int, void*);
  virtual void clean();
  BinaryOperator();
public:
  BinaryOperator(const BinaryOperator&);
  virtual BinaryOperator& operator=(const BinaryOperator&);

  virtual bool isAdd() const;
  virtual bool isSub() const;
  virtual bool isDiv() const;
  virtual bool isMul() const;
  virtual bool isMod() const;
  virtual bool isLth() const;
  virtual bool isLe() const;
  virtual bool isGth() const;
  virtual bool isGe() const;
  virtual bool isEqu() const;
  virtual bool isNe() const;



  virtual ~BinaryOperator();

  static BinaryOperator createAdd();
  static BinaryOperator createSub();
  static BinaryOperator createDiv();
  static BinaryOperator createMul();
  static BinaryOperator createMod();
  static BinaryOperator createLth();
  static BinaryOperator createLe();
  static BinaryOperator createGth();
  static BinaryOperator createGe();
  static BinaryOperator createEqu();
  static BinaryOperator createNe();

};
//----------------------------------

//------------- BinaryOperation ---------------
class BinaryOperation {
  Register outReg;
  BinaryOperationArgument lArg;
  BinaryOperationArgument rArg;
  BinaryOperator bop;
public:
  BinaryOperation(const Register&, const BinaryOperationArgument&, const BinaryOperationArgument&, const BinaryOperator&);
  virtual const Register& getOutReg() const;
  virtual const BinaryOperationArgument& getLArg() const;
  virtual const BinaryOperationArgument& getRArg() const;
  virtual const BinaryOperator& getBop() const;
  virtual Register& getOutReg();
  virtual BinaryOperationArgument& getLArg();
  virtual BinaryOperationArgument& getRArg();
  virtual BinaryOperator& getBop();


  virtual ~BinaryOperation();

};
//----------------------------------

//------------- CallInstr ---------------
class CallInstr {
  RegisterKind retType;
  AnsiString function;
  Registers args;
public:
  CallInstr(const RegisterKind&, const AnsiString&, const Registers&);
  virtual const RegisterKind& getRetType() const;
  virtual const AnsiString& getFunction() const;
  virtual const Registers& getArgs() const;
  virtual RegisterKind& getRetType();
  virtual AnsiString& getFunction();
  virtual Registers& getArgs();


  virtual ~CallInstr();

};
//----------------------------------

//------------- BrIfInstr ---------------
class BrIfInstr {
  Register cond;
  AnsiString ifTrueBlock;
  AnsiString ifFalseBlock;
public:
  BrIfInstr(const Register&, const AnsiString&, const AnsiString&);
  virtual const Register& getCond() const;
  virtual const AnsiString& getIfTrueBlock() const;
  virtual const AnsiString& getIfFalseBlock() const;
  virtual Register& getCond();
  virtual AnsiString& getIfTrueBlock();
  virtual AnsiString& getIfFalseBlock();


  virtual ~BrIfInstr();

};
//----------------------------------

//------------- BrInstr ---------------
class BrInstr {
  AnsiString block;
public:
  BrInstr(const AnsiString&);
  virtual const AnsiString& getBlock() const;
  virtual AnsiString& getBlock();


  virtual ~BrInstr();

};
//----------------------------------

//------------- Instr ---------------
class Instr {
  int _type;
  void* _ptr;

  static const int _TypeBinaryOperationInstr;
  static const int _TypeCallInstr;
  static const int _TypeBrInstr;
  static const int _TypeBrIfInstr;
  static const int _TypePrintInstr;

  virtual void init(int, void*);
  virtual void clean();
  Instr();
public:
  Instr(const Instr&);
  virtual Instr& operator=(const Instr&);

  virtual bool isBinaryOperationInstr() const;
  virtual bool isCallInstr() const;
  virtual bool isBrInstr() const;
  virtual bool isBrIfInstr() const;
  virtual bool isPrintInstr() const;

  virtual const BinaryOperation& asBinaryOperationInstr() const;
  virtual BinaryOperation& asBinaryOperationInstr();
  virtual const CallInstr& asCallInstr() const;
  virtual CallInstr& asCallInstr();
  virtual const BrInstr& asBrInstr() const;
  virtual BrInstr& asBrInstr();
  virtual const BrIfInstr& asBrIfInstr() const;
  virtual BrIfInstr& asBrIfInstr();
  virtual const Register& asPrintInstr() const;
  virtual Register& asPrintInstr();


  virtual ~Instr();

  static Instr createBinaryOperationInstr(const BinaryOperation&);
  static Instr createCallInstr(const CallInstr&);
  static Instr createBrInstr(const BrInstr&);
  static Instr createBrIfInstr(const BrIfInstr&);
  static Instr createPrintInstr(const Register&);

};
//----------------------------------

//------------- InstrArray ---------------
#include "DynSet.h"


class InstrArray : public DynSet<Instr> {
public:
  InstrArray();


  virtual ~InstrArray();

};
//----------------------------------

//------------- LLVMBlock ---------------
class LLVMBlock {
  AnsiString name;
  InstrArray body;
public:
  LLVMBlock(const AnsiString&, const InstrArray&);
  virtual const AnsiString& getName() const;
  virtual const InstrArray& getBody() const;
  virtual AnsiString& getName();
  virtual InstrArray& getBody();


  virtual ~LLVMBlock();

};
//----------------------------------

//------------- LLVMBlockArray ---------------
#include "DynSet.h"


class LLVMBlockArray : public DynSet<LLVMBlock> {
public:
  LLVMBlockArray();


  virtual ~LLVMBlockArray();

};
//----------------------------------

//------------- LLVMFunctionArgument ---------------
class LLVMFunctionArgument {
  RegisterKind type;
  AnsiString name;
public:
  LLVMFunctionArgument(const RegisterKind&, const AnsiString&);
  virtual const RegisterKind& getType() const;
  virtual const AnsiString& getName() const;
  virtual RegisterKind& getType();
  virtual AnsiString& getName();


  virtual ~LLVMFunctionArgument();

};
//----------------------------------

//------------- LLVMFunctionArgumentArray ---------------
#include "DynSet.h"


class LLVMFunctionArgumentArray : public DynSet<LLVMFunctionArgument> {
public:
  LLVMFunctionArgumentArray();


  virtual ~LLVMFunctionArgumentArray();

};
//----------------------------------

//------------- LLVMFunction ---------------
class LLVMFunction {
  AnsiString name;
  RegisterKind type;
  LLVMFunctionArgumentArray args;
  LLVMBlockArray blocks;
public:
  LLVMFunction(const AnsiString&, const RegisterKind&, const LLVMFunctionArgumentArray&, const LLVMBlockArray&);
  virtual const AnsiString& getName() const;
  virtual const RegisterKind& getType() const;
  virtual const LLVMFunctionArgumentArray& getArgs() const;
  virtual const LLVMBlockArray& getBlocks() const;
  virtual AnsiString& getName();
  virtual RegisterKind& getType();
  virtual LLVMFunctionArgumentArray& getArgs();
  virtual LLVMBlockArray& getBlocks();


  virtual ~LLVMFunction();

};
//----------------------------------

//------------- LLVMProgram ---------------
#include "DynSet.h"


class LLVMProgram : public DynSet<LLVMFunction> {
public:
  LLVMProgram();


  virtual ~LLVMProgram();

};
//----------------------------------

#endif
