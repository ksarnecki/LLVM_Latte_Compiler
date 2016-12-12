
#include "Register.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Ident ---------------
//----------------------------------

//------------- RegisterKind ---------------
const int RegisterKind::_TypeValueI1 = 0;
const int RegisterKind::_TypeValueI8 = 1;
const int RegisterKind::_TypeValueI32 = 2;
const int RegisterKind::_TypeValueDouble = 3;
const int RegisterKind::_TypePtr = 4;
const int RegisterKind::_TypeNull = 5;
void RegisterKind::init(int type, void* ptr) {
  if (type==_TypeValueI1) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeValueI8) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeValueI32) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeValueDouble) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypePtr) {
    _type = type;
    _ptr = new RegisterKind(*(RegisterKind*) ptr);
  } else if (type==_TypeNull) {
    _type = type;
    _ptr = 0;
  }
}
void RegisterKind::clean() {
  if (_type==_TypeValueI1) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("RegisterKind::clean()");
  } else if (_type==_TypeValueI8) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("RegisterKind::clean()");
  } else if (_type==_TypeValueI32) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("RegisterKind::clean()");
  } else if (_type==_TypeValueDouble) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("RegisterKind::clean()");
  } else if (_type==_TypePtr) {
    _type = -1;
    delete (RegisterKind*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeNull) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("RegisterKind::clean()");
  }
}
RegisterKind::RegisterKind() : _type(-1), _ptr(0) {
}
RegisterKind::RegisterKind(const RegisterKind& _value) {
  init(_value._type, _value._ptr);
}
RegisterKind& RegisterKind::operator=(const RegisterKind& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool RegisterKind::isValueI1() const {
  return _type==_TypeValueI1;
}
bool RegisterKind::isValueI8() const {
  return _type==_TypeValueI8;
}
bool RegisterKind::isValueI32() const {
  return _type==_TypeValueI32;
}
bool RegisterKind::isValueDouble() const {
  return _type==_TypeValueDouble;
}
bool RegisterKind::isPtr() const {
  return _type==_TypePtr;
}
bool RegisterKind::isNull() const {
  return _type==_TypeNull;
}
const RegisterKind& RegisterKind::asPtr() const {
  if (_type!=_TypePtr)
    throw Exception("RegisterKind::asPtr");
  return *(RegisterKind*) _ptr;
}
RegisterKind& RegisterKind::asPtr() {
  if (_type!=_TypePtr)
    throw Exception("RegisterKind::asPtr");
  return *(RegisterKind*) _ptr;
}


RegisterKind::~RegisterKind() {
  clean();
}
RegisterKind RegisterKind::createValueI1() {
  RegisterKind _value;
  _value._type = _TypeValueI1;
  _value._ptr = 0;
  return _value;
}
RegisterKind RegisterKind::createValueI8() {
  RegisterKind _value;
  _value._type = _TypeValueI8;
  _value._ptr = 0;
  return _value;
}
RegisterKind RegisterKind::createValueI32() {
  RegisterKind _value;
  _value._type = _TypeValueI32;
  _value._ptr = 0;
  return _value;
}
RegisterKind RegisterKind::createValueDouble() {
  RegisterKind _value;
  _value._type = _TypeValueDouble;
  _value._ptr = 0;
  return _value;
}
RegisterKind RegisterKind::createPtr(const RegisterKind& _param) {
  RegisterKind _value;
  _value._type = _TypePtr;
  _value._ptr = new RegisterKind(_param);
  return _value;
}
RegisterKind RegisterKind::createNull() {
  RegisterKind _value;
  _value._type = _TypeNull;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- Register ---------------
Register::Register(const int& _id, const RegisterKind& _kind) : id(_id), kind(_kind) {
}
const int& Register::getId() const {
  return id;
}
int& Register::getId() {
  return id;
}
const RegisterKind& Register::getKind() const {
  return kind;
}
RegisterKind& Register::getKind() {
  return kind;
}
Register::~Register() {
}
//----------------------------------

//------------- Registers ---------------
Registers::Registers() {
}
Registers::~Registers() {
}
//----------------------------------

//------------- RegisterData ---------------
RegisterData::RegisterData(const Register& _lastRegister, const Registers& _registers) : lastRegister(_lastRegister), registers(_registers) {
}
const Register& RegisterData::getLastRegister() const {
  return lastRegister;
}
Register& RegisterData::getLastRegister() {
  return lastRegister;
}
const Registers& RegisterData::getRegisters() const {
  return registers;
}
Registers& RegisterData::getRegisters() {
  return registers;
}
RegisterData::~RegisterData() {
}
//----------------------------------

