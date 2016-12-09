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

//------------- BinaryOperationArgument ---------------
class BinaryOperationArgument {
  int _type;
  void* _ptr;

  static const int _TypeRegister;
  static const int _TypeInteger;

  virtual void init(int, void*);
  virtual void clean();
  BinaryOperationArgument();
public:
  BinaryOperationArgument(const BinaryOperationArgument&);
  virtual BinaryOperationArgument& operator=(const BinaryOperationArgument&);

  virtual bool isRegister() const;
  virtual bool isInteger() const;

  virtual const Register& asRegister() const;
  virtual Register& asRegister();
  virtual const int& asInteger() const;
  virtual int& asInteger();


  virtual ~BinaryOperationArgument();

  static BinaryOperationArgument createRegister(const Register&);
  static BinaryOperationArgument createInteger(const int&);

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



  virtual ~BinaryOperator();

  static BinaryOperator createAdd();
  static BinaryOperator createSub();
  static BinaryOperator createDiv();
  static BinaryOperator createMul();

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

//------------- Instr ---------------
class Instr {
  int _type;
  void* _ptr;

  static const int _TypeBinaryOperationInstr;
  static const int _TypePrintInstr;

  virtual void init(int, void*);
  virtual void clean();
  Instr();
public:
  Instr(const Instr&);
  virtual Instr& operator=(const Instr&);

  virtual bool isBinaryOperationInstr() const;
  virtual bool isPrintInstr() const;

  virtual const BinaryOperation& asBinaryOperationInstr() const;
  virtual BinaryOperation& asBinaryOperationInstr();
  virtual const Register& asPrintInstr() const;
  virtual Register& asPrintInstr();


  virtual ~Instr();

  static Instr createBinaryOperationInstr(const BinaryOperation&);
  static Instr createPrintInstr(const Register&);

};
//----------------------------------

//------------- LLVMProgram ---------------
#include "DynSet.h"


class LLVMProgram : public DynSet<Instr> {
public:
  LLVMProgram();


  virtual ~LLVMProgram();

};
//----------------------------------

#endif
