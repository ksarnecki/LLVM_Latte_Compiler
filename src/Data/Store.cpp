
#include "Store.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Type ---------------
//----------------------------------

//------------- Register ---------------
//----------------------------------

//------------- RegisterKind ---------------
//----------------------------------

//------------- BasicObject ---------------
const int BasicObject::_TypeInt = 0;
const int BasicObject::_TypeBool = 1;
const int BasicObject::_TypeDouble = 2;
const int BasicObject::_TypeChar = 3;
const int BasicObject::_TypeString = 4;
void BasicObject::init(int type, void* ptr) {
  if (type==_TypeInt) {
    _type = type;
    _ptr = new Register(*(Register*) ptr);
  } else if (type==_TypeBool) {
    _type = type;
    _ptr = new Register(*(Register*) ptr);
  } else if (type==_TypeDouble) {
    _type = type;
    _ptr = new Register(*(Register*) ptr);
  } else if (type==_TypeChar) {
    _type = type;
    _ptr = new Register(*(Register*) ptr);
  } else if (type==_TypeString) {
    _type = type;
    _ptr = new Register(*(Register*) ptr);
  }
}
void BasicObject::clean() {
  if (_type==_TypeInt) {
    _type = -1;
    delete (Register*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeBool) {
    _type = -1;
    delete (Register*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeDouble) {
    _type = -1;
    delete (Register*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeChar) {
    _type = -1;
    delete (Register*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeString) {
    _type = -1;
    delete (Register*) _ptr;
    _ptr = 0;
  }
}
BasicObject::BasicObject() : _type(-1), _ptr(0) {
}
BasicObject::BasicObject(const BasicObject& _value) {
  init(_value._type, _value._ptr);
}
BasicObject& BasicObject::operator=(const BasicObject& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool BasicObject::isInt() const {
  return _type==_TypeInt;
}
bool BasicObject::isBool() const {
  return _type==_TypeBool;
}
bool BasicObject::isDouble() const {
  return _type==_TypeDouble;
}
bool BasicObject::isChar() const {
  return _type==_TypeChar;
}
bool BasicObject::isString() const {
  return _type==_TypeString;
}
const Register& BasicObject::asInt() const {
  if (_type!=_TypeInt)
    throw Exception("BasicObject::asInt");
  return *(Register*) _ptr;
}
Register& BasicObject::asInt() {
  if (_type!=_TypeInt)
    throw Exception("BasicObject::asInt");
  return *(Register*) _ptr;
}
const Register& BasicObject::asBool() const {
  if (_type!=_TypeBool)
    throw Exception("BasicObject::asBool");
  return *(Register*) _ptr;
}
Register& BasicObject::asBool() {
  if (_type!=_TypeBool)
    throw Exception("BasicObject::asBool");
  return *(Register*) _ptr;
}
const Register& BasicObject::asDouble() const {
  if (_type!=_TypeDouble)
    throw Exception("BasicObject::asDouble");
  return *(Register*) _ptr;
}
Register& BasicObject::asDouble() {
  if (_type!=_TypeDouble)
    throw Exception("BasicObject::asDouble");
  return *(Register*) _ptr;
}
const Register& BasicObject::asChar() const {
  if (_type!=_TypeChar)
    throw Exception("BasicObject::asChar");
  return *(Register*) _ptr;
}
Register& BasicObject::asChar() {
  if (_type!=_TypeChar)
    throw Exception("BasicObject::asChar");
  return *(Register*) _ptr;
}
const Register& BasicObject::asString() const {
  if (_type!=_TypeString)
    throw Exception("BasicObject::asString");
  return *(Register*) _ptr;
}
Register& BasicObject::asString() {
  if (_type!=_TypeString)
    throw Exception("BasicObject::asString");
  return *(Register*) _ptr;
}


BasicObject::~BasicObject() {
  clean();
}
BasicObject BasicObject::createInt(const Register& _param) {
  BasicObject _value;
  _value._type = _TypeInt;
  _value._ptr = new Register(_param);
  return _value;
}
BasicObject BasicObject::createBool(const Register& _param) {
  BasicObject _value;
  _value._type = _TypeBool;
  _value._ptr = new Register(_param);
  return _value;
}
BasicObject BasicObject::createDouble(const Register& _param) {
  BasicObject _value;
  _value._type = _TypeDouble;
  _value._ptr = new Register(_param);
  return _value;
}
BasicObject BasicObject::createChar(const Register& _param) {
  BasicObject _value;
  _value._type = _TypeChar;
  _value._ptr = new Register(_param);
  return _value;
}
BasicObject BasicObject::createString(const Register& _param) {
  BasicObject _value;
  _value._type = _TypeString;
  _value._ptr = new Register(_param);
  return _value;
}


//----------------------------------

//------------- FunctionObject ---------------
FunctionObject::FunctionObject(const RegisterKind& _type) : type(_type) {
}
const RegisterKind& FunctionObject::getType() const {
  return type;
}
RegisterKind& FunctionObject::getType() {
  return type;
}
FunctionObject::~FunctionObject() {
}
//----------------------------------

//------------- Object ---------------
const int Object::_TypeBasic = 0;
const int Object::_TypeFunction = 1;
const int Object::_TypeClassObject = 2;
const int Object::_TypeNull = 3;
void Object::init(int type, void* ptr) {
  if (type==_TypeBasic) {
    _type = type;
    _ptr = new BasicObject(*(BasicObject*) ptr);
  } else if (type==_TypeFunction) {
    _type = type;
    _ptr = new FunctionObject(*(FunctionObject*) ptr);
  } else if (type==_TypeClassObject) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeNull) {
    _type = type;
    _ptr = 0;
  }
}
void Object::clean() {
  if (_type==_TypeBasic) {
    _type = -1;
    delete (BasicObject*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeFunction) {
    _type = -1;
    delete (FunctionObject*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeClassObject) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("Object::clean()");
  } else if (_type==_TypeNull) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("Object::clean()");
  }
}
Object::Object() : _type(-1), _ptr(0) {
}
Object::Object(const Object& _value) {
  init(_value._type, _value._ptr);
}
Object& Object::operator=(const Object& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool Object::isBasic() const {
  return _type==_TypeBasic;
}
bool Object::isFunction() const {
  return _type==_TypeFunction;
}
bool Object::isClassObject() const {
  return _type==_TypeClassObject;
}
bool Object::isNull() const {
  return _type==_TypeNull;
}
const BasicObject& Object::asBasic() const {
  if (_type!=_TypeBasic)
    throw Exception("Object::asBasic");
  return *(BasicObject*) _ptr;
}
BasicObject& Object::asBasic() {
  if (_type!=_TypeBasic)
    throw Exception("Object::asBasic");
  return *(BasicObject*) _ptr;
}
const FunctionObject& Object::asFunction() const {
  if (_type!=_TypeFunction)
    throw Exception("Object::asFunction");
  return *(FunctionObject*) _ptr;
}
FunctionObject& Object::asFunction() {
  if (_type!=_TypeFunction)
    throw Exception("Object::asFunction");
  return *(FunctionObject*) _ptr;
}


Object::~Object() {
  clean();
}
Object Object::createBasic(const BasicObject& _param) {
  Object _value;
  _value._type = _TypeBasic;
  _value._ptr = new BasicObject(_param);
  return _value;
}
Object Object::createFunction(const FunctionObject& _param) {
  Object _value;
  _value._type = _TypeFunction;
  _value._ptr = new FunctionObject(_param);
  return _value;
}
Object Object::createClassObject() {
  Object _value;
  _value._type = _TypeClassObject;
  _value._ptr = 0;
  return _value;
}
Object Object::createNull() {
  Object _value;
  _value._type = _TypeNull;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- StoreElement ---------------
StoreElement::StoreElement(const int& _id, const Object& _obj) : id(_id), obj(_obj) {
}
const int& StoreElement::getId() const {
  return id;
}
int& StoreElement::getId() {
  return id;
}
const Object& StoreElement::getObj() const {
  return obj;
}
Object& StoreElement::getObj() {
  return obj;
}
StoreElement::~StoreElement() {
}
//----------------------------------

//------------- ObjectArray ---------------
ObjectArray::ObjectArray() {
}
ObjectArray::~ObjectArray() {
}
//----------------------------------

//------------- Store ---------------
Store::Store() {
}
Store::~Store() {
}
//----------------------------------

