
#include "BuilderEnviroment.h"
#include "Exception.h"
#include "StringBuffer.h"
#include "JSONUtil.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- RegisterKind ---------------
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

//------------- BuilderEnviromentElementArray ---------------
BuilderEnviromentElementArray::BuilderEnviromentElementArray() {
}
AnsiString BuilderEnviromentElementArray::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
BuilderEnviromentElementArray BuilderEnviromentElementArray::fromJSON(AnsiString s) {
  BuilderEnviromentElementArray arr = BuilderEnviromentElementArray();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("BuilderEnviromentElementArray::fromJSON");
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
          throw Exception("BuilderEnviromentElementArray::fromJSON");
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
BuilderEnviromentElementArray::~BuilderEnviromentElementArray() {
}
//----------------------------------

//------------- BuilderEnviromentStructElem ---------------
BuilderEnviromentStructElem::BuilderEnviromentStructElem(const AnsiString& _name, const RegisterKind& _kind) : name(_name), kind(_kind) {
}
const AnsiString& BuilderEnviromentStructElem::getName() const {
  return name;
}
AnsiString& BuilderEnviromentStructElem::getName() {
  return name;
}
const RegisterKind& BuilderEnviromentStructElem::getKind() const {
  return kind;
}
RegisterKind& BuilderEnviromentStructElem::getKind() {
  return kind;
}
AnsiString BuilderEnviromentStructElem::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"name\":";
    _json += "\"" + JSONEscape::encode(name) + "\"";
    _json += ",";
    _json += "\"kind\":";
    _json += kind.toJSON();
  _json += "}";
  return _json.get();
}
BuilderEnviromentStructElem BuilderEnviromentStructElem::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("BuilderEnviromentStructElem::fromJSON");
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
            throw Exception("BuilderEnviromentStructElem::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return BuilderEnviromentStructElem((arr[0].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[0].SubString(2, arr[0].Length()-2))), RegisterKind::fromJSON(arr[1]));
}
BuilderEnviromentStructElem::~BuilderEnviromentStructElem() {
}
//----------------------------------

//------------- BuilderEnviromentStructElemArray ---------------
BuilderEnviromentStructElemArray::BuilderEnviromentStructElemArray() {
}
AnsiString BuilderEnviromentStructElemArray::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
BuilderEnviromentStructElemArray BuilderEnviromentStructElemArray::fromJSON(AnsiString s) {
  BuilderEnviromentStructElemArray arr = BuilderEnviromentStructElemArray();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("BuilderEnviromentStructElemArray::fromJSON");
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
          throw Exception("BuilderEnviromentStructElemArray::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(BuilderEnviromentStructElem::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
}
BuilderEnviromentStructElemArray::~BuilderEnviromentStructElemArray() {
}
//----------------------------------

//------------- BuilderEnviromentStruct ---------------
BuilderEnviromentStruct::BuilderEnviromentStruct(const AnsiString& _name, const BuilderEnviromentStructElemArray& _elems) : name(_name), elems(_elems) {
}
const AnsiString& BuilderEnviromentStruct::getName() const {
  return name;
}
AnsiString& BuilderEnviromentStruct::getName() {
  return name;
}
const BuilderEnviromentStructElemArray& BuilderEnviromentStruct::getElems() const {
  return elems;
}
BuilderEnviromentStructElemArray& BuilderEnviromentStruct::getElems() {
  return elems;
}
AnsiString BuilderEnviromentStruct::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"name\":";
    _json += "\"" + JSONEscape::encode(name) + "\"";
    _json += ",";
    _json += "\"elems\":";
    _json += elems.toJSON();
  _json += "}";
  return _json.get();
}
BuilderEnviromentStruct BuilderEnviromentStruct::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("BuilderEnviromentStruct::fromJSON");
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
            throw Exception("BuilderEnviromentStruct::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return BuilderEnviromentStruct((arr[0].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[0].SubString(2, arr[0].Length()-2))), BuilderEnviromentStructElemArray::fromJSON(arr[1]));
}
BuilderEnviromentStruct::~BuilderEnviromentStruct() {
}
//----------------------------------

//------------- BuilderEnviromentStructArray ---------------
BuilderEnviromentStructArray::BuilderEnviromentStructArray() {
}
AnsiString BuilderEnviromentStructArray::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
BuilderEnviromentStructArray BuilderEnviromentStructArray::fromJSON(AnsiString s) {
  BuilderEnviromentStructArray arr = BuilderEnviromentStructArray();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("BuilderEnviromentStructArray::fromJSON");
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
          throw Exception("BuilderEnviromentStructArray::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(BuilderEnviromentStruct::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
}
BuilderEnviromentStructArray::~BuilderEnviromentStructArray() {
}
//----------------------------------

//------------- BuilderEnviroment ---------------
BuilderEnviroment::BuilderEnviroment(const BuilderEnviromentElementArray& _idents, const BuilderEnviromentStructArray& _structs) : idents(_idents), structs(_structs) {
}
const BuilderEnviromentElementArray& BuilderEnviroment::getIdents() const {
  return idents;
}
BuilderEnviromentElementArray& BuilderEnviroment::getIdents() {
  return idents;
}
const BuilderEnviromentStructArray& BuilderEnviroment::getStructs() const {
  return structs;
}
BuilderEnviromentStructArray& BuilderEnviroment::getStructs() {
  return structs;
}
AnsiString BuilderEnviroment::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"idents\":";
    _json += idents.toJSON();
    _json += ",";
    _json += "\"structs\":";
    _json += structs.toJSON();
  _json += "}";
  return _json.get();
}
BuilderEnviroment BuilderEnviroment::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("BuilderEnviroment::fromJSON");
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
            throw Exception("BuilderEnviroment::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return BuilderEnviroment(BuilderEnviromentElementArray::fromJSON(arr[0]), BuilderEnviromentStructArray::fromJSON(arr[1]));
}
BuilderEnviroment::~BuilderEnviroment() {
}
//----------------------------------

