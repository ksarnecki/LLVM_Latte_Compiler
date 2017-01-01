
#include "LLVMProgram.h"
#include "Exception.h"
#include "StringBuffer.h"
#include "JSONUtil.h"
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

AnsiString BinaryOperationArgument::toJSON() const {
  StringBuffer _json;
   _json += "{\"type\":" + AnsiString(_type) + ",\"value\":";
    if (_type==0)
    _json += ((Register*) _ptr)->toJSON();
    else if (_type==1)
    _json += "\"" + JSONEscape::encode(*((AnsiString*) _ptr)) + "\"";
    else
      throw Exception("BinaryOperationArgument::toJSON(" + AnsiString(_type) + ")");
    _json += "}";
    return _json.get();
}
BinaryOperationArgument BinaryOperationArgument::fromJSON(AnsiString s) {
  int ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length()) 
    throw Exception("BinaryOperationArgument::fromJSON");
  if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("0")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("BinaryOperationArgument::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return BinaryOperationArgument::createRegister(Register::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("1")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("BinaryOperationArgument::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return BinaryOperationArgument::createNumber((s.Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(s.SubString(2, s.Length()-2))));
  }
  AnsiString variantName = "";
  ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length() || ix<=4) 
    throw Exception("BinaryOperationArgument::fromJSON");
  variantName = s.SubString(3, ix-4);
  if (variantName==("register")) {
    if (s.Length()-ix-1<=0)
      throw Exception("BinaryOperationArgument::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return BinaryOperationArgument::createRegister(Register::fromJSON(s));
  } else if (variantName==("number")) {
    if (s.Length()-ix-1<=0)
      throw Exception("BinaryOperationArgument::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return BinaryOperationArgument::createNumber((s.Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(s.SubString(2, s.Length()-2))));
  } else 
    throw Exception("BinaryOperationArgument::fromJSON");
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

AnsiString BinaryOperator::toJSON() const {
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
    else if (_type==6)
      _json += "0";
    else if (_type==7)
      _json += "0";
    else if (_type==8)
      _json += "0";
    else if (_type==9)
      _json += "0";
    else if (_type==10)
      _json += "0";
    else
      throw Exception("BinaryOperator::toJSON(" + AnsiString(_type) + ")");
    _json += "}";
    return _json.get();
}
BinaryOperator BinaryOperator::fromJSON(AnsiString s) {
  int ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length()) 
    throw Exception("BinaryOperator::fromJSON");
  if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("0")) {
    return BinaryOperator::createAdd();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("1")) {
    return BinaryOperator::createSub();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("2")) {
    return BinaryOperator::createDiv();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("3")) {
    return BinaryOperator::createMul();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("4")) {
    return BinaryOperator::createMod();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("5")) {
    return BinaryOperator::createLth();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("6")) {
    return BinaryOperator::createLe();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("7")) {
    return BinaryOperator::createGth();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("8")) {
    return BinaryOperator::createGe();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("9")) {
    return BinaryOperator::createEqu();
  } else if (s.Length()>ix+1+2 && s.SubString(ix+1, 2)==("10")) {
    return BinaryOperator::createNe();
  }
  AnsiString variantName = "";
  ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length() || ix<=4) 
    throw Exception("BinaryOperator::fromJSON");
  variantName = s.SubString(3, ix-4);
  if (variantName==("add")) {
    return BinaryOperator::createAdd();
  } else if (variantName==("sub")) {
    return BinaryOperator::createSub();
  } else if (variantName==("div")) {
    return BinaryOperator::createDiv();
  } else if (variantName==("mul")) {
    return BinaryOperator::createMul();
  } else if (variantName==("mod")) {
    return BinaryOperator::createMod();
  } else if (variantName==("lth")) {
    return BinaryOperator::createLth();
  } else if (variantName==("le")) {
    return BinaryOperator::createLe();
  } else if (variantName==("gth")) {
    return BinaryOperator::createGth();
  } else if (variantName==("ge")) {
    return BinaryOperator::createGe();
  } else if (variantName==("equ")) {
    return BinaryOperator::createEqu();
  } else if (variantName==("ne")) {
    return BinaryOperator::createNe();
  } else 
    throw Exception("BinaryOperator::fromJSON");
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
AnsiString BinaryOperation::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"outReg\":";
    _json += outReg.toJSON();
    _json += ",";
    _json += "\"lArg\":";
    _json += lArg.toJSON();
    _json += ",";
    _json += "\"rArg\":";
    _json += rArg.toJSON();
    _json += ",";
    _json += "\"bop\":";
    _json += bop.toJSON();
  _json += "}";
  return _json.get();
}
BinaryOperation BinaryOperation::fromJSON(AnsiString s) {
  AnsiString arr[4];
  int ix=1;
  for (int i=0;i<4;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("BinaryOperation::fromJSON");
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
        if (i<4) {
          if (ix-start-1<=0)
            throw Exception("BinaryOperation::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return BinaryOperation(Register::fromJSON(arr[0]), BinaryOperationArgument::fromJSON(arr[1]), BinaryOperationArgument::fromJSON(arr[2]), BinaryOperator::fromJSON(arr[3]));
}
BinaryOperation::~BinaryOperation() {
}
//----------------------------------

//------------- CallInstrRet ---------------
const int CallInstrRet::_TypeVoid = 0;
const int CallInstrRet::_TypeObj = 1;
void CallInstrRet::init(int type, void* ptr) {
  if (type==_TypeVoid) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeObj) {
    _type = type;
    _ptr = new Register(*(Register*) ptr);
  }
}
void CallInstrRet::clean() {
  if (_type==_TypeVoid) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("CallInstrRet::clean()");
  } else if (_type==_TypeObj) {
    _type = -1;
    delete (Register*) _ptr;
    _ptr = 0;
  }
}
CallInstrRet::CallInstrRet() : _type(-1), _ptr(0) {
}
CallInstrRet::CallInstrRet(const CallInstrRet& _value) {
  init(_value._type, _value._ptr);
}
CallInstrRet& CallInstrRet::operator=(const CallInstrRet& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool CallInstrRet::isVoid() const {
  return _type==_TypeVoid;
}
bool CallInstrRet::isObj() const {
  return _type==_TypeObj;
}
const Register& CallInstrRet::asObj() const {
  if (_type!=_TypeObj)
    throw Exception("CallInstrRet::asObj");
  return *(Register*) _ptr;
}
Register& CallInstrRet::asObj() {
  if (_type!=_TypeObj)
    throw Exception("CallInstrRet::asObj");
  return *(Register*) _ptr;
}

AnsiString CallInstrRet::toJSON() const {
  StringBuffer _json;
   _json += "{\"type\":" + AnsiString(_type) + ",\"value\":";
    if (_type==0)
      _json += "0";
    else if (_type==1)
    _json += ((Register*) _ptr)->toJSON();
    else
      throw Exception("CallInstrRet::toJSON(" + AnsiString(_type) + ")");
    _json += "}";
    return _json.get();
}
CallInstrRet CallInstrRet::fromJSON(AnsiString s) {
  int ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length()) 
    throw Exception("CallInstrRet::fromJSON");
  if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("0")) {
    return CallInstrRet::createVoid();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("1")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("CallInstrRet::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return CallInstrRet::createObj(Register::fromJSON(s));
  }
  AnsiString variantName = "";
  ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length() || ix<=4) 
    throw Exception("CallInstrRet::fromJSON");
  variantName = s.SubString(3, ix-4);
  if (variantName==("void")) {
    return CallInstrRet::createVoid();
  } else if (variantName==("obj")) {
    if (s.Length()-ix-1<=0)
      throw Exception("CallInstrRet::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return CallInstrRet::createObj(Register::fromJSON(s));
  } else 
    throw Exception("CallInstrRet::fromJSON");
}

CallInstrRet::~CallInstrRet() {
  clean();
}
CallInstrRet CallInstrRet::createVoid() {
  CallInstrRet _value;
  _value._type = _TypeVoid;
  _value._ptr = 0;
  return _value;
}
CallInstrRet CallInstrRet::createObj(const Register& _param) {
  CallInstrRet _value;
  _value._type = _TypeObj;
  _value._ptr = new Register(_param);
  return _value;
}


//----------------------------------

//------------- CallInstr ---------------
CallInstr::CallInstr(const CallInstrRet& _retType, const AnsiString& _function, const Registers& _args) : retType(_retType), function(_function), args(_args) {
}
const CallInstrRet& CallInstr::getRetType() const {
  return retType;
}
CallInstrRet& CallInstr::getRetType() {
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
AnsiString CallInstr::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"retType\":";
    _json += retType.toJSON();
    _json += ",";
    _json += "\"function\":";
    _json += "\"" + JSONEscape::encode(function) + "\"";
    _json += ",";
    _json += "\"args\":";
    _json += args.toJSON();
  _json += "}";
  return _json.get();
}
CallInstr CallInstr::fromJSON(AnsiString s) {
  AnsiString arr[3];
  int ix=1;
  for (int i=0;i<3;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("CallInstr::fromJSON");
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
        if (i<3) {
          if (ix-start-1<=0)
            throw Exception("CallInstr::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return CallInstr(CallInstrRet::fromJSON(arr[0]), (arr[1].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[1].SubString(2, arr[1].Length()-2))), Registers::fromJSON(arr[2]));
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
AnsiString BrIfInstr::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"cond\":";
    _json += cond.toJSON();
    _json += ",";
    _json += "\"ifTrueBlock\":";
    _json += "\"" + JSONEscape::encode(ifTrueBlock) + "\"";
    _json += ",";
    _json += "\"ifFalseBlock\":";
    _json += "\"" + JSONEscape::encode(ifFalseBlock) + "\"";
  _json += "}";
  return _json.get();
}
BrIfInstr BrIfInstr::fromJSON(AnsiString s) {
  AnsiString arr[3];
  int ix=1;
  for (int i=0;i<3;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("BrIfInstr::fromJSON");
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
        if (i<3) {
          if (ix-start-1<=0)
            throw Exception("BrIfInstr::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return BrIfInstr(Register::fromJSON(arr[0]), (arr[1].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[1].SubString(2, arr[1].Length()-2))), (arr[2].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[2].SubString(2, arr[2].Length()-2))));
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
AnsiString BrInstr::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"block\":";
    _json += "\"" + JSONEscape::encode(block) + "\"";
  _json += "}";
  return _json.get();
}
BrInstr BrInstr::fromJSON(AnsiString s) {
  AnsiString arr[1];
  int ix=1;
  for (int i=0;i<1;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("BrInstr::fromJSON");
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
            throw Exception("BrInstr::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return BrInstr((arr[0].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[0].SubString(2, arr[0].Length()-2))));
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
AnsiString PhiCase::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"value\":";
    _json += value.toJSON();
    _json += ",";
    _json += "\"label\":";
    _json += "\"" + JSONEscape::encode(label) + "\"";
  _json += "}";
  return _json.get();
}
PhiCase PhiCase::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("PhiCase::fromJSON");
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
            throw Exception("PhiCase::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return PhiCase(Register::fromJSON(arr[0]), (arr[1].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[1].SubString(2, arr[1].Length()-2))));
}
PhiCase::~PhiCase() {
}
//----------------------------------

//------------- PhiCases ---------------
PhiCases::PhiCases() {
}
AnsiString PhiCases::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
PhiCases PhiCases::fromJSON(AnsiString s) {
  PhiCases arr = PhiCases();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("PhiCases::fromJSON");
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
          throw Exception("PhiCases::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(PhiCase::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
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
AnsiString PhiInstr::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"ident\":";
    _json += "\"" + JSONEscape::encode(ident) + "\"";
    _json += ",";
    _json += "\"ret\":";
    _json += ret.toJSON();
    _json += ",";
    _json += "\"caseses\":";
    _json += caseses.toJSON();
  _json += "}";
  return _json.get();
}
PhiInstr PhiInstr::fromJSON(AnsiString s) {
  AnsiString arr[3];
  int ix=1;
  for (int i=0;i<3;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("PhiInstr::fromJSON");
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
        if (i<3) {
          if (ix-start-1<=0)
            throw Exception("PhiInstr::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return PhiInstr((arr[0].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[0].SubString(2, arr[0].Length()-2))), Register::fromJSON(arr[1]), PhiCases::fromJSON(arr[2]));
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

AnsiString Instr::toJSON() const {
  StringBuffer _json;
   _json += "{\"type\":" + AnsiString(_type) + ",\"value\":";
    if (_type==0)
    _json += ((BinaryOperation*) _ptr)->toJSON();
    else if (_type==1)
    _json += ((CallInstr*) _ptr)->toJSON();
    else if (_type==2)
    _json += ((PhiInstr*) _ptr)->toJSON();
    else if (_type==3)
    _json += ((Register*) _ptr)->toJSON();
    else if (_type==4)
    _json += ((BrInstr*) _ptr)->toJSON();
    else if (_type==5)
    _json += ((BrIfInstr*) _ptr)->toJSON();
    else if (_type==6)
    _json += ((Register*) _ptr)->toJSON();
    else
      throw Exception("Instr::toJSON(" + AnsiString(_type) + ")");
    _json += "}";
    return _json.get();
}
Instr Instr::fromJSON(AnsiString s) {
  int ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length()) 
    throw Exception("Instr::fromJSON");
  if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("0")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("Instr::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return Instr::createBinaryOperationInstr(BinaryOperation::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("1")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("Instr::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return Instr::createCallInstr(CallInstr::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("2")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("Instr::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return Instr::createPhiInstr(PhiInstr::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("3")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("Instr::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return Instr::createReturnInstr(Register::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("4")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("Instr::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return Instr::createBrInstr(BrInstr::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("5")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("Instr::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return Instr::createBrIfInstr(BrIfInstr::fromJSON(s));
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("6")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("Instr::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return Instr::createPrintInstr(Register::fromJSON(s));
  }
  AnsiString variantName = "";
  ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length() || ix<=4) 
    throw Exception("Instr::fromJSON");
  variantName = s.SubString(3, ix-4);
  if (variantName==("binaryOperationInstr")) {
    if (s.Length()-ix-1<=0)
      throw Exception("Instr::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return Instr::createBinaryOperationInstr(BinaryOperation::fromJSON(s));
  } else if (variantName==("callInstr")) {
    if (s.Length()-ix-1<=0)
      throw Exception("Instr::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return Instr::createCallInstr(CallInstr::fromJSON(s));
  } else if (variantName==("phiInstr")) {
    if (s.Length()-ix-1<=0)
      throw Exception("Instr::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return Instr::createPhiInstr(PhiInstr::fromJSON(s));
  } else if (variantName==("returnInstr")) {
    if (s.Length()-ix-1<=0)
      throw Exception("Instr::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return Instr::createReturnInstr(Register::fromJSON(s));
  } else if (variantName==("brInstr")) {
    if (s.Length()-ix-1<=0)
      throw Exception("Instr::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return Instr::createBrInstr(BrInstr::fromJSON(s));
  } else if (variantName==("brIfInstr")) {
    if (s.Length()-ix-1<=0)
      throw Exception("Instr::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return Instr::createBrIfInstr(BrIfInstr::fromJSON(s));
  } else if (variantName==("printInstr")) {
    if (s.Length()-ix-1<=0)
      throw Exception("Instr::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return Instr::createPrintInstr(Register::fromJSON(s));
  } else 
    throw Exception("Instr::fromJSON");
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
AnsiString InstrArray::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
InstrArray InstrArray::fromJSON(AnsiString s) {
  InstrArray arr = InstrArray();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("InstrArray::fromJSON");
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
          throw Exception("InstrArray::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(Instr::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
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
AnsiString LLVMBlock::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"name\":";
    _json += "\"" + JSONEscape::encode(name) + "\"";
    _json += ",";
    _json += "\"body\":";
    _json += body.toJSON();
  _json += "}";
  return _json.get();
}
LLVMBlock LLVMBlock::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("LLVMBlock::fromJSON");
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
            throw Exception("LLVMBlock::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return LLVMBlock((arr[0].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[0].SubString(2, arr[0].Length()-2))), InstrArray::fromJSON(arr[1]));
}
LLVMBlock::~LLVMBlock() {
}
//----------------------------------

//------------- LLVMBlockArray ---------------
LLVMBlockArray::LLVMBlockArray() {
}
AnsiString LLVMBlockArray::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
LLVMBlockArray LLVMBlockArray::fromJSON(AnsiString s) {
  LLVMBlockArray arr = LLVMBlockArray();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("LLVMBlockArray::fromJSON");
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
          throw Exception("LLVMBlockArray::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(LLVMBlock::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
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
AnsiString LLVMFunctionArgument::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"reg\":";
    _json += reg.toJSON();
    _json += ",";
    _json += "\"name\":";
    _json += "\"" + JSONEscape::encode(name) + "\"";
  _json += "}";
  return _json.get();
}
LLVMFunctionArgument LLVMFunctionArgument::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("LLVMFunctionArgument::fromJSON");
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
            throw Exception("LLVMFunctionArgument::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return LLVMFunctionArgument(Register::fromJSON(arr[0]), (arr[1].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[1].SubString(2, arr[1].Length()-2))));
}
LLVMFunctionArgument::~LLVMFunctionArgument() {
}
//----------------------------------

//------------- LLVMFunctionArgumentArray ---------------
LLVMFunctionArgumentArray::LLVMFunctionArgumentArray() {
}
AnsiString LLVMFunctionArgumentArray::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
LLVMFunctionArgumentArray LLVMFunctionArgumentArray::fromJSON(AnsiString s) {
  LLVMFunctionArgumentArray arr = LLVMFunctionArgumentArray();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("LLVMFunctionArgumentArray::fromJSON");
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
          throw Exception("LLVMFunctionArgumentArray::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(LLVMFunctionArgument::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
}
LLVMFunctionArgumentArray::~LLVMFunctionArgumentArray() {
}
//----------------------------------

//------------- LLVMFunctionType ---------------
const int LLVMFunctionType::_TypeVoid = 0;
const int LLVMFunctionType::_TypeObj = 1;
void LLVMFunctionType::init(int type, void* ptr) {
  if (type==_TypeVoid) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeObj) {
    _type = type;
    _ptr = new RegisterKind(*(RegisterKind*) ptr);
  }
}
void LLVMFunctionType::clean() {
  if (_type==_TypeVoid) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("LLVMFunctionType::clean()");
  } else if (_type==_TypeObj) {
    _type = -1;
    delete (RegisterKind*) _ptr;
    _ptr = 0;
  }
}
LLVMFunctionType::LLVMFunctionType() : _type(-1), _ptr(0) {
}
LLVMFunctionType::LLVMFunctionType(const LLVMFunctionType& _value) {
  init(_value._type, _value._ptr);
}
LLVMFunctionType& LLVMFunctionType::operator=(const LLVMFunctionType& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool LLVMFunctionType::isVoid() const {
  return _type==_TypeVoid;
}
bool LLVMFunctionType::isObj() const {
  return _type==_TypeObj;
}
const RegisterKind& LLVMFunctionType::asObj() const {
  if (_type!=_TypeObj)
    throw Exception("LLVMFunctionType::asObj");
  return *(RegisterKind*) _ptr;
}
RegisterKind& LLVMFunctionType::asObj() {
  if (_type!=_TypeObj)
    throw Exception("LLVMFunctionType::asObj");
  return *(RegisterKind*) _ptr;
}

AnsiString LLVMFunctionType::toJSON() const {
  StringBuffer _json;
   _json += "{\"type\":" + AnsiString(_type) + ",\"value\":";
    if (_type==0)
      _json += "0";
    else if (_type==1)
    _json += ((RegisterKind*) _ptr)->toJSON();
    else
      throw Exception("LLVMFunctionType::toJSON(" + AnsiString(_type) + ")");
    _json += "}";
    return _json.get();
}
LLVMFunctionType LLVMFunctionType::fromJSON(AnsiString s) {
  int ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length()) 
    throw Exception("LLVMFunctionType::fromJSON");
  if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("0")) {
    return LLVMFunctionType::createVoid();
  } else if (s.Length()>ix+1+1 && s.SubString(ix+1, 1)==("1")) {
    if (s.Length()-ix-10-1<=0)
      throw Exception("LLVMFunctionType::fromJSON");
    s = s.SubString(ix+10+1, s.Length()-ix-10-1);
    return LLVMFunctionType::createObj(RegisterKind::fromJSON(s));
  }
  AnsiString variantName = "";
  ix = 1;
  while (ix<=s.Length() && s[ix]!=':')
    ix++;
  if (ix>s.Length() || ix<=4) 
    throw Exception("LLVMFunctionType::fromJSON");
  variantName = s.SubString(3, ix-4);
  if (variantName==("void")) {
    return LLVMFunctionType::createVoid();
  } else if (variantName==("obj")) {
    if (s.Length()-ix-1<=0)
      throw Exception("LLVMFunctionType::fromJSON");
    s = s.SubString(ix+1, s.Length()-ix-1);
    return LLVMFunctionType::createObj(RegisterKind::fromJSON(s));
  } else 
    throw Exception("LLVMFunctionType::fromJSON");
}

LLVMFunctionType::~LLVMFunctionType() {
  clean();
}
LLVMFunctionType LLVMFunctionType::createVoid() {
  LLVMFunctionType _value;
  _value._type = _TypeVoid;
  _value._ptr = 0;
  return _value;
}
LLVMFunctionType LLVMFunctionType::createObj(const RegisterKind& _param) {
  LLVMFunctionType _value;
  _value._type = _TypeObj;
  _value._ptr = new RegisterKind(_param);
  return _value;
}


//----------------------------------

//------------- LLVMFunction ---------------
LLVMFunction::LLVMFunction(const AnsiString& _name, const LLVMFunctionType& _type, const LLVMFunctionArgumentArray& _args, const LLVMBlockArray& _blocks) : name(_name), type(_type), args(_args), blocks(_blocks) {
}
const AnsiString& LLVMFunction::getName() const {
  return name;
}
AnsiString& LLVMFunction::getName() {
  return name;
}
const LLVMFunctionType& LLVMFunction::getType() const {
  return type;
}
LLVMFunctionType& LLVMFunction::getType() {
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
AnsiString LLVMFunction::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"name\":";
    _json += "\"" + JSONEscape::encode(name) + "\"";
    _json += ",";
    _json += "\"type\":";
    _json += type.toJSON();
    _json += ",";
    _json += "\"args\":";
    _json += args.toJSON();
    _json += ",";
    _json += "\"blocks\":";
    _json += blocks.toJSON();
  _json += "}";
  return _json.get();
}
LLVMFunction LLVMFunction::fromJSON(AnsiString s) {
  AnsiString arr[4];
  int ix=1;
  for (int i=0;i<4;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("LLVMFunction::fromJSON");
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
        if (i<4) {
          if (ix-start-1<=0)
            throw Exception("LLVMFunction::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return LLVMFunction((arr[0].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[0].SubString(2, arr[0].Length()-2))), LLVMFunctionType::fromJSON(arr[1]), LLVMFunctionArgumentArray::fromJSON(arr[2]), LLVMBlockArray::fromJSON(arr[3]));
}
LLVMFunction::~LLVMFunction() {
}
//----------------------------------

//------------- LLVMProgram ---------------
LLVMProgram::LLVMProgram() {
}
AnsiString LLVMProgram::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
LLVMProgram LLVMProgram::fromJSON(AnsiString s) {
  LLVMProgram arr = LLVMProgram();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("LLVMProgram::fromJSON");
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
          throw Exception("LLVMProgram::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(LLVMFunction::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
}
LLVMProgram::~LLVMProgram() {
}
//----------------------------------

