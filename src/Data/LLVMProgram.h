#ifndef _LLVMPROGRAM_GEN_H_
#define _LLVMPROGRAM_GEN_H_
#include "DynSet.h"
#include <stdio.h>
#include <stdlib.h>
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

  virtual AnsiString toJSON() const;
  static BinaryOperationArgument fromJSON(AnsiString);

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


  virtual AnsiString toJSON() const;
  static BinaryOperator fromJSON(AnsiString);

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

  virtual AnsiString toJSON() const;
  static BinaryOperation fromJSON(AnsiString);

  virtual ~BinaryOperation();

};
//----------------------------------

//------------- CallInstrRet ---------------
class CallInstrRet {
  int _type;
  void* _ptr;

  static const int _TypeVoid;
  static const int _TypeObj;

  virtual void init(int, void*);
  virtual void clean();
  CallInstrRet();
public:
  CallInstrRet(const CallInstrRet&);
  virtual CallInstrRet& operator=(const CallInstrRet&);

  virtual bool isVoid() const;
  virtual bool isObj() const;

  virtual const Register& asObj() const;
  virtual Register& asObj();

  virtual AnsiString toJSON() const;
  static CallInstrRet fromJSON(AnsiString);

  virtual ~CallInstrRet();

  static CallInstrRet createVoid();
  static CallInstrRet createObj(const Register&);

};
//----------------------------------

//------------- CallInstr ---------------
class CallInstr {
  CallInstrRet retType;
  AnsiString function;
  Registers args;
public:
  CallInstr(const CallInstrRet&, const AnsiString&, const Registers&);
  virtual const CallInstrRet& getRetType() const;
  virtual const AnsiString& getFunction() const;
  virtual const Registers& getArgs() const;
  virtual CallInstrRet& getRetType();
  virtual AnsiString& getFunction();
  virtual Registers& getArgs();

  virtual AnsiString toJSON() const;
  static CallInstr fromJSON(AnsiString);

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

  virtual AnsiString toJSON() const;
  static BrIfInstr fromJSON(AnsiString);

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

  virtual AnsiString toJSON() const;
  static BrInstr fromJSON(AnsiString);

  virtual ~BrInstr();

};
//----------------------------------

//------------- PhiCase ---------------
class PhiCase {
  Register value;
  AnsiString label;
public:
  PhiCase(const Register&, const AnsiString&);
  virtual const Register& getValue() const;
  virtual const AnsiString& getLabel() const;
  virtual Register& getValue();
  virtual AnsiString& getLabel();

  virtual AnsiString toJSON() const;
  static PhiCase fromJSON(AnsiString);

  virtual ~PhiCase();

};
//----------------------------------

//------------- PhiCases ---------------
#include "DynSet.h"


class PhiCases : public DynSet<PhiCase> {
public:
  PhiCases();

  virtual AnsiString toJSON() const;
  static PhiCases fromJSON(AnsiString);

  virtual ~PhiCases();

};
//----------------------------------

//------------- PhiInstr ---------------
class PhiInstr {
  AnsiString ident;
  Register ret;
  PhiCases caseses;
public:
  PhiInstr(const AnsiString&, const Register&, const PhiCases&);
  virtual const AnsiString& getIdent() const;
  virtual const Register& getRet() const;
  virtual const PhiCases& getCaseses() const;
  virtual AnsiString& getIdent();
  virtual Register& getRet();
  virtual PhiCases& getCaseses();

  virtual AnsiString toJSON() const;
  static PhiInstr fromJSON(AnsiString);

  virtual ~PhiInstr();

};
//----------------------------------

//------------- Instr ---------------
class Instr {
  int _type;
  void* _ptr;

  static const int _TypeBinaryOperationInstr;
  static const int _TypeCallInstr;
  static const int _TypePhiInstr;
  static const int _TypeReturnInstr;
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
  virtual bool isPhiInstr() const;
  virtual bool isReturnInstr() const;
  virtual bool isBrInstr() const;
  virtual bool isBrIfInstr() const;
  virtual bool isPrintInstr() const;

