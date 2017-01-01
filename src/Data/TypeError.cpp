
#include "TypeError.h"
#include "Exception.h"
#include "StringBuffer.h"
#include "JSONUtil.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- TypeError ---------------
TypeError::TypeError(const int& _line, const AnsiString& _msg) : line(_line), msg(_msg) {
}
const int& TypeError::getLine() const {
  return line;
}
int& TypeError::getLine() {
  return line;
}
const AnsiString& TypeError::getMsg() const {
  return msg;
}
AnsiString& TypeError::getMsg() {
  return msg;
}
AnsiString TypeError::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"line\":";
    _json += AnsiString(line);
    _json += ",";
    _json += "\"msg\":";
    _json += "\"" + JSONEscape::encode(msg) + "\"";
  _json += "}";
  return _json.get();
}
TypeError TypeError::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("TypeError::fromJSON");
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
            throw Exception("TypeError::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return TypeError(atoi(arr[0].c_str()), (arr[1].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[1].SubString(2, arr[1].Length()-2))));
}
TypeError::~TypeError() {
}
//----------------------------------

//------------- TypeErrors ---------------
TypeErrors::TypeErrors() {
}
AnsiString TypeErrors::toJSON() const {
  StringBuffer _json;
  _json += "[";
  for (int _i=0;_i<Size();_i++) {
    if (_i!=0) _json += ",";
    _json += (*this)[_i].toJSON();
  }
    _json += "]";
    return _json.get();
}
TypeErrors TypeErrors::fromJSON(AnsiString s) {
  TypeErrors arr = TypeErrors();
  int ix=1;
  while(ix <= s.Length() && s[ix]!='[')
    ix++;
  ix++;
  if (ix>s.Length()) 
    throw Exception("TypeErrors::fromJSON");
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
          throw Exception("TypeErrors::fromJSON");
        AnsiString tmp = s.SubString(start, ix-start);
        arr.Insert(TypeError::fromJSON(tmp));
        ix++;
        break;
      }
      ix++;
    }
  }
  return arr;
}
TypeErrors::~TypeErrors() {
}
//----------------------------------

