
#include "Register.h"
#include "Exception.h"
#include "StringBuffer.h"
#include "JSONUtil.h"
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

AnsiString RegisterKind::toJSON() const {
  StringBuffer _json;
   _json += "{\"type\":" + AnsiString(_type) + ",\"value\":";
    if (_type==0)
      _json += "0";
    else if (_type==1)
      _json += "0";
    else if (_type==2)
      _json += "0";
    else if (_type==3)
      _json += "0";
    else if (_type==4)
    _json += ((RegisterKind*) _ptr)->toJSON();
    else if (_type==5)
      _json += "0";
    else
      throw Exception("RegisterKind::toJSON(" + AnsiString(_type) + ")");
    _json += "}";
    return _json.get();
}
RegisterKind RegisterKind::fromJSON(AnsiString s) {
  int ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length()) 
    throw Exception("RegisterKind::fromJSON");
  if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("0")) {
    return RegisterKind::createValueI1();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("1")) {
    return RegisterKind::createValueI8();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("2")) {
    return RegisterKind::createValueI32();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("3")) {
    return RegisterKind::createValueDouble();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("4")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("RegisterKind::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return RegisterKind::createPtr(RegisterKind::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("5")) {
    return RegisterKind::createNull();
  }
  AnsiString variantName = "";
  ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length() || ix<=4) 
    throw Exception("RegisterKind::fromJSON");
  variantName = s.SubString(3, ix-4);
  if (variantName==("valueI1")) {
    return RegisterKind::createValueI1();
  } else if (variantName==("valueI8")) {
    return RegisterKind::createValueI8();
  } else if (variantName==("valueI32")) {
    return RegisterKind::createValueI32();
  } else if (variantName==("valueDouble")) {
    return RegisterKind::createValueDouble();
  } else if (variantName==("ptr")) {
    if (s.Length()-ix-1<=0)
      throw Exception("RegisterKind::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return RegisterKind::createPtr(RegisterKind::fromJSON(s));
  } else if (variantName==("null")) {
    return RegisterKind::createNull();
  } else 
    throw Exception("RegisterKind::fromJSON");
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
AnsiString Register::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"id\":";
    _json += AnsiString(id);
    _json += ",";
    _json += "\"kind\":";
    _json += kind.toJSON();
  _json += "}";
  return _json.get();
}
Register Register::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("Register::fromJSON");
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
            throw Exception("Register::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return Register(atoi(arr[0].c_str()), RegisterKind::fromJSON(arr[1]));
}
Register::~Register() {
}
//----------------------------------

//------------- Registers ---------------
Registers::Registers() {
}
AnsiString Registers::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
Registers Registers::fromJSON(AnsiString s) {
  Registers arr = Registers();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("Registers::fromJSON");
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
          throw Exception("Registers::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(Register::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
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
AnsiString RegisterData::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"lastRegister\":";
    _json += lastRegister.toJSON();
    _json += ",";
    _json += "\"registers\":";
    _json += registers.toJSON();
  _json += "}";
  return _json.get();
}
RegisterData RegisterData::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("RegisterData::fromJSON");
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
            throw Exception("RegisterData::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return RegisterData(Register::fromJSON(arr[0]), Registers::fromJSON(arr[1]));
}
RegisterData::~RegisterData() {
}
//----------------------------------

