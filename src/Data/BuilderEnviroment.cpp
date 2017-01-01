
#include "BuilderEnviroment.h"
#include "Exception.h"
#include "StringBuffer.h"
#include "JSONUtil.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- BuilderEnviromentElement ---------------
BuilderEnviromentElement::BuilderEnviromentElement(const AnsiString& _ident, const int& _storeId) : ident(_ident), storeId(_storeId) {
}
const AnsiString& BuilderEnviromentElement::getIdent() const {
  return ident;
}
AnsiString& BuilderEnviromentElement::getIdent() {
  return ident;
}
const int& BuilderEnviromentElement::getStoreId() const {
  return storeId;
}
int& BuilderEnviromentElement::getStoreId() {
  return storeId;
}
AnsiString BuilderEnviromentElement::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"ident\":";
    _json += "\"" + JSONEscape::encode(ident) + "\"";
    _json += ",";
    _json += "\"storeId\":";
    _json += AnsiString(storeId);
  _json += "}";
  return _json.get();
}
BuilderEnviromentElement BuilderEnviromentElement::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("BuilderEnviromentElement::fromJSON");
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
            throw Exception("BuilderEnviromentElement::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return BuilderEnviromentElement((arr[0].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[0].SubString(2, arr[0].Length()-2))), atoi(arr[1].c_str()));
}
BuilderEnviromentElement::~BuilderEnviromentElement() {
}
//----------------------------------

//------------- BuilderEnviroment ---------------
BuilderEnviroment::BuilderEnviroment() {
}
AnsiString BuilderEnviroment::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
BuilderEnviroment BuilderEnviroment::fromJSON(AnsiString s) {
  BuilderEnviroment arr = BuilderEnviroment();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("BuilderEnviroment::fromJSON");
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
          throw Exception("BuilderEnviroment::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(BuilderEnviromentElement::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
}
BuilderEnviroment::~BuilderEnviroment() {
}
//----------------------------------

