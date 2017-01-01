
#include "Store.h"
#include "Exception.h"
#include "StringBuffer.h"
#include "JSONUtil.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Type ---------------
//----------------------------------

//------------- Register ---------------
//----------------------------------

//------------- LLVMFunctionType ---------------
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

AnsiString BasicObject::toJSON() const {
  StringBuffer _json;
   _json += "{\"type\":" + AnsiString(_type) + ",\"value\":";
    if (_type==0)
    _json += ((Register*) _ptr)->toJSON();
    else if (_type==1)
    _json += ((Register*) _ptr)->toJSON();
    else if (_type==2)
    _json += ((Register*) _ptr)->toJSON();
    else if (_type==3)
    _json += ((Register*) _ptr)->toJSON();
    else if (_type==4)
    _json += ((Register*) _ptr)->toJSON();
    else
      throw Exception("BasicObject::toJSON(" + AnsiString(_type) + ")");
    _json += "}";
    return _json.get();
}
BasicObject BasicObject::fromJSON(AnsiString s) {
  int ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length()) 
    throw Exception("BasicObject::fromJSON");
  if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("0")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("BasicObject::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return BasicObject::createInt(Register::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("1")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("BasicObject::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return BasicObject::createBool(Register::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("2")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("BasicObject::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return BasicObject::createDouble(Register::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("3")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("BasicObject::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return BasicObject::createChar(Register::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("4")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("BasicObject::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return BasicObject::createString(Register::fromJSON(s));
  }
  AnsiString variantName = "";
  ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length() || ix<=4) 
    throw Exception("BasicObject::fromJSON");
  variantName = s.SubString(3, ix-4);
  if (variantName==("int")) {
    if (s.Length()-ix-1<=0)
      throw Exception("BasicObject::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return BasicObject::createInt(Register::fromJSON(s));
  } else if (variantName==("bool")) {
    if (s.Length()-ix-1<=0)
      throw Exception("BasicObject::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return BasicObject::createBool(Register::fromJSON(s));
  } else if (variantName==("double")) {
    if (s.Length()-ix-1<=0)
      throw Exception("BasicObject::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return BasicObject::createDouble(Register::fromJSON(s));
  } else if (variantName==("char")) {
    if (s.Length()-ix-1<=0)
      throw Exception("BasicObject::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return BasicObject::createChar(Register::fromJSON(s));
  } else if (variantName==("string")) {
    if (s.Length()-ix-1<=0)
      throw Exception("BasicObject::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return BasicObject::createString(Register::fromJSON(s));
  } else 
    throw Exception("BasicObject::fromJSON");
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
FunctionObject::FunctionObject(const LLVMFunctionType& _type) : type(_type) {
}
const LLVMFunctionType& FunctionObject::getType() const {
  return type;
}
LLVMFunctionType& FunctionObject::getType() {
  return type;
}
AnsiString FunctionObject::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"type\":";
    _json += type.toJSON();
  _json += "}";
  return _json.get();
}
FunctionObject FunctionObject::fromJSON(AnsiString s) {
  AnsiString arr[1];
  int ix=1;
  for (int i=0;i<1;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("FunctionObject::fromJSON");
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\')
        ix+=2;
      else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && ((ix<=s.Length() && s[ix]==',') || ix==s.Length())) {
        if (i<1) {
          if (ix-start-1<=0)
            throw Exception("FunctionObject::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return FunctionObject(LLVMFunctionType::fromJSON(arr[0]));
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

AnsiString Object::toJSON() const {
  StringBuffer _json;
   _json += "{\"type\":" + AnsiString(_type) + ",\"value\":";
    if (_type==0)
    _json += ((BasicObject*) _ptr)->toJSON();
    else if (_type==1)
    _json += ((FunctionObject*) _ptr)->toJSON();
    else if (_type==2)
      _json += "0";
    else if (_type==3)
      _json += "0";
    else
      throw Exception("Object::toJSON(" + AnsiString(_type) + ")");
    _json += "}";
    return _json.get();
}
Object Object::fromJSON(AnsiString s) {
  int ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length()) 
    throw Exception("Object::fromJSON");
  if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("0")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("Object::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return Object::createBasic(BasicObject::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("1")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("Object::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return Object::createFunction(FunctionObject::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("2")) {
    return Object::createClassObject();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("3")) {
    return Object::createNull();
  }
  AnsiString variantName = "";
  ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length() || ix<=4) 
    throw Exception("Object::fromJSON");
  variantName = s.SubString(3, ix-4);
  if (variantName==("basic")) {
    if (s.Length()-ix-1<=0)
      throw Exception("Object::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return Object::createBasic(BasicObject::fromJSON(s));
  } else if (variantName==("function")) {
    if (s.Length()-ix-1<=0)
      throw Exception("Object::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return Object::createFunction(FunctionObject::fromJSON(s));
  } else if (variantName==("classObject")) {
    return Object::createClassObject();
  } else if (variantName==("null")) {
    return Object::createNull();
  } else 
    throw Exception("Object::fromJSON");
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
AnsiString StoreElement::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"id\":";
    _json += AnsiString(id);
    _json += ",";
    _json += "\"obj\":";
    _json += obj.toJSON();
  _json += "}";
  return _json.get();
}
StoreElement StoreElement::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("StoreElement::fromJSON");
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\')
        ix+=2;
      else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && ((ix<=s.Length() && s[ix]==',') || ix==s.Length())) {
        if (i<2) {
          if (ix-start-1<=0)
            throw Exception("StoreElement::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return StoreElement(atoi(arr[0].c_str()), Object::fromJSON(arr[1]));
}
StoreElement::~StoreElement() {
}
//----------------------------------

//------------- ObjectArray ---------------
ObjectArray::ObjectArray() {
}
AnsiString ObjectArray::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
ObjectArray ObjectArray::fromJSON(AnsiString s) {
  ObjectArray arr = ObjectArray();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("ObjectArray::fromJSON");
  while (ix<=s.Length()) {
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\')
        ix+=2;
      else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && (s[ix]==',' || ix==s.Length())) {
        if (start==ix)
          return arr;
        if (ix-start<=0)
          throw Exception("ObjectArray::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(Object::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
}
ObjectArray::~ObjectArray() {
}
//----------------------------------

//------------- Store ---------------
Store::Store() {
}
AnsiString Store::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
Store Store::fromJSON(AnsiString s) {
  Store arr = Store();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("Store::fromJSON");
  while (ix<=s.Length()) {
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\')
        ix+=2;
      else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && (s[ix]==',' || ix==s.Length())) {
        if (start==ix)
          return arr;
        if (ix-start<=0)
          throw Exception("Store::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(StoreElement::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
}
Store::~Store() {
}
//----------------------------------

