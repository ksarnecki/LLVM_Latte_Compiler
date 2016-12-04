#ifndef _LLVMDATA_GEN_H_
#define _LLVMDATA_GEN_H_
#include "DynSet.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- VariableRegister ---------------
class VariableRegister {
  AnsiString name;
  int version;
public:
  VariableRegister(const AnsiString&, const int&);
  virtual const AnsiString& getName() const;
  virtual const int& getVersion() const;
  virtual AnsiString& getName();
  virtual int& getVersion();


  virtual ~VariableRegister();

};
//----------------------------------

//------------- Register ---------------
class Register {
  int _type;
  void* _ptr;

  static const int _TypeVariableRegister;
  static const int _TypeIntegerRegister;
  static const int _TypeNull;

  virtual void init(int, void*);
  virtual void clean();
  Register();
public:
  Register(const Register&);
  virtual Register& operator=(const Register&);

  virtual bool isVariableRegister() const;
  virtual bool isIntegerRegister() const;
  virtual bool isNull() const;

  virtual const VariableRegister& asVariableRegister() const;
  virtual VariableRegister& asVariableRegister();
  virtual const int& asIntegerRegister() const;
  virtual int& asIntegerRegister();


  virtual ~Register();

  static Register createVariableRegister(const VariableRegister&);
  static Register createIntegerRegister(const int&);
  static Register createNull();

};
//----------------------------------

//------------- Registers ---------------
#include "DynSet.h"


class Registers : public DynSet<Register> {
public:
  Registers();


  virtual ~Registers();

};
//----------------------------------

//------------- LLVMRegisterData ---------------
class LLVMRegisterData {
  Register lastRegister;
  Registers registers;
public:
  LLVMRegisterData(const Register&, const Registers&);
  virtual const Register& getLastRegister() const;
  virtual const Registers& getRegisters() const;
  virtual Register& getLastRegister();
  virtual Registers& getRegisters();


  virtual ~LLVMRegisterData();

};
//----------------------------------

//------------- LLVMBinaryOperationArgument ---------------
class LLVMBinaryOperationArgument {
  int _type;
  void* _ptr;

  static const int _TypeRegister;
  static const int _TypeInteger;

  virtual void init(int, void*);
  virtual void clean();
  LLVMBinaryOperationArgument();
public:
  LLVMBinaryOperationArgument(const LLVMBinaryOperationArgument&);
  virtual LLVMBinaryOperationArgument& operator=(const LLVMBinaryOperationArgument&);

  virtual bool isRegister() const;
  virtual bool isInteger() const;

  virtual const Register& asRegister() const;
  virtual Register& asRegister();
  virtual const int& asInteger() const;
  virtual int& asInteger();


  virtual ~LLVMBinaryOperationArgument();

  static LLVMBinaryOperationArgument createRegister(const Register&);
  static LLVMBinaryOperationArgument createInteger(const int&);

};
//----------------------------------

//------------- LLVMBinaryOperator ---------------
class LLVMBinaryOperator {
  int _type;
  void* _ptr;

  static const int _TypeAdd;
  static const int _TypeSub;
  static const int _TypeDiv;
  static const int _TypeMul;

  virtual void init(int, void*);
  virtual void clean();
  LLVMBinaryOperator();
public:
  LLVMBinaryOperator(const LLVMBinaryOperator&);
  virtual LLVMBinaryOperator& operator=(const LLVMBinaryOperator&);

  virtual bool isAdd() const;
  virtual bool isSub() const;
  virtual bool isDiv() const;
  virtual bool isMul() const;



  virtual ~LLVMBinaryOperator();

  static LLVMBinaryOperator createAdd();
  static LLVMBinaryOperator createSub();
  static LLVMBinaryOperator createDiv();
  static LLVMBinaryOperator createMul();

};
//----------------------------------

//------------- LLVMBinaryOperation ---------------
class LLVMBinaryOperation {
  Register outReg;
  LLVMBinaryOperationArgument lArg;
  LLVMBinaryOperationArgument rArg;
  LLVMBinaryOperator bop;
public:
  LLVMBinaryOperation(const Register&, const LLVMBinaryOperationArgument&, const LLVMBinaryOperationArgument&, const LLVMBinaryOperator&);
  virtual const Register& getOutReg() const;
  virtual const LLVMBinaryOperationArgument& getLArg() const;
  virtual const LLVMBinaryOperationArgument& getRArg() const;
  virtual const LLVMBinaryOperator& getBop() const;
  virtual Register& getOutReg();
  virtual LLVMBinaryOperationArgument& getLArg();
  virtual LLVMBinaryOperationArgument& getRArg();
  virtual LLVMBinaryOperator& getBop();


  virtual ~LLVMBinaryOperation();

};
//----------------------------------

//------------- LLVMInstr ---------------
class LLVMInstr {
  int _type;
  void* _ptr;

  static const int _TypeBinaryOperationInstr;
  static const int _TypePrintInstr;

  virtual void init(int, void*);
  virtual void clean();
  LLVMInstr();
public:
  LLVMInstr(const LLVMInstr&);
  virtual LLVMInstr& operator=(const LLVMInstr&);

  virtual bool isBinaryOperationInstr() const;
  virtual bool isPrintInstr() const;

  virtual const LLVMBinaryOperation& asBinaryOperationInstr() const;
  virtual LLVMBinaryOperation& asBinaryOperationInstr();
  virtual const Register& asPrintInstr() const;
  virtual Register& asPrintInstr();


  virtual ~LLVMInstr();

  static LLVMInstr createBinaryOperationInstr(const LLVMBinaryOperation&);
  static LLVMInstr createPrintInstr(const Register&);

};
//----------------------------------

//------------- LLVMProgram ---------------
#include "DynSet.h"


class LLVMProgram : public DynSet<LLVMInstr> {
public:
  LLVMProgram();


  virtual ~LLVMProgram();

};
//----------------------------------

#endif
