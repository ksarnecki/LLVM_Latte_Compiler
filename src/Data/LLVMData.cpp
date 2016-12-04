
#include "LLVMData.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- VariableRegister ---------------
VariableRegister::VariableRegister(const AnsiString& _name, const int& _version) : name(_name), version(_version) {
}
const AnsiString& VariableRegister::getName() const {
  return name;
}
AnsiString& VariableRegister::getName() {
  return name;
}
const int& VariableRegister::getVersion() const {
  return version;
}
int& VariableRegister::getVersion() {
  return version;
}
VariableRegister::~VariableRegister() {
}
//----------------------------------

//------------- Register ---------------
const int Register::_TypeVariableRegister = 0;
const int Register::_TypeIntegerRegister = 1;
const int Register::_TypeNull = 2;
void Register::init(int type, void* ptr) {
  if (type==_TypeVariableRegister) {
    _type = type;
    _ptr = new VariableRegister(*(VariableRegister*) ptr);
  } else if (type==_TypeIntegerRegister) {
    _type = type;
    _ptr = new int(*(int*) ptr);
  } else if (type==_TypeNull) {
    _type = type;
    _ptr = 0;
  }
}
void Register::clean() {
  if (_type==_TypeVariableRegister) {
    _type = -1;
    delete (VariableRegister*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeIntegerRegister) {
    _type = -1;
    delete (int*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeNull) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("Register::clean()");
  }
}
Register::Register() : _type(-1), _ptr(0) {
}
Register::Register(const Register& _value) {
  init(_value._type, _value._ptr);
}
Register& Register::operator=(const Register& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool Register::isVariableRegister() const {
  return _type==_TypeVariableRegister;
}
bool Register::isIntegerRegister() const {
  return _type==_TypeIntegerRegister;
}
bool Register::isNull() const {
  return _type==_TypeNull;
}
const VariableRegister& Register::asVariableRegister() const {
  if (_type!=_TypeVariableRegister)
    throw Exception("Register::asVariableRegister");
  return *(VariableRegister*) _ptr;
}
VariableRegister& Register::asVariableRegister() {
  if (_type!=_TypeVariableRegister)
    throw Exception("Register::asVariableRegister");
  return *(VariableRegister*) _ptr;
}
const int& Register::asIntegerRegister() const {
  if (_type!=_TypeIntegerRegister)
    throw Exception("Register::asIntegerRegister");
  return *(int*) _ptr;
}
int& Register::asIntegerRegister() {
  if (_type!=_TypeIntegerRegister)
    throw Exception("Register::asIntegerRegister");
  return *(int*) _ptr;
}


Register::~Register() {
  clean();
}
Register Register::createVariableRegister(const VariableRegister& _param) {
  Register _value;
  _value._type = _TypeVariableRegister;
  _value._ptr = new VariableRegister(_param);
  return _value;
}
Register Register::createIntegerRegister(const int& _param) {
  Register _value;
  _value._type = _TypeIntegerRegister;
  _value._ptr = new int(_param);
  return _value;
}
Register Register::createNull() {
  Register _value;
  _value._type = _TypeNull;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- Registers ---------------
Registers::Registers() {
}
Registers::~Registers() {
}
//----------------------------------

//------------- LLVMRegisterData ---------------
LLVMRegisterData::LLVMRegisterData(const Register& _lastRegister, const Registers& _registers) : lastRegister(_lastRegister), registers(_registers) {
}
const Register& LLVMRegisterData::getLastRegister() const {
  return lastRegister;
}
Register& LLVMRegisterData::getLastRegister() {
  return lastRegister;
}
const Registers& LLVMRegisterData::getRegisters() const {
  return registers;
}
Registers& LLVMRegisterData::getRegisters() {
  return registers;
}
LLVMRegisterData::~LLVMRegisterData() {
}
//----------------------------------

//------------- LLVMBinaryOperationArgument ---------------
const int LLVMBinaryOperationArgument::_TypeRegister = 0;
const int LLVMBinaryOperationArgument::_TypeInteger = 1;
void LLVMBinaryOperationArgument::init(int type, void* ptr) {
  if (type==_TypeRegister) {
    _type = type;
    _ptr = new Register(*(Register*) ptr);
  } else if (type==_TypeInteger) {
    _type = type;
    _ptr = new int(*(int*) ptr);
  }
}
void LLVMBinaryOperationArgument::clean() {
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
LLVMBinaryOperationArgument::LLVMBinaryOperationArgument() : _type(-1), _ptr(0) {
}
LLVMBinaryOperationArgument::LLVMBinaryOperationArgument(const LLVMBinaryOperationArgument& _value) {
  init(_value._type, _value._ptr);
}
LLVMBinaryOperationArgument& LLVMBinaryOperationArgument::operator=(const LLVMBinaryOperationArgument& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool LLVMBinaryOperationArgument::isRegister() const {
  return _type==_TypeRegister;
}
bool LLVMBinaryOperationArgument::isInteger() const {
  return _type==_TypeInteger;
}
const Register& LLVMBinaryOperationArgument::asRegister() const {
  if (_type!=_TypeRegister)
    throw Exception("LLVMBinaryOperationArgument::asRegister");
  return *(Register*) _ptr;
}
Register& LLVMBinaryOperationArgument::asRegister() {
  if (_type!=_TypeRegister)
    throw Exception("LLVMBinaryOperationArgument::asRegister");
  return *(Register*) _ptr;
}
const int& LLVMBinaryOperationArgument::asInteger() const {
  if (_type!=_TypeInteger)
    throw Exception("LLVMBinaryOperationArgument::asInteger");
  return *(int*) _ptr;
}
int& LLVMBinaryOperationArgument::asInteger() {
  if (_type!=_TypeInteger)
    throw Exception("LLVMBinaryOperationArgument::asInteger");
  return *(int*) _ptr;
}


LLVMBinaryOperationArgument::~LLVMBinaryOperationArgument() {
  clean();
}
LLVMBinaryOperationArgument LLVMBinaryOperationArgument::createRegister(const Register& _param) {
  LLVMBinaryOperationArgument _value;
  _value._type = _TypeRegister;
  _value._ptr = new Register(_param);
  return _value;
}
LLVMBinaryOperationArgument LLVMBinaryOperationArgument::createInteger(const int& _param) {
  LLVMBinaryOperationArgument _value;
  _value._type = _TypeInteger;
  _value._ptr = new int(_param);
  return _value;
}


//----------------------------------

//------------- LLVMBinaryOperator ---------------
const int LLVMBinaryOperator::_TypeAdd = 0;
const int LLVMBinaryOperator::_TypeSub = 1;
const int LLVMBinaryOperator::_TypeDiv = 2;
const int LLVMBinaryOperator::_TypeMul = 3;
void LLVMBinaryOperator::init(int type, void* ptr) {
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
void LLVMBinaryOperator::clean() {
  if (_type==_TypeAdd) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("LLVMBinaryOperator::clean()");
  } else if (_type==_TypeSub) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("LLVMBinaryOperator::clean()");
  } else if (_type==_TypeDiv) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("LLVMBinaryOperator::clean()");
  } else if (_type==_TypeMul) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("LLVMBinaryOperator::clean()");
  }
}
LLVMBinaryOperator::LLVMBinaryOperator() : _type(-1), _ptr(0) {
}
LLVMBinaryOperator::LLVMBinaryOperator(const LLVMBinaryOperator& _value) {
  init(_value._type, _value._ptr);
}
LLVMBinaryOperator& LLVMBinaryOperator::operator=(const LLVMBinaryOperator& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool LLVMBinaryOperator::isAdd() const {
  return _type==_TypeAdd;
}
bool LLVMBinaryOperator::isSub() const {
  return _type==_TypeSub;
}
bool LLVMBinaryOperator::isDiv() const {
  return _type==_TypeDiv;
}
bool LLVMBinaryOperator::isMul() const {
  return _type==_TypeMul;
}


LLVMBinaryOperator::~LLVMBinaryOperator() {
  clean();
}
LLVMBinaryOperator LLVMBinaryOperator::createAdd() {
  LLVMBinaryOperator _value;
  _value._type = _TypeAdd;
  _value._ptr = 0;
  return _value;
}
LLVMBinaryOperator LLVMBinaryOperator::createSub() {
  LLVMBinaryOperator _value;
  _value._type = _TypeSub;
  _value._ptr = 0;
  return _value;
}
LLVMBinaryOperator LLVMBinaryOperator::createDiv() {
  LLVMBinaryOperator _value;
  _value._type = _TypeDiv;
  _value._ptr = 0;
  return _value;
}
LLVMBinaryOperator LLVMBinaryOperator::createMul() {
  LLVMBinaryOperator _value;
  _value._type = _TypeMul;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- LLVMBinaryOperation ---------------
LLVMBinaryOperation::LLVMBinaryOperation(const Register& _outReg, const LLVMBinaryOperationArgument& _lArg, const LLVMBinaryOperationArgument& _rArg, const LLVMBinaryOperator& _bop) : outReg(_outReg), lArg(_lArg), rArg(_rArg), bop(_bop) {
}
const Register& LLVMBinaryOperation::getOutReg() const {
  return outReg;
}
Register& LLVMBinaryOperation::getOutReg() {
  return outReg;
}
const LLVMBinaryOperationArgument& LLVMBinaryOperation::getLArg() const {
  return lArg;
}
LLVMBinaryOperationArgument& LLVMBinaryOperation::getLArg() {
  return lArg;
}
const LLVMBinaryOperationArgument& LLVMBinaryOperation::getRArg() const {
  return rArg;
}
LLVMBinaryOperationArgument& LLVMBinaryOperation::getRArg() {
  return rArg;
}
const LLVMBinaryOperator& LLVMBinaryOperation::getBop() const {
  return bop;
}
LLVMBinaryOperator& LLVMBinaryOperation::getBop() {
  return bop;
}
LLVMBinaryOperation::~LLVMBinaryOperation() {
}
//----------------------------------

//------------- LLVMInstr ---------------
const int LLVMInstr::_TypeBinaryOperationInstr = 0;
const int LLVMInstr::_TypePrintInstr = 1;
void LLVMInstr::init(int type, void* ptr) {
  if (type==_TypeBinaryOperationInstr) {
    _type = type;
    _ptr = new LLVMBinaryOperation(*(LLVMBinaryOperation*) ptr);
  } else if (type==_TypePrintInstr) {
    _type = type;
    _ptr = new Register(*(Register*) ptr);
  }
}
void LLVMInstr::clean() {
  if (_type==_TypeBinaryOperationInstr) {
    _type = -1;
    delete (LLVMBinaryOperation*) _ptr;
    _ptr = 0;
  } else if (_type==_TypePrintInstr) {
    _type = -1;
    delete (Register*) _ptr;
    _ptr = 0;
  }
}
LLVMInstr::LLVMInstr() : _type(-1), _ptr(0) {
}
LLVMInstr::LLVMInstr(const LLVMInstr& _value) {
  init(_value._type, _value._ptr);
}
LLVMInstr& LLVMInstr::operator=(const LLVMInstr& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool LLVMInstr::isBinaryOperationInstr() const {
  return _type==_TypeBinaryOperationInstr;
}
bool LLVMInstr::isPrintInstr() const {
  return _type==_TypePrintInstr;
}
const LLVMBinaryOperation& LLVMInstr::asBinaryOperationInstr() const {
  if (_type!=_TypeBinaryOperationInstr)
    throw Exception("LLVMInstr::asBinaryOperationInstr");
  return *(LLVMBinaryOperation*) _ptr;
}
LLVMBinaryOperation& LLVMInstr::asBinaryOperationInstr() {
  if (_type!=_TypeBinaryOperationInstr)
    throw Exception("LLVMInstr::asBinaryOperationInstr");
  return *(LLVMBinaryOperation*) _ptr;
}
const Register& LLVMInstr::asPrintInstr() const {
  if (_type!=_TypePrintInstr)
    throw Exception("LLVMInstr::asPrintInstr");
  return *(Register*) _ptr;
}
Register& LLVMInstr::asPrintInstr() {
  if (_type!=_TypePrintInstr)
    throw Exception("LLVMInstr::asPrintInstr");
  return *(Register*) _ptr;
}


LLVMInstr::~LLVMInstr() {
  clean();
}
LLVMInstr LLVMInstr::createBinaryOperationInstr(const LLVMBinaryOperation& _param) {
  LLVMInstr _value;
  _value._type = _TypeBinaryOperationInstr;
  _value._ptr = new LLVMBinaryOperation(_param);
  return _value;
}
LLVMInstr LLVMInstr::createPrintInstr(const Register& _param) {
  LLVMInstr _value;
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

