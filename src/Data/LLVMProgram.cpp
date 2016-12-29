
#include "LLVMProgram.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Register ---------------
//----------------------------------

//------------- RegisterKind ---------------
//----------------------------------

//------------- Registers ---------------
//----------------------------------

//------------- BinaryOperationArgument ---------------
const int BinaryOperationArgument::_TypeRegister = 0;
const int BinaryOperationArgument::_TypeNumber = 1;
void BinaryOperationArgument::init(int type, void* ptr) {
  if (type==_TypeRegister) {
    _type = type;
    _ptr = new Register(*(Register*) ptr);
  } else if (type==_TypeNumber) {
    _type = type;
    _ptr = new AnsiString(*(AnsiString*) ptr);
  }
}
void BinaryOperationArgument::clean() {
  if (_type==_TypeRegister) {
    _type = -1;
    delete (Register*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeNumber) {
    _type = -1;
    delete (AnsiString*) _ptr;
    _ptr = 0;
  }
}
BinaryOperationArgument::BinaryOperationArgument() : _type(-1), _ptr(0) {
}
BinaryOperationArgument::BinaryOperationArgument(const BinaryOperationArgument& _value) {
  init(_value._type, _value._ptr);
}
BinaryOperationArgument& BinaryOperationArgument::operator=(const BinaryOperationArgument& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool BinaryOperationArgument::isRegister() const {
  return _type==_TypeRegister;
}
bool BinaryOperationArgument::isNumber() const {
  return _type==_TypeNumber;
}
const Register& BinaryOperationArgument::asRegister() const {
  if (_type!=_TypeRegister)
    throw Exception("BinaryOperationArgument::asRegister");
  return *(Register*) _ptr;
}
Register& BinaryOperationArgument::asRegister() {
  if (_type!=_TypeRegister)
    throw Exception("BinaryOperationArgument::asRegister");
  return *(Register*) _ptr;
}
const AnsiString& BinaryOperationArgument::asNumber() const {
  if (_type!=_TypeNumber)
    throw Exception("BinaryOperationArgument::asNumber");
  return *(AnsiString*) _ptr;
}
AnsiString& BinaryOperationArgument::asNumber() {
  if (_type!=_TypeNumber)
    throw Exception("BinaryOperationArgument::asNumber");
  return *(AnsiString*) _ptr;
}


BinaryOperationArgument::~BinaryOperationArgument() {
  clean();
}
BinaryOperationArgument BinaryOperationArgument::createRegister(const Register& _param) {
  BinaryOperationArgument _value;
  _value._type = _TypeRegister;
  _value._ptr = new Register(_param);
  return _value;
}
BinaryOperationArgument BinaryOperationArgument::createNumber(const AnsiString& _param) {
  BinaryOperationArgument _value;
  _value._type = _TypeNumber;
  _value._ptr = new AnsiString(_param);
  return _value;
}


//----------------------------------

//------------- BinaryOperator ---------------
const int BinaryOperator::_TypeAdd = 0;
const int BinaryOperator::_TypeSub = 1;
const int BinaryOperator::_TypeDiv = 2;
const int BinaryOperator::_TypeMul = 3;
const int BinaryOperator::_TypeMod = 4;
const int BinaryOperator::_TypeLth = 5;
const int BinaryOperator::_TypeLe = 6;
const int BinaryOperator::_TypeGth = 7;
const int BinaryOperator::_TypeGe = 8;
const int BinaryOperator::_TypeEqu = 9;
const int BinaryOperator::_TypeNe = 10;
void BinaryOperator::init(int type, void* ptr) {
  if (type==_TypeAdd) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeSub) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeDiv) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeMul) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeMod) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeLth) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeLe) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeGth) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeGe) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeEqu) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeNe) {
    _type = type;
    _ptr = 0;
  }
}
void BinaryOperator::clean() {
  if (_type==_TypeAdd) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeSub) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeDiv) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeMul) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeMod) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeLth) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeLe) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeGth) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeGe) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeEqu) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  } else if (_type==_TypeNe) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BinaryOperator::clean()");
  }
}
BinaryOperator::BinaryOperator() : _type(-1), _ptr(0) {
}
BinaryOperator::BinaryOperator(const BinaryOperator& _value) {
  init(_value._type, _value._ptr);
}
BinaryOperator& BinaryOperator::operator=(const BinaryOperator& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool BinaryOperator::isAdd() const {
  return _type==_TypeAdd;
}
bool BinaryOperator::isSub() const {
  return _type==_TypeSub;
}
bool BinaryOperator::isDiv() const {
  return _type==_TypeDiv;
}
bool BinaryOperator::isMul() const {
  return _type==_TypeMul;
}
bool BinaryOperator::isMod() const {
  return _type==_TypeMod;
}
bool BinaryOperator::isLth() const {
  return _type==_TypeLth;
}
bool BinaryOperator::isLe() const {
  return _type==_TypeLe;
}
bool BinaryOperator::isGth() const {
  return _type==_TypeGth;
}
bool BinaryOperator::isGe() const {
  return _type==_TypeGe;
}
bool BinaryOperator::isEqu() const {
  return _type==_TypeEqu;
}
bool BinaryOperator::isNe() const {
  return _type==_TypeNe;
}


BinaryOperator::~BinaryOperator() {
  clean();
}
BinaryOperator BinaryOperator::createAdd() {
  BinaryOperator _value;
  _value._type = _TypeAdd;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createSub() {
  BinaryOperator _value;
  _value._type = _TypeSub;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createDiv() {
  BinaryOperator _value;
  _value._type = _TypeDiv;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createMul() {
  BinaryOperator _value;
  _value._type = _TypeMul;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createMod() {
  BinaryOperator _value;
  _value._type = _TypeMod;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createLth() {
  BinaryOperator _value;
  _value._type = _TypeLth;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createLe() {
  BinaryOperator _value;
  _value._type = _TypeLe;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createGth() {
  BinaryOperator _value;
  _value._type = _TypeGth;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createGe() {
  BinaryOperator _value;
  _value._type = _TypeGe;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createEqu() {
  BinaryOperator _value;
  _value._type = _TypeEqu;
  _value._ptr = 0;
  return _value;
}
BinaryOperator BinaryOperator::createNe() {
  BinaryOperator _value;
  _value._type = _TypeNe;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- BinaryOperation ---------------
BinaryOperation::BinaryOperation(const Register& _outReg, const BinaryOperationArgument& _lArg, const BinaryOperationArgument& _rArg, const BinaryOperator& _bop) : outReg(_outReg), lArg(_lArg), rArg(_rArg), bop(_bop) {
}
const Register& BinaryOperation::getOutReg() const {
  return outReg;
}
Register& BinaryOperation::getOutReg() {
  return outReg;
}
const BinaryOperationArgument& BinaryOperation::getLArg() const {
  return lArg;
}
BinaryOperationArgument& BinaryOperation::getLArg() {
  return lArg;
}
const BinaryOperationArgument& BinaryOperation::getRArg() const {
  return rArg;
}
BinaryOperationArgument& BinaryOperation::getRArg() {
  return rArg;
}
const BinaryOperator& BinaryOperation::getBop() const {
  return bop;
}
BinaryOperator& BinaryOperation::getBop() {
  return bop;
}
BinaryOperation::~BinaryOperation() {
}
//----------------------------------

//------------- CallInstr ---------------
CallInstr::CallInstr(const RegisterKind& _retType, const AnsiString& _function, const Registers& _args) : retType(_retType), function(_function), args(_args) {
}
const RegisterKind& CallInstr::getRetType() const {
  return retType;
}
RegisterKind& CallInstr::getRetType() {
  return retType;
}
const AnsiString& CallInstr::getFunction() const {
  return function;
}
AnsiString& CallInstr::getFunction() {
  return function;
}
const Registers& CallInstr::getArgs() const {
  return args;
}
Registers& CallInstr::getArgs() {
  return args;
}
CallInstr::~CallInstr() {
}
//----------------------------------

//------------- BrIfInstr ---------------
BrIfInstr::BrIfInstr(const Register& _cond, const AnsiString& _ifTrueBlock, const AnsiString& _ifFalseBlock) : cond(_cond), ifTrueBlock(_ifTrueBlock), ifFalseBlock(_ifFalseBlock) {
}
const Register& BrIfInstr::getCond() const {
  return cond;
}
Register& BrIfInstr::getCond() {
  return cond;
}
const AnsiString& BrIfInstr::getIfTrueBlock() const {
  return ifTrueBlock;
}
AnsiString& BrIfInstr::getIfTrueBlock() {
  return ifTrueBlock;
}
const AnsiString& BrIfInstr::getIfFalseBlock() const {
  return ifFalseBlock;
}
AnsiString& BrIfInstr::getIfFalseBlock() {
  return ifFalseBlock;
}
BrIfInstr::~BrIfInstr() {
}
//----------------------------------

//------------- BrInstr ---------------
BrInstr::BrInstr(const AnsiString& _block) : block(_block) {
}
const AnsiString& BrInstr::getBlock() const {
  return block;
}
AnsiString& BrInstr::getBlock() {
  return block;
}
BrInstr::~BrInstr() {
}
//----------------------------------

//------------- PhiCase ---------------
PhiCase::PhiCase(const Register& _value, const AnsiString& _label) : value(_value), label(_label) {
}
const Register& PhiCase::getValue() const {
  return value;
}
Register& PhiCase::getValue() {
  return value;
}
const AnsiString& PhiCase::getLabel() const {
  return label;
}
AnsiString& PhiCase::getLabel() {
  return label;
}
PhiCase::~PhiCase() {
}
//----------------------------------

//------------- PhiCases ---------------
PhiCases::PhiCases() {
}
PhiCases::~PhiCases() {
}
//----------------------------------

//------------- PhiInstr ---------------
PhiInstr::PhiInstr(const AnsiString& _ident, const Register& _ret, const PhiCases& _caseses) : ident(_ident), ret(_ret), caseses(_caseses) {
}
const AnsiString& PhiInstr::getIdent() const {
  return ident;
}
AnsiString& PhiInstr::getIdent() {
  return ident;
}
const Register& PhiInstr::getRet() const {
  return ret;
}
Register& PhiInstr::getRet() {
  return ret;
}
const PhiCases& PhiInstr::getCaseses() const {
  return caseses;
}
PhiCases& PhiInstr::getCaseses() {
  return caseses;
}
PhiInstr::~PhiInstr() {
}
//----------------------------------

//------------- Instr ---------------
const int Instr::_TypeBinaryOperationInstr = 0;
const int Instr::_TypeCallInstr = 1;
const int Instr::_TypePhiInstr = 2;
const int Instr::_TypeReturnInstr = 3;
const int Instr::_TypeBrInstr = 4;
const int Instr::_TypeBrIfInstr = 5;
const int Instr::_TypePrintInstr = 6;
void Instr::init(int type, void* ptr) {
  if (type==_TypeBinaryOperationInstr) {
    _type = type;
    _ptr = new BinaryOperation(*(BinaryOperation*) ptr);
  } else if (type==_TypeCallInstr) {
    _type = type;
    _ptr = new CallInstr(*(CallInstr*) ptr);
  } else if (type==_TypePhiInstr) {
    _type = type;
    _ptr = new PhiInstr(*(PhiInstr*) ptr);
  } else if (type==_TypeReturnInstr) {
    _type = type;
    _ptr = new Register(*(Register*) ptr);
  } else if (type==_TypeBrInstr) {
    _type = type;
    _ptr = new BrInstr(*(BrInstr*) ptr);
  } else if (type==_TypeBrIfInstr) {
    _type = type;
    _ptr = new BrIfInstr(*(BrIfInstr*) ptr);
  } else if (type==_TypePrintInstr) {
    _type = type;
    _ptr = new Register(*(Register*) ptr);
  }
}
void Instr::clean() {
  if (_type==_TypeBinaryOperationInstr) {
    _type = -1;
    delete (BinaryOperation*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeCallInstr) {
    _type = -1;
    delete (CallInstr*) _ptr;
    _ptr = 0;
  } else if (_type==_TypePhiInstr) {
    _type = -1;
    delete (PhiInstr*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeReturnInstr) {
    _type = -1;
    delete (Register*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeBrInstr) {
    _type = -1;
    delete (BrInstr*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeBrIfInstr) {
    _type = -1;
    delete (BrIfInstr*) _ptr;
    _ptr = 0;
  } else if (_type==_TypePrintInstr) {
    _type = -1;
    delete (Register*) _ptr;
    _ptr = 0;
  }
}
Instr::Instr() : _type(-1), _ptr(0) {
}
Instr::Instr(const Instr& _value) {
  init(_value._type, _value._ptr);
}
Instr& Instr::operator=(const Instr& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool Instr::isBinaryOperationInstr() const {
  return _type==_TypeBinaryOperationInstr;
}
bool Instr::isCallInstr() const {
  return _type==_TypeCallInstr;
}
bool Instr::isPhiInstr() const {
  return _type==_TypePhiInstr;
}
bool Instr::isReturnInstr() const {
  return _type==_TypeReturnInstr;
}
bool Instr::isBrInstr() const {
  return _type==_TypeBrInstr;
}
bool Instr::isBrIfInstr() const {
  return _type==_TypeBrIfInstr;
}
bool Instr::isPrintInstr() const {
  return _type==_TypePrintInstr;
}
const BinaryOperation& Instr::asBinaryOperationInstr() const {
  if (_type!=_TypeBinaryOperationInstr)
    throw Exception("Instr::asBinaryOperationInstr");
  return *(BinaryOperation*) _ptr;
}
BinaryOperation& Instr::asBinaryOperationInstr() {
  if (_type!=_TypeBinaryOperationInstr)
    throw Exception("Instr::asBinaryOperationInstr");
  return *(BinaryOperation*) _ptr;
}
const CallInstr& Instr::asCallInstr() const {
  if (_type!=_TypeCallInstr)
    throw Exception("Instr::asCallInstr");
  return *(CallInstr*) _ptr;
}
CallInstr& Instr::asCallInstr() {
  if (_type!=_TypeCallInstr)
    throw Exception("Instr::asCallInstr");
  return *(CallInstr*) _ptr;
}
const PhiInstr& Instr::asPhiInstr() const {
  if (_type!=_TypePhiInstr)
    throw Exception("Instr::asPhiInstr");
  return *(PhiInstr*) _ptr;
}
PhiInstr& Instr::asPhiInstr() {
  if (_type!=_TypePhiInstr)
    throw Exception("Instr::asPhiInstr");
  return *(PhiInstr*) _ptr;
}
const Register& Instr::asReturnInstr() const {
  if (_type!=_TypeReturnInstr)
    throw Exception("Instr::asReturnInstr");
  return *(Register*) _ptr;
}
Register& Instr::asReturnInstr() {
  if (_type!=_TypeReturnInstr)
    throw Exception("Instr::asReturnInstr");
  return *(Register*) _ptr;
}
const BrInstr& Instr::asBrInstr() const {
  if (_type!=_TypeBrInstr)
    throw Exception("Instr::asBrInstr");
  return *(BrInstr*) _ptr;
}
BrInstr& Instr::asBrInstr() {
  if (_type!=_TypeBrInstr)
    throw Exception("Instr::asBrInstr");
  return *(BrInstr*) _ptr;
}
const BrIfInstr& Instr::asBrIfInstr() const {
  if (_type!=_TypeBrIfInstr)
    throw Exception("Instr::asBrIfInstr");
  return *(BrIfInstr*) _ptr;
}
BrIfInstr& Instr::asBrIfInstr() {
  if (_type!=_TypeBrIfInstr)
    throw Exception("Instr::asBrIfInstr");
  return *(BrIfInstr*) _ptr;
}
const Register& Instr::asPrintInstr() const {
  if (_type!=_TypePrintInstr)
    throw Exception("Instr::asPrintInstr");
  return *(Register*) _ptr;
}
Register& Instr::asPrintInstr() {
  if (_type!=_TypePrintInstr)
    throw Exception("Instr::asPrintInstr");
  return *(Register*) _ptr;
}


Instr::~Instr() {
  clean();
}
Instr Instr::createBinaryOperationInstr(const BinaryOperation& _param) {
  Instr _value;
  _value._type = _TypeBinaryOperationInstr;
  _value._ptr = new BinaryOperation(_param);
  return _value;
}
Instr Instr::createCallInstr(const CallInstr& _param) {
  Instr _value;
  _value._type = _TypeCallInstr;
  _value._ptr = new CallInstr(_param);
  return _value;
}
Instr Instr::createPhiInstr(const PhiInstr& _param) {
  Instr _value;
  _value._type = _TypePhiInstr;
  _value._ptr = new PhiInstr(_param);
  return _value;
}
Instr Instr::createReturnInstr(const Register& _param) {
  Instr _value;
  _value._type = _TypeReturnInstr;
  _value._ptr = new Register(_param);
  return _value;
}
Instr Instr::createBrInstr(const BrInstr& _param) {
  Instr _value;
  _value._type = _TypeBrInstr;
  _value._ptr = new BrInstr(_param);
  return _value;
}
Instr Instr::createBrIfInstr(const BrIfInstr& _param) {
  Instr _value;
  _value._type = _TypeBrIfInstr;
  _value._ptr = new BrIfInstr(_param);
  return _value;
}
Instr Instr::createPrintInstr(const Register& _param) {
  Instr _value;
  _value._type = _TypePrintInstr;
  _value._ptr = new Register(_param);
  return _value;
}


//----------------------------------

//------------- InstrArray ---------------
InstrArray::InstrArray() {
}
InstrArray::~InstrArray() {
}
//----------------------------------

//------------- LLVMBlock ---------------
LLVMBlock::LLVMBlock(const AnsiString& _name, const InstrArray& _body) : name(_name), body(_body) {
}
const AnsiString& LLVMBlock::getName() const {
  return name;
}
AnsiString& LLVMBlock::getName() {
  return name;
}
const InstrArray& LLVMBlock::getBody() const {
  return body;
}
InstrArray& LLVMBlock::getBody() {
  return body;
}
LLVMBlock::~LLVMBlock() {
}
//----------------------------------

//------------- LLVMBlockArray ---------------
LLVMBlockArray::LLVMBlockArray() {
}
LLVMBlockArray::~LLVMBlockArray() {
}
//----------------------------------

//------------- LLVMFunctionArgument ---------------
LLVMFunctionArgument::LLVMFunctionArgument(const Register& _reg, const AnsiString& _name) : reg(_reg), name(_name) {
}
const Register& LLVMFunctionArgument::getReg() const {
  return reg;
}
Register& LLVMFunctionArgument::getReg() {
  return reg;
}
const AnsiString& LLVMFunctionArgument::getName() const {
  return name;
}
AnsiString& LLVMFunctionArgument::getName() {
  return name;
}
LLVMFunctionArgument::~LLVMFunctionArgument() {
}
//----------------------------------

//------------- LLVMFunctionArgumentArray ---------------
LLVMFunctionArgumentArray::LLVMFunctionArgumentArray() {
}
LLVMFunctionArgumentArray::~LLVMFunctionArgumentArray() {
}
//----------------------------------

//------------- LLVMFunction ---------------
LLVMFunction::LLVMFunction(const AnsiString& _name, const RegisterKind& _type, const LLVMFunctionArgumentArray& _args, const LLVMBlockArray& _blocks) : name(_name), type(_type), args(_args), blocks(_blocks) {
}
const AnsiString& LLVMFunction::getName() const {
  return name;
}
AnsiString& LLVMFunction::getName() {
  return name;
}
const RegisterKind& LLVMFunction::getType() const {
  return type;
}
RegisterKind& LLVMFunction::getType() {
  return type;
}
const LLVMFunctionArgumentArray& LLVMFunction::getArgs() const {
  return args;
}
LLVMFunctionArgumentArray& LLVMFunction::getArgs() {
  return args;
}
const LLVMBlockArray& LLVMFunction::getBlocks() const {
  return blocks;
}
LLVMBlockArray& LLVMFunction::getBlocks() {
  return blocks;
}
LLVMFunction::~LLVMFunction() {
}
//----------------------------------

//------------- LLVMProgram ---------------
LLVMProgram::LLVMProgram() {
}
LLVMProgram::~LLVMProgram() {
}
//----------------------------------

