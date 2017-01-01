
#include "TypeCheckerEnviroment.h"
#include "Exception.h"
#include "StringBuffer.h"
#include "JSONUtil.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- TypeCheckerEnviromentElement ---------------
TypeCheckerEnviromentElement::TypeCheckerEnviromentElement(const AnsiString& _ident, const int& _storeId, const int& _nesting) : ident(_ident), storeId(_storeId), nesting(_nesting) {
}
const AnsiString& TypeCheckerEnviromentElement::getIdent() const {
  return ident;
}
AnsiString& TypeCheckerEnviromentElement::getIdent() {
  return ident;
}
const int& TypeCheckerEnviromentElement::getStoreId() const {
  return storeId;
}
int& TypeCheckerEnviromentElement::getStoreId() {
  return storeId;
}
const int& TypeCheckerEnviromentElement::getNesting() const {
  return nesting;
}
int& TypeCheckerEnviromentElement::getNesting() {
  return nesting;
}
AnsiString TypeCheckerEnviromentElement::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"ident\":";
    _json += "\"" + JSONEscape::encode(ident) + "\"";
    _json += ",";
    _json += "\"storeId\":";
    _json += AnsiString(storeId);
    _json += ",";
    _json += "\"nesting\":";
    _json += AnsiString(nesting);
  _json += "}";
  return _json.get();
}
TypeCheckerEnviromentElement TypeCheckerEnviromentElement::fromJSON(AnsiString s) {
  AnsiString arr[3];
  int ix=1;
  for (int i=0;i<3;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("TypeCheckerEnviromentElement::fromJSON");
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
            throw Exception("TypeCheckerEnviromentElement::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return TypeCheckerEnviromentElement((arr[0].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[0].SubString(2, arr[0].Length()-2))), atoi(arr[1].c_str()), atoi(arr[2].c_str()));
}
TypeCheckerEnviromentElement::~TypeCheckerEnviromentElement() {
}
//----------------------------------

//------------- TypeCheckerEnviroment ---------------
TypeCheckerEnviroment::TypeCheckerEnviroment() {
}
AnsiString TypeCheckerEnviroment::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
TypeCheckerEnviroment TypeCheckerEnviroment::fromJSON(AnsiString s) {
  TypeCheckerEnviroment arr = TypeCheckerEnviroment();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("TypeCheckerEnviroment::fromJSON");
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
          throw Exception("TypeCheckerEnviroment::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(TypeCheckerEnviromentElement::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
}
TypeCheckerEnviroment::~TypeCheckerEnviroment() {
}
//----------------------------------

