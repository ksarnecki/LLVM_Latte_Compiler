
#include "LLVMProgram.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Register ---------------
//----------------------------------

//------------- BinaryOperationArgument ---------------
const int BinaryOperationArgument::_TypeRegister = 0;
const int BinaryOperationArgument::_TypeInteger = 1;
void BinaryOperationArgument::init(int type, void* ptr) {
  if (type==_TypeRegister) {
    _type = type;
    _ptr = new Register(*(Register*) ptr);
  } else if (type==_TypeInteger) {
    _type = type;
    _ptr = new int(*(int*) ptr);
  }
}
void BinaryOperationArgument::clean() {
  if (_type==_TypeRegister) {
    _type = -1;
    delete (Register*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeInteger) {
    _type = -1;
    delete (int*) _ptr;
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
bool BinaryOperationArgument::isInteger() const {
  return _type==_TypeInteger;
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
const int& BinaryOperationArgument::asInteger() const {
  if (_type!=_TypeInteger)
    throw Exception("BinaryOperationArgument::asInteger");
  return *(int*) _ptr;
}
int& BinaryOperationArgument::asInteger() {
  if (_type!=_TypeInteger)
    throw Exception("BinaryOperationArgument::asInteger");
  return *(int*) _ptr;
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
BinaryOperationArgument BinaryOperationArgument::createInteger(const int& _param) {
  BinaryOperationArgument _value;
  _value._type = _TypeInteger;
  _value._ptr = new int(_param);
  return _value;
}


//----------------------------------

//------------- BinaryOperator ---------------
const int BinaryOperator::_TypeAdd = 0;
const int BinaryOperator::_TypeSub = 1;
const int BinaryOperator::_TypeDiv = 2;
const int BinaryOperator::_TypeMul = 3;
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

//------------- Instr ---------------
const int Instr::_TypeBinaryOperationInstr = 0;
const int Instr::_TypePrintInstr = 1;
void Instr::init(int type, void* ptr) {
  if (type==_TypeBinaryOperationInstr) {
    _type = type;
    _ptr = new BinaryOperation(*(BinaryOperation*) ptr);
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
Instr Instr::createPrintInstr(const Register& _param) {
  Instr _value;
  _value._type = _TypePrintInstr;
  _value._ptr = new Register(_param);
  return _value;
}


//----------------------------------

//------------- LLVMProgram ---------------
LLVMProgram::LLVMProgram() {
}
LLVMProgram::~LLVMProgram() {
}
//----------------------------------

