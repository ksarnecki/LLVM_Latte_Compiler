
#include "TypeCheckerStore.h"
#include "Exception.h"
#include "StringBuffer.h"
#include "JSONUtil.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Type ---------------
//----------------------------------

//------------- TypeCheckerStoreElement ---------------
TypeCheckerStoreElement::TypeCheckerStoreElement(const int& _id, const Type& _type) : id(_id), type(_type) {
}
const int& TypeCheckerStoreElement::getId() const {
  return id;
}
int& TypeCheckerStoreElement::getId() {
  return id;
}
const Type& TypeCheckerStoreElement::getType() const {
  return type;
}
Type& TypeCheckerStoreElement::getType() {
  return type;
}
AnsiString TypeCheckerStoreElement::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"id\":";
    _json += AnsiString(id);
    _json += ",";
    _json += "\"type\":";
    _json += type.toJSON();
  _json += "}";
  return _json.get();
}
TypeCheckerStoreElement TypeCheckerStoreElement::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("TypeCheckerStoreElement::fromJSON");
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
            throw Exception("TypeCheckerStoreElement::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return TypeCheckerStoreElement(atoi(arr[0].c_str()), Type::fromJSON(arr[1]));
}
TypeCheckerStoreElement::~TypeCheckerStoreElement() {
}
//----------------------------------

//------------- TypeCheckerStore ---------------
TypeCheckerStore::TypeCheckerStore() {
}
AnsiString TypeCheckerStore::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
TypeCheckerStore TypeCheckerStore::fromJSON(AnsiString s) {
  TypeCheckerStore arr = TypeCheckerStore();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("TypeCheckerStore::fromJSON");
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
          throw Exception("TypeCheckerStore::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(TypeCheckerStoreElement::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
}
TypeCheckerStore::~TypeCheckerStore() {
}
//----------------------------------

