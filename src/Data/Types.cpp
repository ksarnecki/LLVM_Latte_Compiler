
#include "Types.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Register ---------------
//----------------------------------

//------------- TypeCheckerEnviroment ---------------
//----------------------------------

//------------- TypeArray ---------------
TypeArray::TypeArray() {
}
TypeArray::~TypeArray() {
}
//----------------------------------

//------------- BasicTypeArray ---------------
BasicTypeArray::BasicTypeArray() {
}
BasicTypeArray::~BasicTypeArray() {
}
//----------------------------------

//------------- FunctionTypeArray ---------------
FunctionTypeArray::FunctionTypeArray() {
}
FunctionTypeArray::~FunctionTypeArray() {
}
//----------------------------------

//------------- Type ---------------
const int Type::_TypeBasic = 0;
const int Type::_TypeFunction = 1;
const int Type::_TypeNull = 2;
void Type::init(int type, void* ptr) {
  if (type==_TypeBasic) {
    _type = type;
    _ptr = new BasicType(*(BasicType*) ptr);
  } else if (type==_TypeFunction) {
    _type = type;
    _ptr = new FunctionType(*(FunctionType*) ptr);
  } else if (type==_TypeNull) {
    _type = type;
    _ptr = 0;
  }
}
void Type::clean() {
  if (_type==_TypeBasic) {
    _type = -1;
    delete (BasicType*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeFunction) {
    _type = -1;
    delete (FunctionType*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeNull) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("Type::clean()");
  }
}
Type::Type() : _type(-1), _ptr(0) {
}
Type::Type(const Type& _value) {
  init(_value._type, _value._ptr);
}
Type& Type::operator=(const Type& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool Type::isBasic() const {
  return _type==_TypeBasic;
}
bool Type::isFunction() const {
  return _type==_TypeFunction;
}
bool Type::isNull() const {
  return _type==_TypeNull;
}
const BasicType& Type::asBasic() const {
  if (_type!=_TypeBasic)
    throw Exception("Type::asBasic");
  return *(BasicType*) _ptr;
}
BasicType& Type::asBasic() {
  if (_type!=_TypeBasic)
    throw Exception("Type::asBasic");
  return *(BasicType*) _ptr;
}
const FunctionType& Type::asFunction() const {
  if (_type!=_TypeFunction)
    throw Exception("Type::asFunction");
  return *(FunctionType*) _ptr;
}
FunctionType& Type::asFunction() {
  if (_type!=_TypeFunction)
    throw Exception("Type::asFunction");
  return *(FunctionType*) _ptr;
}


Type::~Type() {
  clean();
}
Type Type::createBasic(const BasicType& _param) {
  Type _value;
  _value._type = _TypeBasic;
  _value._ptr = new BasicType(_param);
  return _value;
}
Type Type::createFunction(const FunctionType& _param) {
  Type _value;
  _value._type = _TypeFunction;
  _value._ptr = new FunctionType(_param);
  return _value;
}
Type Type::createNull() {
  Type _value;
  _value._type = _TypeNull;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- BasicType ---------------
const int BasicType::_TypeInt = 0;
const int BasicType::_TypeBool = 1;
const int BasicType::_TypeDouble = 2;
const int BasicType::_TypeChar = 3;
const int BasicType::_TypeString = 4;
const int BasicType::_TypeVoid = 5;
void BasicType::init(int type, void* ptr) {
  if (type==_TypeInt) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeBool) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeDouble) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeChar) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeString) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeVoid) {
    _type = type;
    _ptr = 0;
  }
}
void BasicType::clean() {
  if (_type==_TypeInt) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BasicType::clean()");
  } else if (_type==_TypeBool) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BasicType::clean()");
  } else if (_type==_TypeDouble) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BasicType::clean()");
  } else if (_type==_TypeChar) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BasicType::clean()");
  } else if (_type==_TypeString) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BasicType::clean()");
  } else if (_type==_TypeVoid) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("BasicType::clean()");
  }
}
BasicType::BasicType() : _type(-1), _ptr(0) {
}
BasicType::BasicType(const BasicType& _value) {
  init(_value._type, _value._ptr);
}
BasicType& BasicType::operator=(const BasicType& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool BasicType::isInt() const {
  return _type==_TypeInt;
}
bool BasicType::isBool() const {
  return _type==_TypeBool;
}
bool BasicType::isDouble() const {
  return _type==_TypeDouble;
}
bool BasicType::isChar() const {
  return _type==_TypeChar;
}
bool BasicType::isString() const {
  return _type==_TypeString;
}
bool BasicType::isVoid() const {
  return _type==_TypeVoid;
}


BasicType::~BasicType() {
  clean();
}
BasicType BasicType::createInt() {
  BasicType _value;
  _value._type = _TypeInt;
  _value._ptr = 0;
  return _value;
}
BasicType BasicType::createBool() {
  BasicType _value;
  _value._type = _TypeBool;
  _value._ptr = 0;
  return _value;
}
BasicType BasicType::createDouble() {
  BasicType _value;
  _value._type = _TypeDouble;
  _value._ptr = 0;
  return _value;
}
BasicType BasicType::createChar() {
  BasicType _value;
  _value._type = _TypeChar;
  _value._ptr = 0;
  return _value;
}
BasicType BasicType::createString() {
  BasicType _value;
  _value._type = _TypeString;
  _value._ptr = 0;
  return _value;
}
BasicType BasicType::createVoid() {
  BasicType _value;
  _value._type = _TypeVoid;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- FunctionType ---------------
FunctionType::FunctionType(const Type& _returnType, const TypeArray& _args, const TypeCheckerEnviroment& _env) : returnType(_returnType), args(_args), env(_env) {
}
const Type& FunctionType::getReturnType() const {
  return returnType;
}
Type& FunctionType::getReturnType() {
  return returnType;
}
const TypeArray& FunctionType::getArgs() const {
  return args;
}
TypeArray& FunctionType::getArgs() {
  return args;
}
const TypeCheckerEnviroment& FunctionType::getEnv() const {
  return env;
}
TypeCheckerEnviroment& FunctionType::getEnv() {
  return env;
}
FunctionType::~FunctionType() {
}
//----------------------------------