  virtual const BinaryOperation& asBinaryOperationInstr() const;
  virtual BinaryOperation& asBinaryOperationInstr();
  virtual const CallInstr& asCallInstr() const;
  virtual CallInstr& asCallInstr();
  virtual const PhiInstr& asPhiInstr() const;
  virtual PhiInstr& asPhiInstr();
  virtual const Register& asReturnInstr() const;
  virtual Register& asReturnInstr();
  virtual const BrInstr& asBrInstr() const;
  virtual BrInstr& asBrInstr();
  virtual const BrIfInstr& asBrIfInstr() const;
  virtual BrIfInstr& asBrIfInstr();
  virtual const Register& asPrintInstr() const;
  virtual Register& asPrintInstr();

  virtual AnsiString toJSON() const;
  static Instr fromJSON(AnsiString);

  virtual ~Instr();

  static Instr createBinaryOperationInstr(const BinaryOperation&);
  static Instr createCallInstr(const CallInstr&);
  static Instr createPhiInstr(const PhiInstr&);
  static Instr createReturnInstr(const Register&);
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

  virtual AnsiString toJSON() const;
  static InstrArray fromJSON(AnsiString);

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

  virtual AnsiString toJSON() const;
  static LLVMBlock fromJSON(AnsiString);

  virtual ~LLVMBlock();

};
//----------------------------------

//------------- LLVMBlockArray ---------------
#include "DynSet.h"


class LLVMBlockArray : public DynSet<LLVMBlock> {
public:
  LLVMBlockArray();

  virtual AnsiString toJSON() const;
  static LLVMBlockArray fromJSON(AnsiString);

  virtual ~LLVMBlockArray();

};
//----------------------------------

//------------- LLVMFunctionArgument ---------------
class LLVMFunctionArgument {
  Register reg;
  AnsiString name;
public:
  LLVMFunctionArgument(const Register&, const AnsiString&);
  virtual const Register& getReg() const;
  virtual const AnsiString& getName() const;
  virtual Register& getReg();
  virtual AnsiString& getName();

  virtual AnsiString toJSON() const;
  static LLVMFunctionArgument fromJSON(AnsiString);

  virtual ~LLVMFunctionArgument();

};
//----------------------------------

//------------- LLVMFunctionArgumentArray ---------------
#include "DynSet.h"


class LLVMFunctionArgumentArray : public DynSet<LLVMFunctionArgument> {
public:
  LLVMFunctionArgumentArray();

  virtual AnsiString toJSON() const;
  static LLVMFunctionArgumentArray fromJSON(AnsiString);

  virtual ~LLVMFunctionArgumentArray();

};
//----------------------------------

//------------- LLVMFunctionType ---------------
class LLVMFunctionType {
  int _type;
  void* _ptr;

  static const int _TypeVoid;
  static const int _TypeObj;

  virtual void init(int, void*);
  virtual void clean();
  LLVMFunctionType();
public:
  LLVMFunctionType(const LLVMFunctionType&);
  virtual LLVMFunctionType& operator=(const LLVMFunctionType&);

  virtual bool isVoid() const;
  virtual bool isObj() const;

  virtual const RegisterKind& asObj() const;
  virtual RegisterKind& asObj();

  virtual AnsiString toJSON() const;
  static LLVMFunctionType fromJSON(AnsiString);

  virtual ~LLVMFunctionType();

  static LLVMFunctionType createVoid();
  static LLVMFunctionType createObj(const RegisterKind&);

};
//----------------------------------

//------------- LLVMFunction ---------------
class LLVMFunction {
  AnsiString name;
  LLVMFunctionType type;
  LLVMFunctionArgumentArray args;
  LLVMBlockArray blocks;
public:
  LLVMFunction(const AnsiString&, const LLVMFunctionType&, const LLVMFunctionArgumentArray&, const LLVMBlockArray&);
  virtual const AnsiString& getName() const;
  virtual const LLVMFunctionType& getType() const;
  virtual const LLVMFunctionArgumentArray& getArgs() const;
  virtual const LLVMBlockArray& getBlocks() const;
  virtual AnsiString& getName();
  virtual LLVMFunctionType& getType();
  virtual LLVMFunctionArgumentArray& getArgs();
  virtual LLVMBlockArray& getBlocks();

  virtual AnsiString toJSON() const;
  static LLVMFunction fromJSON(AnsiString);

  virtual ~LLVMFunction();

};
//----------------------------------

//------------- LLVMProgram ---------------
#include "DynSet.h"


class LLVMProgram : public DynSet<LLVMFunction> {
public:
  LLVMProgram();

  virtual AnsiString toJSON() const;
  static LLVMProgram fromJSON(AnsiString);

  virtual ~LLVMProgram();

};
//----------------------------------

#endif
