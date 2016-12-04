
#include "Types.h"
#include "Exception.h"
#include "StringBuffer.h"
#include "JSONUtil.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- TypeArray ---------------
TypeArray::TypeArray() {
}
AnsiString TypeArray::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
TypeArray TypeArray::fromJSON(AnsiString s) {
  TypeArray arr = TypeArray();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("TypeArray::fromJSON");
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
          throw Exception("TypeArray::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(Type::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
}
TypeArray::~TypeArray() {
}
//----------------------------------

//------------- BasicTypeArray ---------------
BasicTypeArray::BasicTypeArray() {
}
AnsiString BasicTypeArray::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
BasicTypeArray BasicTypeArray::fromJSON(AnsiString s) {
  BasicTypeArray arr = BasicTypeArray();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("BasicTypeArray::fromJSON");
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
          throw Exception("BasicTypeArray::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(BasicType::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
}
BasicTypeArray::~BasicTypeArray() {
}
//----------------------------------

//------------- FunctionTypeArray ---------------
FunctionTypeArray::FunctionTypeArray() {
}
AnsiString FunctionTypeArray::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
FunctionTypeArray FunctionTypeArray::fromJSON(AnsiString s) {
  FunctionTypeArray arr = FunctionTypeArray();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("FunctionTypeArray::fromJSON");
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
          throw Exception("FunctionTypeArray::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(FunctionType::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
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

AnsiString Type::toJSON() const {
  StringBuffer _json;
   _json += "{\"type\":" + AnsiString(_type) + ",\"value\":";
    if (_type==0)
    _json += ((BasicType*) _ptr)->toJSON();
    else if (_type==1)
    _json += ((FunctionType*) _ptr)->toJSON();
    else if (_type==2)
      _json += "0";
    else
      throw Exception("Type::toJSON(" + AnsiString(_type) + ")");
    _json += "}";
    return _json.get();
}
Type Type::fromJSON(AnsiString s) {
  int ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length()) 
    throw Exception("Type::fromJSON");
  if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("0")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("Type::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return Type::createBasic(BasicType::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("1")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("Type::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return Type::createFunction(FunctionType::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("2")) {
    return Type::createNull();
  }
  AnsiString variantName = "";
  ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length() || ix<=4) 
    throw Exception("Type::fromJSON");
  variantName = s.SubString(3, ix-4);
  if (variantName==("basic")) {
    if (s.Length()-ix-1<=0)
      throw Exception("Type::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return Type::createBasic(BasicType::fromJSON(s));
  } else if (variantName==("function")) {
    if (s.Length()-ix-1<=0)
      throw Exception("Type::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return Type::createFunction(FunctionType::fromJSON(s));
  } else if (variantName==("null")) {
    return Type::createNull();
  } else 
    throw Exception("Type::fromJSON");
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

AnsiString BasicType::toJSON() const {
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
      _json += "0";
    else if (_type==5)
      _json += "0";
    else
      throw Exception("BasicType::toJSON(" + AnsiString(_type) + ")");
    _json += "}";
    return _json.get();
}
BasicType BasicType::fromJSON(AnsiString s) {
  int ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length()) 
    throw Exception("BasicType::fromJSON");
  if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("0")) {
    return BasicType::createInt();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("1")) {
    return BasicType::createBool();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("2")) {
    return BasicType::createDouble();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("3")) {
    return BasicType::createChar();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("4")) {
    return BasicType::createString();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("5")) {
    return BasicType::createVoid();
  }
  AnsiString variantName = "";
  ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length() || ix<=4) 
    throw Exception("BasicType::fromJSON");
  variantName = s.SubString(3, ix-4);
  if (variantName==("int")) {
    return BasicType::createInt();
  } else if (variantName==("bool")) {
    return BasicType::createBool();
  } else if (variantName==("double")) {
    return BasicType::createDouble();
  } else if (variantName==("char")) {
    return BasicType::createChar();
  } else if (variantName==("string")) {
    return BasicType::createString();
  } else if (variantName==("void")) {
    return BasicType::createVoid();
  } else 
    throw Exception("BasicType::fromJSON");
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
FunctionType::FunctionType(const Type& _returnType, const TypeArray& _args) : returnType(_returnType), args(_args) {
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
AnsiString FunctionType::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"returnType\":";
    _json += returnType.toJSON();
    _json += ",";
    _json += "\"args\":";
    _json += args.toJSON();
  _json += "}";
  return _json.get();
}
FunctionType FunctionType::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("FunctionType::fromJSON");
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
            throw Exception("FunctionType::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return FunctionType(Type::fromJSON(arr[0]), TypeArray::fromJSON(arr[1]));
}
FunctionType::~FunctionType() {
}
//----------------------------------

